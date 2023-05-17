#include "viewcontroller.h"

ViewController::ViewController(QVariant defaultUserType, QObject *obj)
    : QObject(obj)
    , userViewType(std::move(defaultUserType))
{}

void ViewController::setUserViewType(QVariant userViewType)
{
    this->userViewType = userViewType;
    emit userViewTypeChanged();
}

ViewSwitcherController::ViewSwitcherController(QObject *switcher,
                                               QVariant defaultUserType,
                                               QObject *obj)
    : ViewController(std::move(defaultUserType), obj)
    , switcherModel(switcher)
{}

//namespace ViewControllerGenerators {
//template<typename EnumStatus>
//using UserSwitcherModel = CustomListModel<SwitcherModel<EnumStatus>, ModelStatuses::UserViewsRoles>;

//template<typename EnumStatus>
//std::shared_ptr<AbstractViewControllerAdapter<EnumStatus>> createNonSwitcherViewContorller(
//    EnumStatus status, QObject *obj)
//{
//    return std::make_shared<AbstractViewControllerAdapter<EnumStatus>>(
//        new ViewController(QVariant::fromValue(status), obj));
//}

//template<typename EnumStatus>
//std::shared_ptr<AbstractViewControllerAdapter<EnumStatus>> createSwitcherViewContorller(
//    QPointer<UserSwitcherModel<EnumStatus>> switcherModel, EnumStatus status, QObject *obj)
//{
//    return std::make_shared<AbstractViewControllerAdapter<EnumStatus>>(
//        new ViewSwitcherController(switcherModel, QVariant::fromValue(status), obj));
//}

//} // namespace ViewControllerGenerators
