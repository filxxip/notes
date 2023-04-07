from __future__ import annotations
print("in json")
import json
from typing_extensions import Type, TypeVar, Any

_T = TypeVar("_T", bound=Any)


class JsonGeneratorObject:
    def to_json(self) -> dict:
        return {pair: self.__dict__[
            pair] for pair in self.__dict__ if pair[0][0] != "_"}

    @classmethod
    def from_json(cls: Type[_T], json_obj: str) -> _T:
        return cls(**json.loads(json_obj))

    def update_from_json(self, json_obj: str) -> JsonGeneratorObject:
        items = json.loads(json_obj)
        for key in items:
            if key in self.__dict__:
                self.__setattr__(key, items[key])
            else:
                raise AttributeError("Unsupported type: " + key)
        return self
