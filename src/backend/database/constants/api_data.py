from typing import Final

people_index: Final[str] = '/people/<int:index>'
categories_index: Final[str] = '/categories/<int:index>'
notes_index: Final[str] = '/notes/<int:index>'
guidialogs_index: Final[str] = '/guidialogs/<int:index>'
people: Final[str] = '/people'
categories: Final[str] = '/categories'
notes: Final[str] = '/notes'
guidialogs: Final[str] = '/guidialogs'
people_sorted: Final[str] = '/people/<sorted_name>'
categories_sorted: Final[str] = '/categories/<sorted_name>'
notes_sorted: Final[str] = '/notes/<sorted_name>'

people_index_name: Final[str] = 'myview_with_id'
categories_index_name: Final[str] = 'category_with_id'
notes_index_name: Final[str] = 'notes_with_id'
guidialogs_index_name: Final[str] = 'guidialogs_with_id'
people_name: Final[str] = 'each_person'
categories_name: Final[str] = 'each_category'
notes_name: Final[str] = 'each_note'
guidialogs_name: Final[str] = 'each_guidialog'
people_sorted_name: Final[str] = 'each_person_sorted'
categories_sorted_name: Final[str] = 'each_category_sorted'
notes_sorted_name: Final[str] = 'each_note_sorted'

date_syntax : Final[str] = '%Y-%m-%d-%H-%M-%S'

database_name : Final[str] = 'sqlite:///example.db'
