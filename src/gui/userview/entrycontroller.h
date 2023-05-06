#pragma once

#include <QObject>
#include <QPointer>
#include <QTimer>
#include "../calendar/calendarcontroller.h"
#include "../models/switchermodel.h"
#include "../models/userviewlistmodel.h"
#include "../modelutils/listmodelbuilder.h"
#include "../statuses.h"

class EntryController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(UserViewListModel *model MEMBER model CONSTANT)

protected:
    QPointer<UserViewListModel> model
        = new UserViewListModel; //window controler kazdy musi miec pointer

public:
    EntryController(QObject *obj = nullptr);

signals:
    void confirm();

private slots:
    virtual void onConfirmed() = 0;
};

class RegisterController : public EntryController
{
    Q_OBJECT

    QPointer<CalendarController> calendarController;

public:
    RegisterController(QPointer<CalendarController> controller, QObject *obj = nullptr);

public slots:
    void onConfirmed() override;
};

class LoginController : public EntryController
{
    Q_OBJECT
public:
    LoginController(QObject *obj = nullptr);

public slots:
    void onConfirmed() override;
};

class GuestController : public EntryController
{
    Q_OBJECT
public:
    GuestController(QObject *obj = nullptr);

public slots:
    void onConfirmed() override;
};
