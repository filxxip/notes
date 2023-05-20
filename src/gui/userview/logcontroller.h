#pragma once
#include <QDebug>
#include <QHash>
#include <QModelIndex>
#include <QObject>
#include <QPointer>
#include <QQmlProperty>
#include <QQmlPropertyMap>
#include <QTimer>
#include "../calendar/calendarcontroller.h"
#include "../models/switchermodel.h"
#include "../models/userviewlistmodel.h"
#include "../modelutils/listmodelbuilder.h"
#include "../statuses.h"
#include "../viewcontroller/viewcontroller.h"
#include "entrycontroller.h"

class LogController : public QObject
{
    using PrevEnumViewController = AbstractViewControllerAdapter<ModelStatuses::MainUserViews>;
    using EnumStatus = ModelStatuses::UserViews;
    using UserSwitcherModel
        = CustomListModel<SwitcherModel<EnumStatus>, ModelStatuses::UserViewsRoles>;

    Q_OBJECT

    Q_PROPERTY(QQmlPropertyMap *controllers MEMBER ownerData CONSTANT)

    Q_PROPERTY(ViewController *view MEMBER logViewController CONSTANT)

public:
    LogController(std::shared_ptr<PrevEnumViewController> mainViewController,
                  std::shared_ptr<DataClient> dataClient,
                  QPointer<DialogController> dialogController_,
                  QObject *obj = nullptr);

private:

    QHash<EnumStatus, QPointer<EntryController>> controllers;

    QQmlPropertyMap *ownerData = new QQmlPropertyMap(this);

    SingletonObjectManager<Person> logoutManager;

    std::shared_ptr<PrevEnumViewController> prevViewController;

    QPointer<ViewController> logViewController;
};
