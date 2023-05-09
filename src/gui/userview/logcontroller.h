#pragma once
#include <QDebug>
#include <QHash>
#include <QModelIndex>
#include <QObject>
#include <QPointer>
#include <QQmlPropertyMap>
#include <QTimer>
#include "../calendar/calendarcontroller.h"
#include "../models/switchermodel.h"
#include "../models/userviewlistmodel.h"
#include "../modelutils/listmodelbuilder.h"
#include "../statuses.h"
#include "entrycontroller.h"

class LogController : public QObject
{
    using EnumStatus = ModelStatuses::UserViews;
    using UserSwitcherModel
        = CustomListModel<SwitcherModel<EnumStatus>, ModelStatuses::UserViewsRoles>;

    Q_OBJECT

    Q_PROPERTY(QQmlPropertyMap *controllers MEMBER ownerData CONSTANT)

    Q_PROPERTY(EnumStatus userViewType READ getUserView WRITE setUserView NOTIFY userViewChanged)

    Q_PROPERTY(UserSwitcherModel *switcherModel MEMBER switcherModel CONSTANT)

    Q_PROPERTY(CalendarController *calendarController MEMBER calendarController CONSTANT)
public:
    LogController(std::shared_ptr<DataClient> dataclient_,
                  QPointer<DialogController> dialogController_,
                  QObject *obj = nullptr);

private:
    EnumStatus m_userView = EnumStatus::LOGIN;
    QPointer<CalendarController> calendarController = new CalendarController(this);

    QHash<EnumStatus, QPointer<EntryController>> controllers;
    QQmlPropertyMap *ownerData = new QQmlPropertyMap(this);

    QPointer<UserSwitcherModel> switcherModel;

    EnumStatus getUserView() const;

    void setUserView(EnumStatus newView);

signals:
    void userViewChanged();
};
