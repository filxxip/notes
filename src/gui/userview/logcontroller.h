#pragma once
#include <QDebug>
#include <QHash>
#include <QModelIndex>
#include <QObject>
#include <QPointer>
#include <QTimer>
#include "../models/switchermodel.h"
#include "../models/userviewlistmodel.h"
#include "../statuses.h"

namespace {
using EnumStatus = ModelStatuses::UserViews;
using UserSwitcherModel = CustomListModel<SwitcherModel<EnumStatus>, ModelStatuses::UserViewsRoles>;
} // namespace

class LogController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(EnumStatus userViewType MEMBER m_userView NOTIFY userViewChanged)
    Q_PROPERTY(UserViewListModel *userModel READ getUserModel NOTIFY userViewChanged CONSTANT)
    Q_PROPERTY(UserSwitcherModel *switcherModel MEMBER switcherModel CONSTANT)
    Q_PROPERTY(bool activityPossible MEMBER m_activity_possible NOTIFY activityStatusChanged)

public:
    LogController();

private:
    EnumStatus m_userView = EnumStatus::LOGIN;
    bool m_activity_possible = true;

    QHash<EnumStatus, QPointer<UserViewListModel>> models
        = {{EnumStatus::LOGIN, new RegisterViewModel},
           {EnumStatus::REGISTER, new RegisterViewModel},
           {EnumStatus::GUEST, new RegisterViewModel}};

    QPointer<UserSwitcherModel> switcherModel;

    void setActivity(bool value);

    QPointer<UserViewListModel> getUserModel() const { return models[m_userView]; }

private slots:
    void onRegisteringModel();

public slots:
    void onSwitchedChanged(ModelStatuses::UserViews s);

signals:
    void loginActiveChanged();

    void confirmEnter();

    void registerObjectInModel(); //gdzie to emit

    void activityStatusChanged();

    void userViewChanged(ModelStatuses::UserViews newView);
};
