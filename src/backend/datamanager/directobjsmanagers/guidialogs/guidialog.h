#pragma once

#include "../basicdatabasedata.h"

struct GuiDialog final
{
    ConstIntData id{"id"};
    StrData content{"content"};
    StrData title{"title"};
    BoolData isOk{"isOk"};
    BoolData isYes{"isYes"};
    BoolData isNo{"isNo"};
    StrData path{"path"};
    IntData fontSize{"fontSize"};
};
