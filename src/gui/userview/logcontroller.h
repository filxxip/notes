#pragma once
#include <QDebug>
#include <QHash>
#include <QModelIndex>
#include <QObject>
#include <QPointer>
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

    Q_PROPERTY(EntryController *entryController READ getController CONSTANT) //ewentualnie notify

    //    Q_PROPERTY(EnumStatus userViewType MEMBER m_userView NOTIFY userViewChanged)
    Q_PROPERTY(EnumStatus userViewType READ userviewread WRITE userviewwrite NOTIFY userViewChanged)

    Q_PROPERTY(UserSwitcherModel *switcherModel MEMBER switcherModel CONSTANT)
    Q_PROPERTY(bool activityPossible MEMBER m_activity_possible NOTIFY activityStatusChanged)
    Q_PROPERTY(CalendarController *calendarController MEMBER calendarController CONSTANT)
public:
    LogController(QObject *obj = nullptr);

    QPointer<EntryController> getController() { return controllers[m_userView]; }

private:
    EnumStatus m_userView = EnumStatus::LOGIN;
    bool m_activity_possible = true;
    QPointer<CalendarController> calendarController = new CalendarController(this);

    QHash<EnumStatus, QPointer<EntryController>>
        controllers{{EnumStatus::REGISTER, new RegisterController(calendarController, this)},
                    {EnumStatus::LOGIN, new LoginController(this)},
                    {EnumStatus::GUEST, new GuestController(this)}};

    QPointer<UserSwitcherModel> switcherModel;

    void setActivity(bool value);

    EnumStatus userviewread() { return m_userView; }

public slots:
    void onSwitchedChanged(ModelStatuses::UserViews s);

    void userviewwrite(EnumStatus status)
    {
        m_userView = status;
        //        calendarController->clear();
        qDebug() << "Fsdfsdfsdfsd";
        emit userViewChanged();
    }

signals:

    void loginActiveChanged();

    void activityStatusChanged();

    void userViewChanged();
};
