#include "customlistviewmodel.h"
#include "registerboxmodel.h"

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

template<typename T>
CustomListModel<T>::CustomListModel::CustomListModel(QObject *parent)
    : AbstractListModelInvokableClass(parent)
{}

template<typename T>
int CustomListModel<T>::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_data.count();
}

template<typename T>
void CustomListModel<T>::setEntries(QVector<T> vector)
{
    m_data = std::move(vector);
}

template<typename T>
QHash<int, QByteArray> CustomListModel<T>::roleNames() const
{
    return names;
}

template<typename T>
QVariant CustomListModel<T>::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_data.count() || !getterActivities.contains(role)) {
        return QVariant();
    }

    const T &entry = m_data.at(index.row());
    return getterActivities[role](entry);
}

template<typename T>
QVariant CustomListModel<T>::data(int index, int role) const
{
    return data(this->index(index), role);
}

template<typename T>
bool CustomListModel<T>::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.row() < 0 || index.row() >= m_data.count() || !updateActivities.contains(role)) {
        return false;
    }
    T &entry = m_data[index.row()];
    updateActivities[role](entry, value);
    emit dataChanged(index, index); // <- this does not trigger a recompution of the view
    return true;
}

template<typename T>
void CustomListModel<T>::addEntry(T element)
{
    m_data.append(std::move(element));
}

template class CustomListModel<EntryFieldModel>;
