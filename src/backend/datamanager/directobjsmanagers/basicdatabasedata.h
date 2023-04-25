#pragma once

#include <QDate>
#include <QString>
#include "overallmanager.h"
#include <algorithm>
#include <memory>
#include <unordered_map>

//#define ADD_ATTRIBUTE(name) DatabaseData name{initMapData(#name)};
//#define ADD_ID(name) IDDatabaseData name{#name};

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

//template<typename T>
//class AbstractData
//{
//}

template<typename T>
class DbData
{
    QString __name__;
    std::optional<T> value;
    std::optional<T> initValue;

public:
    DbData(QString name);

    void set(T newvalue);

    virtual DbData<T> &operator=(T other) noexcept;

    const T &get() const;

    const std::optional<T> &getUpdated() const; //tylko updated i updatuje wtedy kiedy jest zmiana

    const QString &getName() const { return __name__; }

    void setBaseOnJson(const json &genson);
};

template<typename T>
class ConstDbData
{
    QString __name__;
    std::optional<T> value;

public:
    const QString &getName() const { return __name__; }
    ConstDbData(QString name);
    void set(T newvalue);

    const T &get() const;
    void setBaseOnJson(const json &genson);
};

using IntData = DbData<int>;
using StrData = DbData<QString>;
using DateData = DbData<QDateTime>;

using ConstIntData = ConstDbData<int>;
using ConstStrData = ConstDbData<QString>;
using ConstDateData = ConstDbData<QDateTime>;
//class BasicDatabaseData
//{
//protected:
//    QString __name__;

//public:
//    BasicDatabaseData(QString name);

//    virtual void set(QString newvalue) = 0;

//    virtual BasicDatabaseData &operator=(QString other) noexcept;

//    virtual const QString &get() const = 0;
//};

//class IDDatabaseData final : public BasicDatabaseData
//{
//protected: //id tez musi isc do mapy????
//    QString value;

//public:
//    using BasicDatabaseData::operator=;

//    IDDatabaseData(QString name);

//    void set(QString newvalue) override;

//    const QString &get() const override;
//};

//class DatabaseData final : public BasicDatabaseData
//{
//    std::shared_ptr<std::unordered_map<QString, QString>> updatedKeyMap;
//    std::shared_ptr<std::unordered_map<QString, QString>> keyMap;
//    bool canbeupdated = false;

//    void updateMap(const QString &val, std::shared_ptr<std::unordered_map<QString, QString>> &map);

//public:
//    using BasicDatabaseData::operator=;

//    DatabaseData(QString name,
//                 std::shared_ptr<std::unordered_map<QString, QString>> updatedkeyMap_,
//                 std::shared_ptr<std::unordered_map<QString, QString>> keyMap_);

//    const QString &get() const override;

//    void set(QString newvalue) override;
//};
