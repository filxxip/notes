#include "peoplemanager.h"

PeopleManager::PeopleManager(std::shared_ptr<DataClient> dataClient_)
    : OverallManager("people", dataClient_)
{}

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
////jedno duze macro wstrzykiwane do obiektu aby tylko miec to i aby jedynie dziedziczyc po basic klasie reszte ogarnie makro poprzez podanie mu atrybutow
void PeopleManager::update(const Person &object)
{
    setAdditionUpdateParameter(object.birthday);
    setAdditionUpdateParameter(object.surname);
    setAdditionUpdateParameter(object.country);
    setAdditionUpdateParameter(object.name);
    setAdditionUpdateParameter(object.email);
    setAdditionUpdateParameter(object.password);
    dataClient->update(generatePath(object.id.get()));
}

void PeopleManager::add(const Person &object)
{
    setAdditionAddParameter(object.birthday);
    setAdditionAddParameter(object.surname);
    setAdditionAddParameter(object.country);
    setAdditionAddParameter(object.name);
    setAdditionAddParameter(object.email);
    setAdditionAddParameter(object.password);
    dataClient->add(UrlPath(name));
}
