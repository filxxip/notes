#pragma once
#include "../basicdatabasedata.h"
#include <chrono>
#include <ctime>

namespace PidContants {
const inline int PID_VALUE = QDateTime().currentMSecsSinceEpoch();
} // namespace PidContants

struct Ids final
{
    ConstIntData id{"id"};
    IntData index{"index"};
    ConstIntData pid{"pid"};

    Ids() { pid = PidContants::PID_VALUE; }
};
