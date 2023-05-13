import abc

from src.backend.database.tables import Base


class Seeder(abc.ABC):
    @abc.abstractmethod
    def seed(self) -> list[Base]:
        pass
