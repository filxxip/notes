#include "peoplemanager.h"

PeopleManager::PeopleManager(std::shared_ptr<DataClient> dataClient_)
    : OverallManager("people", dataClient_)
{}

std::optional<Person> PeopleManager::get(int index) const
{
    std::optional<json> content = dataClient->get(generatePath(index));
    if (content.has_value()) {
        auto contentValue = content.value();
        Person person;
        person.id = QString::number(index);
        person.name = OverallManagerMethods::getContentStrValue(contentValue, "name");
        person.surname = OverallManagerMethods::getContentStrValue(contentValue, "surname");
        person.birthday = OverallManagerMethods::getContentStrValue(contentValue, "birthday");
        person.country = OverallManagerMethods::getContentStrValue(contentValue, "country");
        person.email = OverallManagerMethods::getContentStrValue(contentValue, "email");
        person.password = OverallManagerMethods::getContentStrValue(contentValue, "password");
        return person;
    }
    return {};
}

