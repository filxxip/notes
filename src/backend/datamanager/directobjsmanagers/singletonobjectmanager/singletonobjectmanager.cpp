#include "singletonobjectmanager.h"

namespace {
constexpr char INVALID_ACCESS[]
    = "Invalid access to database, manager is not empty or name is not correct";
}

template<typename DataObject>
SingletonObjectManager<DataObject>::Status SingletonObjectManager<DataObject>::status
    = SingletonObjectManager::Status::WAIT_FOR_LOAD;

template<typename DataObject>
SingletonObjectManager<DataObject>::SingletonObjectManager(
    std::unique_ptr<IdsManager> idsManager_, std::shared_ptr<OverallManager<DataObject>> manager_)
    : idsManager(std::move(idsManager_))
    , manager(manager_)
{}

template<typename DataObject>
void SingletonObjectManager<DataObject>::addObjectToData(int id)
{
    Ids idObject;
    idObject.index = id;
    idsManager->add(idObject);
}

template<typename DataObject>
std::optional<DataObject> SingletonObjectManager<DataObject>::retrieveObject(const Ids &obj)
{
    idsManager->remove(1);
    return manager->get(obj.index.get());
}

template<typename DataObject>
void SingletonObjectManager<DataObject>::set(const DataObject &object, bool autoReady)
{
    if (auto elements = idsManager->get(); elements.has_value() && elements->size() == 0) {
        addObjectToData(object.id.get());
        if (autoReady) {
            setReadyStatus();
        }
        return;
    }
    qDebug() << INVALID_ACCESS;
}

template<typename DataObject>
std::optional<DataObject> SingletonObjectManager<DataObject>::get()
{
    auto obj = idsManager->getFiltered({{"pid", PidContants::PID_VALUE}});
    if (obj.has_value() && obj->size() > 0) {
        auto retrieve = retrieveObject(obj->at(0));
        status = Status::WAIT_FOR_LOAD;
        return retrieve;
    }
    return std::nullopt;
}

template<typename DataObject>
bool SingletonObjectManager<DataObject>::isDataAvaible() const
{
    return idsManager->get()->size() > 0;
}

template<typename DataObject>
AutoRemoveSingleObjectManager<DataObject>::AutoRemoveSingleObjectManager(
    std::unique_ptr<IdsManager> idsManager_, std::shared_ptr<OverallManager<DataObject>> manager_)
    : SingletonObjectManager<DataObject>(std::move(idsManager_), manager_)
{}

template<typename DataObject>
std::optional<DataObject> AutoRemoveSingleObjectManager<DataObject>::retrieveObject(const Ids &obj)
{
    auto retObj = SingletonObjectManager<DataObject>::retrieveObject(obj);
    if (retObj.has_value()) {
        this->indexesToRemove.push_back(obj.index.get());
    }
    return retObj;
}

template<typename DataObject>
AutoRemoveSingleObjectManager<DataObject>::~AutoRemoveSingleObjectManager()
{
    for (auto index : indexesToRemove) {
        this->manager->remove(index);
    }
}

#include "../people/peoplemanager.h"
template class SingletonObjectManager<Person>;
template class AutoRemoveSingleObjectManager<Person>;
