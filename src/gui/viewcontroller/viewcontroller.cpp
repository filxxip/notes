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
