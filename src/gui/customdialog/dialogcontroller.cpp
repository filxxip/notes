#include "dialogcontroller.h"

DialogViewModel::DialogViewModel(QObject *parent)
    : CustomListModel(parent)
{
    ADD_DATA(ModelStatuses::DialogRoles::CONTENT, content)
    ADD_DATA(ModelStatuses::DialogRoles::IS_OK, isOk)
    ADD_DATA(ModelStatuses::DialogRoles::IS_YES, isYes)
    ADD_DATA(ModelStatuses::DialogRoles::IS_NO, isNo)
    ADD_DATA(ModelStatuses::DialogRoles::TITLE, title)
    ADD_DATA(ModelStatuses::DialogRoles::PATH, path)
}
