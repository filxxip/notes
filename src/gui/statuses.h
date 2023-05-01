#pragma once

#include <QObject>

namespace ModelStatuses {

Q_NAMESPACE
Q_CLASSINFO("RegisterEnumClassesUnscoped", "false")

//enum class MyStatus {
//    First,
//    Second,
//    Third
//};

enum class PersonComponents { EMAIL, PASSWORD, NAME, SURNAME, BIRTHDAY, COUNTRY };

enum class Roles { PLACEHOLDER, VALUE, COLOR, PASS_STATUS };

Q_ENUM_NS(Roles);

//Q_ENUM_NS(MyStatus);

Q_ENUM_NS(PersonComponents);
} // namespace ModelStatuses
