#pragma once

#include "../ids/idsmanager.h"
#include "../overallmanager.h"
#include <optional>

/*DataObject should be class which containt id database attribute**/
template<typename DataObject>
class SingletonObjectManager
{
    std::unique_ptr<IdsManager> idsManager;

protected:
    std::shared_ptr<OverallManager<DataObject>> manager;

    virtual void addObjectToData(int id);

    virtual std::optional<DataObject> retrieveObject(const Ids &obj);

public:
    enum class Status { READY_TO_GET, WAIT_FOR_LOAD };
    static Status status;

    SingletonObjectManager(std::unique_ptr<IdsManager> idsManager_,
                           std::shared_ptr<OverallManager<DataObject>> manager_);

    virtual ~SingletonObjectManager() = default;

    void set(const DataObject &object, bool autoReady = false);

    std::optional<DataObject> get();

    bool isDataAvaible() const;

    inline static void setReadyStatus() { status = Status::READY_TO_GET; }
};

template<typename DataObject>
class AutoRemoveSingleObjectManager : public SingletonObjectManager<DataObject>
{
    std::vector<int> indexesToRemove;

public:
    AutoRemoveSingleObjectManager(std::unique_ptr<IdsManager> idsManager_,
                                  std::shared_ptr<OverallManager<DataObject>> manager_);

    ~AutoRemoveSingleObjectManager();

protected:
    std::optional<DataObject> retrieveObject(const Ids &obj) override;
};
