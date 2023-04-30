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
    LogController()
        : QObject()
    {
        QVector<EntryFieldModel> dataRegister;
        dataRegister.push_back(EntryFieldModel{Statuses::PersonComponents::NAME, "Name..."});
        dataRegister.push_back(EntryFieldModel{Statuses::PersonComponents::SURNAME, "Surname..."});
        dataRegister.push_back(EntryFieldModel{Statuses::PersonComponents::EMAIL, "Email..."});
        dataRegister.push_back(EntryFieldModel{Statuses::PersonComponents::PASSWORD, "Password..."});
        dataRegister.push_back(EntryFieldModel{Statuses::PersonComponents::COUNTRY, "Country..."});
        registerModel->setEntries(std::move(dataRegister));

        QVector<EntryFieldModel> dataLogin;
        dataLogin.push_back(EntryFieldModel{Statuses::PersonComponents::EMAIL, "Login..."});
        auto entry = EntryFieldModel{Statuses::PersonComponents::PASSWORD, "Password..."};
        entry.passwordStatus = true;
        dataLogin.push_back(std::move(entry));
        loginModel->setEntries(std::move(dataLogin));

        connect(this,
                &LogController::registerObjectInModel,
                this,
                &LogController::onRegisteringModel);
    }

signals:
    void loginActiveChanged(); //jak sie zrobi operator= to moze ten person i template bedzie dzialac

private:
    bool m_loginActive;
    bool m_registeringPossible = true;
    QPointer<RegisterViewModel> registerModel = new RegisterViewModel();
    QPointer<RegisterViewModel> loginModel = new RegisterViewModel();

    void setRegistering(bool value)
    {
        m_registeringPossible = value;
        emit registeringChanged();
    }

private slots:
    void onRegisteringModel()
    {
        int passIndex = registerModel->indexOf(Statuses::PersonComponents::PASSWORD);
        auto password = registerModel->data(passIndex, RegisterViewModel::COLOR).value<QString>();
        if (std::none_of(password.begin(), password.end(), [](const QChar &ch) {
                return ch.isUpper();
            })) {
            auto previousColor = registerModel->data(passIndex, RegisterViewModel::COLOR);
            registerModel->setData<QColor>(passIndex, "black", RegisterViewModel::COLOR);
            setRegistering(false);
            emit registeringChanged();
            QTimer::singleShot(2500, [this, previousColor, passIndex]() {
                registerModel->setData(passIndex, previousColor, RegisterViewModel::COLOR);
                setRegistering(true);
            });
        }
    }

signals:
    void registerConfirmEnter();
    void registerObjectInModel();
    void registeringChanged();
};
