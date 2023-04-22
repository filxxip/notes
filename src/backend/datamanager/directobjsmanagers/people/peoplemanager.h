#pragma once

#include "../overallmanager.h"
#include "person.h"

class PeopleManager final : public OverallManager<Person>
{
protected:
    Person generateInstance(const json &genson) const override;

public:
    PeopleManager(std::shared_ptr<DataClient> dataClient_);

    //    std::optional<Person> get(int index) const override;

    //    std::optional<QList<Person>> get() const override;
};
