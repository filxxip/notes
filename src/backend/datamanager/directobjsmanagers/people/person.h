#pragma once
#include <QObject>
#include "../../../../gui/cpputils/utils.h"
#include "../basicdatabasedata.h"

struct Person final
{
    ConstIntData id{"id"};
    StrData name{"name"};
    StrData surname{"surname"};
    StrData country{"country"};
    DateData birthday{"birthday"};
    DateData created{"created"};
    StrData email{"email"};
    StrData password{"password"};
    CodedStrData gender{"gender", {{0, DatabaseCodes::MALE}, {1, DatabaseCodes::FEMALE}}};
};
