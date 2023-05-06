#pragma once

#include "invokablelistmodel.h"
#include <functional>

#define ADD_DATA(role, name) addPart(role, &TemplateType::name, #name);

namespace {
template<typename T, typename ReturnType>
std::function<QVariant(const T &)> makeGetterFunction(ReturnType T::*method)
{
    return [method](const T &object) {
        constexpr auto isConstructible = std::is_constructible<QVariant, ReturnType>::value;
        if constexpr (isConstructible)
            return QVariant(object.*method);
        else
            return QVariant::fromValue(object.*method);
    };
}
} // namespace

template<typename T, typename ReturnType>
std::function<void(T &, const QVariant &)> makeUpdateFunction(ReturnType T::*method)
{
    return [method](T &object, const QVariant &variant) {
        object.*method = variant.value<ReturnType>();
    };
}

template<typename StructType, typename EnumData>
class CustomListModel : public AbstractListModelInvokableClass
{
protected:
    using TemplateType = StructType;

    QVector<StructType> m_data;

    QHash<int, QByteArray> names;

    QHash<EnumData, std::function<QVariant(const StructType &)>> getterActivities;

    QHash<EnumData, std::function<void(StructType &, const QVariant &)>> updateActivities;

public:
    explicit CustomListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    void setEntries(QVector<StructType> vector);

    void addEntry(StructType element);

    QHash<int, QByteArray> roleNames() const override; //Q_META_ENUM

    template<typename ReturnType>
    CustomListModel &addPart(EnumData role,
                             ReturnType StructType::*attributeProperty,
                             const QByteArray &name)
    {
        getterActivities.insert(role, makeGetterFunction(attributeProperty));
        updateActivities.insert(role, makeUpdateFunction(attributeProperty));
        names.insert(static_cast<int>(role), name);
        return *this;
    }

    QVariant data(const QModelIndex &index, int role) const override;

    QVariant data(int index, EnumData role) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    template<typename ValueType>
    bool setData(int indexvalue, const ValueType &value, EnumData role)
    {
        return setData(index(indexvalue), QVariant::fromValue(value), static_cast<int>(role));
    }

    bool removeRow(int row, const QModelIndex &parent)
    {
        if (row < 0 || row >= rowCount(parent)) {
            return false;
        }
        beginRemoveRows(parent, row, row);
        m_data.removeAt(row);
        endRemoveRows();
        return true;
    }
    bool removeRows(int row, int count, const QModelIndex &parent)
    {
        qDebug() << rowCount(parent) << "row count";
        if (row < 0 || row + count > rowCount(parent)) {
            return false;
        }
        qDebug() << "usuwam od indeksu" << row << "liczbe rowna" << count;

        beginRemoveRows(parent, row, row + count - 1);

        // Remove the items from your internal data structure
        // For example, if your model is a list of strings:
        qDebug() << row;
        for (int i = 0; i < count; i++) {
            qDebug() << row + i << "hhhhhhhhhhhhhhhhhh";
            m_data.removeAt(row);
        }

        endRemoveRows();
        return true;
    }

    bool removeRows(int row, int count) { return removeRows(row, count, QModelIndex()); }
    bool removeRow(int row) { return removeRow(row, QModelIndex()); }
};
