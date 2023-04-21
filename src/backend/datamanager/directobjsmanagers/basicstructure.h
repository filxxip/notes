#pragma once
#include "basicdatabasedata.h"
#include <memory>

class BasicForDatabaseStructure
{
protected:
    std::shared_ptr<std::unordered_map<QString, QString>> updatedKeyMap;
    std::shared_ptr<std::unordered_map<QString, QString>> keyMap;

    DatabaseData initMapData(QString name);

public:
    BasicForDatabaseStructure();

    std::shared_ptr<std::unordered_map<QString, QString>> getMapOfUpdates() const;

    std::shared_ptr<std::unordered_map<QString, QString>> getMapOfAtrributes() const;
};
