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

class AbstractEditController : public EntryController
{
    Q_OBJECT

protected:
    using EntryRoles = ModelStatuses::Roles;

    std::optional<Person> person;

public:
    Q_INVOKABLE virtual void moveDataFromPersonToModel() = 0;

    AbstractEditController(
        std::shared_ptr<PrevEnumViewController> mainViewController,
        std::unique_ptr<SingletonObjectManager<Person>> singletonObjectLogoutManager,
        QPointer<DialogController> dialogController_,
        QObject *obj);

    std::optional<int> getPersonId() const;

public slots:
    virtual void setNewPerson(Person person);

    void onLogout();
signals:
    void resetData();

    void updatePersonData(const Person &person);

    void removePersonData(int id);

    void logout();
};

class GuestEditController : public AbstractEditController
{
    Q_OBJECT

public:
    GuestEditController(std::shared_ptr<PrevEnumViewController> mainViewController,
                        std::unique_ptr<SingletonObjectManager<Person>> singletonObjectLogoutManager,
                        QPointer<DialogController> dialogController_,
                        QObject *obj = nullptr);

    Q_INVOKABLE void moveDataFromPersonToModel() override;

public slots:
    void onConfirmed() override;
};

class UserEditController : public AbstractEditController
{
    Q_OBJECT
    Q_PROPERTY(RadioButtonController *radioButtonController MEMBER radioButtonController CONSTANT)
    Q_PROPERTY(CalendarController *calendarController MEMBER calendarController CONSTANT)

protected:
    QPointer<CalendarController> calendarController;
    QPointer<RadioButtonController> radioButtonController;

public:
    UserEditController(std::shared_ptr<PrevEnumViewController> mainViewController,
                       std::unique_ptr<SingletonObjectManager<Person>> singletonObjectLogoutManager,
                       QPointer<DialogController> dialogController_,
                       QObject *obj = nullptr);

    Q_INVOKABLE void moveDataFromPersonToModel() override;

private slots:
    void onRemove();

public slots:

    void onConfirmed() override;

signals:

    void remove();
};
