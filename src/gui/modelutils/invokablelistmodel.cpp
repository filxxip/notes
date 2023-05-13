#include "invokablelistmodel.h"

AbstractListModelInvokableClass::AbstractListModelInvokableClass(QObject *object)
    : QAbstractListModel(object)
{
    model = new AdapterForQmlModelObject(this);
}

AdapterForQmlModelObject *AbstractListModelInvokableClass::get(int elementIndex)
{
    model->setCurrentIndex(index(elementIndex, 0));
    return model;
}
