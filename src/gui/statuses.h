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

enum class Roles { PLACEHOLDER = 0, VALUE, COLOR, PASS_STATUS };

Q_ENUM_NS(Roles);

Q_ENUM_NS(MyStatus);

Q_ENUM_NS(PersonComponents);
} // namespace Statuses
