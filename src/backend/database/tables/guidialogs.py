from __future__ import annotations
from sqlalchemy import Text
from sqlalchemy.orm import Mapped, mapped_column
from sqlalchemy.types import DateTime, Integer, String, Boolean

from src.backend.database.tables.base import Base
from ..constants import tables_names
from ..json_generator import auto_apply_jsonify_content
from ..utils import set_conversion, convert_str_date_to_datetime, convert_str_to_bool


@auto_apply_jsonify_content
@set_conversion(releaseDate=convert_str_date_to_datetime, isOk=convert_str_to_bool, isAbort=convert_str_to_bool,
                isYes=convert_str_to_bool, isNo=convert_str_to_bool)
class GuiDialog(Base):
    __tablename__ = tables_names.guiDialogsName
    id: Mapped[int] = mapped_column(
        Integer(), primary_key=True, nullable=False, autoincrement=True)
    isOk: Mapped[bool] = mapped_column(Boolean())
    isAbort: Mapped[bool] = mapped_column(Boolean())
    isYes: Mapped[bool] = mapped_column(Boolean())
    isNo: Mapped[bool] = mapped_column(Boolean())
    title: Mapped[str] = mapped_column(String(50))
    content: Mapped[str] = mapped_column(Text())
