from __future__ import annotations

from sqlalchemy.orm import Mapped, mapped_column
from sqlalchemy.types import Integer

from src.backend.database.tables.base import Base
from ..constants import tables_names
from ..json_generator import auto_apply_jsonify_content

@auto_apply_jsonify_content
class IdTable:
    id: Mapped[int] = mapped_column(
        Integer(), primary_key=True, nullable=False, autoincrement=True)
    index: Mapped[int] = mapped_column(Integer())


class PersonRemoveAccount(IdTable, Base):
    __tablename__ = tables_names.peopleRemoveAccountName


class PersonRegister(IdTable, Base):
    __tablename__ = tables_names.peopleRegisterName


class PersonLogin(IdTable, Base):
    __tablename__ = tables_names.peopleLoginName


class PersonLogout(IdTable, Base):
    __tablename__ = tables_names.peopleLogoutName


