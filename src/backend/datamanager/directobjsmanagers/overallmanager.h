#pragma once

#include <QDate>
#include <QDateTime>
#include <QString>
#include <QTime>
#include <QVector>
#include <algorithm>
#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

#include "../dataclient.h"
#include "../pathmanager/path.h"
#include "basicdatabasedata.h"

template<typename T>
class BaseData;

template<typename DataObject>
class OverallManager
{
    template<typename T>
    void setAdditionUpdateParameter(const T &data)
    {
        auto &param = data.getUpdated();
        if (param.has_value()) {
            dataClient->setAdditionalParameters(data);
        }
    }

    template<typename T>
    void setAdditionAddParameter(const T &data)
    {
        dataClient->setAdditionalParameters(data);
    }

    template<typename T, typename... Args>
    void addObjectBasicMethod(const T &t, const Args &...args)
    {
        setAdditionAddParameter(t);
        if constexpr (sizeof...(args) > 0) {
            addObjectBasicMethod(args...);
        }
    }

    template<typename T, typename... Args>
    void updateObjectBasicMethod(const T &t, const Args &...args)
    {
        setAdditionUpdateParameter(t);
        if constexpr (sizeof...(args) > 0) {
            updateObjectBasicMethod(args...);
        }
    }

    std::shared_ptr<DataClient> dataClient;

    UrlPath generatePath(int index) const;

    UrlPath generatePath() const;

    QString generateParms(const std::shared_ptr<std::unordered_map<QString, QString>> &map) const;

    QString name;

protected:
    virtual DataObject generateInstance(const json &genson) const = 0;

    template<typename... Args>
    void updateObject(int id, const Args &...args) // recursive variadic function
    {
        updateObjectBasicMethod(args...);
        dataClient->update(generatePath(id));
    }

    template<typename... Args>
    void addObject(const Args &...args) // recursive variadic function
    {
        addObjectBasicMethod(args...);
        dataClient->add(UrlPath(name));
    }

    template<typename Arg, typename... Args>
    void initObject(const json &genson, Arg &arg, Args &...args) const
    {
        arg.setBaseOnJson(genson);
        if constexpr (sizeof...(args) > 0) {
            initObject(genson, args...);
        }
    }

public:
    explicit OverallManager(QString name_, std::shared_ptr<DataClient> dataClient_);

    virtual void update(const DataObject &object) = 0;

    void remove(int index);

    virtual void add(const DataObject &object) = 0;

    std::optional<DataObject> get(int index) const;

    std::optional<QVector<DataObject>> getFiltered(const json &genson) const;

    std::optional<QVector<DataObject>> get() const;
};
