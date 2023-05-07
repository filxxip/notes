#include "entrycontroller.h"
#include <QRegularExpression>
#include <QStringLiteral>

namespace {
constexpr const char *DOUBLE_EMAIL
    = "This is email is not unique in database or your data files. Check it and fix this issue.";

const auto PERSON_CREATED = QStringLiteral("New user : %1 has just been added to database.");

const QRegularExpression emailRegex(".*@.*\\.com");

} // namespace

EntryController::EntryController(QPointer<DialogController> dialogController_, QObject *obj)
    : QObject(obj)
    , dialogController(dialogController_)
{
    connect(this, &EntryController::confirm, this, &EntryController::onConfirmed);
}

void EntryController::emitSuccessDialogWithClear(int code)
{
    emit clear();
    dialogController->showDialog(code);
    dialogController->applyConnection([this](auto status) { emit operationSuccess(); });
}
RegisterController::RegisterController(QPointer<CalendarController> calendarController_,
                                       std::shared_ptr<DataClient> dataclient_,
                                       QPointer<DialogController> dialogController_,
                                       QObject *obj)
    : EntryController(dialogController_, obj)
    , calendarController(calendarController_)
    , manager(dataclient_)
{
    model->setEntries({{EnumStatus::NAME, "Name..."},
                       {EnumStatus::SURNAME, "Surname..."},
                       {EnumStatus::EMAIL, "Email..."},
                       {EnumStatus::PASSWORD, "Password..."},
                       {EnumStatus::COUNTRY, "Country..."}});
}

QString RegisterController::getPartOfPerson(EnumStatus componentEnum) const
{
    auto index = model->indexOf(componentEnum);
    return model->data(index, ModelStatuses::Roles::VALUE).value<QString>();
}

void RegisterController::onConfirmed()
{
    auto password = getPartOfPerson(EnumStatus::PASSWORD);
    auto email = getPartOfPerson(EnumStatus::EMAIL);
    auto country = getPartOfPerson(EnumStatus::COUNTRY);
    auto name = getPartOfPerson(EnumStatus::NAME);
    auto surname = getPartOfPerson(EnumStatus::SURNAME);

    auto temporaryStruct = {&password, &email, &country, &name, &surname};

    if (std::any_of(std::begin(temporaryStruct), std::end(temporaryStruct), [](const auto data) {
            return data->isEmpty();
        })) {
        dialogController->showDialog(DialogCodes::UserViews::INVALID_FIELDS);
        return;
    }

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
    Person person;

    person.birthday = calendarController->getCurrentDateTime();
    person.email = std::move(email);
    person.password = std::move(password);
    person.country = std::move(country);
    person.name = std::move(name);
    person.surname = std::move(surname);

    manager.add(person);

    qDebug() << PERSON_CREATED.arg(person.email.get());

    calendarController->clear();
    emitSuccessDialogWithClear(DialogCodes::UserViews::REGISTER_NEW_USER_SUCCESS);
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
        emitSuccessDialogWithClear(9);
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
    if (name.isEmpty()) {
        dialogController->showDialog(DialogCodes::UserViews::EMPTY_NAME_GUEST);
        return;
    }

    emitSuccessDialogWithClear(DialogCodes::UserViews::REGISTER_GUEST_SUCCESS);
}
