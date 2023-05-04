#pragma once

#include <QAbstractListModel>
#include <QObject>

class AdapterForQmlModelObject : public QObject
{
    Q_OBJECT

    QAbstractListModel *model;

    QModelIndex currentIndex;

public:
    AdapterForQmlModelObject(QAbstractListModel *modelPointer);

    void setCurrentIndex(QModelIndex currentIndex);

    Q_INVOKABLE QVariant get(int role) const;

    Q_INVOKABLE bool update(const QVariant &variant, int role);
};
