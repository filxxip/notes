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
    QPointer<UserViewListModel> model = new UserViewListModel;

public:
    EntryController();

signals:
    void confirm();

private slots:
    virtual void onConfirmed() = 0;
};

class RegisterController : public EntryController
{
    Q_OBJECT
public:
    RegisterController();

public slots:
    void onConfirmed() override;
};

class LoginController : public EntryController
{
    Q_OBJECT
public:
    LoginController();

public slots:
    void onConfirmed() override;
};

class GuestController : public EntryController
{
    Q_OBJECT
public:
    GuestController();

public slots:
    void onConfirmed() override;
};
