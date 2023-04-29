#include "customlistviewmodel.h"
#include "registerboxmodel.h"

template<typename T>
CustomListModel<T>::CustomListModel::CustomListModel(QObject *parent)
    : QAbstractListModel(parent)
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
    if (index.row() < 0 || index.row() >= m_data.count() || !activities.contains(role)) {
        return QVariant();
    }

    const T &entry = m_data.at(index.row());
    return activities[role](entry);
}

template class CustomListModel<EntryFieldModel>;
