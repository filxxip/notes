from __future__ import annotations

import json

from sqlalchemy import Text
from sqlalchemy.orm import Mapped, mapped_column

from ..json_generator import auto_apply_jsonify_content
from .base import Base



@auto_apply_jsonify_content
class Schemas(Base):
    __tablename__ = "Schamas"
    name: Mapped[str] = mapped_column(primary_key=True)
    schema: Mapped[str] = mapped_column(Text())#powinien byc dictionary w schema i baziedanych a nie string
