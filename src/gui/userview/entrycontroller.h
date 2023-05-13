#pragma once

#include <QObject>
#include <QPointer>
#include <QTimer>
#include "../../backend/datamanager/dataclient.h"
#include "../../backend/datamanager/directobjsmanagers/people/peoplemanager.h"
#include "../calendar/calendarcontroller.h"
#include "../cpputils/utils.h"
#include "../customdialog/dialogcontroller.h"
#include "../models/switchermodel.h"
#include "../models/userviewlistmodel.h"
#include "../modelutils/listmodelbuilder.h"
#include "../radiobutton/radiobuttoncontroller.h"
#include "../statuses.h"

class EntryController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(UserViewListModel *model MEMBER model CONSTANT)

protected:
    using EnumStatus = ModelStatuses::PersonComponents;

    QPointer<DialogController> dialogController;

    QPointer<UserViewListModel> model = new UserViewListModel(this);

    void emitSuccessDialogWithClear(int code, Person person);

public:
    EntryController(QPointer<DialogController> dialogController_, QObject *obj = nullptr);

signals:
    void confirm();

    void clear();

    void changingViewOperationSuccess(Person person);

private slots:
    virtual void onConfirmed() = 0;
};
