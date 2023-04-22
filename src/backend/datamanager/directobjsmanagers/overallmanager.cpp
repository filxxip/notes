#include "overallmanager.h"

namespace OverallManagerMethods {

QString getContentStrValue(const json &jsonFile, std::string key)
{
    return QString::fromStdString(jsonFile[key].get<std::string>());
}

QString getContentIntValue(const json &jsonFile, std::string key)
{
    return QString::number(jsonFile[key].get<int>());
}

} // namespace OverallManagerMethods

template<typename DataObject>
OverallManager<DataObject>::OverallManager(QString name_, std::shared_ptr<DataClient> dataClient_)
    : dataClient(dataClient_)
    , name(std::move(name_))
{}

template<typename DataObject>
UrlPath OverallManager<DataObject>::generatePath(int index) const
{
    return UrlPath(QString("%1/%2").arg(name, QString::number(index)));
}

template<typename DataObject>
UrlPath OverallManager<DataObject>::generatePath() const
{
    return UrlPath(QString(name));
}

template<typename DataObject>
void OverallManager<DataObject>::update(const DataObject &person)
{
    dataClient->setAdditionalParameters(generateParms(person.getMapOfUpdates()));
    dataClient->update(generatePath(person.id.get().toInt()));
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
        params += QString("&%1=%2").arg(key, value);
    }
    return params.remove(0, 1);
}

template<typename DataObject>
void OverallManager<DataObject>::add(const DataObject &person)
{
    dataClient->setAdditionalParameters(generateParms(person.getMapOfAtrributes()));
    dataClient->add(UrlPath(name));
}
template<typename DataObject>
std::optional<DataObject> OverallManager<DataObject>::get(int index) const
{
    std::optional<json> content = dataClient->get(generatePath(index));
    if (content.has_value()) {
        return generateInstance(content.value());
    }
    return {};
}

template<typename DataObject>
std::optional<QList<DataObject>> OverallManager<DataObject>::get() const
{
    QList<DataObject> list;
    std::optional<json> content = dataClient->getGroup(generatePath());
    if (content.has_value()) {
        for (const auto &element : content.value()) {
            list.push_back(generateInstance(element));
        }
        return list;
    }
    return {};
}

#include "categories/category.h"
#include "notes/note.h"
#include "people/person.h"
REGISTER_MANAGER(Person)
REGISTER_MANAGER(Note)
REGISTER_MANAGER(Category)
