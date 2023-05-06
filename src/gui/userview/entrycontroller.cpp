#include "entrycontroller.h"
#include <QRegularExpression>

namespace {
constexpr const char *DOUBLE_EMAIL
    = "This is email is not unique in database or your data files. Check it and fix this issue.";

const QRegularExpression emailRegex(".*@.*\\.com");

} // namespace

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
    , manager(dataclient_)
{
    model->setEntries({{ModelStatuses::PersonComponents::NAME, "Name..."},
                       {ModelStatuses::PersonComponents::SURNAME, "Surname..."},
                       {ModelStatuses::PersonComponents::EMAIL, "Email..."},
                       {ModelStatuses::PersonComponents::PASSWORD, "Password..."},
                       {ModelStatuses::PersonComponents::COUNTRY, "Country..."}});
}

void RegisterController::onConfirmed()
{
    int passIndex = model->indexOf(ModelStatuses::PersonComponents::PASSWORD);
    auto password = model->data(passIndex, ModelStatuses::Roles::VALUE).value<QString>();

    int emailIndex = model->indexOf(ModelStatuses::PersonComponents::EMAIL);
    auto email = model->data(emailIndex, ModelStatuses::Roles::VALUE).value<QString>();

    auto hasNoUppercase = std::none_of(password.begin(), password.end(), [](const QChar &ch) {
        return ch.isUpper();
    });

    auto hasNoEmailMatches = !emailRegex.match(email).hasMatch();

    if (hasNoUppercase && hasNoEmailMatches) {
        dialogController->showDialog(DialogCodes::UserViews::INVALID_REGISTER_PASSWORD_AND_EMAIL);
        return;
    }

    if (hasNoUppercase) {
        dialogController->showDialog(DialogCodes::UserViews::INVALID_REGISTER_PASSWORD);
        return;
    }
    if (hasNoEmailMatches) {
        dialogController->showDialog(DialogCodes::UserViews::INVALID_REGISTER_EMAIL);
        return;
    }

    //dorzucic jeszcze sprawdzenie reszty elementow aby nie byly puste(i dialog do tego jakis), ewentualnie moze wybor kraju ale to za duzo roboty

    qDebug() << "Access";
    emit operationSuccess();
}

LoginController::LoginController(std::shared_ptr<DataClient> dataclient_,
                                 QPointer<DialogController> dialogController_,
                                 QObject *obj)
    : EntryController(dialogController_, obj)
    , manager(dataclient_)
{
    model->setEntries({{ModelStatuses::PersonComponents::EMAIL, "Login..."},
                       {ModelStatuses::PersonComponents::PASSWORD, "Password..."}});
    model->setData(1, true, ModelStatuses::Roles::PASSWORD_STATUS);
}

void LoginController::onConfirmed()
{
    auto name = model->data(0, ModelStatuses::Roles::VALUE).toString();
    auto password = model->data(1, ModelStatuses::Roles::VALUE).toString();
    auto personWithGiveEmail = manager.getFiltered({{"email", name.toStdString()}});
    if (personWithGiveEmail.has_value() && personWithGiveEmail->size() > 1) {
        qDebug() << DOUBLE_EMAIL;
        return;
    }
    if (personWithGiveEmail->size() == 1 && personWithGiveEmail->at(0).password == password) {
        qDebug() << "Access";
        emit operationSuccess();
    } else {
        dialogController->showDialog(DialogCodes::UserViews::LOGIN_INVALID_ACCESS);
    }
}

GuestController::GuestController(QPointer<DialogController> dialogController_, QObject *obj)
    : EntryController(dialogController_, obj)
{
    model->setEntries({{ModelStatuses::PersonComponents::NAME, "Temporary name..."}});
}

void GuestController::onConfirmed()
{
    auto name = model->data(0, ModelStatuses::Roles::VALUE).toString();
    qDebug() << name;
    if (name.isEmpty()) {
        dialogController->showDialog(DialogCodes::UserViews::EMPTY_NAME_GUEST);
        return;
    }
    emit operationSuccess();
}
