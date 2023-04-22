#pragma once
#include "../basicstructure.h"

struct Person : public BasicForDatabaseStructure
{
    ADD_ID(id)
    ADD_ATTRIBUTE(name)
    ADD_ATTRIBUTE(surname)
    ADD_ATTRIBUTE(country)
    ADD_ATTRIBUTE(birthday)
    ADD_ATTRIBUTE(email)
    ADD_ATTRIBUTE(password)
    /* IDDatabaseData id{"id"};
    DatabaseData name{initMapData("name")};
    DatabaseData surname{initMapData("surname")};
    DatabaseData country{initMapData(
        "country")}; //przymyslec ten update danych oraz jak przetrzymac integer np bo obecnie sie sprawadza do samych string -> qstring
    DatabaseData birthday{initMapData("birthday")};
    DatabaseData email{initMapData("email")};
    DatabaseData password{initMapData("password")}*/
};
