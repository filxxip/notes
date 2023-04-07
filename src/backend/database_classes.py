from __future__ import annotations
from src.backend.controller import APIController
from src.backend.main_config_database_vars import app

if __name__ == '__main__':
    controller = APIController()
    controller.add_rules()
    app.run()
