#include "overallmanager.h"
#include <QStringLiteral>

namespace {
const auto ADDITION_PARAMS = QStringLiteral("&%1=%2");
const auto ADDITION_URL_PATH = QStringLiteral("%1/%2");
} // namespace

template<typename DataObject>
OverallManager<DataObject>::OverallManager(DatabaseCodes::Names databaseName,
                                           std::shared_ptr<DataClient> dataClient_)
    : dataClient(dataClient_)
    , name(DatabaseCodes::namesMap.at(databaseName))
{}

template<typename DataObject>
UrlPath OverallManager<DataObject>::generatePath(int index) const
{
    return UrlPath(ADDITION_URL_PATH.arg(name, QString::number(index)));
}

template<typename DataObject>
UrlPath OverallManager<DataObject>::generatePath() const
{
    return UrlPath(QString(name));
}

template<typename DataObject>
void OverallManager<DataObject>::remove(int index)
{
    dataClient->remove(generatePath(index));
}

template<typename DataObject>
QString OverallManager<DataObject>::generateParms(
    const std::shared_ptr<std::unordered_map<QString, QString>> &map) const
{
    QString params;
    for (const auto &[key, value] : *map) {
        params += ADDITION_PARAMS.arg(key, value);
    }
    return params.remove(0, 1);
}

template<typename DataObject>
std::optional<DataObject> OverallManager<DataObject>::get(int index) const
{
    if (auto content = dataClient->get(generatePath(index)); content.has_value()) {
        return generateInstance(content.value());
    }
    return {};
}

template<typename DataObject>
std::optional<QVector<DataObject>> OverallManager<DataObject>::get() const
{
    qDebug() << generatePath().getFullPath();
    if (auto content = dataClient->getGroup(generatePath()); content.has_value()) {
        dataClient->clearFilters();
        QVector<DataObject> list;
        for (const auto &element : *content) {
            list.append(generateInstance(element));
        }
        return list;
    }
    return {};
}

template<typename DataObject>
std::optional<QVector<DataObject>> OverallManager<DataObject>::getFiltered(const json &genson) const
{
    dataClient->setGroupFilter(genson);
    return get();
}

#include "utils/overallmanagerregister.h"
