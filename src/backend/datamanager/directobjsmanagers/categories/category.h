#pragma once
#include "../basicstructure.h"

struct Category : public BasicForDatabaseStructure
{
    ADD_ID(id)
    ADD_ATTRIBUTE(color)
    ADD_ATTRIBUTE(creationDate)
    ADD_ATTRIBUTE(name)
};
