#pragma once

#include "adaptermodel.h"

class AbstractListModelInvokableClass : public QAbstractListModel
{
    Q_OBJECT

    AdapterForQmlModelObject *model;

public:
    AbstractListModelInvokableClass(QObject *object);

    virtual ~AbstractListModelInvokableClass() { delete model; }

    Q_INVOKABLE AdapterForQmlModelObject *get(int elementIndex);
};
