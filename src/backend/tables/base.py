from sqlalchemy.orm import DeclarativeBase

from src.backend.main_config_database_vars import db_session


class Base(DeclarativeBase):
    query = db_session.query_property()
