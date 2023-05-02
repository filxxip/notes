#pragma once

#include "../basicdatabasedata.h"

struct GuiDialog
{
    ConstIntData id{"id"};
    StrData content{"content"};
    StrData title{"title"};
    BoolData isOk{"isOk"};
    BoolData isYes{"isYes"};
    BoolData isNo{"isNo"};
    BoolData isAbort{"isAbort"};
};
