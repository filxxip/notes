#include "usereditcontroller.h"
#include <QTime>
#include "../cpputils/utils.h"

namespace {
constexpr const char *NAME = "Name";
constexpr const char *SURNAME = "Surname";
constexpr const char *EMAIL = "Email";
constexpr const char *PASSWORD = "Password";
constexpr const char *COUNTRY = "Country";
constexpr const char *CREATED = "Created Date";
} // namespace

//to do
UserEditController::UserEditController(
    std::shared_ptr<PrevEnumViewController> mainViewController,
    std::unique_ptr<SingletonObjectManager<Person>> singletonObjectLogoutManager,
    QPointer<DialogController> dialogController_,
    QObject *obj)
    : UserConfigController(mainViewController,
                           std::move(singletonObjectLogoutManager),
                           dialogController_,
                           obj)
{
    model->setEntries({{EnumStatus::CREATED, CREATED},
                       {EnumStatus::EMAIL, EMAIL},
                       {EnumStatus::PASSWORD, PASSWORD},
                       {EnumStatus::NAME, NAME},
                       {EnumStatus::SURNAME, SURNAME},
                       {EnumStatus::COUNTRY, COUNTRY}});

    connect(this, &UserEditController::remove, this, &UserEditController::onRemove);
    connect(this,
            &UserEditController::logout,
            this,
            &UserEditController::onLogout); //disconnect do tego pozniej
    Person person;
    person.name = "F";
    person.surname = "P";
    person.birthday = QDateTime(QDate(1999, 1, 1), QTime(1, 1, 1));
    person.created = QDateTime().currentDateTime();
    person.country = "Polska";
    person.gender.setByCode(1);
    person.password = "Pass";
    person.email = "mail";
    person.id = 10;
    setNewPerson(std::move(person));
}

void UserEditController::moveDataFromPersonToModel()
{
    model->setData(model->indexOf(EnumStatus::NAME), person->name.get(), EntryRoles::VALUE);
    model->setData(model->indexOf(EnumStatus::SURNAME), person->surname.get(), EntryRoles::VALUE);
    model->setData(model->indexOf(EnumStatus::COUNTRY), person->country.get(), EntryRoles::VALUE);
    model->setData(model->indexOf(EnumStatus::PASSWORD), person->password.get(), EntryRoles::VALUE);
    model->setData(model->indexOf(EnumStatus::EMAIL), person->email.get(), EntryRoles::VALUE);
    model->setData(model->indexOf(EnumStatus::CREATED),
                   DateStringAlternatives::convertToStringFormat(person->created.get().date()),
                   EntryRoles::VALUE);

    auto birthday = person->birthday.get().date();
    calendarController->changeDate(birthday.year(), birthday.month(), birthday.day());

    radioButtonController->setValue(person->gender.getByCode(), true);

    emit resetData();
}

void UserEditController::onRemove()
{
    dialogController->showDialog(DialogCodes::UserViews::CHECK_ACCOUNT_REMOVE);
    dialogController->applyConnection(
        [this](auto status) {
            if (status == DialogController::ActivityStatus::ACCEPT) {
                emitSuccessDialogWithClear(DialogCodes::UserViews::ACCOUNT_REMOVE_INFORMATION,
                                           person.value());
                emit removePersonData(person->id.get());
                person.reset();
            }
        },
        true);
}

void UserEditController::onConfirmed()
{
    auto name = getPartOfPerson(EnumStatus::NAME);
    auto surname = getPartOfPerson(EnumStatus::SURNAME);
    auto country = getPartOfPerson(EnumStatus::COUNTRY);
    auto password = getPartOfPerson(EnumStatus::PASSWORD);
    auto container = {&password, &name, &surname, &country};

    if (!Validators::fieldsValidator(container)) {
        dialogController->showDialog(DialogCodes::UserViews::INVALID_UPDATED_FIELDS);
        return;
    }

    if (!Validators::passwordValidator(password)) {
        dialogController->showDialog(DialogCodes::UserViews::INVALID_UPDATED_PASSWORD);
        return;
    }
    if (!radioButtonController->isValid()) {
        qDebug() << Messages::INVALID_RADIO_BUTTON;
        return;
    }
    person->name = std::move(name);
    person->password = std::move(password);
    person->surname = std::move(surname);
    person->country = std::move(country);
    person->birthday = calendarController->getCurrentDateTime();
    person->gender.setByCode(radioButtonController->getValue(0) ? 0 : 1);

    moveDataFromPersonToModel();

    dialogController->showDialog(DialogCodes::UserViews::UPDATES_PERSOS_SUCCESS);

    emit updatePersonData(person.value());
}

void UserEditController::setNewPerson(Person person)
{
    this->person = person;
    moveDataFromPersonToModel();
}

void UserEditController::onLogout()
{
    dialogController->showDialog(DialogCodes::UserViews::LOGOUT);
    dialogController->applyConnection(
        [this](auto status) {
            if (status == DialogController::ActivityStatus::ACCEPT) {
                emitSuccessDialogWithClear(DialogCodes::UserViews::LOGOUT_INFO, person.value());
                person.reset();
            }
        },
        true);
}
