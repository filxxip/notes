#pragma once
#include <QAbstractListModel>
#include <QMap>
#include <QObject>
#include <QPointer>
#include <QProperty>
#include <functional>

#define ADD_DATA(role, name) addPart(role, &TemplateType::name, #name);

namespace {
template<typename T, typename ReturnType>
std::function<QVariant(const T &)> makeGetterFunction(ReturnType T::*method)
{
    return [method](const T &object) {
        return QVariant::fromValue<ReturnType>(object.*method);
    }; //not the best way, there are some qtcore classes which can be initialized much faster with normal constructors
}

template<typename T, typename ReturnType>
std::function<void(T &, const QVariant &)> makeUpdateFunction(ReturnType T::*method)
{
    return [method](T &object, const QVariant &variant) {
        object.*method = variant.value<ReturnType>();
    };
}
} // namespace

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

class AbstractListModelInvokableClass : public QAbstractListModel
{
    Q_OBJECT

    AdapterForQmlModelObject *model;

public:
    AbstractListModelInvokableClass(QObject *object);

    virtual ~AbstractListModelInvokableClass() { delete model; }

    Q_INVOKABLE AdapterForQmlModelObject *get(int elementIndex);
};

template<typename T>
class CustomListModel : public AbstractListModelInvokableClass
{
protected:
    using TemplateType = T;

    QVector<T> m_data;

    QHash<int, QByteArray> names;

    QHash<int, std::function<QVariant(const T &)>> getterActivities;

    QHash<int, std::function<void(T &, const QVariant &)>> updateActivities;

public:
    explicit CustomListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    void setEntries(QVector<T> vector);

    void addEntry(T element);

    QHash<int, QByteArray> roleNames() const override;

    template<typename ReturnType>
    CustomListModel &addPart(int role, ReturnType T::*attributeProperty, const QByteArray &name)
    {
        getterActivities.insert(role, makeGetterFunction(attributeProperty));
        updateActivities.insert(role, makeUpdateFunction(attributeProperty));
        names.insert(role, name);
        return *this;
    }

    QVariant data(const QModelIndex &index, int role) const override;

    QVariant data(int index, int role) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    template<typename ValueType>
    bool setData(int indexvalue, const ValueType &value, int role)
    {
        return setData(index(indexvalue), QVariant::fromValue(value), role);
    }
public slots:
    //    void resetModel2()
    //    {
    //        beginResetModel();
    //        endResetModel();
    //    }???
};
