#pragma once

#include "../overallmanager.h"
#include "ids.h"

class IdsManager final : public OverallManager<Ids>
{
protected:
    Ids generateInstance(const json &genson) const override;

public:
    IdsManager(DatabaseCodes::Names databaseName, std::shared_ptr<DataClient> dataClient_);

    void update(const Ids &object) override;

    void add(const Ids &object) override;
};
