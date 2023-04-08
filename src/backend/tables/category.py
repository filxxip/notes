from __future__ import annotations
from dataclasses import dataclass
from sqlalchemy.orm import Mapped, mapped_column
from sqlalchemy.types import DateTime, Integer, String
from ..json_generator import JsonGeneratorObject
from ..tables.base import Base
from ..utils import set_conversion, convert_str_date_to_datetime


@set_conversion(creationDate=convert_str_date_to_datetime)
@dataclass
class Category(Base, JsonGeneratorObject):
    __tablename__ = "Categories"
    id: Mapped[int] = mapped_column(
        Integer(), primary_key=True, nullable=False, autoincrement=True)
    name: Mapped[str] = mapped_column(String(50))
    color: Mapped[str] = mapped_column(String(50))
    creationDate: Mapped[str] = mapped_column(DateTime())
