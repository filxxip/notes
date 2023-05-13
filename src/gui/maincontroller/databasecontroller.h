#pragma once
#include "../../backend/datamanager/directobjsmanagers/categories/categoriesmanager.h"
#include "../../backend/datamanager/directobjsmanagers/guidialogs/guidialogmanager.h"
#include "../../backend/datamanager/directobjsmanagers/notes/notesmanager.h"
#include "../../backend/datamanager/directobjsmanagers/people/peoplemanager.h"

#include <QPointer>

#include <memory>

struct DatabaseController
{
private:
    std::shared_ptr<DataClient> dataClient;

public:
    DatabaseController(std::shared_ptr<DataClient> dataClient_)
        : dataClient(dataClient_)
    {}

    std::shared_ptr<PeopleManager> peopleManager = std::make_shared(dataClient);
    std::shared_ptr<CategoriesManager> categoriesManager = std::make_shared(dataClient);
    std::shared_ptr<NotesManager> notesManager = std::make_shared(dataClient);
    std::shared_ptr<GuiDialogsManager> dialogsManager = std::make_shared(dataClient);
};

//metoda zbiorowa add update ew to mozna jakos przy uzyciu constexpr i decltype(auto)
//ale chyba bez sensu
