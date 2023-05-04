from __future__ import annotations
from dataclasses import dataclass
from sqlalchemy import Text
from sqlalchemy.orm import Mapped, mapped_column

from src.backend.database.tables.base import Base


class Schemas(Base):
    __tablename__ = "Schamas"
    name: Mapped[str] = mapped_column(primary_key=True)
    schema: Mapped[str] = mapped_column(Text())