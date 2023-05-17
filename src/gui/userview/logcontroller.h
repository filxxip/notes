#pragma once
#include <QDebug>
#include <QHash>
#include <QModelIndex>
#include <QObject>
#include <QPointer>
#include <QQmlProperty>
#include <QQmlPropertyMap>
#include <QTimer>
#include "../calendar/calendarcontroller.h"
#include "../models/switchermodel.h"
#include "../models/userviewlistmodel.h"
#include "../modelutils/listmodelbuilder.h"
#include "../statuses.h"
#include "../viewcontroller/viewcontroller.h"
#include "entrycontroller.h"

class LogController : public QObject
{
    using EnumStatus = ModelStatuses::UserViews;
    using UserSwitcherModel
        = CustomListModel<SwitcherModel<EnumStatus>, ModelStatuses::UserViewsRoles>;

    Q_OBJECT

    Q_PROPERTY(QQmlPropertyMap *controllers MEMBER ownerData CONSTANT)

    Q_PROPERTY(ViewController *view MEMBER logViewController CONSTANT)

    Q_PROPERTY(UserSwitcherModel *switcherModel MEMBER switcherModel CONSTANT)

    Q_PROPERTY(CalendarController *calendarController MEMBER calendarController CONSTANT)
public:
    LogController(std::shared_ptr<AbstractViewControllerAdapter<ModelStatuses::MainUserViews>>
                      mainViewController,
                  std::shared_ptr<DataClient> dataClient,
                  QPointer<CalendarController> calendarController_,
                  QPointer<DialogController> dialogController_,
                  QObject *obj = nullptr);

private:
    //    EnumStatus m_userView = EnumStatus::LOGIN;
    QPointer<CalendarController> calendarController;

    QHash<EnumStatus, QPointer<EntryController>> controllers;
    QQmlPropertyMap *ownerData = new QQmlPropertyMap(this);

    SingletonObjectManager<Person> logoutManager;

    QPointer<UserSwitcherModel> switcherModel;

    std::shared_ptr<AbstractViewControllerAdapter<ModelStatuses::MainUserViews>> prevViewController;

    QPointer<ViewController> logViewController;

    //    EnumStatus getUserView() const;

    //    void setUserView(EnumStatus newView);

    //signals:
    //    void userViewChanged();

    //    void mainViewChanged(ModelStatuses::MainUserViews mainView);
};

//class ViewController : public QObject
//{
//    Q_OBJECT

//    //    QQmlProperty switcherModel;
//    Q_PROPERTY(QVariant userViewType MEMBER userViewType NOTIFY userViewTypeChanged)

//    QVariant userViewType;

//public:
//    ViewController(QVariant defaultUserType, QObject *obj = nullptr)
//        : QObject(obj)
//        , userViewType(std::move(defaultUserType))
//    {}

//    void setUserViewType(QVariant userViewType)
//    {
//        this->userViewType = userViewType;
//        emit userViewTypeChanged();
//    }

//    template<typename ViewType>
//    ViewType getUserViewType() const
//    {
//        return userViewType.value<ViewType>();
//    }

//signals:
//    void userViewTypeChanged();
//};

//class ViewSwitcherController : public ViewController
//{
//    Q_OBJECT

//    Q_PROPERTY(QObject *switcherModel MEMBER switcherModel CONSTANT)

//    QObject *switcherModel;

//public:
//    ViewSwitcherController(QObject *switcher, QVariant defaultUserType, QObject *obj = nullptr)
//        : ViewController(std::move(defaultUserType), obj)
//        , switcherModel(switcher)
//    {}
//};
