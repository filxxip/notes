import random
from datetime import datetime, timedelta

from .seeder_base import Seeder
from src.backend.database.tables import Base, Category
from ..utils import convert_datetime_to_str


class CategorySeeder(Seeder):
    def seed(self) -> list[Base]:
        categories = []
        names = ["kitchen", "free time", "maths", "economy", "history", "childhood", "present", "english", "PE",
                 "sport", "grocery lists"]
        colors = ['blue', 'yellow', 'green', 'black', 'grey']

        for i in range(50):
            name = random.choice(names)
            color = random.choice(colors)
            creation_date = convert_datetime_to_str(
                datetime.now() - timedelta(minutes=random.randint(1, 60), hours=random.randint(1, 24),
                                           days=random.randint(1, 90)))
            owner = random.randrange(4)
            cat = Category(name=name, color=color, creationDate=creation_date, owner=owner)
            categories.append(cat)
        return categories
