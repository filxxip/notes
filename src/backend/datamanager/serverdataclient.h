#pragma once
#include <QDir>
#include <QString>
#include "dataclient.h"
#include <curl/curl.h>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/cURLpp.hpp>
#include <nlohmann/json.hpp>
namespace {
using json = nlohmann::json;
}

class ServerDataClient final : public DataClient
{
    mutable QString additionalParams;

    mutable curlpp::Easy request;

    void initRequest(const Path &url, std::string mode) const;

    void performRequest() const;

    void addParamsToRequest() const;

public:
    //    void setAdditionalParameters(const QString &params) override;

    void setAdditionalParameters(const QString &key, int value) override;

    void setAdditionalParameters(const QString &key, const QString &value) override;

    void update(const Path &) override;

    void remove(const Path &) override;

    void add(const Path &) override;

    std::optional<json> get(const Path &) const override;

    std::optional<json> getGroup(const Path &path) const override;
};
