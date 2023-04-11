from __future__ import annotations
from src.backend.tables.schema import Schemas
import datetime
import json
from functools import wraps
from typing import Any, Callable, Type, TypeVar
import jsonschema
from flask import request, jsonify
from flask_sqlalchemy.query import Query
from sqlalchemy.orm.attributes import InstrumentedAttribute

from main_config_database_vars import db_session, app

_T = TypeVar("_T", bound=Any)


# def save_session(function: callable):
#     @wraps(function)
#     def wrapper(*args, **kwargs):
#         # with app.app_context():
#             result = function(*args, **kwargs)
#             db_session.commit()
#             return result
#
#     return wrapper


def set_conversion(**attrs: Callable):
    def wrapper(cls: Type[_T]):
        def _custom_setattr(self, key, value):
            super(cls, self).__setattr__(key, attrs[key](value) if key in attrs else value)

        cls.__setattr__ = _custom_setattr
        return cls

    return wrapper


def jsonify_result(function: callable):
    @wraps(function)
    def wrapper(*args, **kwargs):
        return jsonify(function(*args, **kwargs))

    return wrapper


def set_jsonify_attributes(*args: str):
    """To apply on JsonGeneratorObject instance"""
    def wrapper(cls):
        cls.__serialize_attrs__ = args

    return wrapper


def catchable_db_connection_exceptions(*exs: Type[Exception]):
    def wrapper(func: Callable):
        def inner_wrapper(*args, **kwargs):
            try:
                return func(*args, **kwargs)
            except exs as ex:
                return "Invalid access to database, error occurred : " + str(ex), 404

        return inner_wrapper

    return wrapper


def convert_str_date_to_datetime(d):
    return datetime.date(*[int(m) for m in d.split("-")]) if isinstance(d, str) else d


def get_relevant_sorted_query(cls_name: Type[_T], sorted_name: str = None) -> Query:
    jsonschema.validate(request.args.to_dict(), json.loads(
        db_session.query(Schemas).where(Schemas.name == cls_name.__name__).first().schema))
    filter_dict = request.args.to_dict()
    base = db_session.query(cls_name)
    if base.count() > 0:
        for key in filter_dict:
            if all(getattr(obj, key, None) for obj in base.all()):
                base = base.where(cls_name.__dict__[key] == filter_dict.get(key))
            else:
                raise AttributeError("No such key in class dictionary : " + str(key))
    if sorted_name:
        if sorted_name in cls_name.__dict__ and isinstance(cls_name.__dict__[sorted_name], InstrumentedAttribute):
            base = base.order_by(sorted_name)
        else:
            raise AttributeError("Cannot sort by : " + sorted_name)
    return base
