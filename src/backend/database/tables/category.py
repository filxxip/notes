from __future__ import annotations
from sqlalchemy import ForeignKey
from sqlalchemy.orm import Mapped, mapped_column
from sqlalchemy.types import DateTime, Integer, String
from ..constants.attribute_dep_names import peopleId
from .base import Base
from ..constants import tables_names, attribute_dep_names
from ..json_generator import auto_apply_jsonify_content
from ..utils import set_conversion, convert_str_date_to_datetime
from .notes import Note
from ..property_utils import register_dependency


@auto_apply_jsonify_content
@register_dependency(Note, attribute_dep_names.categoryName)
@set_conversion(creationDate=convert_str_date_to_datetime)
class Category(Base):
    __tablename__ = tables_names.categoryName
    id: Mapped[int] = mapped_column(
        Integer(), primary_key=True, nullable=False, autoincrement=True)
    name: Mapped[str] = mapped_column(String(50))
    color: Mapped[str] = mapped_column(String(50))
    creationDate: Mapped[str] = mapped_column(DateTime())
    owner: Mapped[int] = mapped_column(Integer(), ForeignKey(peopleId))
