#include "filedataclientadapter.h"
#include <QDir>
#include <QStringList>

FileDataClientAdapter::FileDataClientAdapter(std::shared_ptr<DataClient> dataClient_)
    : dataClient(std::move(dataClient_))
{}

QString FileDataClientAdapter::convertUrlToDirectoryPath(const QString &path) const
{
    QStringList splittedPath = path.split("/");
    QString sep("/");
    QString result = std::accumulate(splittedPath.begin() + 3,
                                     splittedPath.end(),
                                     QString(),
                                     [&sep](auto &str1, auto &str2) { return str1 + sep + str2; });
    return result.mid(1);
}

void FileDataClientAdapter::setAdditionalParameters(const QString &params)
{
    dataClient->setAdditionalParameters(params);
}

int FileDataClientAdapter::getDirectoryElementsNumber(const QString &url) const
{
    auto path = convertUrlToDirectoryPath(url);
    return QDir(path).count();
}

QString FileDataClientAdapter::generatePathWithIndex(const QString &url, int index) const
{
    return convertUrlToDirectoryPath(url) + "/" + QString::number(index);
}

void FileDataClientAdapter::add(const QString &path) const
{
    dataClient->add(generatePathWithIndex(path, getDirectoryElementsNumber(path)));
}

std::optional<json> FileDataClientAdapter::get(const QString &url) const
{
    QStringList els = convertUrlToDirectoryPath(url).split("/");
    bool ok;
    if (els.last().toDouble(&ok)) {
        return dataClient->get(url);
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

void FileDataClientAdapter::update(const QString &url) const
{
    dataClient->update(convertUrlToDirectoryPath(url));
}

void FileDataClientAdapter::remove(const QString &url) const
{
    dataClient->remove(convertUrlToDirectoryPath(url));
}
