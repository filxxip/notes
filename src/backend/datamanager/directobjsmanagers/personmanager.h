#pragma once

#include <QDate>
#include <QString>
#include "../dataclient.h"
#include "../pathmanager/path.h"

//struct Person
//{
//    QString name;
//    QString surname;
//    QString country;
//    QString birthday;
//    QString email;
//    QString password;
//};

class PersonManager
{
    class DatabaseData : public QString
    {
        DatabaseData(QString newValue)
            : QString(newValue)
        {}
    };

    struct Person
    {
        QString name;
        QString surname;
        QString country; //przymyslec ten update danych oraz jak przetrzymac integer np bo obecnie sie sprawadza do samych string -> qstring
        QString birthday;
        QString email;
        QString password;
    };
    QString params;
    std::shared_ptr<DataClient> dataClient;

    UrlPath generatePath(int index) const;

    QString getContentValue(const json &jsonFile, std::string key) const;

public:
    explicit PersonManager(std::shared_ptr<DataClient> dataClient_);

    PersonManager &addParam(const QString &key, const QString &value);

    void update(int index);

    void remove(int index);

    void add(Person person);

    std::optional<Person> get(int index) const;
};
