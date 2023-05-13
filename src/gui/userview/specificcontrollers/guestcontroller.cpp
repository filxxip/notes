#include "guestcontroller.h"

GuestController::GuestController(QPointer<DialogController> dialogController_, QObject *obj)
    : EntryController(dialogController_, obj)
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

    emitSuccessDialogWithClear(DialogCodes::UserViews::REGISTER_GUEST_SUCCESS, std::move(person));
}
