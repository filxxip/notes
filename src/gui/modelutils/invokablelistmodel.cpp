#include "invokablelistmodel.h"

AbstractListModelInvokableClass::AbstractListModelInvokableClass(QObject *object)
    : QAbstractListModel(object)
{
    model = new AdapterForQmlModelObject(this);
    connect(this, &AbstractListModelInvokableClass::rowsInserted, [this] {
        emit rowCountChanged(rowCount());
    });
    connect(this, &AbstractListModelInvokableClass::rowsRemoved, [this] {
        emit rowCountChanged(rowCount());
    });
}

AdapterForQmlModelObject *AbstractListModelInvokableClass::get(int elementIndex)
{
    model->setCurrentIndex(index(elementIndex, 0));
    return model;
}
