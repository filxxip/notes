#include "databasecontroller.h"

namespace {
constexpr char PEOPLE_NAME[] = "people";
constexpr char CATEGORIES_NAME[] = "categories";
constexpr char NOTES_NAME[] = "notes";
constexpr char GUIDIALOGS_NAME[] = "guidialogs";
constexpr char PEOPLE_TRANSFERED_NAME[] = "peopleTransfered";
} // namespace

DatabaseController::DatabaseController(std::shared_ptr<DataClient> dataClient_)
    : dataClient(dataClient_)
    , peopleManager(std::make_shared<PeopleManager>(PEOPLE_NAME, dataClient))
    , notesManager(std::make_shared<NotesManager>(NOTES_NAME, dataClient))
    , categoriesManager(std::make_shared<CategoriesManager>(CATEGORIES_NAME, dataClient))
    , dialogsManager(std::make_shared<GuiDialogsManager>(GUIDIALOGS_NAME, dataClient))
    , peopleTransferedManager(std::make_shared<SingletonObjectManager<Person>>(
          std::make_unique<PeopleManager>(PEOPLE_TRANSFERED_NAME, dataClient)))
{}
