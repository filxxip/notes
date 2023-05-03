#pragma once
#include <QDebug>
#include <QModelIndex>
#include <QObject>
#include <QPointer>
#include <QTimer>
#include "registerboxmodel.h"

class LogController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ModelStatuses::UserViews userView MEMBER m_userView NOTIFY userViewChanged)
    Q_PROPERTY(bool loginActive MEMBER m_loginActive NOTIFY loginActiveChanged)
    Q_PROPERTY(RegisterViewModel *registerModel MEMBER registerModel CONSTANT)
    Q_PROPERTY(RegisterViewModel *loginModel MEMBER loginModel CONSTANT)
    Q_PROPERTY(bool activityPossible MEMBER m_activity_possible NOTIFY activityStatusChanged CONSTANT)

public:
    LogController();

signals:
    void loginActiveChanged(); //jak sie zrobi operator= to moze ten person i template bedzie dzialac

private:
    ModelStatuses::UserViews m_userView = ModelStatuses::UserViews::LOGIN;
    bool m_loginActive = true;
    bool m_activity_possible = true;
    QPointer<RegisterViewModel> registerModel = new RegisterViewModel();
    QPointer<RegisterViewModel> loginModel = new RegisterViewModel();

    void setActivity(bool value);

private slots:
    void onRegisteringModel();

signals:
    void confirmEnter();
    void registerObjectInModel();
    void activityStatusChanged();

    void userViewChanged();
};
