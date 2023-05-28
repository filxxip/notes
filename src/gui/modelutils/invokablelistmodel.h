#pragma once

#include "adaptermodel.h"

class AbstractListModelInvokableClass : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(int count READ rowCount NOTIFY rowCountChanged CONSTANT)

    AdapterForQmlModelObject *model;

public:
    AbstractListModelInvokableClass(QObject *object);

    virtual ~AbstractListModelInvokableClass() { delete model; }

    Q_INVOKABLE AdapterForQmlModelObject *get(int elementIndex);

signals:
    void rowCountChanged(int value);
};
