#include "peoplemanager.h"

PeopleManager::PeopleManager(std::shared_ptr<DataClient> dataClient_)
    : OverallManager("people", dataClient_)
{}

#define ADD_MANAGER_CONTENT()

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
    return person;
}

void PeopleManager::update(const Person &object)
{
    updateObject(object.id.get(),
                 object.birthday,
                 object.surname,
                 object.country,
                 object.name,
                 object.email,
                 object.password);
    //    setAdditionUpdateParameter(object.birthday);
    //    setAdditionUpdateParameter(object.surname);
    //    setAdditionUpdateParameter(object.country);
    //    setAdditionUpdateParameter(object.name);
    //    setAdditionUpdateParameter(object.email);
    //    setAdditionUpdateParameter(object.password);
    //    dataClient->update(generatePath(object.id.get()));
}

void PeopleManager::add(const Person &object)
{
    addObject(object.birthday,
              object.surname,
              object.country,
              object.name,
              object.email,
              object.password);
    //    setAdditionAddParameter(object.birthday);
    //    setAdditionAddParameter(object.surname);
    //    setAdditionAddParameter(object.country);
    //    setAdditionAddParameter(object.name);
    //    setAdditionAddParameter(object.email);
    //    setAdditionAddParameter(object.password);
    //    dataClient->add(UrlPath(name));
}
