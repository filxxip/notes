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

template<typename T>
void init_from_json(const json &j, BaseData<T> &p)
{
    auto key = j[p.getName().toStdString()];
    auto value = key.template get<T>(); //WTF
    p.set(value);
}

template<>
void to_json<QString>(json &j, const BaseData<QString> &p)
{
    j = generateJson(j, p.getName(), p.get().toStdString());
}

template<>
void init_from_json<QString>(const json &j, BaseData<QString> &p)
{
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
}

template<>
void init_from_json<QDateTime>(const json &j, BaseData<QDateTime> &p)
{
    QStringList content = QString::fromStdString(j[p.getName().toStdString()].get<std::string>())
                              .split("-");
    p.set(QDateTime(QDate(content.at(0).toInt(), content.at(1).toInt(), content.at(2).toInt()),
                    QTime(content.at(3).toInt(), content.at(4).toInt(), content.at(5).toInt())));
}

template<typename T>
BaseData<T>::BaseData(QString name)
    : __name__(std::move(name))
{}

template<typename T>
bool BaseData<T>::operator==(const T &data) const
{
    return data == get();
}

template<typename T>
BaseData<T> &BaseData<T>::operator=(const T &obj)
{
    this->set(obj);
    return *this;
}

template<typename T>
BaseData<T> &BaseData<T>::operator=(const QVariant &obj)
{
    return operator=(obj.value<T>());
}

template<typename T>
const QString &BaseData<T>::getName() const
{
    return __name__;
}

template<typename T>
void BaseData<T>::setBaseOnJson(const json &genson)
{
    auto name = getName().toStdString();
    if (genson.contains(name)) {
        init_from_json(genson, *this);
    } else {
        throw UndefinedDataException("Json doesn't contain some key : " + name);
    }
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
        throw UndefinedDataException("Multiple set of attribute impossible");
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

template<typename T>
CodedDbData<T>::CodedDbData(QString name, std::map<int, T> codeMap_)
    : DbData<T>(std::move(name))
    , codeMap(codeMap_)
{}

template<typename T>
std::optional<int> CodedDbData<T>::getCodeByValue(const T &codedValue) const
{
    auto itrValue = std::find_if(std::begin(codeMap),
                                 std::end(codeMap),
                                 [&codedValue](const auto &pair) {
                                     return pair.second == codedValue;
                                 });
    if (itrValue != codeMap.end()) {
        return itrValue->first;
    }
    return std::nullopt;
}

template<typename T>
void CodedDbData<T>::set(T newvalue)
{
    if (getCodeByValue(newvalue).has_value()) {
        DbData<T>::set(std::move(newvalue));
        return;
    }

    throw UndefinedDataException("This value from get() method is not valid");
}

template<typename T>
int CodedDbData<T>::getByCode() const
{
    auto val = getCodeByValue(get());
    if (val.has_value()) {
        return val.value();
    }
    throw UndefinedDataException("This value from get() method is not valid");
}

template<typename T>
void CodedDbData<T>::setByCode(int value)
{
    if (std::find_if(std::begin(codeMap),
                     std::end(codeMap),
                     [value](const auto &pair) { return pair.first == value; })
        != std::end(codeMap)) {
        set(codeMap[value]);
        return;
    }
    throw UndefinedDataException("This code is not valid : " + std::to_string(value));
}

#include "utils/basicdatabasedataregister.h"
