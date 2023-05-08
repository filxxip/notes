from __future__ import annotations
from sqlalchemy import Text
from sqlalchemy.orm import Mapped, mapped_column

from .base import Base


class Schemas(Base):
    __tablename__ = "Schamas"
    name: Mapped[str] = mapped_column(primary_key=True)
    schema: Mapped[str] = mapped_column(Text())
