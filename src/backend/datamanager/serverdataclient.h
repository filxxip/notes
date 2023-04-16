#pragma once
#include <QDir>
#include <QFile>
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

class ServerDataClient : public DataClient
{
    mutable QString additionalParams;
    mutable curlpp::Easy request;
    void initRequest(const Path &url, std::string mode) const;
    void performRequest() const;
    void addParamsToRequest() const;

public:
    void setAdditionalParameters(const QString &params);
    void update(const Path &);
    void remove(const Path &);
    void add(const Path &);
    std::optional<json> get(const Path &) const;
};
