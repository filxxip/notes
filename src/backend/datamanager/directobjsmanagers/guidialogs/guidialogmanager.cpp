#include "guidialogmanager.h"
#include "guidialog.h"

GuiDialogsManager::GuiDialogsManager(std::shared_ptr<DataClient> dataClient_)
    : OverallManager("guidialogs", dataClient_)
{}

GuiDialog GuiDialogsManager::generateInstance(const json &genson) const
{
    GuiDialog guidialog;
    initObject(guidialog.id,
               guidialog.content,
               guidialog.title,
               guidialog.isOk,
               guidialog.isYes,
               guidialog.isNo,
               guidialog.isAbort);
    return guidialog;
}

void GuiDialogsManager::update(const GuiDialog &object)
{
    updateObject(object.id.get(),
                 object.content,
                 object.title,
                 object.isAbort,
                 object.isOk,
                 object.isNo,
                 object.isYes);
}

void GuiDialogsManager::add(const GuiDialog &object)
{
    addObject(object.content, object.title, object.isAbort, object.isOk, object.isNo, object.isYes);
}
