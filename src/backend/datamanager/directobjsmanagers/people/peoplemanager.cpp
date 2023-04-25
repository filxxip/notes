#include "peoplemanager.h"

#define ADD_UPDATE_ATTRIBUTE(object, client, param) \
    { \
        auto result = object.param.getUpdated(); \
        if (result.has_value()) { \
            dataClient->setAdditionalParameters(#param, result.value()); \
        } \
    }

#define ADD_CONVERTED_UPDATE_ATTRIBUTE(object, client, param, method) \
    { \
        auto result = object.param.getUpdated(); \
        if (result.has_value()) { \
            dataClient->setAdditionalParameters(#param, method(result.value())); \
        } \
    }

#define ADD_CONVERTED_ATTRIBUTE(object, client, param, method) \
    dataClient->setAdditionalParameters(#param, method(object.param.get()));

#define ADD_ATTRIBUTE(object, client, param) \
    dataClient->setAdditionalParameters(#param, object.param.get());

#define INIT_ATTRIBUTE(object, genson, name) object.name.set(OverallManagerMethods::getContentValue<decltype(object.name

template<typename T>
class AttributeManagerSupporter
{
public:
};

PeopleManager::PeopleManager(std::shared_ptr<DataClient> dataClient_)
    : OverallManager("people", dataClient_)
{
    //    A a1;
    //    a1.attribute = Person::name;
    //    a1.converter = nullptr;
    //    a1.isConstant = false;
    //    a1.name = "name";
    //    attrMap.push_back(a1);
}

Person PeopleManager::generateInstance(const json &genson) const
{
    Person person;
    person.id.setBaseOnJson(genson);
    person.name.setBaseOnJson(genson);
    person.surname.setBaseOnJson(genson);
    person.birthday.setBaseOnJson(genson);
    person.country.setBaseOnJson(genson);
    person.email.setBaseOnJson(genson);
    person.password.setBaseOnJson(genson);
    //    person.id.set(OverallManagerMethods::getContentIntValue(genson, "id"));
    //    person.name.set(OverallManagerMethods::getContentStrValue(genson, "name"));
    //    person.surname.set(OverallManagerMethods::getContentStrValue(genson, "surname"));
    //    person.birthday.set(OverallManagerMethods::getContentDateValue(genson, "birthday"));
    //    person.country.set(OverallManagerMethods::getContentStrValue(genson, "country"));
    //    person.email.set(OverallManagerMethods::getContentStrValue(genson, "email"));
    //    person.password.set(OverallManagerMethods::getContentStrValue(genson, "password"));
    return person;
}
////jedno duze macro wstrzykiwane do obiektu aby tylko miec to i aby jedynie dziedziczyc po basic klasie reszte ogarnie makro poprzez podanie mu atrybutow
void PeopleManager::update(const Person &object)
{
    //    auto param = object.birthday.getUpdated();
    //    if (param.has_value()) {
    //        dataClient->setAdditionalParameters(object.birthday.getName(), param.value());
    //    }
    setAdditionUpdateParameter(object.birthday, OverallManagerMethods::datetimeToQString);
    setAdditionUpdateParameter(object.surname);
    setAdditionUpdateParameter(object.country);
    setAdditionUpdateParameter(object.name);
    setAdditionUpdateParameter(object.email);
    setAdditionUpdateParameter(object.password);
    //    ADD_CONVERTED_UPDATE_ATTRIBUTE(object,
    //                                   dataClient,
    //                                   birthday,
    //                                   OverallManagerMethods::datetimeToQString)
    //    ADD_UPDATE_ATTRIBUTE(object, dataClient, name)
    //    //    ADD_UPDATE_ATTRIBUTE(object, dataClient, id)
    //    ADD_UPDATE_ATTRIBUTE(object, dataClient, surname)
    //    ADD_UPDATE_ATTRIBUTE(object, dataClient, country)
    //    ADD_UPDATE_ATTRIBUTE(object, dataClient, email)
    //    ADD_UPDATE_ATTRIBUTE(object, dataClient, password)
    dataClient->update(generatePath(object.id.get()));
    //    dataClient->setAdditionalParameters("name", object.name.get());
    //    dataClient->setAdditionalParameters("id", object.id.get());
    //    dataClient->setAdditionalParameters("surname", object.surname.get());
    //    dataClient->setAdditionalParameters("country", object.country.get());
    //    dataClient->setAdditionalParameters("email", object.email.get());
    //    dataClient->setAdditionalParameters("password", object.password.get());
    //    dataClient->update(generatePath(person.id.get().toInt()));
}

void PeopleManager::add(const Person &object)
{
    setAdditionAddParameter(object.birthday, OverallManagerMethods::datetimeToQString);
    setAdditionAddParameter(object.surname);
    setAdditionAddParameter(object.country);
    setAdditionAddParameter(object.name);
    setAdditionAddParameter(object.email);
    setAdditionAddParameter(object.password);
    //    ADD_CONVERTED_ATTRIBUTE(object, dataClient, birthday, OverallManagerMethods::datetimeToQString)
    //    ADD_ATTRIBUTE(object, dataClient, name)
    //    //    ADD_UPDATE_ATTRIBUTE(object, dataClient, id)
    //    ADD_ATTRIBUTE(object, dataClient, surname)
    //    ADD_ATTRIBUTE(object, dataClient, country)
    //    ADD_ATTRIBUTE(object, dataClient, email)
    //    ADD_ATTRIBUTE(object, dataClient, password)
    dataClient->add(UrlPath(name));
}
