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

class EntryController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(UserViewListModel *model MEMBER model CONSTANT)

private:
    QPointer<UserViewListModel> model = new UserViewListModel;

    EntryController()
        : QObject()
    {
        connect(this, &EntryController::confirm, this, &EntryController::onConfirmed);
    }
signals:
    void confirm();

public slots:
    virtual void onConfirmed() = 0;
};

class LogController : public QObject
{
    using EnumStatus = ModelStatuses::UserViews;
    using UserSwitcherModel
        = CustomListModel<SwitcherModel<EnumStatus>, ModelStatuses::UserViewsRoles>;

    Q_OBJECT
    Q_PROPERTY(EnumStatus userViewType MEMBER m_userView NOTIFY userViewChanged)
    Q_PROPERTY(UserViewListModel *loginModel MEMBER loginModel CONSTANT)
    Q_PROPERTY(UserViewListModel *registerModel MEMBER registerModel CONSTANT)
    Q_PROPERTY(UserViewListModel *guestModel MEMBER guestModel CONSTANT)
    Q_PROPERTY(UserSwitcherModel *switcherModel MEMBER switcherModel CONSTANT)
    Q_PROPERTY(bool activityPossible MEMBER m_activity_possible NOTIFY activityStatusChanged)
    Q_PROPERTY(CalendarController *calendarController MEMBER calendarController CONSTANT)
public:
    LogController();

private:
    EnumStatus m_userView = EnumStatus::LOGIN;
    bool m_activity_possible = true;

    //    QHash<EnumStatus, QPointer<UserViewListModel>> models
    //        = {{EnumStatus::LOGIN, new UserViewListModel},
    //           {EnumStatus::REGISTER, new UserViewListModel},
    //           {EnumStatus::GUEST, new UserViewListModel}};
    QPointer<UserViewListModel> loginModel = new UserViewListModel;
    QPointer<UserViewListModel> registerModel = new UserViewListModel;
    QPointer<UserViewListModel> guestModel = new UserViewListModel;

    QPointer<UserSwitcherModel> switcherModel;
    QPointer<CalendarController> calendarController = new CalendarController();

    void setActivity(bool value);

    //    QPointer<UserViewListModel> getUserModel() const { return models[m_userView]; }

private slots:
    void onRegisteringModel();

public slots:
    void onSwitchedChanged(ModelStatuses::UserViews s);

signals:
    void loginActiveChanged();

    void confirmRegister();

    void confirmLogin();

    void confirmGuest();

    //    void registerObjectInModel(); //gdzie to emit

    void activityStatusChanged();

    void userViewChanged();
};
