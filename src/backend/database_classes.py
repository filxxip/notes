from __future__ import annotations
from controller import APIController
from main_config_database_vars import app

if __name__ == '__main__':
    with app.app_context():
        controller = APIController()
        controller.add_rules()
        app.run()
