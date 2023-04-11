from __future__ import annotations
from dataclasses import dataclass
from sqlalchemy.orm import Mapped, mapped_column
from sqlalchemy.types import DateTime, Integer, String

from ..json_generator import auto_apply_jsonify_content
from ..tables.base import Base
from ..utils import set_conversion, convert_str_date_to_datetime


@auto_apply_jsonify_content
@set_conversion(creationDate=convert_str_date_to_datetime)
class Category(Base):
    __tablename__ = "Categories"
    id: Mapped[int] = mapped_column(
        Integer(), primary_key=True, nullable=False, autoincrement=True)
    name: Mapped[str] = mapped_column(String(50))
    color: Mapped[str] = mapped_column(String(50))
    creationDate: Mapped[str] = mapped_column(DateTime())
