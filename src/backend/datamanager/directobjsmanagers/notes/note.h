#pragma once
#include "../basicdatabasedata.h"

struct Note
{
    ConstIntData id{"id"};
    StrData content{"content"};
    StrData title{"title"};
    DateData releaseDate{"releaseDate"};
    IntData owner{"owner"};
    IntData category{"category"};
};
