#include "personmanager.h"

PersonManager::PersonManager(std::shared_ptr<DataClient> dataClient_)
    : dataClient(dataClient_)
{}

UrlPath PersonManager::generatePath(int index) const
{
    return UrlPath(QString("people/%1").arg(QString::number(index)));
}

void PersonManager::update(int index)
{
    dataClient->setAdditionalParameters(params);
    dataClient->update(generatePath(index));
    params.clear();
}

void PersonManager::remove(int index)
{
    dataClient->remove(generatePath(index));
    params.clear();
}

PersonManager &PersonManager::addParam(const QString &key, const QString &value)
{
    params += QString("&%1=%2").arg(key, value);
    return *this;
}

void PersonManager::add(Person person)
{
    copyParamsFromObjectChanges(person);
    /*his->addParam("name", person.name)
        .addParam("surname", person.surname)
        .addParam("birthday", person.birthday)
        .addParam("country", person.country)
        .addParam("email", person.email)
        .addParam("password", person.password);*/

    //    dataClient->setAdditionalParameters(params);
    dataClient->add(UrlPath("person"));
    params.clear();
}

QString PersonManager::getContentValue(const json &jsonFile, std::string key) const
{
    return QString::fromStdString(jsonFile[key].get<std::string>());
}

std::optional<Person> PersonManager::get(int index) const
{
    std::optional<json> content = dataClient->get(generatePath(index));
    if (content.has_value()) {
        auto contentValue = content.value();
        Person person;
        person.name = getContentValue(contentValue, "name");
        person.surname = getContentValue(contentValue, "surname");
        person.birthday = getContentValue(contentValue, "birthday");
        person.country = getContentValue(contentValue, "country");
        person.email = getContentValue(contentValue, "email");
        person.password = getContentValue(contentValue, "password");
        return person;
    }
    return {};
}
