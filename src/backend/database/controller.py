from __future__ import annotations

from .utils import jsonify_result
from .tables import Base, Person, Note, Category, Schemas, GuiDialog
import json
from . import table_schemas
from .APIs import ItemAPI, GroupAPI, GroupSortedAPI
from .main_config_database_vars import app, engine, db_session

from .constants import api_data

@jsonify_result
@app.route(api_data.main_site)
def main_site():
    return api_data.main_site_information

class APIController:
    def __init__(self):
        Base.metadata.create_all(bind=engine)

    def add_rules(self):
        app.add_url_rule(api_data.people_index, view_func=ItemAPI.as_view(api_data.people_index_name, Person))
        app.add_url_rule(api_data.categories_index, view_func=ItemAPI.as_view(api_data.categories_index_name, Category))
        app.add_url_rule(api_data.notes_index, view_func=ItemAPI.as_view(api_data.notes_index_name, Note))
        app.add_url_rule(api_data.guidialogs_index,
                         view_func=ItemAPI.as_view(api_data.guidialogs_index_name, GuiDialog))
        app.add_url_rule(api_data.people, view_func=GroupAPI.as_view(api_data.people_name, Person))
        app.add_url_rule(api_data.categories, view_func=GroupAPI.as_view(api_data.categories_name, Category))
        app.add_url_rule(api_data.notes, view_func=GroupAPI.as_view(api_data.notes_name, Note))
        app.add_url_rule(api_data.guidialogs, view_func=GroupAPI.as_view(api_data.guidialogs_name, GuiDialog))
        app.add_url_rule(api_data.people_sorted, view_func=GroupSortedAPI.as_view(api_data.people_sorted_name, Person))
        app.add_url_rule(api_data.categories_sorted,
                         view_func=GroupSortedAPI.as_view(api_data.categories_sorted_name, Category))
        app.add_url_rule(api_data.notes_sorted, view_func=GroupSortedAPI.as_view(api_data.notes_sorted_name, Note))

    def reclear_tables(self, tables_to_clear=None):
        tabs = None
        if tables_to_clear is list:
            tabs = [table.__table__ for table in tables_to_clear]
        Base.metadata.drop_all(bind=engine, tables=tabs)
        Base.metadata.create_all(bind=engine, tables=tabs)

    def init_schemas(self):
        self.reclear_tables([Schemas])
        for T, schema in zip((Person, Note, Category, GuiDialog),
                             (table_schemas.people_schema, table_schemas.notes_schema, table_schemas.category_schema,
                              table_schemas.guidialog_schema)):
            db_session.add(Schemas(name=T.__name__, schema=json.dumps(schema)))
        db_session.commit()
