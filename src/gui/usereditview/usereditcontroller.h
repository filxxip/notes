#pragma once
#include <QObject>
#include "../../backend/datamanager/directobjsmanagers/people/person.h"
#include "../cpputils/utils.h"
#include "../customdialog/dialogcontroller.h"
#include "../models/userviewlistmodel.h"
#include "../radiobutton/radiobuttoncontroller.h"
#include "../statuses.h"
#include "../userview/entrycontroller.h"
#include "../userview/specificcontrollers/registercontroller.h"

class UserEditController : public UserConfigController
{
    Q_OBJECT
    using EntryRoles = ModelStatuses::Roles;

    std::optional<Person> person;

public:
    UserEditController(std::unique_ptr<SingletonObjectManager<Person>> singletonObjectLogoutManager,
                       QPointer<CalendarController> calendarController,
                       QPointer<DialogController> dialogController_,
                       QObject *obj = nullptr);

    Q_INVOKABLE void moveDataFromPersonToModel();

private slots:
    void onRemove();

public slots:
    void setNewPerson(Person person);

    void onConfirmed() override;

    void onLogout();

signals:
    void resetData();

    void updatePersonData(const Person &person);

    void remove();

    void logout();

    void removePersonData(int id);
};
