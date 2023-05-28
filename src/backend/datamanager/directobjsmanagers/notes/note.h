#pragma once
#include "../basicdatabasedata.h"

struct Note final
{
    ConstIntData id{"id"};
    StrData content{"content"};
    StrData title{"title"};
    DateData releaseDate{"releaseDate"};
    ConstIntData owner{"owner"};
    IntData category{"category"};
};
