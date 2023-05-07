#pragma once

#include <QString>
#include "pathmanager/path.h"
#include <memory>
#include <optional>
#include <nlohmann/json.hpp>

namespace {
    using json = nlohmann::json;
}

class DataClient {
public:
    virtual void setAdditionalParameters(json parameters) = 0;

    virtual void update(const Path &path) = 0;

    virtual void remove(const Path &path) = 0;

    virtual void add(const Path &path) = 0;

    virtual std::optional<json> get(const Path &path) const = 0;

    virtual std::optional<json> getGroup(const Path &path) const = 0;

    virtual void setGroupFilter(const json &genson) = 0;

    virtual void clearFilters() = 0;

    virtual bool isValid() const = 0;
};
