#include "personmanager.h"

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

PersonManager::PersonManager(std::shared_ptr<DataClient> dataClient_)
    : dataClient(dataClient_)
{}

UrlPath PersonManager::generatePath(int index) const
{
    return UrlPath(QString("people/%1").arg(QString::number(index)));
}

void PersonManager::update(const Person &person)
{
    //    QString params;
    //    for (const auto &[key, value] : *(person.getMapOfUpdates().get())) {
    //        params += QString("&%1=%2").arg(key, value);
    //    }
    //    params = params.remove(0, 1);
    //    qDebug() << params;
    //    qDebug() << person.id.get();
    dataClient->setAdditionalParameters(generateParms(person.getMapOfUpdates()));
    //    qDebug() << generatePath(person.id.get().toInt()).getFullPath();
    dataClient->update(generatePath(person.id.get().toInt()));
}

void PersonManager::remove(int index)
{
    dataClient->remove(generatePath(index));
}

QString PersonManager::generateParms(
    const std::shared_ptr<std::unordered_map<QString, QString>> &map) const
{
    QString params;
    for (const auto &[key, value] : *map) {
        params += QString("&%1=%2").arg(key, value);
    }
    return params.remove(0, 1);
}

void PersonManager::add(const Person &person)
{
    //    QString params;
    //    for (const auto &[key, value] : *(person.getMapOfAtrributes().get())) {
    //        params += QString("&%1=%2").arg(key, value);
    //    }
    //    params = params.remove(0, 1);
    //    qDebug() << params;
    //    auto &updatesMap = *(basic.getMapOfUpdates().get());
    //    for (const auto &[key, value] : updatesMap) {
    //        addParam(key, value);
    //    }
    dataClient->setAdditionalParameters(generateParms(person.getMapOfAtrributes()));
    //    copyParamsFromObjectChanges(person);
    dataClient->add(UrlPath("people"));
}

std::optional<Person> PersonManager::get(int index) const
{
    qDebug() << "eh";
    std::optional<json> content = dataClient->get(generatePath(index));
    qDebug() << "eh2";
    if (content.has_value()) {
        auto contentValue = content.value();
        Person person;
        person.id = getContentIntValue(contentValue, "id");
        qDebug() << person.id.get();
        person.name = getContentStrValue(contentValue, "name");
        person.surname = getContentStrValue(contentValue, "surname");
        person.birthday = getContentStrValue(contentValue, "birthday");
        person.country = getContentStrValue(contentValue, "country");
        person.email = getContentStrValue(contentValue, "email");
        person.password = getContentStrValue(contentValue, "password");
        return person;
    }
    return {};
}
