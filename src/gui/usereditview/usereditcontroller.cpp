#include "usereditcontroller.h"
#include "../cpputils/utils.h"

UserEditController::UserEditController(QPointer<DialogController> dialogController_,
                                       QObject *obj = nullptr)
    : QObject(obj)
    , dialogController(dialogController_)
{
    model->setEntries({{EnumStatus::NAME, "Name"},
                       {EnumStatus::SURNAME, "Surname"},
                       {EnumStatus::EMAIL, "Email"},
                       {EnumStatus::PASSWORD, "Password"},
                       {EnumStatus::COUNTRY, "Country"}});

    connect(this, &UserEditController::confirm, [this] { emit updatePersonData(person); });
    connect(this, &UserEditController::remove, [this] {
        emit clear();
        emit removePersonData(person.id.get());
    });
}

//na przycisk confirm lacze w gui sygnal z updatepersondata, na przycisk reset updates wysylam sygnal do gui i jakos odpalam move data from person to model a nastepnie wysylam sygnal reset data ktory w gui jest polaczony
// z funkcjami ktory z modelu przy uzyciu get wlasnego poprawne stare dane i je wrzuca do entryfieldow, tam chyba stworze sygnal set text i bedizie cos takiego settext(model.value)
void UserEditController::moveDataFromPersonToModel()
{
    model->setData(model->indexOf(EnumStatus::NAME), person.name.get(), EntryRoles::VALUE);
    model->setData(model->indexOf(EnumStatus::SURNAME), person.surname.get(), EntryRoles::VALUE);
    model->setData(model->indexOf(EnumStatus::COUNTRY), person.country.get(), EntryRoles::VALUE);
    model->setData(model->indexOf(EnumStatus::PASSWORD), person.password.get(), EntryRoles::VALUE);
    model->setData(model->indexOf(EnumStatus::EMAIL), person.email.get(), EntryRoles::VALUE);

    auto birthday = person.birthday.get().date();
    calendarController->changeDate(birthday.year(), birthday.month(), birthday.day());

    emit resetData();
}

void UserEditController::updatePersonData()
{
    //tam na klika updatuje ten model i emituje sygnal zeby sobie tutaj pozmieniac i posprawdzac
    auto name = model->data(model->indexOf(EnumStatus::NAME), EntryRoles::VALUE);
    auto surname = model->data(model->indexOf(EnumStatus::SURNAME), EntryRoles::VALUE);
    auto country = model->data(model->indexOf(EnumStatus::COUNTRY), EntryRoles::VALUE);
    auto password
        = model->data(model->indexOf(EnumStatus::COUNTRY),
                      EntryRoles::VALUE); //w gui bedzie non stop zmieniany model albo to co wyzej

    auto container = {&password, &name, &surname, &country};

    if (!Validators::emptyFieldsValidator(container)) {
        dialogController->showDialog(DialogCodes::UserViews::INVALID_UPDATED_FIELDS);
        //        moveDataFromPersonToModel();
        //        emit resetData(); //sygnal lapany z gui i tam pobieram wtedy zmieniam z uzyciem po prostu modela
        return;
    }

    if (!Validators::passwordValidator(password)) {
        dialogController->showDialog(DialogCodes::UserViews::INVALID_UPDATED_PASSWORD);
        //        moveDataFromPersonToModel();
        //        emit resetData();
        return;
    }

    person.name = std::move(name);
    person.password = std::move(password);
    person.surname = std::move(surname);
    person.country = std::move(country);
    person.birthday = calendarController->getCurrentDateTime();

    //    emit updatePersonData(person);//jakis fajny dialog by mozna dodac ze sie udalo
}

void UserEditController::setNewPerson(
    Person person) //w gui cos w stylu on resetdata to pobieram z modelu
{
    this->person = person;

    moveDataFromPersonToModel();
}
