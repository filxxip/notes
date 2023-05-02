from __future__ import annotations
import json
from typing_extensions import Type, TypeVar, Any

from src.backend.database.tables import Base

from .constants import information_texts

_T = TypeVar("_T", bound=Any)


def _to_json(self) -> dict:
    return {attr: getattr(self, attr) for attr in self.__json_attributes__}


def _from_json(cls: Type[_T], json_obj: str) -> _T:
    return cls(**json.loads(json_obj))


def _update_from_json(self, json_obj: str):
    custom_dict = self.__dict__["_sa_instance_state"].dict
    items = json.loads(json_obj)
    for key in items:
        if key in custom_dict and key in self.__json_attributes__:
            self.__setattr__(key, items[key])
        else:
            raise AttributeError(information_texts.unsupportedType + key)
    return self


def _set_relevant_json_function(cls, attrs: list[str]):
    cls.__json_attributes__ = attrs
    cls.to_json = _to_json
    cls.update_from_json = _update_from_json
    cls.from_json = classmethod(_from_json)
    return cls


def apply_jsonify_content(*attrs: str):
    def wrapper(cls):
        _set_relevant_json_function(cls, list(attrs))

    return wrapper


def auto_apply_jsonify_content(cls):
    return _set_relevant_json_function(cls, [a for a in cls.__dict__ if a not in Base.__dict__ and a[0] != "_"])
