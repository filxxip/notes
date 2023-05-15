#include "singletonobjectmanager.h"

namespace {
constexpr char INVALID_ACCESS[]
    = "Invalid access to database, manager is not empty or name is not correct";
}

template<typename DataObject>
SingletonObjectManager<DataObject>::SingletonObjectManager(
    std::unique_ptr<OverallManager<DataObject>> manager_)
    : manager(std::move(manager_))
{}

template<typename DataObject>
void SingletonObjectManager<DataObject>::set(const DataObject &object)
{
    if (auto elements = manager->get(); elements.has_value() && elements->size() == 0) {
        manager->add(object);
        return;
    }
    qDebug() << INVALID_ACCESS;
}

template<typename DataObject>
std::optional<DataObject> SingletonObjectManager<DataObject>::get()
{
    auto obj = manager->get();
    if (obj->size() > 0) {
        manager->remove(1);
        return obj->at(0);
    }
    return std::nullopt;
}

template<typename DataObject>
bool SingletonObjectManager<DataObject>::isDataAvaible() const
{
    return manager->get()->size() > 0;
}

#include "../people/peoplemanager.h"
template class SingletonObjectManager<Person>;
