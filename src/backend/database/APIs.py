from __future__ import annotations
from src.backend.database.tables.schema import Schemas
import json
from dataclasses import dataclass
from typing import Type, Protocol
import jsonschema
from flask import request
from flask.views import MethodView
from jsonschema.exceptions import ValidationError, SchemaError

from .main_config_database_vars import db_session
from .utils import _T, catchable_db_connection_exceptions, jsonify_result, get_relevant_sorted_query


@dataclass
class ProtocolDatabaseClass(Protocol):
    id: int

    def to_json(self) -> dict:
        ...

    @classmethod
    def from_json(cls: Type[_T], json_obj: str) -> _T:
        ...

    def update_from_json(self, json_obj: str) -> ProtocolDatabaseClass:
        ...


@dataclass
class MethodViewWithClassName(MethodView):
    className: Type[ProtocolDatabaseClass]


class ItemAPI(MethodViewWithClassName):
    def _validate_index(self, index: int) -> bool:
        return 0 < index <= db_session.query(self.className).count()

    def _get_on_id(self, index: int) -> ProtocolDatabaseClass:
        if not self._validate_index(index):
            raise IndexError("Such index is out of range: " + str(index))
        return db_session.query(self.className).filter(index == self.className.id).first()

    @catchable_db_connection_exceptions(IndexError)
    @jsonify_result
    def get(self, index: int):
        return self._get_on_id(index).to_json()

    @catchable_db_connection_exceptions(ValidationError, SchemaError, IndexError)
    @jsonify_result
    def patch(self, index: int):
        item = self._get_on_id(index)
        jsonschema.validate(request.form.to_dict(), json.loads(
            db_session.query(Schemas).where(Schemas.name == self.className.__name__).first().schema))
        item = item.update_from_json(json.dumps(request.form.to_dict()))
        db_session.commit()
        return item.to_json()

    @catchable_db_connection_exceptions(IndexError)
    def delete(self, index: int):
        db_session.delete(self._get_on_id(index))
        db_session.commit()
        return "Object removed from database"


class GroupAPI(MethodViewWithClassName):
    @catchable_db_connection_exceptions(ValidationError, SchemaError)
    @jsonify_result
    def get(self):
        return [item.to_json() for item in get_relevant_sorted_query(self.className).all()]

    @catchable_db_connection_exceptions(ValidationError, SchemaError)
    def post(self):
        jsonschema.validate(request.form.to_dict(), json.loads(
            db_session.query(Schemas).where(Schemas.name == self.className.__name__).first().schema))
        db_session.add(self.className.from_json(json.dumps(request.form.to_dict())))
        db_session.commit()
        return "Adding new object to database"


class GroupSortedAPI(MethodViewWithClassName):
    @catchable_db_connection_exceptions(ValidationError, SchemaError, AttributeError)
    @jsonify_result
    def get(self, sorted_name: str):
        return [item.to_json() for item in get_relevant_sorted_query(self.className, sorted_name).all()]
