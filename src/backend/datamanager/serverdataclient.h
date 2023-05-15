#pragma once
#include <QDir>
#include <QObject>
#include <QString>
#include "dataclient.h"
#include <curl/curl.h>
#include <curlpp/Easy.hpp>
#include <curlpp/Infos.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/cURLpp.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace Operations {
Q_NAMESPACE

enum class DatabaseOperation { GET, PATCH, DELETE, POST };

Q_ENUM_NS(DatabaseOperation);

} // namespace Operations

class ServerDataClient final : public DataClient
{
    QString groupFilterString;

    mutable QString additionalParams;

    mutable curlpp::Easy request;

    void initRequest(const Path &url, QString mode) const;

    int performRequest() const;

    void addParamsToRequest() const;

public:
    void setAdditionalParameters(json parameters) override;

    void update(const Path &) override;

    void remove(const Path &) override;

    void add(const Path &) override;

    std::optional<json> get(const Path &) const override;

    std::optional<json> getGroup(const Path &path) const override;

    void clearFilters() override;

    void setGroupFilter(const json &genson) override;

    bool isValid() const override;
};
