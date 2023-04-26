#include "overallmanager.h"

namespace OverallManagerMethods {

template<typename T>
QString codeTypeToQString(const T &object)
{
    throw UndefinedDataException("This type is not supported");
}

template<>
QString codeTypeToQString<QDateTime>(const QDateTime &object)
{
    auto date = object.date();
    auto time = object.time();
    return QString("%1-%2-%3-%4-%5-%6")
        .arg(date.year())
        .arg(date.month())
        .arg(date.day())
        .arg(time.hour())
        .arg(time.minute())
        .arg(time.second());
}

template<>
QString codeTypeToQString<QString>(const QString &object)
{
    return object;
}
template<>
QString codeTypeToQString<int>(const int &object)
{
    return QString::number(object);
}

template<>
QString codeTypeToQString<std::string>(const std::string &object)
{
    return QString::fromStdString(object);
}

template<>
QString codeTypeToQString<json>(const json &object)
{
    switch (object.type()) {
    case json::value_t::number_integer: {
        return codeTypeToQString<int>(object.get<int>());
    }
    case json::value_t::string: {
        return codeTypeToQString<std::string>(object.get<std::string>());
    }
    }
    throw UndefinedDataException("This type is not supported"); //nie dziala dla dat niestety
}
} // namespace OverallManagerMethods

template<typename DataObject>
OverallManager<DataObject>::OverallManager(QString name_, std::shared_ptr<DataClient> dataClient_)
    : dataClient(dataClient_)
    , name(std::move(name_))
{}

template<typename DataObject>
UrlPath OverallManager<DataObject>::generatePath(int index) const
{
    return UrlPath(QString("%1/%2").arg(name, QString::number(index)));
}

template<typename DataObject>
UrlPath OverallManager<DataObject>::generatePath() const
{
    return UrlPath(QString(name));
}

template<typename DataObject>
void OverallManager<DataObject>::remove(int index)
{
    dataClient->remove(generatePath(index));
}

template<typename DataObject>
QString OverallManager<DataObject>::generateParms(
    const std::shared_ptr<std::unordered_map<QString, QString>> &map) const
{
    QString params;
    for (const auto &[key, value] : *map) {
        params += QString("&%1=%2").arg(key, value);
    }
    return params.remove(0, 1);
}

template<typename DataObject>
std::optional<DataObject> OverallManager<DataObject>::get(int index) const
{
    if (auto content = dataClient->get(generatePath(index)); content.has_value()) {
        return generateInstance(content.value());
    }
    return {};
}

template<typename DataObject>
std::optional<QList<DataObject>> OverallManager<DataObject>::get() const
{
    if (auto content = dataClient->getGroup(generatePath()); content.has_value()) {
        dataClient->clearFilters();
        QList<DataObject> list;
        for (const auto &element : *content) {
            list.append(generateInstance(element));
        }
        return list;
    }
    return {};
}

template<typename DataObject>
std::optional<QList<DataObject>> OverallManager<DataObject>::getFiltered(const json &genson) const
{
    dataClient->setGroupFilter(genson);
    return get();
}

#include "categories/category.h"
#include "notes/note.h"
#include "people/person.h"
REGISTER_MANAGER(Person)
REGISTER_MANAGER(Note)
REGISTER_MANAGER(Category)
