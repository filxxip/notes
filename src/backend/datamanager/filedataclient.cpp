#include "filedataclient.h"

FileDataClient::FileDataClient()
{
    fileManager = FileManager();
}

void FileDataClient::setAdditionalParameters(const QString &additionalParameters)
{
    QStringList paramsList = additionalParameters.split("&");
    for (const auto &el : paramsList) {
        QStringList data = el.split("=");
        additionParams.at(data.at(0).toStdString()) = data.at(1).toStdString();
    }
}
void FileDataClient::update(const QString &filePath) const
{
    auto file = fileManager.readFromFile(filePath);
    if (file.has_value()) {
        auto content = json::parse(file.value().toStdString());
        for (const auto &[key, value] : additionParams) {
            content[key] = value;
        }
    }
    additionParams.clear();
}

void FileDataClient::remove(const QString &path) const
{
    fileManager.removeFile(path);
}

void FileDataClient::add(const QString &path) const
{
    json content;
    for (const auto &[key, value] : additionParams) {
        content[key] = value;
    }
    additionParams.clear();
    fileManager.writeToFile(path, QString::fromStdString(content.dump()));
}

std::optional<json> FileDataClient::get(const QString &path) const
{
    auto content = fileManager.readFromFile(path);
    if (content.has_value()) {
        return json::parse(content.value().toStdString());
    }
    return {};
}
//void FileDataClient::writeJsonToFile(json jsonObject, const QString &path) const
//{
//    fileManager.writeToFile(path, QString::fromStdString(jsonObject.dump()));
//}
