from __future__ import annotations
import json
from typing_extensions import Type, TypeVar, Any

from src.backend.tables import Base

# class JsonGeneratorObject:
#     __serialize_attrs__ : dict[Type, list[str]]
#
#     def to_json(self) -> dict:
#         # return {key : self.__dict__[key] for key in JsonGeneratorObject.__serialize_attrs__}
#         return {pair: str(self.__dict__[
#             pair]) for pair in self.__dict__ if pair[0][0] != ""}
#         # return {"x":self.__class__.__name__}
#
#     @classmethod
#     def from_json(cls: Type[_T], json_obj: str) -> _T:
#         return cls(**json.loads(json_obj))
#
#     def update_from_json(self, json_obj: str) -> JsonGeneratorObject:
#         items = json.loads(json_obj)
#         for key in items:
#             if key in self.__dict__:
#                 self.__setattr__(key, items[key])
#             else:
#                 raise AttributeError("Unsupported type: " + key)
#         return self
#
#
# class JsonGenerator:
#     def __init__(self, cls : Type, keys : list[str]):
#         JsonGeneratorObject.__serialize_attrs__[cls] = keys
#     def __call__(self, *args, **kwargs):


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
            raise AttributeError("Unsupported type: " + key)
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
