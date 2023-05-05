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

protected:
    QPointer<UserViewListModel> model = new UserViewListModel;

public:
    EntryController()
        : QObject()
    {
        connect(this, &EntryController::confirm, this, &EntryController::onConfirmed);
    }
signals:
    void confirm();

private slots:
    virtual void onConfirmed() = 0;
};

class RegisterController : public EntryController
{
    Q_OBJECT
public:
    RegisterController()
        : EntryController()
    {
        model->setEntries({{ModelStatuses::PersonComponents::NAME, "Name..."},
                           {ModelStatuses::PersonComponents::SURNAME, "Surname..."},
                           {ModelStatuses::PersonComponents::EMAIL, "Email..."},
                           {ModelStatuses::PersonComponents::PASSWORD, "Password..."},
                           {ModelStatuses::PersonComponents::COUNTRY, "Country..."},
                           {ModelStatuses::PersonComponents::BIRTHDAY, "Birthday..."}});
    }
public slots:
    void onConfirmed() override { qDebug() << "register"; }
};
class LoginController : public EntryController
{
    Q_OBJECT
public:
    LoginController()
        : EntryController()
    {
        model->setEntries({{ModelStatuses::PersonComponents::EMAIL, "Login..."},
                           {ModelStatuses::PersonComponents::PASSWORD, "Password..."}});
        model->setData(1, true, ModelStatuses::Roles::PASS_STATUS);
    }
public slots:
    void onConfirmed() override { qDebug() << "login"; }
};
class GuestController : public EntryController
{
    Q_OBJECT
public:
    GuestController()
        : EntryController()
    {
        model->setEntries({{ModelStatuses::PersonComponents::NAME, "Temporary name..."}});
    }
public slots:
    void onConfirmed() override { qDebug() << "guest"; }
};

class LogController : public QObject
{
    using EnumStatus = ModelStatuses::UserViews;
    using UserSwitcherModel
        = CustomListModel<SwitcherModel<EnumStatus>, ModelStatuses::UserViewsRoles>;

    Q_OBJECT

    Q_PROPERTY(EntryController *entryController READ getController CONSTANT) //ewentualnie notify

    Q_PROPERTY(EnumStatus userViewType MEMBER m_userView NOTIFY userViewChanged)
    //    Q_PROPERTY(UserViewListModel *loginModel MEMBER loginModel CONSTANT)
    //    Q_PROPERTY(UserViewListModel *registerModel MEMBER registerModel CONSTANT)
    //    Q_PROPERTY(UserViewListModel *guestModel MEMBER guestModel CONSTANT)
    Q_PROPERTY(UserSwitcherModel *switcherModel MEMBER switcherModel CONSTANT)
    Q_PROPERTY(bool activityPossible MEMBER m_activity_possible NOTIFY activityStatusChanged)
    Q_PROPERTY(CalendarController *calendarController MEMBER calendarController CONSTANT)
public:
    LogController();

    QPointer<EntryController> getController() { return controllers[m_userView]; }

private:
    EnumStatus m_userView = EnumStatus::LOGIN;
    bool m_activity_possible = true;

    //    QHash<EnumStatus, QPointer<UserViewListModel>> models
    //        = {{EnumStatus::LOGIN, new UserViewListModel},
    //           {EnumStatus::REGISTER, new UserViewListModel},
    //           {EnumStatus::GUEST, new UserViewListModel}};
    QHash<EnumStatus, QPointer<EntryController>> controllers{{EnumStatus::REGISTER,
                                                              new RegisterController},
                                                             {EnumStatus::LOGIN,
                                                              new LoginController},
                                                             {EnumStatus::GUEST,
                                                              new GuestController}};

    //    QPointer<UserViewListModel> loginModel = new UserViewListModel;
    //    QPointer<UserViewListModel> registerModel = new UserViewListModel;
    //    QPointer<UserViewListModel> guestModel = new UserViewListModel;

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

    //    void confirmRegister();

    //    void confirmLogin();

    //    void confirmGuest();

    //    void registerObjectInModel(); //gdzie to emit

    void activityStatusChanged();

    void userViewChanged();
};
