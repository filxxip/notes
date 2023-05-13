#pragma once

#include <QObject>

namespace ModelStatuses {

Q_NAMESPACE
Q_CLASSINFO("RegisterEnumClassesUnscoped", "false")

enum class UserViews { REGISTER, LOGIN, GUEST };

enum class UserViewsRoles { TEXT, TYPE };

enum class PersonComponents { EMAIL, PASSWORD, NAME, SURNAME, BIRTHDAY, COUNTRY, CREATED };

enum class Roles { PLACEHOLDER, VALUE, COLOR, PASSWORD_STATUS };

enum class DialogRoles { IS_OK, IS_NO, IS_YES, CONTENT, TITLE, PATH, FONT_SIZE, ID };

enum class CalendarRoles { CONTENT, VALUE, OBJ };

enum class RadioButtonRoles { TEXT, VALUE, GROUP };

enum class InnerUserEditViews { EDIT, NOTEBOOK };

Q_ENUM_NS(InnerUserEditViews);

Q_ENUM_NS(Roles);

Q_ENUM_NS(RadioButtonRoles);

Q_ENUM_NS(UserViewsRoles);

Q_ENUM_NS(UserViews);

Q_ENUM_NS(DialogRoles);

Q_ENUM_NS(PersonComponents);

Q_ENUM_NS(CalendarRoles);

} // namespace ModelStatuses
