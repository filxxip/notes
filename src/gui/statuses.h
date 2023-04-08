#pragma once

#include <QObject>

namespace Statuses {

Q_NAMESPACE
Q_CLASSINFO("RegisterEnumClassesUnscoped", "false")

enum class MyStatus {
    First,
    Second,
    Third
};
Q_ENUM_NS(MyStatus);

}
