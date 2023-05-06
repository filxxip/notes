#pragma once

#include <QDate>
#include <QObject>
#include <QString>
#include <QVariant>
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

    inline operator QVariant() const { return QVariant::fromValue(get()); }

    virtual const T &get() const = 0;

    virtual const QString &getName() const;

    virtual void setBaseOnJson(const json &genson);
};

template<typename T>
class DbData : public BaseData<T>
{
    std::optional<T> initValue;

public:
    DbData() = default;

    DbData(QString name);

    void set(T newvalue) override;

    const T &get() const override;

    const std::optional<T> &getUpdated() const;
};

template<typename T>
class ConstDbData : public BaseData<T>
{
public:
    ConstDbData() = default;

    ConstDbData(QString name);

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


template<typename T>
void to_json(json &j, const BaseData<T> &p);

template<typename T>
void init_from_json(const json &j, BaseData<T> &p);

using IntData = DbData<int>;
using StrData = DbData<QString>;
using DateData = DbData<QDateTime>;
using BoolData = DbData<bool>;

using ConstIntData = ConstDbData<int>;
using ConstStrData = ConstDbData<QString>;
using ConstDateData = ConstDbData<QDateTime>;
using ConstBoolData = ConstDbData<bool>;
