#pragma once
#include "../basicdatabasedata.h"

#define INJECT_DATABASE_MAP std::map<std::string, int typeid(*this).name()::*> member_map;
#define APPLY_ATTRIBUTE(name) member_map.insert({#name, typeid(*this).name()::##name});

template<typename T>
class DataBaseObjectType
{
protected:
    std::map<std::string, int T::*> member_map;
};

struct Person
{
    ConstIntData id{"id"};
    StrData name{"name"};
    StrData surname{"surname"};
    StrData country{"country"};
    DateData birthday{"birthday"};
    StrData email{"email"};
    StrData password{"password"};

    //    ADD_ID(id)
    //    ADD_ATTRIBUTE(name)
    //    ADD_ATTRIBUTE(surname)
    //    ADD_ATTRIBUTE(country)
    //    ADD_ATTRIBUTE(birthday)
    //    ADD_ATTRIBUTE(email)
    //    ADD_ATTRIBUTE(password)
    /* IDDatabaseData id{"id"};
    DatabaseData name{initMapData("name")};
    DatabaseData surname{initMapData("surname")};
    DatabaseData country{initMapData(
        "country")}; //przymyslec ten update danych oraz jak przetrzymac integer np bo obecnie sie sprawadza do samych string -> qstring
    DatabaseData birthday{initMapData("birthday")};
    DatabaseData email{initMapData("email")};
    DatabaseData password{initMapData("password")}*/
};
