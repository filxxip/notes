import abc

from src.backend.tables import Base


class Seeder(abc.ABC):
    @abc.abstractmethod
    def seed(self) -> list[Base]:
        pass
