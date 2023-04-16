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

void FileDataClientAdapter::setAdditionalParameters(const QString &params)
{
    dataClient->setAdditionalParameters(params);
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
                   [](auto &element) { return element.replace(".json", "").toInt(); });
    auto maxelement = std::max_element(elements.begin(), elements.end());
    dataClient->add(
        generatePathWithIndex(path, 1 + (maxelement != elements.end() ? *maxelement : 0)));
}

std::optional<json> FileDataClientAdapter::get(const Path &url) const
{
    auto path = convertUrlToJsonFilePath(url);
    bool ok;
    if (path.lastWithoutExtension().toDouble(&ok)) {
        return dataClient->get(path);
    }
    auto num = getDirectoryElementsNumber(url);
    json jsonArray = json::array();
    for (int i = 0; i < num; i++) {
        auto content = get(generatePathWithIndex(url, i));
        if (content.has_value()) {
            jsonArray.push_back(content.value());
        }
    }
    return jsonArray;
}

void FileDataClientAdapter::update(const Path &url)
{
    dataClient->update(convertUrlToJsonFilePath(url));
}

void FileDataClientAdapter::remove(const Path &url)
{
    dataClient->remove(convertUrlToJsonFilePath(url));
}
