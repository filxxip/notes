from __future__ import annotations

from tables import Base, Person, Note, Category, Schemas
import json
import table_schemas
from APIs import ItemAPI, GroupAPI, GroupSortedAPI
from main_config_database_vars import app, engine, db_session
from utils import save_session


class APIController:
    def __init__(self):
        Base.metadata.create_all(bind=engine)

    def add_rules(self):
        app.add_url_rule('/people/<int:index>', view_func=ItemAPI.as_view('myview_with_id', Person))
        app.add_url_rule('/categories/<int:index>', view_func=ItemAPI.as_view('category_with_id', Category))
        app.add_url_rule('/notes/<int:index>', view_func=ItemAPI.as_view('notes_with_id', Note))
        app.add_url_rule('/people', view_func=GroupAPI.as_view('each_person', Person))
        app.add_url_rule('/categories', view_func=GroupAPI.as_view('each_category', Category))
        app.add_url_rule('/notes', view_func=GroupAPI.as_view('each_note', Note))
        app.add_url_rule('/people/<sorted_name>', view_func=GroupSortedAPI.as_view('each_person_sorted', Person))
        app.add_url_rule('/categories/<sorted_name>',
                         view_func=GroupSortedAPI.as_view('each_category_sorted', Category))
        app.add_url_rule('/notes/<sorted_name>', view_func=GroupSortedAPI.as_view('each_note_sorted', Note))

    def reclear_tables(self, tables_to_clear=None):
        Base.metadata.drop_all(bind=engine, tables=tables_to_clear)
        Base.metadata.create_all(bind=engine, tables=tables_to_clear)

    @save_session
    def init_schemas(self):
        self.reclear_tables([Schemas])
        for T, schema in zip((Person, Note, Category),
                             (table_schemas.people_schema, table_schemas.notes_schema, table_schemas.category_schema)):
            db_session.add(Schemas(name=T.__name__, schema=json.dumps(schema)))
