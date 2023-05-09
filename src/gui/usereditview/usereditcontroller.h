#pragma once
#include <QObject>
#include "../../backend/datamanager/directobjsmanagers/people/person.h"
#include "../calendar/calendarcontroller.h"
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

    Person person;

public:
    UserEditController(QPointer<CalendarController> calendarController,
                       QPointer<DialogController> dialogController_,
                       QObject *obj = nullptr);

    //private slots:
    Q_INVOKABLE void moveDataFromPersonToModel();

public slots:
    void setNewPerson(Person person);

    void onConfirmed() override;

signals:
    void resetData();
    ////
    void updatePersonData(const Person &person);

    void remove();

    void removePersonData(int id); //signals taken from upper controller
};

////to do
//class UserEditController : public QObject
//{
//    using EnumStatus = ModelStatuses::PersonComponents;
//    using EntryRoles = ModelStatuses::Roles;

//    Q_OBJECT

//    Q_PROPERTY(CalendarController *calendarController MEMBER calendarController CONSTANT)
//    Q_PROPERTY(UserViewListModel *userViewModel MEMBER model CONSTANT)

//    Person person;
//    QPointer<UserViewListModel> model = new UserViewListModel(this);
//    QPointer<DialogController> dialogController;
//    QPointer<CalendarController> calendarController = new CalendarController(this);
//    QPointer<RadioButtonController> radioButtonController;

//public:
//    UserEditController(QPointer<DialogController> dialogController_, QObject *obj = nullptr);

//    void moveDataFromPersonToModel();

//    void reset();

//public slots:
//    void setNewPerson(Person person);

//    void updatePersonData();

//signals:
//    //    void updatePersonData(const Person &person);

//    void removePersonData(int id); //signals taken from upper controller

//    void clear();

//    void resetData();

//    void confirm();

//    void remove();

//    //wyemitowac sygnal zeby sobie pobral z data jakas dana
//};
