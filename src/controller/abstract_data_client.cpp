#include "abstract_data_client.h"
#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QString>
#include <iostream>
#include <optional>

QString FileManager::getMainFileSrc() const
{
    QString current = __FILE__;
    current.replace("src/controller/abstract_data_client.cpp", "");
    return current;
}

std::optional<QString> FileManager::readFromFile(const QString & path)const{
    auto newPath = getMainFileSrc()+path;
    if (!QFileInfo::exists(newPath)) {
        qDebug()<<path;
        qDebug() << "File doesn't exist!";
        return {};

    }
    QFile file(newPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file:" << file.errorString();
        return {};
    }
    return file.readAll();
}


void FileManager::writeToFile(const QString &path, const QString &content) const{
    auto newPath = getMainFileSrc()+path;
    QFile file(newPath);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug()<<"Cannot write data to file";
    }
    QTextStream out(&file);
    out << content;
}

FileDataClient::FileDataClient(){
    fileManager = FileManager();
}

std::optional<json> FileDataClient::convertToJson(const QString & path)const{
    auto result = fileManager.readFromFile(path);
    if (result.has_value()){
        auto res = json::parse(result.value().toStdString());
        return res;
    }
    return {};
}

void FileDataClient::writeJsonToFile(json jsonObject, const QString & path)const{
    fileManager.writeToFile(path,QString::fromStdString(jsonObject.dump()));
}

ServerDataClient::ServerDataClient()
{
    curl = curl_easy_init();
    curl_easy_setopt(
        curl,
        CURLOPT_WRITEFUNCTION,
        ServerDataClient::
            handle_response); //ewentualnie przerzucic pomiedzy curl easy setup w convert to json
}

size_t ServerDataClient::handle_response(char *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *) userp)->append((char *) contents, size * nmemb);
    return size * nmemb;
}

std::optional<json> ServerDataClient::convertToJson(const QString &url) const
{
    curl_easy_setopt(curl, CURLOPT_URL, url.toStdString().c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPPOST, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
    //    CURLOPT_GET
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        return {};
    }
    long http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    if (http_code == 404) {
        std::cerr << "Page not found" << std::endl;
        return {};
    }

    //         curl_easy_cleanup(curl);
    qDebug() << QString::fromStdString(result);
    return json::parse(result);
    ;
}
