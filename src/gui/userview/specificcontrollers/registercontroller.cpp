#include "registercontroller.h"

namespace {
constexpr const char *NAME_PLACEHOLDER = "Name...";
constexpr const char *SURNAME_PLACEHOLDER = "Surname...";
constexpr const char *EMAIL_PLACEHOLDER = "Email...";
constexpr const char *PASSWORD_PLACEHOLDER = "Password...";
constexpr const char *COUNTRY_PLACEHOLDER = "Country...";

const auto PERSON_CREATED = QStringLiteral("New user : %1 has just been added to database.");

} // namespace

RegisterController::RegisterController(QPointer<CalendarController> calendarController,
                                       std::shared_ptr<DataClient> dataclient_,
                                       QPointer<DialogController> dialogController_,
                                       QObject *obj)
    : UserConfigController(calendarController, dialogController_, obj)
    , manager(dataclient_)
{
    model->setEntries({{EnumStatus::EMAIL, EMAIL_PLACEHOLDER},
                       {EnumStatus::PASSWORD, PASSWORD_PLACEHOLDER},
                       {EnumStatus::NAME, NAME_PLACEHOLDER},
                       {EnumStatus::SURNAME, SURNAME_PLACEHOLDER},
                       {EnumStatus::COUNTRY, COUNTRY_PLACEHOLDER}});
}

void RegisterController::onConfirmed()
{
    auto password = getPartOfPerson(EnumStatus::PASSWORD);
    auto email = getPartOfPerson(EnumStatus::EMAIL);
    auto country = getPartOfPerson(EnumStatus::COUNTRY);
    auto name = getPartOfPerson(EnumStatus::NAME);
    auto surname = getPartOfPerson(EnumStatus::SURNAME);

    auto temporaryStruct = {&password, &email, &country, &name, &surname};

    if (!Validators::fieldsValidator(temporaryStruct)) {
        dialogController->showDialog(DialogCodes::UserViews::INVALID_FIELDS);
        return;
    }

    auto hasNoEmailMatches = !Validators::emailValidator(email);
    auto hasNoUppercase = !Validators::passwordValidator(password);

    auto elementsNumber = DatabaseSupportMethods::getElementsWithGivenValue(manager,
                                                                            "email",
                                                                            name.toStdString());
    if (!elementsNumber.has_value()) {
        return;
    }
    if (elementsNumber.value() != 0) {
        dialogController->showDialog(DialogCodes::UserViews::EMAIL_IN_USE);
        return;
    }

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
    person.gender.setByCode(radioButtonController->getValue(0) ? 0 : 1);

    manager.add(person);

    qDebug() << PERSON_CREATED.arg(person.email.get());

    calendarController->clear();
    emitSuccessDialogWithClear(DialogCodes::UserViews::REGISTER_NEW_USER_SUCCESS, std::move(person));
}