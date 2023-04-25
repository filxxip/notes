#include "filedataclient.h"

FileDataClient::FileDataClient()
    : DataClient()
{}

//void FileDataClient::setAdditionalParameters(
//    const QString &additionalParameters) //na biezaco klepac jsona, dwa paramy wstring i Template param
//{
//    QStringList paramsList = additionalParameters.split("&");
//    for (const auto &el : paramsList) {
//        QStringList data = el.split("=");
//        additionParams.insert({data.at(0).toStdString(), data.at(1).toStdString()});
//    }
//}

//void FileDataClient::setAdditionalParameters(
//    const QString &key,
//    const QString &value) //na biezaco klepac jsona, dwa paramy wstring i Template param
//{
//    //    QStringList paramsList = additionalParameters.split("&");
//    //    for (const auto &el : paramsList) {
//    //        QStringList data = el.split("=");
//    additionParams.insert({key.toStdString(), value.toStdString()});
//    //    }
//}

void FileDataClient::setAdditionalParameters(
    const QString &key,
    const QString &value) //na biezaco klepac jsona, dwa paramy wstring i Template param
{
    //    QStringList paramsList = additionalParameters.split("&");
    //    for (const auto &el : paramsList) {
    //        QStringList data = el.split("=");
    addedParams[key.toStdString()] = value.toStdString();
    //    additionParams.insert({key.toStdString(), value.toStdString()});
    //    }
}

void FileDataClient::setAdditionalParameters(
    const QString &key,
    int value) //na biezaco klepac jsona, dwa paramy wstring i Template param
{
    //    QStringList paramsList = additionalParameters.split("&");
    //    for (const auto &el : paramsList) {
    //        QStringList data = el.split("=");
    addedParams[key.toStdString()] = value;
    //    additionParams.insert({key.toStdString(), value.toStdString()});
    //    }
}

void FileDataClient::performWritingToFile(const json &content, const Path &path)
{
    fileManager.writeToFile(path, QString::fromStdString(content.dump()));
    //    additionParams.clear();
    addedParams.clear();
}

void FileDataClient::update(const Path &filePath)
{
    auto file = fileManager.readFromFile(filePath);
    if (file.has_value()) {
        json content = json::parse(file.value().toStdString());
        for (const auto &pair : addedParams.items()) {
            content[pair.key()] = pair.value();
        }
        performWritingToFile(content, filePath);
    }
}

void FileDataClient::remove(const Path &path)
{
    fileManager.removeFile(path);
}

void FileDataClient::add(const Path &path)
{
    //    json content;
    //    for (const auto &[key, value] : additionParams) {
    //        content[key] = value;
    //    }
    performWritingToFile(addedParams, path);
}

std::optional<json> FileDataClient::get(const Path &path) const
{
    auto content = fileManager.readFromFile(path);

    if (content.has_value()) {
        return json::parse(content.value().toStdString());
    }
    return {};
}

std::optional<json> FileDataClient::getGroup(const Path &path) const
{
    auto content = fileManager.readFromDir(path);

    if (content.has_value()) {
        json jsonArray = json::array();
        for (const auto &element : content.value()) {
            jsonArray.push_back(json::parse(element.toStdString()));
        }
        return jsonArray;
    }
    return {};
}
