#pragma once
#include "../basicdatabasedata.h"

struct Note final
{
    ConstIntData id{"id"};
    StrData content{"content"};
    StrData title{"title"};
    DateData releaseDate{"releaseDate"};
    IntData owner{"owner"};
    IntData category{"category"};
};
