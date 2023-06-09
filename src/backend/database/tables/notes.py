from __future__ import annotations

from sqlalchemy import ForeignKey, Text
from sqlalchemy.orm import Mapped, mapped_column
from sqlalchemy.types import DateTime, Integer, String

from src.backend.database.tables.base import Base
from ..json_generator import auto_apply_jsonify_content
from ..utils import set_conversion, convert_str_date_to_datetime
from ..constants import tables_names, attribute_dep_names


@auto_apply_jsonify_content
@set_conversion(releaseDate=convert_str_date_to_datetime)
class Note(Base):
    __tablename__ = tables_names.notesName
    id: Mapped[int] = mapped_column(
        Integer(), primary_key=True, nullable=False, autoincrement=True)
    category: Mapped[int] = mapped_column(Integer(), ForeignKey(attribute_dep_names.categoriesId))
    owner: Mapped[int] = mapped_column(Integer(), ForeignKey(attribute_dep_names.peopleId))
    title: Mapped[str] = mapped_column(String(50))
    content: Mapped[str] = mapped_column(Text())
    releaseDate: Mapped[str] = mapped_column(DateTime())
