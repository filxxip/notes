#include "usereditcontroller.h"
#include <QEventLoop>
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

AbstractEditController::AbstractEditController(
    std::shared_ptr<PrevEnumViewController> mainViewController,
    std::unique_ptr<SingletonObjectManager<Person>> singletonObjectLogoutManager,
    QPointer<DialogController> dialogController_,
    QObject *obj)
    : EntryController(mainViewController,
                      std::move(singletonObjectLogoutManager),
                      dialogController_,
                      obj)
{
    connect(this, &AbstractEditController::logout, this, &AbstractEditController::onLogout);
}

std::optional<int> AbstractEditController::getPersonId() const
{
    return person.has_value() ? std::make_optional(person->id.get()) : std::nullopt;
}

void AbstractEditController::setNewPerson(Person person)
{
    this->person = person;
    moveDataFromPersonToModel();
}

void AbstractEditController::onLogout()
{
    dialogController->showDialog(DialogCodes::UserViews::LOGOUT);
    dialogController->applyConnection(
        [this](auto status) {
            if (status == DialogController::ActivityStatus::ACCEPT) {
                this->emitSuccessDialogWithClear(DialogCodes::UserViews::LOGOUT_INFO,
                                                 person.value());
                person.reset();
            }
        },
        true);
}

UserEditController::UserEditController(
    std::shared_ptr<PrevEnumViewController> mainViewController,
    std::unique_ptr<SingletonObjectManager<Person>> singletonObjectLogoutManager,
    QPointer<DialogController> dialogController_,
    QObject *obj)
    : AbstractEditController(mainViewController,
                             std::move(singletonObjectLogoutManager),
                             dialogController_,
                             obj)
    , calendarController(new CalendarController(this))
    , radioButtonController(UserConfigControllerUtils::generateRadioButton(this))
{
    model->setEntries({{EnumStatus::CREATED, CREATED},
                       {EnumStatus::EMAIL, EMAIL},
                       {EnumStatus::PASSWORD, PASSWORD},
                       {EnumStatus::NAME, NAME},
                       {EnumStatus::SURNAME, SURNAME},
                       {EnumStatus::COUNTRY, COUNTRY}});

    connect(this, &UserEditController::remove, this, &UserEditController::onRemove);
    UserConfigControllerUtils::connectClear(this, calendarController, radioButtonController);
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
    auto name = UserConfigControllerUtils::getPartOfPerson(EnumStatus::NAME, model);
    auto surname = UserConfigControllerUtils::getPartOfPerson(EnumStatus::SURNAME, model);
    auto country = UserConfigControllerUtils::getPartOfPerson(EnumStatus::COUNTRY, model);
    auto password = UserConfigControllerUtils::getPartOfPerson(EnumStatus::PASSWORD, model);
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

GuestEditController::GuestEditController(
    std::shared_ptr<PrevEnumViewController> mainViewController,
    std::unique_ptr<SingletonObjectManager<Person>> singletonObjectLogoutManager,
    QPointer<DialogController> dialogController_,
    QObject *obj)
    : AbstractEditController(mainViewController,
                             std::move(singletonObjectLogoutManager),
                             dialogController_,
                             obj)
{
    model->setEntries({{EnumStatus::NAME, NAME}});
}

void GuestEditController::onConfirmed()
{
    auto name = UserConfigControllerUtils::getPartOfPerson(EnumStatus::NAME, model);

    if (name.isEmpty()) {
        dialogController->showDialog(DialogCodes::UserViews::INVALID_UPDATED_FIELDS);
        return;
    }

    person->name = std::move(name);
    moveDataFromPersonToModel();
    dialogController->showDialog(DialogCodes::UserViews::UPDATES_PERSOS_SUCCESS);
    emit updatePersonData(person.value());
}

void GuestEditController::emitSuccessDialogWithClear(int code, Person person)
{
    removePerson();
    AbstractEditController::emitSuccessDialogWithClear(code, std::move(person));
}

void GuestEditController::setNewPerson(Person person)
{
    removePerson();
    AbstractEditController::setNewPerson(std::move(person));
}

void GuestEditController::removePerson()
{
    if (person.has_value()) {
        emit removePersonData(person.value().id.get());
    }
}

void GuestEditController::moveDataFromPersonToModel()
{
    model->setData(model->indexOf(EnumStatus::NAME), person->name.get(), EntryRoles::VALUE);

    emit resetData();
}
