import random
from datetime import datetime, timedelta

from .seeder_base import Seeder
from src.backend.database.tables import Base, Person


class PersonSeeder(Seeder):
    def seed(self) -> list[Base]:
        people = []
        names = ['Emma', 'Noah', 'Olivia', 'Liam', 'Ava', 'William', 'Sophia', 'Mason', 'Isabella', 'James']
        surnames = ['Smith', 'Johnson', 'Brown', 'Garcia', 'Miller', 'Davis', 'Martinez', 'Taylor', 'Wilson',
                    'Anderson']
        countries = ['USA', 'Canada', 'UK', 'France', 'Germany', 'Japan', 'Australia', 'New Zealand', 'South Africa',
                     'Brazil']

        for i in range(50):
            name = random.choice(names)
            surname = random.choice(surnames)
            email = f'{name.lower()}.{surname.lower()}@example.com'
            password = ''.join(random.choices('abcdefghijklmnopqrstuvwxyz1234567890', k=8))
            country = random.choice(countries)
            birthday = datetime.now() - timedelta(days=365 * random.randint(18, 65))
            person = Person(name=name, surname=surname, email=email, password=password, country=country,
                            birthday=birthday)
            people.append(person)
        return people
