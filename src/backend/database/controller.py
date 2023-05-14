from __future__ import annotations

from .tables import Base, Note, Category, Schemas, GuiDialog, PersonTransfered, PersonNormal
import json
from . import table_schemas
from .APIs import ItemAPI, GroupAPI, GroupSortedAPI
from .main_config_database_vars import app, engine, db_session

from .constants import api_data

from .main_site_route import main_site


class APIController:
    def __init__(self):
        Base.metadata.create_all(bind=engine)

    def add_rules(self):
        app.add_url_rule(api_data.people_index, view_func=ItemAPI.as_view(api_data.people_index_name, PersonNormal))
        app.add_url_rule(api_data.categories_index, view_func=ItemAPI.as_view(api_data.categories_index_name, Category))
        app.add_url_rule(api_data.notes_index, view_func=ItemAPI.as_view(api_data.notes_index_name, Note))
        app.add_url_rule(api_data.guidialogs_index,
                         view_func=ItemAPI.as_view(api_data.guidialogs_index_name, GuiDialog))
        app.add_url_rule(api_data.people_transfered_index,
                         view_func=ItemAPI.as_view(api_data.people_transfered_index_name, PersonTransfered))

        app.add_url_rule(api_data.people, view_func=GroupAPI.as_view(api_data.people_name, PersonNormal))
        app.add_url_rule(api_data.categories, view_func=GroupAPI.as_view(api_data.categories_name, Category))
        app.add_url_rule(api_data.notes, view_func=GroupAPI.as_view(api_data.notes_name, Note))
        app.add_url_rule(api_data.guidialogs, view_func=GroupAPI.as_view(api_data.guidialogs_name, GuiDialog))
        app.add_url_rule(api_data.schema, view_func=GroupAPI.as_view(api_data.schemas_name, Schemas))
        app.add_url_rule(api_data.people_transfered,
                         view_func=GroupAPI.as_view(api_data.people_transfered_name, PersonTransfered))

        app.add_url_rule(api_data.people_sorted,
                         view_func=GroupSortedAPI.as_view(api_data.people_sorted_name, PersonNormal))
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
        for T, schema in zip((PersonTransfered, PersonNormal, Note, Category, GuiDialog, Schemas),
                             (table_schemas.people_schema, table_schemas.people_schema, table_schemas.notes_schema,
                              table_schemas.category_schema,
                              table_schemas.guidialog_schema, table_schemas.schema_schema)):
            db_session.add(Schemas(name=T.__name__, schema=json.dumps(schema)))
        db_session.commit()
