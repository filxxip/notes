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
