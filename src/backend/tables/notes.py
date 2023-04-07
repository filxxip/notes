from __future__ import annotations
from src.backend.tables.base import Base
from dataclasses import dataclass
from sqlalchemy import ForeignKey, Text
from sqlalchemy.orm import Mapped, mapped_column
from sqlalchemy.types import DateTime, Integer, String
from src.backend.json_generator import JsonGeneratorObject
from src.backend.utils import set_conversion, convert_str_date_to_datetime


@set_conversion(releaseDate=convert_str_date_to_datetime)
@dataclass
class Note(Base, JsonGeneratorObject):
    __tablename__ = "Notes"
    id: Mapped[int] = mapped_column(
        Integer(), primary_key=True, nullable=False, autoincrement=True)
    category: Mapped[int] = mapped_column(Integer(), ForeignKey("People.id"))
    owner: Mapped[int] = mapped_column(Integer(), ForeignKey("Categories.id"))
    title: Mapped[str] = mapped_column(String(50))
    content: Mapped[str] = mapped_column(Text())
    releaseDate: Mapped[str] = mapped_column(DateTime())
