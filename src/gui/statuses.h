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

enum class PersonComponents { EMAIL, PASSWORD, NAME, SURNAME, BIRTHDAY, COUNTRY };

Q_ENUM_NS(MyStatus);

Q_ENUM_NS(PersonComponents);
} // namespace Statuses
