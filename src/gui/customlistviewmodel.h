#pragma once
#include <QAbstractListModel>
#include <QMap>
#include <QObject>
#include <QPointer>
#include <QProperty>
#include <functional>
#include <typeinfo>

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
        //        constexpr auto isConstructible = std::is_constructible<QVariant, ReturnType>::value;
        //        return isConstructible ? QVariant(object.*method) : QVariant(0);
        //                   : QVariant::fromValue(object.*method);
    };
}

template<typename T, typename ReturnType>
std::function<void(T &, const QVariant &)> makeUpdateFunction(ReturnType T::*method)
{
    return [method](T &object, const QVariant &variant) {
        object.*method = variant.value<ReturnType>();
    };
}
} // namespace

//class AdapterForQmlModelObject : public QObject
//{
//    Q_OBJECT

//    QAbstractListModel *model;

//    QModelIndex currentIndex;

//public:
//    AdapterForQmlModelObject(QAbstractListModel *modelPointer);

//    void setCurrentIndex(QModelIndex currentIndex);

//    Q_INVOKABLE QVariant get(int role) const;

//    Q_INVOKABLE bool update(const QVariant &variant, int role);
//};

//class AbstractListModelInvokableClass : public QAbstractListModel
//{
//    Q_OBJECT

//    AdapterForQmlModelObject *model;

//public:
//    AbstractListModelInvokableClass(QObject *object);

//    virtual ~AbstractListModelInvokableClass() { delete model; }

//    Q_INVOKABLE AdapterForQmlModelObject *get(int elementIndex);
//};

template<typename T, typename EnumData>
class CustomListModel : public AbstractListModelInvokableClass
{
protected:
    using TemplateType = T;

    QVector<T> m_data;

    QHash<int, QByteArray> names;

    QHash<EnumData, std::function<QVariant(const T &)>> getterActivities;

    QHash<EnumData, std::function<void(T &, const QVariant &)>> updateActivities;

public:
    explicit CustomListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    void setEntries(QVector<T> vector);

    void addEntry(T element);

    QHash<int, QByteArray> roleNames() const override;

    template<typename ReturnType>
    CustomListModel &addPart(EnumData role, ReturnType T::*attributeProperty, const QByteArray &name)
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
};

template<typename ModelStructType, typename EnumRoles>
class FastModelBuilder
{
    QPointer<CustomListModel<ModelStructType, EnumRoles>> model;

public:
    FastModelBuilder(QObject *qobject = nullptr)
        : model(new CustomListModel<ModelStructType, EnumRoles>(qobject))
    {}

    template<typename ReturnType>
    FastModelBuilder &add(EnumRoles role,
                          ReturnType ModelStructType::*attributeProperty,
                          const QByteArray &name)
    {
        model->addPart(role, attributeProperty, name);
        return *this;
    }

    QPointer<CustomListModel<ModelStructType, EnumRoles>> build() { return model; }
};
