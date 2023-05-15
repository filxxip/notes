#include "guestcontroller.h"

namespace {
const auto UNDEFINED_MOCK = QString("**undefined-mock-%1**");
}

GuestController::GuestController(
    std::unique_ptr<SingletonObjectManager<Person>> singleLoginPersonManager,
    QPointer<DialogController> dialogController_,
    QObject *obj)
    : EntryController(std::move(singleLoginPersonManager), dialogController_, obj)
{
    model->setEntries({{EnumStatus::NAME, "Temporary name..."}});
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
    person.surname = UNDEFINED_MOCK.arg("surname");
    person.country = UNDEFINED_MOCK.arg("country");
    person.email = UNDEFINED_MOCK.arg("email");
    person.password = UNDEFINED_MOCK.arg("password");
    person.birthday = QDateTime().currentDateTime();
    person.created = QDateTime().currentDateTime();
    person.gender = "male";

    emitSuccessDialogWithClear(DialogCodes::UserViews::REGISTER_GUEST_SUCCESS, std::move(person));
}
