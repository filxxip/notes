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
    ADD_DATA(ModelStatuses::DialogRoles::FONT_SIZE, fontSize)
    GuiDialog dialog;
    dialog.content.set("xxxxfsdgfsdsdxxxfsdgfsdsdxxxfsdgfsdsdxxxfsdgfsdsdxxxfsdgfsdsdxfsdgfsdsdx");
    dialog.title.set("Incorrect Data");
    dialog.isOk.set(true);
    dialog.isYes.set(true);
    dialog.isNo.set(true);
    dialog.path.set("qrc:/resources/information.png");
    dialog.fontSize.set(13);
    addEntry(dialog);
}
