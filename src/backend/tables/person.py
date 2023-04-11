from __future__ import annotations

from sqlalchemy.orm import Mapped, mapped_column
from sqlalchemy.types import DateTime, Integer, String

from src.backend.tables.base import Base
from ..json_generator import  auto_apply_jsonify_content
from ..utils import set_conversion, convert_str_date_to_datetime


@auto_apply_jsonify_content
@set_conversion(birthday=convert_str_date_to_datetime, age=int)
class Person(Base):
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
