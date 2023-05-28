from __future__ import annotations

from datetime import date

from sqlalchemy.ext.hybrid import hybrid_property
from sqlalchemy.orm import Mapped, mapped_column
from sqlalchemy.types import DateTime, Integer, String

from src.backend.database.tables.base import Base
from . import Category, Note
from .. import property_utils
from ..constants import tables_names, attribute_dep_names
from ..json_generator import auto_apply_jsonify_content
from ..utils import set_conversion, convert_str_date_to_datetime


@auto_apply_jsonify_content
@property_utils.register_dependency(Category, attribute_dep_names.ownerName)
@property_utils.register_dependency(Note, attribute_dep_names.ownerName)
@set_conversion(birthday=convert_str_date_to_datetime, created=convert_str_date_to_datetime)
class Person(Base):
    __tablename__ = tables_names.peopleName
    id: Mapped[int] = mapped_column(
        Integer(), primary_key=True, nullable=False, autoincrement=True)
    name: Mapped[str] = mapped_column(String(50))
    surname: Mapped[str] = mapped_column(String(50))
    email: Mapped[str] = mapped_column(String(50))
    password: Mapped[str] = mapped_column(String(50))
    country: Mapped[str] = mapped_column(String(50))
    birthday: Mapped[str] = mapped_column(DateTime())
    gender: Mapped[str] = mapped_column(String(30))
    created: Mapped[str] = mapped_column(DateTime())

    @hybrid_property
    def age(self):
        today = date.today()
        years_diff = today.year - self.birthday.year
        if today.month < self.birthday.month or (today.month == self.birthday.month and today.day < self.birthday.day):
            years_diff -= 1
        return years_diff
