#pragma once
#include <QDate>
#include <QString>
#include "../overallmanager.h"
#include <algorithm>
#include <memory>
#include <unordered_map>

#include "../../dataclient.h"
#include "../../pathmanager/path.h"
#include "../basicdatabasedata.h"
#include "../basicstructure.h"
#include "person.h"

class PeopleManager : public OverallManager<Person>
{
public:
    PeopleManager(std::shared_ptr<DataClient> dataClient_);

    std::optional<Person> get(int index) const;
};
