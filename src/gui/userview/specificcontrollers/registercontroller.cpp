#include "registercontroller.h"

namespace {
constexpr const char *MALE_DATABASE_CODE = "male";
constexpr const char *FEMALE_DATABASE_CODE = "female";

constexpr const char *NAME_PLACEHOLDER = "Name...";
constexpr const char *SURNAME_PLACEHOLDER = "Surname...";
constexpr const char *EMAIL_PLACEHOLDER = "Email...";
constexpr const char *PASSWORD_PLACEHOLDER = "Password...";
constexpr const char *COUNTRY_PLACEHOLDER = "Country...";

constexpr const char *FEMALE_TEXT_BUTTON = "female";
constexpr const char *MALE_TEXT_BUTTON = "male";

const auto PERSON_CREATED = QStringLiteral("New user : %1 has just been added to database.");

} // namespace

RegisterController::RegisterController(QPointer<CalendarController> calendarController_,
                                       std::shared_ptr<DataClient> dataclient_,
                                       QPointer<DialogController> dialogController_,
                                       QObject *obj)
    : EntryController(dialogController_, obj)
    , calendarController(calendarController_)
    , manager(dataclient_)
{
    radioButtonController = new RadioButtonController({RadioButtonModel(MALE_TEXT_BUTTON, true, 1),
                                                       RadioButtonModel(FEMALE_TEXT_BUTTON,
                                                                        false,
                                                                        1)},
                                                      this);

    model->setEntries({{EnumStatus::NAME, NAME_PLACEHOLDER},
                       {EnumStatus::SURNAME, SURNAME_PLACEHOLDER},
                       {EnumStatus::EMAIL, EMAIL_PLACEHOLDER},
                       {EnumStatus::PASSWORD, PASSWORD_PLACEHOLDER},
                       {EnumStatus::COUNTRY, COUNTRY_PLACEHOLDER}});

    connect(this, &RegisterController::clear, [this] {
        calendarController->clear();
        radioButtonController->setValue(0, true);
    }); //ewentualnie wycczyszczenie reszty ale to dzieje sie automatycznie
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

    if (!Validators::fieldsValidator(temporaryStruct)) {
        dialogController->showDialog(DialogCodes::UserViews::INVALID_FIELDS);
        return;
    }

    auto hasNoEmailMatches = !Validators::emailValidator(email);
    auto hasNoUppercase = !Validators::passwordValidator(password);

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
    person.gender = radioButtonController->getValue(0) ? MALE_DATABASE_CODE : FEMALE_DATABASE_CODE;

    manager.add(person);

    qDebug() << PERSON_CREATED.arg(person.email.get());

    calendarController->clear();
    emitSuccessDialogWithClear(DialogCodes::UserViews::REGISTER_NEW_USER_SUCCESS, std::move(person));
}
