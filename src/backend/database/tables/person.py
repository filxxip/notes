from __future__ import annotations

import dataclasses
from datetime import date

from sqlalchemy.orm import Mapped, mapped_column
from sqlalchemy.types import DateTime, Integer, String
from sqlalchemy.ext.hybrid import hybrid_property
from src.backend.database.tables.base import Base
from ..json_generator import auto_apply_jsonify_content
from ..utils import set_conversion, convert_str_date_to_datetime


@auto_apply_jsonify_content
@set_conversion(birthday=convert_str_date_to_datetime)
class Person(Base):
    __tablename__ = "People"
    id: Mapped[int] = mapped_column(
        Integer(), primary_key=True, nullable=False, autoincrement=True)
    name: Mapped[str] = mapped_column(String(50))
    surname: Mapped[str] = mapped_column(String(50))
    email: Mapped[str] = mapped_column(String(50))
    password: Mapped[str] = mapped_column(String(50))
    country: Mapped[str] = mapped_column(String(50))
    birthday: Mapped[str] = mapped_column(DateTime())

    @hybrid_property
    def age(self):
        today = date.today()
        years_diff = today.year - self.birthday.year
        if today.month < self.birthday.month or (today.month == self.birthday.month and today.day < self.birthday.day):
            years_diff -= 1
        return years_diff


Person(name = "aa", surname = "aa", email = "aa", password ="aa", country = "aa", birthday= "2000-1-1")
