from typing import Type

from sqlalchemy import event

from .tables import Base


def register_dependency(dependant_class: Type[Base], attribute_dependant_name: str, attribute_name: str = "id"):
    def register_wrapper(owner: Type[Base]):
        @event.listens_for(owner, 'before_delete')
        def before_custom_delete(mapper, connection, target):
            dependant_class.query.filter_by(**{attribute_dependant_name: getattr(target, attribute_name)}).delete()

        return owner

    return register_wrapper
