from __future__ import annotations
from src.backend.tables.base import Base
from dataclasses import dataclass
from sqlalchemy.orm import Mapped, mapped_column
from sqlalchemy.types import DateTime, Integer, String
from src.backend.json_generator import JsonGeneratorObject
from src.backend.utils import set_conversion, convert_str_date_to_datetime

@set_conversion(birthday=convert_str_date_to_datetime, age=int)
@dataclass
class Person(Base, JsonGeneratorObject):
    __tablename__ = "People"
    id: Mapped[int] = mapped_column(
        Integer(), primary_key=True, nullable=False, autoincrement=True)
    name: Mapped[str] = mapped_column(String(50))
    surname: Mapped[str] = mapped_column(String(50))
    age: Mapped[int] = mapped_column(Integer())
    email: Mapped[str] = mapped_column(String(50))
    password: Mapped[str] = mapped_column(String(50))
    country: Mapped[str] = mapped_column(String(50))
    birthday: Mapped[str] = mapped_column(DateTime())
