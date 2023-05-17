#pragma once

#include "../ids/idsmanager.h"
#include "../overallmanager.h"
#include <optional>

/*DataObject should be class which containt id database attribute**/
template<typename DataObject>
class SingletonObjectManager
{
    std::unique_ptr<IdsManager> idsManager;
    std::shared_ptr<OverallManager<DataObject>> manager;

public:
    SingletonObjectManager() = default;
    SingletonObjectManager(std::unique_ptr<IdsManager> idsManager_,
                           std::shared_ptr<OverallManager<DataObject>> manager_);

    void set(const DataObject &object);

    std::optional<DataObject> get();

    bool isDataAvaible() const;
};
