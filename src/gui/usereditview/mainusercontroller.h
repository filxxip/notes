#pragma once
#include <QObject>
#include <QQmlEngine>
#include "../models/switchermodel.h"
#include "../models/userviewlistmodel.h"
#include "../modelutils/listmodelbuilder.h"
#include "../statuses.h"
#include "usereditcontroller.h"

class MainUserController : public QObject
{
    using EnumStatus = ModelStatuses::InnerUserEditViews;
    using UserSwitcherModel
        = CustomListModel<SwitcherModel<EnumStatus>, ModelStatuses::UserViewsRoles>;

    Q_PROPERTY(EnumStatus userViewType MEMBER m_userView NOTIFY userViewChanged)

    Q_PROPERTY(UserSwitcherModel *switcherModel MEMBER switcherModel CONSTANT)

    Q_PROPERTY(UserEditController *userEditController MEMBER userEditController CONSTANT)

    Q_OBJECT
public:
    explicit MainUserController(QPointer<CalendarController> calendarController,
                                QPointer<DialogController> dialogController,
                                QObject *obj = nullptr);

private:
    QPointer<UserSwitcherModel> switcherModel;

    EnumStatus m_userView = EnumStatus::EDIT;

    QPointer<UserEditController> userEditController;

signals:
    void userViewChanged();
};
