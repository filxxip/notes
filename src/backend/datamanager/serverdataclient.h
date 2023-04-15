#pragma once
#include <QDir>
#include <QFile>
#include <QString>
#include "dataclient.h"
#include <curl/curl.h>
//#include <curlpp/Easy.hpp>
//#include <curlpp/Options.hpp>
//#include <curlpp/cURLpp.hpp>
#include <nlohmann/json.hpp>
namespace {
using json = nlohmann::json;
}

class ServerDataClient : public DataClient
{
    CURL *curl;
    mutable CURLcode res;

    curl_mime *mime;
    curl_mimepart *part;
    //to finish
    std::string result;
    static size_t handle_response(char *ptr, size_t size, size_t nmemb, void *userdata);
    mutable QString additionalParams;

public:
    ServerDataClient();
    void setAdditionalParameters(const QString &params);
    void update(const QString &) const;
    void remove(const QString &) const;
    void add(const QString &) const;
    std::optional<json> get(const QString &) const;
};
