#pragma once
#include <QObject>
#include "../../backend/datamanager/directobjsmanagers/people/person.h"
#include "../calendar/calendarcontroller.h"
#include "../customdialog/dialogcontroller.h"
#include "../models/userviewlistmodel.h"
#include "../statuses.h"

class UserEditController : public QObject
{
    using EnumStatus = ModelStatuses::PersonComponents;
    using EntryRoles = ModelStatuses::Roles;

    Q_OBJECT

    Person person;
    QPointer<UserViewListModel> model = new UserViewListModel(this);
    QPointer<DialogController> dialogController;
    QPointer<CalendarController> calendarController = new CalendarController(this);

    UserEditController(QPointer<DialogController> dialogController_, QObject *obj = nullptr);

    void moveDataFromPersonToModel();

    void reset();

public slots:
    void setNewPerson(Person person);
    void updatePersonData();

signals:
    void updatePersonData(const Person &person);

    void removePersonData(int id); //signals taken from upper controller

    void clear();

    void resetData();

    void confirm();

    void remove();

    //wyemitowac sygnal zeby sobie pobral z data jakas dana
};
