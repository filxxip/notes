#include "guestcontroller.h"
#include "src/backend/datamanager/directobjsmanagers/ids/ids.h"

namespace {
const auto UNDEFINED_MOCK = QString("**undefined-mock-data%1**").arg(PidContants::PID_VALUE);
constexpr char DATA[] = "data";
constexpr char TEMPORARY_NAME[] = "Temporary name...";
}

GuestController::GuestController(
    std::shared_ptr<PrevEnumViewController> mainViewController_,
    std::unique_ptr<SingletonObjectManager<Person>> singleLoginPersonManager,
    std::shared_ptr<PeopleManager> peopleManager_,
    QPointer<DialogController> dialogController_,
    QObject *obj)
    : EntryController(mainViewController_,
                      std::move(singleLoginPersonManager),
                      dialogController_,
                      obj)
    , manager(peopleManager_)
{
    model->setEntries({{EnumStatus::NAME, TEMPORARY_NAME}});
}

void GuestController::onConfirmed()
{
    auto name = model->data(0, ModelStatuses::Roles::VALUE).toString();
    if (name.isEmpty()) {
        dialogController->showDialog(DialogCodes::UserViews::EMPTY_NAME_GUEST);
        return;
    }

    Person person;

    person.name = name;

    for (auto contentPtr : {&person.surname, &person.country, &person.email, &person.password}) {
        contentPtr->set(UNDEFINED_MOCK);
    }

    person.birthday = QDateTime::currentDateTime();
    person.created = QDateTime::currentDateTime();
    person.gender.setByCode(0);

    manager->add(person);
    emitSuccessDialogWithClear(DialogCodes::UserViews::REGISTER_GUEST_SUCCESS,
                               DatabaseUtilsFunctions::getLastObjectOfDatabase<Person>(manager)
                                   .value()); //ewentualnie po mailu ale lokalnie sie sprawdza
}
