#pragma once

#include <QDebug>
#include <QMetaEnum>
#include "../models/calendarmodel.h"
#include "invokablelistmodel.h"
#include <functional>

#define ADD_DATA(role, name) addPart(role, &TemplateType::name);

namespace {
template<typename Value>
QVariant variantFromValue(const Value &value)
{
    constexpr auto isConstructible = std::is_constructible<QVariant, Value>::value;
    if constexpr (isConstructible) {
        return QVariant(value);
    } else {
        return QVariant::fromValue(value);
    }
}

template<typename T, typename ReturnType>
std::function<QVariant(const T &)> makeGetterFunction(ReturnType T::*method)
{
    return [method](const T &object) { return variantFromValue(object.*method); };
}

template<typename T, typename ReturnType>
std::function<QVariant(const T &)> makeGetterFunction(
    std::function<ReturnType(const T &)> getter) //kopia?
{
    return [inner = std::move(getter)](const T &object) mutable {
        return variantFromValue(inner(object));
    };
}

template<typename T, typename ReturnType>
std::function<void(T &, const QVariant &)> makeUpdateFunction(
    ReturnType T::*
        method) //search if there is any operator= which can assign varaint object to object.*method
{
    return [method](T &object, const QVariant &variant) {
        constexpr auto isAssignable = std::is_assignable<ReturnType, QVariant>::value;
        if constexpr (isAssignable) {
            qDebug() << variant;
            object.*method = variant;
        } else {
            object.*method = variant.value<ReturnType>();
        }
    };
}

template<typename T, typename ReturnType>
std::function<void(T &, const QVariant &)>
makeUpdateFunction( //take exacly this type which is in ReturnType
    std::function<void(T &, const ReturnType &)> setter)
{
    return
        [setter = std::move(setter)](
            T &object,
            const QVariant &
                variant) mutable { //can be problem with copying, copy operator, should be const reference
            setter(object, variant.value<ReturnType>());
        };
}

} // namespace

template<typename StructType, typename EnumData>
class CustomListModel : public AbstractListModelInvokableClass
{
    /**Class used to creating cpp models which can be easily used in qml.
     *  To add some attribute use addPart method.
     *  EnumData's instances used in this class should have SOME_ATTR_TO_GET syntax.
     *  Struct that this class will refer to should have someAttrToGet syntax.
     *  Otherwise this class wont be working properly.*/

    void updateNames(EnumData role);

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

    QHash<int, QByteArray> roleNames() const override;

    template<typename ReturnType>
    CustomListModel &addPart(EnumData role, ReturnType StructType::*attributeProperty)
    {
        updateNames(role);
        getterActivities.insert(role, makeGetterFunction(attributeProperty));
        updateActivities.insert(role, makeUpdateFunction(attributeProperty));
        return *this;
    }
    template<typename ReturnType>
    CustomListModel &addPart(EnumData role,
                             std::function<ReturnType(const StructType &)> getter,
                             std::function<void(StructType &, const ReturnType &)> setter)
    {
        updateNames(role);
        getterActivities.insert(role, makeGetterFunction(std::move(getter)));
        updateActivities.insert(role, makeUpdateFunction(std::move(setter)));
        return *this;
    }

    template<typename ReturnType>
    CustomListModel &addPart(EnumData role, std::function<ReturnType(const StructType &)> getter)
    {
        updateNames(role);
        getterActivities.insert(role, makeGetterFunction(std::move(getter)));
        return *this;
    }

    QVariant data(const QModelIndex &index, int role) const override;

    QVariant data(int index, EnumData role) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    template<typename ValueType>
    bool setData(int indexvalue, const ValueType &value, EnumData role)
    {
        return setData(index(indexvalue), variantFromValue(value), static_cast<int>(role));
    }

    bool removeRow(int row, const QModelIndex &parent);

    bool removeRows(int row, int count, const QModelIndex &parent);

    bool removeRows(int row, int count);

    bool removeRow(int row);
};
