from typing import Final

main_site: Final[str] = "/"
main_site_information: Final[dict] = {"information": "Access to the database is correct."}

# apis urls

people: Final[str] = '/people'
categories: Final[str] = '/categories'
notes: Final[str] = '/notes'
guidialogs: Final[str] = '/guidialogs'
schema: Final[str] = "/schemas"

people_login: Final[str] = "/peopleLogin";
people_register: Final[str] = "/peopleRegister";
people_logout: Final[str] = "/peopleLogout";
people_remove_account: Final[str] = "/peopleRemoveAccount";
people_guest : Final[str] = "/peopleGuest";

people_index: Final[str] = '/people/<int:index>'
categories_index: Final[str] = '/categories/<int:index>'
notes_index: Final[str] = '/notes/<int:index>'
guidialogs_index: Final[str] = '/guidialogs/<int:index>'

people_login_index: Final[str] = "/peopleLogin/<int:index>"
people_register_index: Final[str] = "/peopleRegister/<int:index>"
people_logout_index: Final[str] = "/peopleLogout/<int:index>"
people_remove_account_index: Final[str] = "/peopleRemoveAccount/<int:index>"
people_guest_index : Final[str] = "/peopleGuest/<int:index>";

people_sorted: Final[str] = '/people/<sorted_name>'
categories_sorted: Final[str] = '/categories/<sorted_name>'
notes_sorted: Final[str] = '/notes/<sorted_name>'

# names

people_name: Final[str] = 'each_person'
categories_name: Final[str] = 'each_category'
notes_name: Final[str] = 'each_note'
guidialogs_name: Final[str] = 'each_guidialog'

people_login_name: Final[str] = "each_peopleLogin"
people_register_name: Final[str] = "each_peopleRegister"
people_logout_name: Final[str] = "each_peopleLogout"
people_guest_name: Final[str] = "each_peopleGuest"
people_remove_account_name: Final[str] = "each_peopleRemoveAccount"

schemas_name: Final[str] = "schemas"
people_index_name: Final[str] = 'myview_with_id'
categories_index_name: Final[str] = 'category_with_id'
notes_index_name: Final[str] = 'notes_with_id'
guidialogs_index_name: Final[str] = 'guidialogs_with_id'

people_login_index_name: Final[str] = "each_peopleLogin_with_id"
people_register_index_name: Final[str] = "each_peopleRegister_with_id"
people_logout_index_name: Final[str] = "each_peopleLogout_with_id"
people_guest_index_name: Final[str] = "each_peopleGuest_with_id"
people_remove_account_index_name: Final[str] = "each_peopleRemoveAccount_with_id"

people_sorted_name: Final[str] = 'each_person_sorted'
categories_sorted_name: Final[str] = 'each_category_sorted'
notes_sorted_name: Final[str] = 'each_note_sorted'

date_syntax: Final[str] = '%Y-%m-%d-%H-%M-%S'

database_name: Final[str] = 'sqlite:///example.db'
