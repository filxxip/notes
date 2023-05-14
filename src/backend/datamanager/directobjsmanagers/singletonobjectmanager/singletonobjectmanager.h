#pragma once

#include "../overallmanager.h"
#include <optional>

template<typename DataObject>
class SingletonObjectManager
{
    std::unique_ptr<OverallManager<DataObject>> manager;

public:
    SingletonObjectManager(std::unique_ptr<OverallManager<DataObject>> manager_);

    void set(const DataObject &object);

    std::optional<DataObject> get();
};
