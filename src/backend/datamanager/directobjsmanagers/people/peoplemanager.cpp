#include "peoplemanager.h"

PeopleManager::PeopleManager(std::shared_ptr<DataClient> dataClient_)
    : OverallManager("people", dataClient_)
{}

#define ADD_MANAGER_CONTENT()

Person PeopleManager::generateInstance(const json &genson) const
{
    Person person;
    initObject(genson,
               person.id,
               person.name,
               person.surname,
               person.birthday,
               person.country,
               person.email,
               person.password,
               person.gender,
               person.created);
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
                 object.password,
                 object.gender,
                 object.created);
}

void PeopleManager::add(const Person &object)
{
    addObject(object.birthday,
              object.surname,
              object.country,
              object.name,
              object.email,
              object.password,
              object.gender,
              object.created);
}
