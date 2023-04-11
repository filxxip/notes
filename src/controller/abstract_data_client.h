#pragma once

#include <nlohmann/json.hpp>
#include <QString>
#include <QFile>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

namespace {
using json = nlohmann::json;
}

class AbstractDataCient{
public:
    virtual void convertToJson(const QString &) const = 0;
};


class FileManager{
    QString getMainFileSrc()const;
public:
    std::optional<QString> readFromFile(const QString & path)const;
    void writeToFile(const QString & path, const QString & content)const;
};

class DataClient{
public:
   virtual std::optional<json> convertToJson(const QString &)const = 0;
};

class FileDataClient : public DataClient{
    FileManager fileManager;
public:
    FileDataClient();
    std::optional<json> convertToJson(const QString & path)const;
    void writeJsonToFile(json jsonObject, const QString & path)const;
};

class ServerDataClient : public DataClient{
    CURL *curl;
    mutable CURLcode res;
    std::string result;
    static size_t handle_response(char* ptr, size_t size, size_t nmemb, void* userdata);
public:
    ServerDataClient();
    std::optional<json> convertToJson(const QString &)const;
};
