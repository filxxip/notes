#pragma once

#include <QDate>
#include <QString>
#include <algorithm>
#include <memory>
#include <unordered_map>

#include "../dataclient.h"
#include "../pathmanager/path.h"

//struct Person
//{
//    QString name;
//    QString surname;
//    QString country;
//    QString birthday;
//    QString email;
//    QString password;
//};

//template<typename T, QString name>
//class DatabaseData
//{
//    T value;

//public:
//    DatabaseData(T value_)
//        : value(value_)
//    {}
//    void set(T newvalue){
//        value = std::move(newvalue);

//    }
//};

//template<QString attributeName>
//class DatabaseData
//{
//    std::unordered_map<QString, QString> updatedKeyMap;
//    QString value;

//public:
//    DatabaseData() = default;
//    DatabaseData(QString value_)
//        : value(value_)
//    {}
//    void set(QString newvalue)
//    {
//        value = std::move(newvalue);
//        updatedKeyMap.insert({attributeName, newvalue});
//    }
//    const QString &get() const { return value; }
//};
class PersonManager;

class BasicDatabaseData
{
protected:
    QString __name__;

public:
    BasicDatabaseData(QString name)
        : __name__(name)
    {}

    virtual void set(QString newvalue) = 0;

    virtual BasicDatabaseData &operator=(QString other) noexcept
    {
        set(std::move(other));
        return *this;
    }
    virtual const QString &get() const = 0;
};

class IDDatabaseData : public BasicDatabaseData
{
protected:
    QString value;

public:
    using BasicDatabaseData::operator=;

    IDDatabaseData(QString name)
        : BasicDatabaseData(std::move(name))
    {}
    virtual BasicDatabaseData &operator=(QString other) noexcept
    {
        return BasicDatabaseData::operator=(std::move(other));
    }

    void set(QString newvalue) override { value = std::move(newvalue); }

    const QString &get() const { return value; }
};

class DatabaseData : public BasicDatabaseData
{
protected:
    std::shared_ptr<std::unordered_map<QString, QString>> updatedKeyMap;

protected:
    void updateMap(const QString &val, std::shared_ptr<std::unordered_map<QString, QString>> &map)
    {
        if (std::find_if(map->begin(),
                         map->end(),
                         [this](const auto &pair) { return pair.first == __name__; })
            != map->end()) {
            map->at(__name__) = val;
        } else {
            map->insert({__name__, val});
        }
    }

public:
    DatabaseData(QString name, std::shared_ptr<std::unordered_map<QString, QString>> keyMap)
        : BasicDatabaseData(std::move(name))
        , updatedKeyMap(keyMap)
    {}

    const QString &get() const { return updatedKeyMap->at(__name__); }
};

//class InitDatabaseData final : public DatabaseData
//{
//public:
//    using BasicDatabaseData::operator=;

//    InitDatabaseData(QString name, std::shared_ptr<std::unordered_map<QString, QString>> keyMap)
//        : DatabaseData(std::move(name), keyMap)
//    {}
//    void set(QString newvalue) override { updateMap(newvalue); }
//};

class UpdatedDatabaseData final : public DatabaseData
{
    std::shared_ptr<std::unordered_map<QString, QString>> keyMap;
    bool canbeupdated = false;

public:
    using BasicDatabaseData::operator=;
    UpdatedDatabaseData(QString name,
                        std::shared_ptr<std::unordered_map<QString, QString>> updatedkeyMap,
                        std::shared_ptr<std::unordered_map<QString, QString>> keyMap_)
        : DatabaseData(std::move(name), updatedkeyMap)
        , keyMap(keyMap_)
    {}
    void set(QString newvalue) override
    {
        updateMap(newvalue, keyMap);
        if (canbeupdated) {
            updateMap(newvalue, updatedKeyMap);
        } else {
            canbeupdated = true;
        }
        //        if (!initValue.has_value()) {
        //            initValue = newvalue;
        //        } else {
        //            wasUpdated = true;
        //            updateMap(newvalue);
        //        }
    }
    const QString &get() const { return keyMap->at(__name__); }
};

class BasicForDatabaseStructure
{
protected:
    std::shared_ptr<std::unordered_map<QString, QString>> updatedKeyMap;
    std::shared_ptr<std::unordered_map<QString, QString>> keyMap;
    UpdatedDatabaseData initMapData(QString name)
    {
        return UpdatedDatabaseData{std::move(name), updatedKeyMap, keyMap};
    }

public:
    BasicForDatabaseStructure()
        : updatedKeyMap(std::make_shared<std::unordered_map<QString, QString>>())
        , keyMap(std::make_shared<std::unordered_map<QString, QString>>())
    {}

    std::shared_ptr<std::unordered_map<QString, QString>> getMapOfUpdates() const
    {
        return updatedKeyMap;
    }
    std::shared_ptr<std::unordered_map<QString, QString>> getMapOfAtrributes() const
    {
        return keyMap;
    }
};

struct Person : public BasicForDatabaseStructure
{

    IDDatabaseData id{"id"};
    UpdatedDatabaseData name{initMapData("name")};
    UpdatedDatabaseData surname{initMapData("surname")};
    UpdatedDatabaseData country{initMapData(
        "country")}; //przymyslec ten update danych oraz jak przetrzymac integer np bo obecnie sie sprawadza do samych string -> qstring
    UpdatedDatabaseData birthday{initMapData("birthday")};
    UpdatedDatabaseData email{initMapData("email")};
    UpdatedDatabaseData password{initMapData("password")};
};
//na template klasa nizej
class PersonManager
{
    //    QString params;
    std::shared_ptr<DataClient> dataClient;

    UrlPath generatePath(int index) const;


public:
    explicit PersonManager(std::shared_ptr<DataClient> dataClient_);

    //    PersonManager &addParam(const QString &key, const QString &value);

    //    void copyParamsFromObjectChanges(const BasicForDatabaseStructure &basic)
    //    {
    //        auto &updatesMap = *(basic.getMapOfUpdates().get());
    //        for (const auto &[key, value] : updatesMap) {
    //            addParam(key, value);
    //        }
    //    }

    void update(const Person &person);

    void remove(int index);

    void add(const Person &person);

    std::optional<Person> get(int index) const;
};
