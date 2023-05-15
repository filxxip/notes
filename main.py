from __future__ import annotations
from src.backend.database.controller import APIController
from src.backend.database.main_config_database_vars import app
from src.backend.database.seeders import OverallSeeder, NotesSeeder, CategorySeeder, PersonSeeder, GuiDialogSeeder

if __name__ == '__main__':
    with app.app_context():
        controller = APIController()
        controller.reclear_tables()
        controller.init_schemas()
        OverallSeeder(NotesSeeder(), PersonSeeder(), CategorySeeder() ).seed()
        controller.add_rules()
        app.run()
