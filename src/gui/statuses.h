#pragma once

#include <QObject>

namespace ModelStatuses {

Q_NAMESPACE
Q_CLASSINFO("RegisterEnumClassesUnscoped", "false")

enum class UserViews { REGISTER, LOGIN, GUEST };

enum class UserViewsRoles { TEXT, TYPE };

enum class PersonComponents { EMAIL, PASSWORD, NAME, SURNAME, BIRTHDAY, COUNTRY };

enum class Roles { PLACEHOLDER, VALUE, COLOR, PASS_STATUS };

enum class DialogRoles { IS_OK, IS_NO, IS_YES, CONTENT, TITLE, PATH, FONT_SIZE };

Q_ENUM_NS(Roles);

Q_ENUM_NS(UserViewsRoles);

Q_ENUM_NS(UserViews);

Q_ENUM_NS(DialogRoles);

Q_ENUM_NS(PersonComponents);

} // namespace ModelStatuses
