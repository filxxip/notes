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
    //    Q_PROPERTY(EntryController *loginController MEMBER controllers[EnumStatus::LOGIN] CONSTANT)
    //    Q_PROPERTY(EntryController *guestController MEMBER controllers[EnumStatus::GUEST] CONSTANT)

    Q_PROPERTY(EntryController *entryController READ getController CONSTANT)

    Q_PROPERTY(
        EnumStatus userViewType READ getUserView WRITE onSwitchedChanged NOTIFY userViewChanged)

    Q_PROPERTY(UserSwitcherModel *switcherModel MEMBER switcherModel CONSTANT)
    Q_PROPERTY(bool activityPossible MEMBER m_activity_possible NOTIFY activityStatusChanged)
    Q_PROPERTY(CalendarController *calendarController MEMBER calendarController CONSTANT)
public:
    LogController(std::shared_ptr<DataClient> dataclient_,
                  QPointer<DialogController> dialogController_,
                  QObject *obj = nullptr);

    QPointer<EntryController> getController() { return controllers[m_userView]; }

    //    Q_INVOKABLE QVariant getMyController(EnumStatus status) { return controllers[status].data(); }

private:
    EnumStatus m_userView = EnumStatus::LOGIN;
    bool m_activity_possible = true;
    QPointer<CalendarController> calendarController = new CalendarController(this);

    QHash<EnumStatus, QPointer<EntryController>> controllers;
    QQmlPropertyMap *ownerData = new QQmlPropertyMap(this);

    QPointer<UserSwitcherModel> switcherModel;

    void setActivity(bool value);

    EnumStatus getUserView() const { return m_userView; }

public slots:
    void onSwitchedChanged(EnumStatus s);

signals:

    void loginActiveChanged();

    void activityStatusChanged();

    void userViewChanged();
};
