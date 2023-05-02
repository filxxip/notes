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
    Q_PROPERTY(bool loginActive MEMBER m_loginActive NOTIFY loginActiveChanged)
    Q_PROPERTY(RegisterViewModel *registerModel MEMBER registerModel CONSTANT)
    Q_PROPERTY(RegisterViewModel *loginModel MEMBER loginModel CONSTANT)
    Q_PROPERTY(
        bool registeringPossible MEMBER m_registeringPossible NOTIFY registeringChanged CONSTANT)

public:
    LogController();

signals:
    void loginActiveChanged(); //jak sie zrobi operator= to moze ten person i template bedzie dzialac

private:
    bool m_loginActive = true;
    bool m_registeringPossible = true;
    QPointer<RegisterViewModel> registerModel = new RegisterViewModel();
    QPointer<RegisterViewModel> loginModel = new RegisterViewModel();

    void setRegistering(bool value);

private slots:
    void onRegisteringModel();

signals:
    void registerConfirmEnter();
    void registerObjectInModel();
    void registeringChanged();
};
