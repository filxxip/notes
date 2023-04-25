#pragma once
#include "../basicdatabasedata.h"

struct Category
{
    ConstIntData id{"id"};
    StrData content{"color"};
    StrData title{"name"};
    DateData creationDate{"creationDate"};
};
