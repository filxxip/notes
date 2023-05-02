#include "basicdatabasedata.h"
#include <exception>

namespace {
template<typename T>
T getContentValue(const json &jsonFile, const std::string &key)
{
    throw UndefinedDataException("This type is not supported");
}
template<>
QString getContentValue<QString>(const json &jsonFile, const std::string &key)
{
    return QString::fromStdString(jsonFile[key].get<std::string>());
}

template<>
int getContentValue<int>(const json &jsonFile, const std::string &key)
{
    return jsonFile[key].get<int>();
}

template<>
bool getContentValue<bool>(const json &jsonFile, const std::string &key)
{
    return jsonFile[key].get<bool>();
}

template<>
QDateTime getContentValue<QDateTime>(const json &jsonFile, const std::string &key)
{
    QStringList content = QString::fromStdString(jsonFile[key].get<std::string>()).split("-");
    return QDateTime(QDate(content.at(0).toInt(), content.at(1).toInt(), content.at(2).toInt()),
                     QTime(content.at(3).toInt(), content.at(4).toInt(), content.at(5).toInt()));
}
} // namespace
namespace {
template<typename T>
json generateJson(json &j, const QString &name, T t)
{
    json newjson;
    newjson[name.toStdString()] = std::move(t);
    return newjson;
}
} // namespace

//namespace ns {

//std::string getFirstKey(json &j)
//{
//    return j.begin().key();
//}
//} // namespace ns
template<typename T>
void to_json(json &j, const BaseData<T> &p)
{
    j = generateJson(j, p.getName(), p.get());
}
void to_json(json &j, const BaseData<bool> &p)
{
    to_json<bool>(j, p);
}
void to_json(json &j, const BaseData<int> &p)
{
    to_json<int>(j, p);
}
//template<>
//void to_json<bool>(json &j, const BaseData<bool> &p);

//template<typename T>
//void init_from_json(const json &j, BaseData<T> &p)
//{
//    auto key = j[p.getName().toStdString()];
//    //    int value = key.get<int>();
//    p.set(key.get<int>());
//}
template<typename T>
void init_from_json(const json &j, BaseData<T> &p)
{
    auto key = j[p.getName().toStdString()];
    auto value = key.template get<T>(); //WTF
    p.set(value);
}

//template<>
//void init_from_json<int>(const json &j, BaseData<int> &p);
//template<>
//void init_from_json<bool>(const json &j, BaseData<bool> &p);

//void init_from_json(const json &j, BaseData<int> &p)
//{
//    auto key = j[p.getName().toStdString()];
//    int value = key.get<int>();
//    p.set(value);
//}

template<>
void to_json<QString>(json &j, const BaseData<QString> &p)
{
    j = generateJson(j, p.getName(), p.get().toStdString());
}

template<>
void init_from_json<QString>(const json &j, BaseData<QString> &p)
{
    //    p.setName(getFirstKey(j));
    p.set(QString::fromStdString(j[p.getName().toStdString()].get<std::string>()));
}

template<>
void to_json<QDateTime>(json &j, const BaseData<QDateTime> &p)
{
    auto date = p.get().date();
    auto time = p.get().time();
    auto value = QString("%1-%2-%3-%4-%5-%6")
                     .arg(date.year())
                     .arg(date.month())
                     .arg(date.day())
                     .arg(time.hour())
                     .arg(time.minute())
                     .arg(time.second())
                     .toStdString();
    j = generateJson(j, p.getName(), value);
    //    j = json{p.getName().toStdString(), value};
}

template<>
void init_from_json<QDateTime>(const json &j, BaseData<QDateTime> &p)
{
    //    p.setName(getFirstKey(j));
    QStringList content = QString::fromStdString(j[p.getName().toStdString()].get<std::string>())
                              .split("-");
    p.set(QDateTime(QDate(content.at(0).toInt(), content.at(1).toInt(), content.at(2).toInt()),
                    QTime(content.at(3).toInt(), content.at(4).toInt(), content.at(5).toInt())));
}

template<typename T>
BaseData<T>::BaseData(QString name)
    : __name__(std::move(name))
{}

//template<typename T>
//BaseData<T> &BaseData<T>::operator=(T other) noexcept
//{
//    set(std::move(other));
//    return *this;
//}

template<typename T>
const QString &BaseData<T>::getName() const
{
    return __name__;
}

template<typename T>
void BaseData<T>::setBaseOnJson(const json &genson)
{
    init_from_json(genson, *this);
    //    this->value = genson[getName().toStdString()].get<BaseData<T>>().get();
    //    set(getContentValue<T>(genson, __name__.toStdString()));
}

template<typename T>
DbData<T>::DbData(QString name)
    : BaseData<T>(std::move(name))
{}

template<typename T>
void DbData<T>::set(T newvalue)
{
    if (!initValue.has_value()) {
        initValue = std::move(newvalue);
        return;
    }

    this->value = std::move(newvalue);
}

template<typename T>
const T &DbData<T>::get() const
{
    if (this->value.has_value()) {
        return this->value.value();
    }
    if (initValue.has_value()) {
        return initValue.value();
    }
    throw UndefinedDataException("Undefined parameter: " + this->__name__.toStdString());
}

template<typename T>
const std::optional<T> &DbData<T>::getUpdated() const
{
    return this->value;
}

template<typename T>
ConstDbData<T>::ConstDbData(QString name)
    : BaseData<T>(std::move(name))
{}

template<typename T>
void ConstDbData<T>::set(T newvalue)
{
    if (this->value.has_value()) {
        throw UndefinedDataException(
            "Multiple set of attribute impossible"); //dziwne ze wszedzie this, cos przyslania jakby value i __name__
    }
    this->value = std::move(newvalue);
}

template<typename T>
const T &ConstDbData<T>::get() const
{
    if (this->value.has_value()) {
        return this->value.value();
    }
    throw UndefinedDataException("Undefined parameter: " + this->__name__.toStdString());
}

#include "utils/basicdatabasedataregister.h"
