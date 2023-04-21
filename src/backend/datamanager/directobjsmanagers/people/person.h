#pragma once
#include <QDate>
#include <QString>
#include "../overallmanager.h"
#include <algorithm>
#include <memory>
#include <unordered_map>

#include "../../dataclient.h"
#include "../../pathmanager/path.h"
#include "../basicdatabasedata.h"
#include "../basicstructure.h"

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
