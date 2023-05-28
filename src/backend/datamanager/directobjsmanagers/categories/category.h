#pragma once
#include "../basicdatabasedata.h"

struct Category final
{
    ConstIntData id{"id"};
    StrData color{"color"};
    StrData title{"name"};
    DateData creationDate{"creationDate"};
    ConstIntData owner{"owner"};
};
