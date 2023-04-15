from __future__ import annotations
from controller import APIController
from main_config_database_vars import app
from seeders import OverallSeeder, NotesSeeder, CategorySeeder, PersonSeeder

if __name__ == '__main__':
    with app.app_context():
        controller = APIController()
        controller.reclear_tables()
        controller.init_schemas()
        OverallSeeder(NotesSeeder(), PersonSeeder(), CategorySeeder()).seed()
        controller.add_rules()
        app.run()
