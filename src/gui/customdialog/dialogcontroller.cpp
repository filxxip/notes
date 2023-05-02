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
    GuiDialog dialog;
    dialog.content.set("xxx");
    dialog.title.set("title");
    dialog.isOk.set(true);
    dialog.isYes.set(true);
    dialog.isNo.set(true);
    addEntry(dialog);
}
