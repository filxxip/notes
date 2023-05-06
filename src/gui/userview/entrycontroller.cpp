#include "entrycontroller.h"

EntryController::EntryController(QObject *obj)
    : QObject(obj)
{
    connect(this, &EntryController::confirm, this, &EntryController::onConfirmed);
}

RegisterController::RegisterController(QPointer<CalendarController> controller, QObject *obj)
    : EntryController(obj)
    , calendarController(controller)
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

LoginController::LoginController(QObject *obj)
    : EntryController(obj)
{
    model->setEntries({{ModelStatuses::PersonComponents::EMAIL, "Login..."},
                       {ModelStatuses::PersonComponents::PASSWORD, "Password..."}});
    model->setData(1, true, ModelStatuses::Roles::PASSWORD_STATUS);
}

void LoginController::onConfirmed()
{
    qDebug() << "login";
}

GuestController::GuestController(QObject *obj)
    : EntryController(obj)
{
    model->setEntries({{ModelStatuses::PersonComponents::NAME, "Temporary name..."}});
}

void GuestController::onConfirmed()
{
    qDebug() << "guest";
}
