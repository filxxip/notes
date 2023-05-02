//#pragma once

//#include <QDir>
//#include <QFile>
//#include <QString>
//#include <curl/curl.h>
//#include <curlpp/Easy.hpp>
//#include <curlpp/Options.hpp>
//#include <curlpp/cURLpp.hpp>
//#include <nlohmann/json.hpp>

//namespace {
//using json = nlohmann::json;
//}

//class AbstractDataCient{
//public:
//    virtual void convertToJson(const QString &) const = 0;
//};

//class FileManager{
//    QString getMainFileSrc()const;
//public:
//    std::optional<QString> readFromFile(const QString & path)const;
//    void writeToFile(const QString & path, const QString & content)const;
//    bool removeFile(const QString &path) const;
//};

//class DataClient{
//public:
//    enum class Operation { GET, UPDATE, DELETE, ADD };

//    virtual void setAdditionalParameters(const QString &) = 0;
//    virtual void update(const QString &) const = 0;
//    virtual void remove(const QString &) const = 0;
//    virtual void add(const QString &) const = 0;
//    virtual std::optional<json> get(const QString &) const = 0;
//};

//class FileDataClient : public DataClient{
//    FileManager fileManager;
//    std::map<QString, QString> additionParams;

//public:
//    FileDataClient();
//    void setAdditionalParameters(const QString &params);
//    void update(const QString &path) const;
//    void remove(const QString &path) const;
//    void add(const QString &path) const;
//    std::optional<json> get(const QString &path) const;
//};

//class FileDataClientAdapter : public DataClient
//{
//    std::shared_ptr<DataClient> dataClient;
//    int getDirectoryElementsNumber(const QString &path) const;
//    QString generatePathWithIndex(const QString &path, int index) const;

//public:
//    FileDataClientAdapter(std::shared_ptr<DataClient> dataClient_)
//        : dataClient(std::move(dataClient_))
//    {}
//    void setAdditionalParameters(const QString &params)
//    {
//        dataClient->setAdditionalParameters(params);
//    }
//    void update(const QString &path) const { dataClient->update(path); }
//    void remove(const QString &path) const { dataClient->remove(path); }
//    void add(const QString &path) const;
//    std::optional<json> get(const QString &path) const;
//};

//class ServerDataClient : public DataClient
//{
//    CURL *curl;
//    mutable CURLcode res;

//    curl_mime *mime;
//    curl_mimepart *part;
//    //to finish
//    std::string result;
//    static size_t handle_response(char* ptr, size_t size, size_t nmemb, void* userdata);
//    QString additionalParams;

//public:
//    ServerDataClient();
//    void setAdditionalParameters(const QString &params);
//    void update(const QString &) const;
//    void remove(const QString &) const;
//    void add(const QString &) const;
//    std::optional<json> get(const QString &) const;
//};
