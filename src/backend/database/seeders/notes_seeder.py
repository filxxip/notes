import random
from datetime import datetime, timedelta

from .seeder_base import Seeder
from src.backend.database.tables import Base, Note
from ..utils import convert_datetime_to_str


class NotesSeeder(Seeder):
    def seed(self) -> list[Base]:
        notes = []
        titles = ["NoteNum1", "NoteNum2", "Another One", "Some Funny"]
        contents = ['SomeContent', 'SpecificContent', 'Other Content', 'Super Secret']

        for i in range(50):
            category = random.randint(1, 10)
            owner = random.randint(1, 5)
            title = random.choice(titles)
            content = random.choice(contents)
            release_date = convert_datetime_to_str(
                datetime.now() - timedelta(minutes=random.randint(1, 60), hours=random.randint(1, 24),
                                           days=random.randint(1, 90)))
            note = Note(category=category, owner=owner, title=title, content=content,
                        releaseDate=release_date)
            notes.append(note)
        return notes
