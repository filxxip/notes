#include "adaptermodel.h"

AdapterForQmlModelObject::AdapterForQmlModelObject(QAbstractListModel *modelPointer)
    : model(modelPointer)
    , QObject()
{}

void AdapterForQmlModelObject::setCurrentIndex(QModelIndex currentIndex)
{
    this->currentIndex = std::move(currentIndex);
}

QVariant AdapterForQmlModelObject::get(int role) const
{
    return model->data(currentIndex, role);
}

bool AdapterForQmlModelObject::update(const QVariant &variant, int role)
{
    return model->setData(currentIndex, variant, role);
}
