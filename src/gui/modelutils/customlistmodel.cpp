#include "customlistmodel.h"

template<typename StructType, typename EnumData>
CustomListModel<StructType, EnumData>::CustomListModel::CustomListModel(QObject *parent)
    : AbstractListModelInvokableClass(parent)
{}

template<typename StructType, typename EnumData>
int CustomListModel<StructType, EnumData>::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_data.count();
}

template<typename StructType, typename EnumData>
void CustomListModel<StructType, EnumData>::setEntries(QVector<StructType> vector)
{
    m_data = std::move(vector);
}

template<typename StructType, typename EnumData>
QHash<int, QByteArray> CustomListModel<StructType, EnumData>::roleNames() const
{
    return names;
}

template<typename StructType, typename EnumData>
QVariant CustomListModel<StructType, EnumData>::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_data.count()
        || !getterActivities.contains(static_cast<EnumData>(role))) {
        return QVariant();
    }

    return getterActivities[static_cast<EnumData>(role)](m_data.at(index.row()));
}

template<typename StructType, typename EnumData>
QVariant CustomListModel<StructType, EnumData>::data(int index, EnumData role) const
{
    return data(this->index(index), static_cast<int>(role));
}

template<typename StructType, typename EnumData>
bool CustomListModel<StructType, EnumData>::setData(const QModelIndex &index,
                                                    const QVariant &value,
                                                    int role)
{
    if (index.row() < 0 || index.row() >= m_data.count()
        || !updateActivities.contains(static_cast<EnumData>(role))) {
        return false;
    }
    updateActivities[static_cast<EnumData>(role)](m_data[index.row()], value);
    emit dataChanged(index, index); // <- this does not trigger a recompution of the view
    return true;
}

template<typename StructType, typename EnumData>
void CustomListModel<StructType, EnumData>::addEntry(StructType element)
{
    m_data.append(std::move(element));
}

#include "customlistmodelregistering.h"
