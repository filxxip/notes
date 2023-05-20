#include "registercontroller.h"

namespace {
constexpr const char *NAME_PLACEHOLDER = "Name...";
constexpr const char *SURNAME_PLACEHOLDER = "Surname...";
constexpr const char *EMAIL_PLACEHOLDER = "Email...";
constexpr const char *PASSWORD_PLACEHOLDER = "Password...";
constexpr const char *COUNTRY_PLACEHOLDER = "Country...";

constexpr char EMAIL_KEY[] = "email";

const auto PERSON_CREATED = QStringLiteral("New user : %1 has just been added to database.");

} // namespace

RegisterController::RegisterController(
    std::shared_ptr<PrevEnumViewController> mainViewController_,
    std::unique_ptr<SingletonObjectManager<Person>> singleLoginPersonManager,
    std::shared_ptr<PeopleManager> peopleManager,
    QPointer<DialogController> dialogController_,
    QObject *obj)
    : EntryController(mainViewController_,
                      std::move(singleLoginPersonManager),
                      dialogController_,
                      obj)
    , manager(peopleManager)
    , calendarController(new CalendarController(this))
    , radioButtonController(UserConfigControllerUtils::generateRadioButton(this))
{
    model->setEntries({{EnumStatus::EMAIL, EMAIL_PLACEHOLDER},
                       {EnumStatus::PASSWORD, PASSWORD_PLACEHOLDER},
                       {EnumStatus::NAME, NAME_PLACEHOLDER},
                       {EnumStatus::SURNAME, SURNAME_PLACEHOLDER},
                       {EnumStatus::COUNTRY, COUNTRY_PLACEHOLDER}});
    UserConfigControllerUtils::connectClear(this, calendarController, radioButtonController);
}

void RegisterController::onConfirmed()
{
    auto getPart = [this](auto typeEnum) {
        return UserConfigControllerUtils::getPartOfPerson(typeEnum, model);
    };

    auto password = getPart(EnumStatus::PASSWORD);
    auto email = getPart(EnumStatus::EMAIL);
    auto country = getPart(EnumStatus::COUNTRY);
    auto name = getPart(EnumStatus::NAME);
    auto surname = getPart(EnumStatus::SURNAME);

    auto temporaryStruct = {&password, &email, &country, &name, &surname};

    if (!Validators::fieldsValidator(temporaryStruct)) {
        dialogController->showDialog(DialogCodes::UserViews::INVALID_FIELDS);
        return;
    }

    auto hasNoEmailMatches = !Validators::emailValidator(email);
    auto hasNoUppercase = !Validators::passwordValidator(password);

    auto searchedElements = manager->getFiltered({{EMAIL_KEY, email.toStdString()}});

    if (!searchedElements.has_value()) {
        qDebug() << Messages::INVALID_KEYWORD;
        return;
    }

    if (searchedElements->size() != 0) {
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
    if (!radioButtonController->isValid()) {
        qDebug() << Messages::INVALID_RADIO_BUTTON;
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
    person.created = QDateTime().currentDateTime();

    manager->add(person);

    qDebug() << PERSON_CREATED.arg(person.email.get());

    calendarController->clear();
    emitSuccessDialogWithClear(DialogCodes::UserViews::REGISTER_NEW_USER_SUCCESS,
                               DatabaseUtilsFunctions::getLastObjectOfDatabase<Person>(manager)
                                   .value());
}
