#pragma once

#include "../overallmanager.h"
#include "category.h"
#include <functional>

class CategoriesManager final : public OverallManager<Category>
{
protected:
    Category generateInstance(const json &genson) const override;

public:
    CategoriesManager(std::shared_ptr<DataClient> dataClient_);

    void update(const Category &object) override;

    void add(const Category &object) override;
};
