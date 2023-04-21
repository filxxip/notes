#pragma once

#include <QDate>
#include <QString>
#include <algorithm>
#include <memory>
#include <unordered_map>

#include "../dataclient.h"
#include "../pathmanager/path.h"
#include "basicdatabasedata.h"

class BasicForDatabaseStructure
{
protected:
    std::shared_ptr<std::unordered_map<QString, QString>> updatedKeyMap;
    std::shared_ptr<std::unordered_map<QString, QString>> keyMap;
    DatabaseData initMapData(QString name)
    {
        return DatabaseData{std::move(name), updatedKeyMap, keyMap};
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
    DatabaseData name{initMapData("name")};
    DatabaseData surname{initMapData("surname")};
    DatabaseData country{initMapData(
        "country")}; //przymyslec ten update danych oraz jak przetrzymac integer np bo obecnie sie sprawadza do samych string -> qstring
    DatabaseData birthday{initMapData("birthday")};
    DatabaseData email{initMapData("email")};
    DatabaseData password{initMapData("password")};
};
//na template klasa nizej
class PersonManager
{
    //    QString params;
    std::shared_ptr<DataClient> dataClient;

    UrlPath generatePath(int index) const;

    QString generateParms(const std::shared_ptr<std::unordered_map<QString, QString>> &map) const;

public:
    explicit PersonManager(std::shared_ptr<DataClient> dataClient_);

    void update(const Person &person);

    void remove(int index);

    void add(const Person &person);

    std::optional<Person> get(int index) const;
};
