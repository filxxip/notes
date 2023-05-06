#pragma once

#include <QObject>
#include <QPointer>
#include <QTimer>
#include "../../backend/datamanager/dataclient.h"
#include "../calendar/calendarcontroller.h"
#include "../customdialog/dialogcontroller.h"
#include "../models/switchermodel.h"
#include "../models/userviewlistmodel.h"
#include "../modelutils/listmodelbuilder.h"
#include "../statuses.h"

class EntryController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(UserViewListModel *model MEMBER model CONSTANT)

protected:
    QPointer<DialogController> dialogController;

    QPointer<UserViewListModel> model = new UserViewListModel(
        this); //window controler kazdy musi miec pointer

public:
    EntryController(QPointer<DialogController> dialogController_, QObject *obj = nullptr);

signals:
    void confirm();

    void operationSuccess();

private slots:
    virtual void onConfirmed() = 0;
};

class RegisterController : public EntryController
{
    Q_OBJECT

    std::shared_ptr<DataClient> dataClient;

    QPointer<CalendarController> calendarController;

public:
    RegisterController(QPointer<CalendarController> calendarController,
                       std::shared_ptr<DataClient> dataclient_,
                       QPointer<DialogController> dialogController_,
                       QObject *obj = nullptr);

public slots:
    void onConfirmed() override;
};

class LoginController : public EntryController
{
    Q_OBJECT

    std::shared_ptr<DataClient> dataClient;

public:
    LoginController(std::shared_ptr<DataClient> dataclient_,
                    QPointer<DialogController> dialogController_,
                    QObject *obj = nullptr);

public slots:
    void onConfirmed() override;
};

class GuestController : public EntryController
{
    Q_OBJECT
public:
    GuestController(QPointer<DialogController> dialogController_, QObject *obj = nullptr);

public slots:
    void onConfirmed() override;
};
