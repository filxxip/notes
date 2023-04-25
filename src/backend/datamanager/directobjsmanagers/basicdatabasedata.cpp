#include "basicdatabasedata.h"
#include <exception>
//DbData::BasicDatabaseData(QString name)
//    : __name__(name)
//{}

template<typename T>
DbData<T>::DbData(QString name)
    : __name__(std::move(name))
{}

template<typename T>
void DbData<T>::set(T newvalue)
{
    if (!initValue.has_value()) {
        initValue = std::move(newvalue);
        return;
    }
    value = std::move(newvalue);
}

template<typename T>
DbData<T> &DbData<T>::operator=(T other) noexcept
{
    set(std::move(other));
    return *this;
}
template<typename T>
void DbData<T>::setBaseOnJson(const json &genson)
{
    set(OverallManagerMethods::getContentValue<T>(genson, __name__.toStdString()));
}

template<typename T>
const T &DbData<T>::get() const
{
    if (value.has_value()) {
        qDebug() << "tutj2";
        return value.value();
    }
    if (initValue.has_value()) {
        qDebug() << "tutj";
        return initValue.value();
    }
    qDebug() << "tutj23";
    throw UndefinedDataException("Undefined parameter: " + __name__.toStdString());
}
template<typename T>
const std::optional<T> &DbData<T>::getUpdated() const
{
    return value;
}

template<typename T>
ConstDbData<T>::ConstDbData(QString name)
    : __name__(std::move(name))
{}

template<typename T>
void ConstDbData<T>::set(T newvalue)
{
    if (value.has_value()) {
        throw UndefinedDataException("Multiple set of attribute impossible");
    }
    value = std::move(newvalue);
}

template<typename T>
const T &ConstDbData<T>::get() const
{
    if (value.has_value()) {
        return value.value();
    }
    throw UndefinedDataException("Undefined parameter: " + __name__.toStdString());
}

template<typename T>
void ConstDbData<T>::setBaseOnJson(const json &genson)
{
    set(OverallManagerMethods::getContentValue<T>(genson, __name__.toStdString()));
}

template class DbData<int>;

template class DbData<QDateTime>;

template class DbData<QString>;

template class ConstDbData<int>;

template class ConstDbData<QString>;

template class ConstDbData<QDateTime>;

//BasicDatabaseData &BasicDatabaseData::operator=(QString other) noexcept
//{
//    set(std::move(other));
//    return *this;
//}

//IDDatabaseData::IDDatabaseData(QString name)
//    : BasicDatabaseData(std::move(name))
//{}

//void IDDatabaseData::set(QString newvalue)
//{
//    value = std::move(newvalue);
//}

//const QString &IDDatabaseData::get() const
//{
//    return value;
//}

//void DatabaseData::updateMap(const QString &val,
//                             std::shared_ptr<std::unordered_map<QString, QString>> &map)
//{
//    (*map)[__name__] = val;
//    //    if (std::find_if(map->begin(),
//    //                     map->end(),
//    //                     [this](const auto &pair) { return pair.first == __name__; })
//    //        != map->end()) {
//    //        map->at(__name__) = val;
//    //    } else {
//    //        map->insert({__name__, val});
//    //    }
//}

//DatabaseData::DatabaseData(QString name,
//                           std::shared_ptr<std::unordered_map<QString, QString>> updatedkeyMap_,
//                           std::shared_ptr<std::unordered_map<QString, QString>> keyMap_)
//    : BasicDatabaseData(std::move(name))
//    , updatedKeyMap(updatedkeyMap_)
//    , keyMap(keyMap_)
//{}

//const QString &DatabaseData::get() const
//{
//    return keyMap->at(__name__);
//}

//void DatabaseData::set(QString newvalue)
//{
//    updateMap(newvalue, keyMap);
//    if (canbeupdated) {
//        updateMap(newvalue, updatedKeyMap);
//    } else {
//        canbeupdated = true;
//    }
//}
