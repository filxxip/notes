#include "basicdatabasedata.h"

BasicDatabaseData::BasicDatabaseData(QString name)
    : __name__(name)
{}

BasicDatabaseData &BasicDatabaseData::operator=(QString other) noexcept
{
    set(std::move(other));
    return *this;
}

IDDatabaseData::IDDatabaseData(QString name)
    : BasicDatabaseData(std::move(name))
{}

void IDDatabaseData::set(QString newvalue)
{
    value = std::move(newvalue);
}

const QString &IDDatabaseData::get() const
{
    return value;
}

void DatabaseData::updateMap(const QString &val,
                             std::shared_ptr<std::unordered_map<QString, QString>> &map)
{
    (*map)[__name__] = val;
    //    if (std::find_if(map->begin(),
    //                     map->end(),
    //                     [this](const auto &pair) { return pair.first == __name__; })
    //        != map->end()) {
    //        map->at(__name__) = val;
    //    } else {
    //        map->insert({__name__, val});
    //    }
}

DatabaseData::DatabaseData(QString name,
                           std::shared_ptr<std::unordered_map<QString, QString>> updatedkeyMap_,
                           std::shared_ptr<std::unordered_map<QString, QString>> keyMap_)
    : BasicDatabaseData(std::move(name))
    , updatedKeyMap(updatedkeyMap_)
    , keyMap(keyMap_)
{}

const QString &DatabaseData::get() const
{
    return keyMap->at(__name__);
}

void DatabaseData::set(QString newvalue)
{
    updateMap(newvalue, keyMap);
    if (canbeupdated) {
        updateMap(newvalue, updatedKeyMap);
    } else {
        canbeupdated = true;
    }
}
