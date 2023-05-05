#include "entrycontroller.h"

EntryController::EntryController()
    : QObject()
{
    connect(this, &EntryController::confirm, this, &EntryController::onConfirmed);
}

RegisterController::RegisterController(QPointer<CalendarController> controller)
    : EntryController()
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

LoginController::LoginController()
    : EntryController()
{
    model->setEntries({{ModelStatuses::PersonComponents::EMAIL, "Login..."},
                       {ModelStatuses::PersonComponents::PASSWORD, "Password..."}});
    model->setData(1, true, ModelStatuses::Roles::PASS_STATUS);
}

void LoginController::onConfirmed()
{
    qDebug() << "login";
}

GuestController::GuestController()
    : EntryController()
{
    model->setEntries({{ModelStatuses::PersonComponents::NAME, "Temporary name..."}});
}

void GuestController::onConfirmed()
{
    qDebug() << "guest";
}
