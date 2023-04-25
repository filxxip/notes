#pragma once
#include "../basicdatabasedata.h"

struct Person
{
    ConstIntData id{"id"};
    StrData name{"name"};
    StrData surname{"surname"};
    StrData country{"country"};
    DateData birthday{"birthday"};
    StrData email{"email"};
    StrData password{"password"};
};
