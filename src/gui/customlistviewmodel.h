#pragma once
#include <QAbstractListModel>
#include <QPointer>
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

class CustomType : public QMap<QString, QVariant>
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
    QVariant &operator[](const QString &key)
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
        return QMap::operator[](key);
    }
};

Q_DECLARE_METATYPE(CustomType)

Q_DECLARE_METATYPE(CustomQVariant)

class SomeInvocableClass : public QAbstractListModel
{
    Q_OBJECT

    int customindex;
    QSharedPointer<QVariantMap> attributes = QSharedPointer<QVariantMap>::
        create(); //ta mapa musi zawierac odnosnik do customlistmodel, emitacja sygnalu odbieranego przez custolismodel

public:
    using QAbstractListModel::QAbstractListModel;

    Q_INVOKABLE void meth() { qDebug() << "Hello world"; }

    //    Q_INVOKABLE QSharedPointer<QVariantMap> getmap() const
    //    {
    //        qDebug() << attributes;
    //        //        QVariantMap map;
    //        //        map.insert("key1", 10);
    //        //        map.insert("key2", 12);
    //        //        return map;
    //        return attributes;
    //    }
    Q_INVOKABLE QMap<QString, QVariant> *get(
        int index) //zadeklarowac enuma i wywolywac po prostu metode set jako q invokable
    {
        qDebug() << "plisss";
        CustomType *customtype = new CustomType();
        customtype->setModel(this);
        customtype->setIndex(index);
        return customtype;
    }
};

template<typename T>
class CustomListModel : public SomeInvocableClass
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
