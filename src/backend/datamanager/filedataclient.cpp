#include "filedataclient.h"

FileDataClient::FileDataClient()
    : DataClient()
{}

void FileDataClient::setAdditionalParameters(const QString &additionalParameters)
{
    QStringList paramsList = additionalParameters.split("&");
    for (const auto &el : paramsList) {
        QStringList data = el.split("=");
        additionParams.insert({data.at(0).toStdString(), data.at(1).toStdString()});
    }
}

void FileDataClient::performWritingToFile(json content, const Path &path)
{
    fileManager.writeToFile(path, QString::fromStdString(content.dump()));
    additionParams.clear();
}

void FileDataClient::update(const Path &filePath)
{
    auto file = fileManager.readFromFile(filePath);
    if (file.has_value()) {
        auto content = json::parse(file.value().toStdString());
        for (const auto &[key, value] : additionParams) {
            content[key] = value;
        }
        fileManager.writeToFile(filePath, QString::fromStdString(content.dump()));
    }
    additionParams.clear();
}

void FileDataClient::remove(const Path &path)
{
    fileManager.removeFile(path);
}

void FileDataClient::add(const Path &path)
{
    json content;
    for (const auto &[key, value] : additionParams) {
        content[key] = value;
    }
    additionParams.clear();
    fileManager.writeToFile(path, QString::fromStdString(content.dump()));
}

std::optional<json> FileDataClient::get(const Path &path) const
{
    auto content = fileManager.readFromFile(path);
    if (content.has_value()) {
        return json::parse(content.value().toStdString());
    }
    return {};
}
