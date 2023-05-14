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
    auto obj = manager->get(0);
    if (obj.has_value()) {
        manager->remove(0);
        return obj;
    }
    return std::nullopt;
}

#include "../people/peoplemanager.h"
template class SingletonObjectManager<Person>;
