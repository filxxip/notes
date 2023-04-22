#pragma once

#include "../overallmanager.h"
#include "person.h"

class PeopleManager final : public OverallManager<Person>
{
public:
    PeopleManager(std::shared_ptr<DataClient> dataClient_);

    std::optional<Person> get(int index) const override;
};
