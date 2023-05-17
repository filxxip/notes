#include "singletonobjectmanager.h"

namespace {
constexpr char INVALID_ACCESS[]
    = "Invalid access to database, manager is not empty or name is not correct";
}

template<typename DataObject>
SingletonObjectManager<DataObject>::SingletonObjectManager(
    std::unique_ptr<IdsManager> idsManager_, std::shared_ptr<OverallManager<DataObject>> manager_)
    : idsManager(std::move(idsManager_))
    , manager(manager_)
{}

template<typename DataObject>
void SingletonObjectManager<DataObject>::set(const DataObject &object)
{
    if (auto elements = idsManager->get(); elements.has_value() && elements->size() == 0) {
        Ids id;
        id.index = object.id.get();
        idsManager->add(id);
        return;
    }
    qDebug() << INVALID_ACCESS;
}

template<typename DataObject>
std::optional<DataObject> SingletonObjectManager<DataObject>::get()
{
    auto obj = idsManager->get();
    if (obj.has_value() && obj->size() > 0) {
        idsManager->remove(1);
        return manager->get(obj->at(0).index.get());
    }
    return std::nullopt;
}

template<typename DataObject>
bool SingletonObjectManager<DataObject>::isDataAvaible() const
{
    return idsManager->get()->size() > 0;
}

#include "../people/peoplemanager.h"
template class SingletonObjectManager<Person>;
