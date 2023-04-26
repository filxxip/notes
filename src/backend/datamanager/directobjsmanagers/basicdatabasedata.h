#pragma once

#include <QDate>
#include <QObject>
#include <QString>
#include "overallmanager.h"
#include <algorithm>
#include <memory>
#include <unordered_map>

class UndefinedDataException : public std::exception
{
public:
    UndefinedDataException(std::string error)
        : msg_(std::move(error))
    {}
    virtual const char *what() const noexcept { return msg_.c_str(); }

private:
    std::string msg_;
};

template<typename T>
class BaseData
{
protected:
    QString __name__;
    std::optional<T> value;

public:
    BaseData(QString name);

    virtual void set(T newvalue) = 0;

    virtual BaseData<T> &operator=(T other) noexcept;

    virtual const T &get() const = 0;

    virtual const QString &getName() const;

    virtual void setBaseOnJson(const json &genson);
};

template<typename T>
class DbData : public BaseData<T>
{
    std::optional<T> initValue;

public:
    using BaseData<T>::operator=;

    DbData(QString name);

    void set(T newvalue) override;

    const T &get() const override;

    const std::optional<T> &getUpdated() const; //tylko updated i updatuje wtedy kiedy jest zmiana

};

template<typename T>
class ConstDbData : public BaseData<T>
{
public:
    using BaseData<T>::operator=;

    ConstDbData(QString name);

    void set(T newvalue) override;

    const T &get() const override;
};

#define REGISTER_DATA(type) \
    template class BaseData<type>; \
    template class DbData<type>; \
    template class ConstDbData<type>;

using IntData = DbData<int>;
using StrData = DbData<QString>;
using DateData = DbData<QDateTime>;

using ConstIntData = ConstDbData<int>;
using ConstStrData = ConstDbData<QString>;
using ConstDateData = ConstDbData<QDateTime>;
