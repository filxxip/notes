#include "idsmanager.h"
#include <QDateTime>
#include "ids.h"

IdsManager::IdsManager(DatabaseCodes::Names databaseName, std::shared_ptr<DataClient> dataClient_)
    : OverallManager(databaseName, dataClient_)
{}

Ids IdsManager::generateInstance(const json &genson) const
{
    Ids note;
    initObject(genson, note.id, note.index);
    return note;
}

void IdsManager::update(const Ids &object)
{
    updateObject(object.id.get(), object.index);
}

void IdsManager::add(const Ids &object)
{
    addObject(object.index, object.pid);
}
