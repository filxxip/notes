#include "filedataclient.h"
#include "directobjsmanagers/overallmanager.h"


void FileDataClient::setAdditionalParameters(json parameters)
{
    addedParams.merge_patch(parameters);
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

    if (content) {
        json jsonArray;
        for (const auto &element : *content) {
            json el = json::parse(element.toStdString());

            bool condition = true;
            for (const auto &[key, value] : filterParams.items()) {
                if (el[key] != value) {
                    condition = false;
                    break;
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

bool FileDataClient::isValid() const
{
    return QDir(FilePath("").getFullPath()).exists();
}
