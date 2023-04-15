from .seeder_base import Seeder
from src.backend.main_config_database_vars import db_session


class OverallSeeder(Seeder):
    def __init__(self, *seeders: Seeder):
        self.seeders = seeders

    def seed(self):
        for seeder in self.seeders:
            for item in seeder.seed():
                db_session.add(item)
                db_session.commit()
