#include "clockcontroller.h"
#include <QStringLiteral>

namespace {
constexpr const char *SECOND = "second";
constexpr const char *MINUTE = "minute";
constexpr const char *HOUR = "hour";
constexpr const char *DAY = "day";
constexpr const char *MONTH = "month";
constexpr const char *YEAR = "year";

constexpr const char *FULL_DATE = "fullDate";


} // namespace

ClockController::ClockController(QObject *obj)
    : QObject(obj)
{
    connect(&timer, &QTimer::timeout, this, &ClockController::updateTime);
    timer.start(999);

    for (const auto &name : {SECOND, MINUTE, HOUR}) {
        clock->insert(name, 0);
    }

    clock->insert(FULL_DATE, "");

    updateTime();
}

void ClockController::updateTime()
{
    auto currentTime = current.currentDateTime();
    auto time = currentTime.time();
    auto date = currentTime.date();

    clock->setProperty(HOUR, time.hour());
    clock->setProperty(MINUTE, time.minute());
    clock->setProperty(SECOND, time.second());

    clock->setProperty(FULL_DATE, DateStringAlternatives::convertToStringFormat(date));
}
