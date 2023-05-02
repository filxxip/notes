#include "guidialogmanager.h"
#include "guidialog.h"

GuiDialogsManager::GuiDialogsManager(std::shared_ptr<DataClient> dataClient_)
    : OverallManager("guidialogs", dataClient_)
{}

GuiDialog GuiDialogsManager::generateInstance(const json &genson) const
{
    GuiDialog guidialog;
    guidialog.id.setBaseOnJson(genson);
    guidialog.content.setBaseOnJson(genson);
    guidialog.title.setBaseOnJson(genson);
    guidialog.isOk.setBaseOnJson(genson);
    guidialog.isYes.setBaseOnJson(genson);
    guidialog.isNo.setBaseOnJson(genson);
    guidialog.isAbort.setBaseOnJson(genson);
    return guidialog;
}

void GuiDialogsManager::update(const GuiDialog &object)
{
    setAdditionUpdateParameter(object.content);
    setAdditionUpdateParameter(object.title);
    setAdditionUpdateParameter(object.isAbort);
    setAdditionUpdateParameter(object.isOk);
    setAdditionUpdateParameter(object.isNo);
    setAdditionUpdateParameter(object.isYes);
    dataClient->update(generatePath(object.id.get()));
}

void GuiDialogsManager::add(const GuiDialog &object)
{
    setAdditionAddParameter(object.content);
    setAdditionAddParameter(object.title);
    setAdditionAddParameter(object.isAbort);
    setAdditionAddParameter(object.isOk);
    setAdditionAddParameter(object.isNo);
    setAdditionAddParameter(object.isYes);
    dataClient->add(UrlPath(name));
}
