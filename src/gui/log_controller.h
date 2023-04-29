#pragma once

#include <QObject>
#include <QPointer>
#include "registerboxmodel.h"

class LogController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool loginActive MEMBER m_loginActive NOTIFY loginActiveChanged)
    Q_PROPERTY(RegisterViewModel *registerModel MEMBER registerModel CONSTANT)

signals:
    void loginActiveChanged();

private:
    bool m_loginActive;
    QPointer<RegisterViewModel> registerModel = new RegisterViewModel();
};
