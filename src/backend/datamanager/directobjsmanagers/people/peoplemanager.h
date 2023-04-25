#pragma once

#include "../overallmanager.h"
#include "person.h"
#include <functional>

//template<typename T>
//struct A
//{
//    int T::*attribute;
//    QString name;
//    std::function<QString(const T &)> converter;
//    bool isConstant;
//};

class PeopleManager final : public OverallManager<Person>
{
protected:
    Person generateInstance(const json &genson) const override;

public:
    PeopleManager(std::shared_ptr<DataClient> dataClient_);

    void update(const Person &object) override;

    void add(const Person &object) override;

    //    std::optional<Person> get(int index) const override;

    //    std::optional<QList<Person>> get() const override;
};
