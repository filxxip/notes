#pragma once

#include "../overallmanager.h"
#include "person.h"
#include <functional>

class PeopleManager final : public OverallManager<Person>
{
protected:
    Person generateInstance(const json &genson) const override;

public:
    PeopleManager(std::shared_ptr<DataClient> dataClient_);

    void update(const Person &object) override;

    void add(const Person &object) override;
};
