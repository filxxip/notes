#include "entrycontroller.h"

EntryController::EntryController(QPointer<DialogController> dialogController_, QObject *obj)
    : QObject(obj)
    , dialogController(dialogController_)
{
    connect(this, &EntryController::confirm, this, &EntryController::onConfirmed);
}

RegisterController::RegisterController(QPointer<CalendarController> calendarController_,
                                       std::shared_ptr<DataClient> dataclient_,
                                       QPointer<DialogController> dialogController_,
                                       QObject *obj)
    : EntryController(dialogController_, obj)
    , calendarController(calendarController_)
    , dataClient(dataclient_)
{
    model->setEntries({{ModelStatuses::PersonComponents::NAME, "Name..."},
                       {ModelStatuses::PersonComponents::SURNAME, "Surname..."},
                       {ModelStatuses::PersonComponents::EMAIL, "Email..."},
                       {ModelStatuses::PersonComponents::PASSWORD, "Password..."},
                       {ModelStatuses::PersonComponents::COUNTRY, "Country..."}});
}

void RegisterController::onConfirmed()
{
    qDebug() << "register";
}

LoginController::LoginController(std::shared_ptr<DataClient> dataclient_,
                                 QPointer<DialogController> dialogController_,
                                 QObject *obj)
    : EntryController(dialogController_, obj)
    , dataClient(dataclient_)
{
    model->setEntries({{ModelStatuses::PersonComponents::EMAIL, "Login..."},
                       {ModelStatuses::PersonComponents::PASSWORD, "Password..."}});
    model->setData(1, true, ModelStatuses::Roles::PASSWORD_STATUS);
}

void LoginController::onConfirmed()
{
    qDebug() << "login";
}

GuestController::GuestController(QPointer<DialogController> dialogController_, QObject *obj)
    : EntryController(dialogController_, obj)
{
    model->setEntries({{ModelStatuses::PersonComponents::NAME, "Temporary name..."}});
}

void GuestController::onConfirmed()
{
    qDebug() << "confirm";
    auto name = model->data(0, ModelStatuses::Roles::VALUE).toString();
    qDebug() << name;
    if (name.isEmpty()) {
        dialogController->showDialog(DialogCodes::UserViews::EMPTY_NAME_GUEST);
    } else {
        emit operationSuccess();
    }
}
