#include "overallmanager.h"

namespace {

QString getContentStrValue(const json &jsonFile, std::string key)
{
    return QString::fromStdString(jsonFile[key].get<std::string>());
}

QString getContentIntValue(const json &jsonFile, std::string key)
{
    return QString::number(jsonFile[key].get<int>());
}

} // namespace

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

//template<typename DataObject>
//std::optional<DataObject> PersonManager<DataObject>::get(int index) const
//{
//    std::optional<json> content = dataClient->get(generatePath(index));
//    if (content.has_value()) {
//        auto contentValue = content.value();
//        Person person;
//        person.id = getContentIntValue(contentValue, "id");
//        person.name = getContentStrValue(contentValue, "name");
//        person.surname = getContentStrValue(contentValue, "surname");
//        person.birthday = getContentStrValue(contentValue, "birthday");
//        person.country = getContentStrValue(contentValue, "country");
//        person.email = getContentStrValue(contentValue, "email");
//        person.password = getContentStrValue(contentValue, "password");
//        return person;
//    }
//    return {};
//}
template class OverallManager<Person>;
//template class PersonManager<Person>;
