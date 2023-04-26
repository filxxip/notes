#include "filedataclient.h"

FileDataClient::FileDataClient()
    : DataClient()
{}

void FileDataClient::setAdditionalParameters(const QString &key, const QString &value)
{
    addedParams[key.toStdString()] = value.toStdString();
}

void FileDataClient::setAdditionalParameters(const QString &key, int value)
{
    addedParams[key.toStdString()] = value;
}

void FileDataClient::performWritingToFile(const json &content, const Path &path)
{
    fileManager.writeToFile(path, QString::fromStdString(content.dump()));
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
            auto el = json::parse(element.toStdString());
            bool condition = true;
            for (auto it = el.begin(); it != el.end(); ++it) {
                auto key = it.key();
                auto value = it.value();

                if (el[key] != value) {
                    condition = false;
                }
            }
            if (condition) {
                jsonArray.push_back(std::move(el));
            }
        }
        return jsonArray;
    }
    return {};
}

void FileDataClient::setGroupFilter(const json &genson)
{
    filterParams.merge_patch(genson);
}
void FileDataClient::clearFilters()
{
    filterParams.clear();
}
