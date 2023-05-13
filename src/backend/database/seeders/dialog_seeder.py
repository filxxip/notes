from .seeder_base import Seeder
from src.backend.database.tables import Base, GuiDialog


class GuiDialogSeeder(Seeder):
    def seed(self) -> list[Base]:
        notes = []
        titles = ["Dialog1", "Dialog2", "Dialog3", "Dialog4"]
        contents = ['SomeContent', 'SpecificContent', 'Other Content', 'Super Secret']
        isOks = [True, False, False, True]
        isYes = [False, True, True, False]
        isNo = [False, True, True, False]

        for title, content, isok, isyes, isno in zip(titles, contents, isOks, isYes, isNo):
            notes.append(GuiDialog(content=content, title=title, isOk=isok, isYes=isyes, isNo=isno,fontSize = 15, path = "undefined"))

        return notes
