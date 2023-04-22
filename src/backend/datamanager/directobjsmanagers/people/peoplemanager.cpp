#include "peoplemanager.h"

PeopleManager::PeopleManager(std::shared_ptr<DataClient> dataClient_)
    : OverallManager("people", dataClient_)
{}

//std::optional<Person> PeopleManager::get(int index) const
//{
//    std::optional<json> content = dataClient->get(generatePath(index));
//    if (content.has_value()) {
//        //        auto contentValue = content.value();
//        //        Person person;
//        //        person.id = OverallManagerMethods::getContentStrValue(contentValue, "id");
//        //        person.name = OverallManagerMethods::getContentStrValue(contentValue, "name");
//        //        person.surname = OverallManagerMethods::getContentStrValue(contentValue, "surname");
//        //        person.birthday = OverallManagerMethods::getContentStrValue(contentValue, "birthday");
//        //        person.country = OverallManagerMethods::getContentStrValue(contentValue, "country");
//        //        person.email = OverallManagerMethods::getContentStrValue(contentValue, "email");
//        //        person.password = OverallManagerMethods::getContentStrValue(contentValue, "password");
//        //        return person;
//        return generateInstance(content.value());
//    }
//    return {};
//}

//std::optional<QList<Person>> PeopleManager::get() const
//{
//    QList<Person> list;
//    std::optional<json> content = dataClient->getGroup(generatePath());
//    if (content.has_value()) {
//        for (const auto &element : content.value()) {
//            list.push_back(generateInstance(element));
//        }
//        return list;
//    }
//    return {};
//}

Person PeopleManager::generateInstance(const json &genson) const
{
    Person person;
    person.id = OverallManagerMethods::getContentStrValue(genson, "id");
    person.name = OverallManagerMethods::getContentStrValue(genson, "name");
    person.surname = OverallManagerMethods::getContentStrValue(genson, "surname");
    person.birthday = OverallManagerMethods::getContentStrValue(genson, "birthday");
    person.country = OverallManagerMethods::getContentStrValue(genson, "country");
    person.email = OverallManagerMethods::getContentStrValue(genson, "email");
    person.password = OverallManagerMethods::getContentStrValue(genson, "password");
    return person;
}
