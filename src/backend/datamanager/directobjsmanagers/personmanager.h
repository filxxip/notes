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

class DatabaseData
{
    std::shared_ptr<std::unordered_map<QString, QString>> updatedKeyMap;
    QString __name__;
    std::optional<QString> initValue;

public:
    DatabaseData() = default;
    DatabaseData(QString name, std::shared_ptr<std::unordered_map<QString, QString>> keyMap)
        : __name__(std::move(name))
        , updatedKeyMap(std::move(keyMap))
    {}
    void set(QString newvalue)
    {
        if (!initValue.has_value()) {
            initValue = newvalue;
        } else {
            if (std::find_if(updatedKeyMap->begin(),
                             updatedKeyMap->end(),
                             [this](const auto &pair) { return pair.first == __name__; })
                != updatedKeyMap->end()) {
                updatedKeyMap->at(__name__) = newvalue;
            } else {
                updatedKeyMap->insert({__name__, newvalue});
            }
        }
    }

    DatabaseData &operator=(QString other) noexcept
    {
        qDebug() << other;
        set(std::move(other));
        return *this;
    }
    const QString &get() const { return updatedKeyMap->at(__name__); }
};

class BasicForDatabaseStructure
{

protected:
    std::shared_ptr<std::unordered_map<QString, QString>> updatedKeyMap;
    DatabaseData initData(QString name) { return DatabaseData{name, updatedKeyMap}; }

public:
    BasicForDatabaseStructure()
        : updatedKeyMap(std::make_shared<std::unordered_map<QString, QString>>())
    {}

    std::shared_ptr<std::unordered_map<QString, QString>> getMapOfUpdates() const
    {
        return updatedKeyMap;
    }
};

struct Person : BasicForDatabaseStructure
{
    DatabaseData name{initData("name")};
    DatabaseData surname{initData("surname")};
    DatabaseData country{initData(
        "country")}; //przymyslec ten update danych oraz jak przetrzymac integer np bo obecnie sie sprawadza do samych string -> qstring
    DatabaseData birthday{initData("birthday")};
    DatabaseData email{initData("email")};
    DatabaseData password{initData("password")};
};

class PersonManager
{

    QString params;
    std::shared_ptr<DataClient> dataClient;

    UrlPath generatePath(int index) const;

    QString getContentValue(const json &jsonFile, std::string key) const;

public:
    explicit PersonManager(std::shared_ptr<DataClient> dataClient_);

    PersonManager &addParam(const QString &key, const QString &value);

    void copyParamsFromObjectChanges(const BasicForDatabaseStructure &basic)
    {
        auto &updatesMap = *(basic.getMapOfUpdates().get());
        for (const auto &[key, value] : updatesMap) {
            addParam(key, value);
        }
    }

    void update(int person);

    void remove(int index);

    void add(Person person);

    std::optional<Person> get(int index) const;
};
