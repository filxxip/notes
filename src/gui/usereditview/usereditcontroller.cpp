#include "usereditcontroller.h"
#include <QTime>
#include "../cpputils/utils.h"

namespace {
constexpr const char *NAME = "Name";
constexpr const char *SURNAME = "Surname";
constexpr const char *EMAIL = "Email";
constexpr const char *PASSWORD = "Password";
constexpr const char *COUNTRY = "Country";
} // namespace

//to do
UserEditController::UserEditController(QPointer<CalendarController> calendarController,
                                       QPointer<DialogController> dialogController_,
                                       QObject *obj)
    : UserConfigController(calendarController, dialogController_, obj)
{
    model->setEntries({{EnumStatus::EMAIL, EMAIL},
                       {EnumStatus::PASSWORD, PASSWORD},
                       {EnumStatus::NAME, NAME},
                       {EnumStatus::SURNAME, SURNAME},
                       {EnumStatus::COUNTRY, COUNTRY}});

    connect(this, &EntryController::confirm, [this] { emit updatePersonData(person); });
    connect(this, &UserEditController::remove, [this] {
        emit clear();
        emit removePersonData(person.id.get());
    });
    Person person;
    person.name = "Filip";
    person.surname = "Poltoraczyk";
    person.birthday = QDateTime(QDate(1999, 1, 1), QTime(1, 1, 1));
    person.country = "Polska";
    person.gender = "male";
    person.password = "Pass";
    person.email = "mail";
    setNewPerson(std::move(person));
}

//na przycisk confirm lacze w gui sygnal z updatepersondata, na przycisk reset updates wysylam sygnal do gui i
//jakos odpalam move data from person to model a nastepnie wysylam sygnal reset data ktory w gui jest polaczony
// z funkcjami ktory z modelu przy uzyciu get wlasnego poprawne stare dane i je wrzuca do entryfieldow,
//tam chyba stworze sygnal set text i bedizie cos takiego settext(model.value)
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

void UserEditController::onConfirmed()
{
    //tam na klika updatuje ten model i emituje sygnal zeby sobie tutaj pozmieniac i posprawdzac ->
    //raczej to, tak jak w poprzednich onTextChanged : model.value = text, i jakby bedzie jeden nawrot danych ale mam nadzieje ze to nie zepsuje
    auto name = getPartOfPerson(EnumStatus::NAME);
    auto surname = getPartOfPerson(EnumStatus::SURNAME);
    auto country = getPartOfPerson(EnumStatus::COUNTRY);
    auto password = getPartOfPerson(
        EnumStatus::PASSWORD); //w gui bedzie non stop zmieniany model albo to co wyzej

    auto container = {&password, &name, &surname, &country};

    if (!Validators::fieldsValidator(container)) {
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
