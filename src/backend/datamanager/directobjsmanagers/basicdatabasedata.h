#pragma once

#include <QDate>
#include <QObject>
#include <QString>
#include "overallmanager.h"
#include <algorithm>
#include <memory>
#include <unordered_map>

class UndefinedDataException : public std::exception
{
public:
    UndefinedDataException(std::string error)
        : msg_(std::move(error))
    {}
    virtual const char *what() const noexcept { return msg_.c_str(); }

private:
    std::string msg_;
};

template<typename T>
class BaseData
{
protected:
    QString __name__;
    std::optional<T> value;

public:
    BaseData() = default;
    BaseData(QString name);

    void setName(QString name) { __name__ = std::move(name); }

    virtual void set(T newvalue) = 0;

    //    BaseData<T> &operator=(const BaseData<T> &base) = default;
    //    BaseData(const BaseData<T> &base) = default;

    //    BaseData() = default;
    //    ~BaseData() = default;
    //    BaseData(const BaseData &) = default;
    //    virtual BaseData<T> &operator=(T other) noexcept;

    virtual const T &get() const = 0;

    virtual const QString &getName() const;

    virtual void setBaseOnJson(const json &genson);
};

template<typename T>
class DbData : public BaseData<T>
{
    std::optional<T> initValue;

public:
    //public:
    //    DbData() = default;
    //    ~DbData() = default;
    //    DbData(const DbData &) = default;
    //    using BaseData<T>::operator=;
    //    DbData(const DbData<T> &base) = default;
    //    DbData<T> &operator=(const DbData<T> &base) = default;
    DbData() = default;
    DbData(QString name);

    void set(T newvalue) override;

    const T &get() const override;

    const std::optional<T> &getUpdated() const; //tylko updated i updatuje wtedy kiedy jest zmiana

};

template<typename T>
class ConstDbData : public BaseData<T>
{
public:
    //    using BaseData<T>::operator=;
    //    ConstDbData() = default;
    ConstDbData() = default;
    ConstDbData(QString name);

    //    ConstDbData(const DbData<T> &base) = default;
    //    DbData<T> &operator=(const DbData<T> &base) = default;

    void set(T newvalue) override;

    const T &get() const override;
};

class MyIntData : public QObject, public DbData<int>
{
    Q_OBJECT

    Q_PROPERTY(int value READ get WRITE set NOTIFY settingValueSignal)

public:
    MyIntData(QString name)
        : DbData(name)
        , QObject()
    {}

    void set(int newvalue) override
    {
        DbData::set(newvalue);
        emit settingValueSignal();
    }

signals:
    void settingValueSignal();
};

//class MyClassInt : public QObject, public DbData<int>
//{
//    Q_OBJECT
//    Q_PROPERTY(int value READ get WRITE set NOTIFY valueChanged)

//public:
//    MyClassInt(QString name)
//        : QObject()
//        , DbData(std::move(name))
//    {}
//    void set(int newvalue)
//    {
//        DbData::set(newvalue);
//        emit valueChanged();
//    }
//signals:
//    void valueChanged();
//};
//Q_DECLARE_METATYPE_TEMPLATE_1ARG(BaseData)

//Q_DECLARE_METATYPE_TEMPLATE_1ARG(DbData)

//Q_DECLARE_METATYPE(MyClassInt)

template<typename T>
void to_json(json &j, const BaseData<T> &p);

template<typename T>
void init_from_json(const json &j, BaseData<T> &p);

//template<typename T>
//to_json(json &j, const BaseData<T> &p);

//template<typename T>
//void from_json(const json &j, BaseData<T> &p);
// namespace ns

#define REGISTER_DATA(type) \
    template class BaseData<type>; \
    template class DbData<type>; \
    template class ConstDbData<type>;

using IntData = DbData<int>;
using StrData = DbData<QString>;
using DateData = DbData<QDateTime>;
using BoolData = DbData<bool>;
//Q_DECLARE_METATYPE_TEMPLATE_1ARG(DbData) //ogarnac jak sie dostawac do wartosci

using ConstIntData = ConstDbData<int>;
using ConstStrData = ConstDbData<QString>;
using ConstDateData = ConstDbData<QDateTime>;
using ConstBoolData = ConstDbData<bool>;
