#pragma once
#include <QAbstractListModel>
#include <QMap>
#include <QObject>
#include <QPointer>
#include <QProperty>
#include <QQmlPropertyMap>
#include <QSharedPointer>
#include <QVariantMap>
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

//class CustomQVariantList : public QVariantMap{

//};

class MyCustomClass : public QObject
{
    Q_OBJECT
public:
    explicit MyCustomClass(QObject *parent = nullptr)
        : QObject(parent)
    {}

    QVariantMap properties;

    Q_INVOKABLE void set(const QString &key, const QVariant &value)
    {
        if (properties.value(key) != value) {
            properties[key] = value;
            emit propertyChanged(key);
        }
    }

    Q_INVOKABLE QVariant get(const QString &key) const { return properties.value(key); }

    Q_INVOKABLE QVariant operator[](const QString &key) const { return get(key); }

signals:
    void propertyChanged(const QString &key);
};
class CustomQVariant : public QVariant
{
    QAbstractListModel *model;
    int customindex;
    int role;

public:
    using QVariant::QVariant;
    void setRole(int role) { this->role = role; }
    void setModel(QAbstractListModel *model) { this->model = model; }
    QVariant &operator=(QVariant &qvariant)
    {
        model->setData(model->index(customindex), qvariant, role);
        return *this;
    }
};

class CustomType : public QVariantMap
{
    QAbstractListModel *model;
    int customindex;

public:
    using QMap::QMap;

    void setModel(QAbstractListModel *model) { this->model = model; }
    void setIndex(int id) { customindex = id; }
    QVariant insert(const QString &key, const QVariant &value)
    {
        qDebug() << "wchodze tututututut" << value;
        //        CustomQVariant variant;
        //        auto hashmap = model->roleNames();
        //        for (auto keys = hashmap.keys(); const auto &key : keys) {
        //            if (hashmap[key] == role) {
        //                variant.setRole(key);
        //            }
        //        }
        //        variant.setModel(model);
        //        QMap<QString, QVariant>::insert(key, value);
        return QVariant();
    }
    Q_INVOKABLE QVariant &operator[](QVariant key)
    {
        qDebug() << "wchodze tututututut" << key;
        //        CustomQVariant variant;
        //        auto hashmap = model->roleNames();
        //        for (auto keys = hashmap.keys(); const auto &key : keys) {
        //            if (hashmap[key] == role) {
        //                variant.setRole(key);
        //            }
        //        }
        //        variant.setModel(model);
        //        QMap<QString, QVariant>::insert(key, value);
        auto varr = QVariant();
        return QMap::operator[](key.value<QString>());
    }
};

Q_DECLARE_METATYPE(CustomType)

Q_DECLARE_METATYPE(CustomQVariant)

class MyMap : public QObject
{
    Q_OBJECT

    //    Q_PROPERTY(QVariant operator[] READ getAtIndex NOTIFY isInserted)

public slots:
    void insert(QString key, QVariant value)
    {
        _map.insert(key, value);
        emit isInserted(value);
    }

public:
    using QObject::QObject;
    Q_INVOKABLE QVariant operator[](QString key) const
    {
        qDebug() << "prosze a";
        return _map.operator[](key);
    }

    Q_INVOKABLE QVariant &method(const QString &key)
    {
        qDebug() << "prosze a";
        return _map.operator[](key);
    }
signals:
    void isInserted(QVariant key);

private:
    QMap<QString, QVariant> _map;
};

class AbstractListModelInvokableClass : public QAbstractListModel
{
    Q_OBJECT
    int customindex;
    QSharedPointer<QQmlPropertyMap> propertyMap = QSharedPointer<QQmlPropertyMap>();

private slots:
    void onMapUpdated(const QString &key, const QVariant &value)
    {
        auto id = getKeyByName(key);
        if (id.has_value()) {
            setData(index(customindex), value, id.value());
            propertyMap.clear();
        } else {
            qDebug() << "Property undefined : " << key;
        }
    }

protected:
    virtual std::optional<int> getKeyByName(const QString &name) = 0;

public:
    AbstractListModelInvokableClass(QObject *parent = nullptr)
        : QAbstractListModel(parent)
    {
        connect(propertyMap.data(),
                &QQmlPropertyMap::valueChanged,
                this,
                &AbstractListModelInvokableClass::onMapUpdated);
    }

    Q_INVOKABLE MyCustomClass *get(int elementIndex)
    {
        MyCustomClass *t = new MyCustomClass();
        customindex = elementIndex;
        return t;
    }
    Q_INVOKABLE bool update(int indexxx, const QVariant &value, int role)
    {
        qDebug() << "XDDD";
        return setData(index(indexxx), value, role);
    }
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

    std::optional<int> getKeyByName(const QString &name)
    {
        auto hashmap = roleNames();
        for (auto keys = names.keys(); const auto &key : keys) {
            if (hashmap[key] == name) {
                return key;
            }
        }
        return std::nullopt;
    }

public:
    explicit CustomListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    void setEntries(QVector<T> vector);

    QHash<int, QByteArray> roleNames() const;

    template<typename ReturnType>
    CustomListModel &addPart(int role, ReturnType T::*attributeProperty, const QByteArray &name)
    {
        getterActivities.insert(role, makeGetterFunction(attributeProperty));
        updateActivities.insert(role, makeUpdateFunction(attributeProperty));
        names.insert(role, name);
        return *this;
    }

    QVariant data(const QModelIndex &index, int role) const;

    QVariant data(int index, int role) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override
    {
        if (index.row() < 0 || index.row() >= m_data.count() || !updateActivities.contains(role)) {
            return false;
        }
        T &entry = m_data[index.row()];
        updateActivities[role](entry, value);
        emit dataChanged(index, index); // <- this does not trigger a recompution of the view
        return true;
    }
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
