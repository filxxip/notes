#pragma once

#include <QObject>
#include <QPointer>
#include <QVariant>

#include "../models/switchermodel.h"
#include "../modelutils/customlistmodel.h"
#include "../statuses.h"

class ViewController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariant userViewType MEMBER userViewType NOTIFY userViewTypeChanged)

    QVariant userViewType;

public:
    ViewController(QVariant defaultUserType, QObject *obj = nullptr);

    void setUserViewType(QVariant userViewType);

    template<typename ViewType>
    ViewType getUserViewType() const
    {
        return userViewType.value<ViewType>();
    }

signals:
    void userViewTypeChanged();
};

class ViewSwitcherController : public ViewController
{
    Q_OBJECT

    Q_PROPERTY(QObject *switcherModel MEMBER switcherModel CONSTANT)

    QPointer<QObject> switcherModel;

public:
    ViewSwitcherController(QObject *switcher, QVariant defaultUserType, QObject *obj = nullptr);
};

template<typename EnumStatus>
class AbstractViewControllerAdapter
{
    QPointer<ViewController> controller;

public:
    AbstractViewControllerAdapter(QPointer<ViewController> controller_)
        : controller(controller_)
    {}

    EnumStatus getUserViewType() const { return controller->getUserViewType<EnumStatus>(); }

    void setUserViewType(EnumStatus userViewType)
    {
        controller->setUserViewType(QVariant::fromValue(userViewType));
    }

    QPointer<ViewController> getController() const { return controller; }
};

namespace ViewControllerGenerators {
template<typename EnumStatus>
using UserSwitcherModel = CustomListModel<SwitcherModel<EnumStatus>, ModelStatuses::UserViewsRoles>;

template<typename EnumStatus>
std::shared_ptr<AbstractViewControllerAdapter<EnumStatus>> createNonSwitcherViewContorller(
    EnumStatus status, QObject *obj = nullptr)
{
    return std::make_shared<AbstractViewControllerAdapter<EnumStatus>>(
        new ViewController(QVariant::fromValue(status), obj));
}

template<typename EnumStatus>
std::shared_ptr<AbstractViewControllerAdapter<EnumStatus>> createSwitcherViewContorller(
    QPointer<UserSwitcherModel<EnumStatus>> switcherModel, EnumStatus status, QObject *obj = nullptr)
{
    return std::make_shared<AbstractViewControllerAdapter<EnumStatus>>(
        new ViewSwitcherController(switcherModel.data(), QVariant::fromValue(status), obj));
}

} // namespace ViewControllerGenerators
