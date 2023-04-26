#include "filedataclientadapter.h"
#include <QDir>
#include <QStringList>

namespace {
constexpr char EXTENSION[] = ".json";
constexpr char DELIMETER[] = "/";
FilePath convertUrlToJsonFilePath(const Path &path)
{
    auto newpath = FilePath(path.getRelativePath());
    newpath.add(".json");
    return newpath;
}

} // namespace

FileDataClientAdapter::FileDataClientAdapter(std::shared_ptr<DataClient> dataClient_)
    : dataClient(dataClient_)
{}

void FileDataClientAdapter::setAdditionalParameters(const QString &key, int value)
{
    dataClient->setAdditionalParameters(key, value);
}

void FileDataClientAdapter::setAdditionalParameters(const QString &key, const QString &value)
{
    dataClient->setAdditionalParameters(key, value);
}

int FileDataClientAdapter::getDirectoryElementsNumber(const Path &url) const
{
    auto path = FilePath(url.getRelativePath());
    return QDir(path.getFullPath()).count() - 2;
}

FilePath FileDataClientAdapter::generatePathWithIndex(const Path &url, int index) const
{
    auto path = FilePath(url.getRelativePath());
    path.add(DELIMETER + QString::number(index) + EXTENSION);
    return path;
}

void FileDataClientAdapter::add(const Path &path)
{
    QStringList filenames = QDir(FilePath(path.getRelativePath()).getFullPath())
                                .entryList(QDir::Files);
    std::vector<int> elements;
    std::transform(filenames.begin(),
                   filenames.end(),
                   std::back_inserter(elements),
                   [](auto &element) { return element.replace(EXTENSION, "").toInt(); });
    auto maxelement = std::max_element(elements.begin(), elements.end());
    auto index = 1 + (maxelement != elements.end() ? *maxelement : 0);
    setAdditionalParameters("id", index);
    dataClient->add(generatePathWithIndex(path, index));
}

std::optional<json> FileDataClientAdapter::get(const Path &url) const
{
    return dataClient->get(convertUrlToJsonFilePath(url));
}

//std::optional<json> FileDataClientAdapter::getGroup(const Path &path) const
//{
//    auto relative = path.getRelativePath();
//    std::optional<json> group = dataClient->getGroup(FilePath(relative));
//    if (group.has_value()) {
//        auto result = group.value();
//        for(const auto & element : result.items()){
//            for(const auto & keyvalue : filte)
//        }

//        //        if (relative.contains('?')) {
//        //            QStringList parts = relative.split('?');
//        //            for (auto b = parts.begin() + 1; b != parts.end(); b++) {
//        //                QStringList innerParts = (*b).split('=');
//        //                auto &key = innerParts.at(0);
//        //                auto &value = innerParts.at(1);
//        //                for (const json &el : result.items()) {
//        //                    el.erase(std::remove_if(el.begin(), el.end(), [](const std::pair<const std::string, json>& item) {
//        //                        return item.second.is_string() && item.second.get<std::string>() == "John";)
//        //                    if(el[key].get<std::string>()!=value){

//        //                    }
//        //                }
//        //                }
//        //            }
//        //            return group;
//        //        }
//        return {};
//    }
//    return {};
//}
std::optional<json> FileDataClientAdapter::getGroup(const Path &path) const
{
    return dataClient->getGroup(FilePath(path.getRelativePath()));
}

void FileDataClientAdapter::update(const Path &url)
{
    dataClient->update(convertUrlToJsonFilePath(url));
}

void FileDataClientAdapter::remove(const Path &url)
{
    dataClient->remove(convertUrlToJsonFilePath(url));
}

void FileDataClientAdapter::setGroupFilter(const json &genson)
{
    dataClient->setGroupFilter(genson);
}
void FileDataClientAdapter::clearFilters()
{
    dataClient->clearFilters();
}
