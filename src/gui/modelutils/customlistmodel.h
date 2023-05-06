#pragma once

#include <QMetaEnum>
#include "invokablelistmodel.h"
#include <functional>

#define ADD_DATA(role, name) addPart(role, &TemplateType::name);

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

template<typename T, typename ReturnType>
std::function<void(T &, const QVariant &)> makeUpdateFunction(ReturnType T::*method)
{
    return [method](T &object, const QVariant &variant) {
        object.*method = variant.value<ReturnType>();
    };
}

QByteArray convertUnderscoreToCamelCase(const char *str)
{
    QString suppertStr(str);
    QString result;
    bool capNext = false;
    for (auto c : suppertStr) {
        if (c != '_') {
            result.append(capNext ? c : c.toLower());
            capNext = false;
        } else {
            capNext = true;
        }
    }
    return result.toUtf8();
} //where to store it
} // namespace

template<typename StructType, typename EnumData>
class CustomListModel : public AbstractListModelInvokableClass
{
    /**Class used to creating cpp models which can be easily used in qml.
     *  To add some attribute use addPart method.
     *  EnumData's instances used in this class should have SOME_ATTR_TO_GET syntax.
     *  Struct that this class will refer to should have someAttrToGet syntax.
     *  Otherwise this class wont be working properly.*/

protected:
    using TemplateType = StructType;

    QMetaEnum metaEnum;

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
    CustomListModel &addPart(EnumData role, ReturnType StructType::*attributeProperty)
    {
        auto intenum = static_cast<int>(role);
        auto attributeQMLName = convertUnderscoreToCamelCase(metaEnum.valueToKey(intenum));
        getterActivities.insert(role, makeGetterFunction(attributeProperty));
        updateActivities.insert(role, makeUpdateFunction(attributeProperty));
        names.insert(intenum, attributeQMLName);
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

    bool removeRow(int row, const QModelIndex &parent);

    bool removeRows(int row, int count, const QModelIndex &parent);

    bool removeRows(int row, int count);

    bool removeRow(int row);
};
