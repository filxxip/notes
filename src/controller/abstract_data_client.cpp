//#include "abstract_data_client.h"
//#include <QCoreApplication>
//#include <QDebug>
//#include <QFile>
//#include <QFileInfo>
//#include <QString>
//#include <iostream>
//#include <optional>

//QString FileManager::getMainFileSrc() const
//{
//    QString current = __FILE__;
//    current.replace("src/controller/abstract_data_client.cpp", "");
//    return current;
//}

//std::optional<QString> FileManager::readFromFile(const QString & path)const{
//    auto newPath = getMainFileSrc()+path;
//    if (!QFileInfo::exists(newPath)) {
//        qDebug()<<path;
//        qDebug() << "File doesn't exist!";
//        return {};

//    }
//    QFile file(newPath);
//    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//        qDebug() << "Failed to open file:" << file.errorString();
//        return {};
//    }
//    return file.readAll();
//}

//void FileManager::writeToFile(const QString &path, const QString &content) const{
//    auto newPath = getMainFileSrc()+path;
//    QFile file(newPath);
//    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
//        qDebug()<<"Cannot write data to file";
//    }
//    QTextStream out(&file);
//    out << content;
//}

//bool FileManager::removeFile(const QString &path) const
//{
//    QFile file(getMainFileSrc() + path);
//    return file.remove();
//}

//FileDataClient::FileDataClient(){
//    fileManager = FileManager();
//}

//std::optional<json> FileDataClient::convertToJson(const QString & path)const{
//    auto result = fileManager.readFromFile(path);
//    if (result.has_value()){
//        auto res = json::parse(result.value().toStdString());
//        return res;
//    }
//    return {};
//}

//void FileDataClient::setAdditionalParameters(const QString &additionalParameters)
//{
//    QStringList paramsList = additionalParameters.split("&");
//    for (const auto &el : paramsList) {
//        QStringList data = el.split("=");
//        additionParams.insert(std::make_pair(data.at(0), data.at(1);));
//    }
//}
//void FileDataClient::update(const QString &filePath) const
//{
//    auto file = fileManager.readFromFile(filePath);
//    if (file.has_value()) {
//        auto content = json::parse(file.value().toStdString());
//        for (const auto &[key, value] : additionParams) {
//            content[key] = value;
//        }
//    }
//    additionParams.clear();
//}

//void FileDataClient::remove(const QString &path) const
//{
//    fileManager.removeFile(path);
//}

//void FileDataClient::add(const QString &path) const
//{
//    json content;
//    for (const auto &[key, value] : additionParams) {
//        content[key] = value;
//    }
//    additionParams.clear();
//    fileManager.writeToFile(path, content.dump());
//}

//std::optional<json> FileDataClient::get(const QString &path) const
//{
//    auto content = fileManager.readFromFile(path);
//    if (content.has_value()) {
//        return json::parse(content.value().toStdString());
//    }
//    return {};
//}
//void FileDataClient::writeJsonToFile(json jsonObject, const QString &path) const
//{
//    fileManager.writeToFile(path, QString::fromStdString(jsonObject.dump()));
//}
//int FileDataClientAdapter::getDirectoryElementsNumber(const QString &path) const
//{
//    QDir directory(path);
//    return directory.count();
//}

//void FileDataClientAdapter::generatePathWithIndex(const QString &path, int index) const
//{
//    return path + "/" + QString::number(index);
//}

//void FileDataClientAdapter::add(const QString &path) const
//{
//    dataClient->add(generatePathWithIndex(path, getDirectoryElementsNumber(path)));
//}
//std::optional<json> FileDataClientAdapter::get(const QString &path) const
//{
//    QStringList els = path.split("/");
//    bool ok;
//    if (els.last().toDouble(&ok)) {
//        return dataClient->get(path);
//    }
//    auto num = getDirectoryElementsNumber(path);
//    json jsonArray = json::array();
//    for (int i = 0; i < num; i++) {
//        jsonArray.push_back(get(generatePathWithIndex(path, i)));
//    }
//    return jsonArray;
//}

//ServerDataClient::ServerDataClient()
//{
//    curl = curl_easy_init();
//    curl_easy_setopt(
//        curl,
//        CURLOPT_WRITEFUNCTION,
//        ServerDataClient::
//            handle_response); //ewentualnie przerzucic pomiedzy curl easy setup w convert to json
//}

//size_t ServerDataClient::handle_response(char *contents, size_t size, size_t nmemb, void *userp)
//{
//    ((std::string *) userp)->append((char *) contents, size * nmemb);
//    return size * nmemb;
//}

//std::optional<json> ServerDataClient::convertToJson(const QString &url) const
//{
//    curl_easy_setopt(curl, CURLOPT_URL, url.toStdString().c_str());
//    //    curl_easy_setopt(curl, CURLOPT_HTTPPOST, 1L);
//    json j{{"name", "Filip"}};
//    qDebug() << QString::fromStdString(j.dump());
//    std::string PATCH_DATA = "name='Filipek'";
//    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
//    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, PATCH_DATA.c_str());

//    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
//    //    CURLOPT_GET
//    curl_easy_setopt(
//        curl,
//        CURLOPT_WRITEFUNCTION,
//        ServerDataClient::
//            handle_response); //ewentualnie przerzucic pomiedzy curl easy setup w convert to json
//    res = curl_easy_perform(curl);
//    if (res != CURLE_OK) {
//        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
//        return {};
//    }
//    long http_code = 0;
//    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
//    if (http_code == 404) {
//        std::cerr << "Page not found : " << result << std::endl;
//        return {};
//    }

//    //         curl_easy_cleanup(curl);
//    qDebug() << QString::fromStdString(result);
//    return json::parse(result);
//    ;
//}

//void ServerDataClient::setAdditionalParameters(const QString &params)
//{
//    additionalParams = params;
//}
//void ServerDataClient::update(const QString &url) const
//{
//    curlpp::Easy request;
//    request.setOpt<curlpp::options::Url>(url);
//    request.setOpt<curlpp::options::PostFields>(additionalParams);
//    request.perform();
//    additionalParams.clear();
//}
//void ServerDataClient::remove(const QString &url) const
//{
//    curlpp::Easy request;
//    request.setOpt<curlpp::options::Url>(url);
//    request.setOpt<curlpp::options::CustomRequest>("DELETE");
//    request.perform();
//}
//void ServerDataClient::add(const QString &) const;
//std::optional<json> ServerDataClient::get(const QString &) const;
