#pragma once

#include <QDate>
#include <QDateTime>
#include <QList>
#include <QString>
#include <QTime>
#include <algorithm>
#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

#include "../dataclient.h"
#include "../pathmanager/path.h"
#include "basicdatabasedata.h"
#include "basicstructure.h"

#define REGISTER_MANAGER(cls) template class OverallManager<cls>;

namespace {}

template<typename T>
struct A
{
    int T::*attribute;
    QString name;
    std::function<QString(const T &)> converter;
    bool isConstant;
};

namespace OverallManagerMethods {

//QString getContentStrValue(const json &jsonFile, std::string key);
//int getContentIntValue(const json &jsonFile, std::string key);
//QDateTime getContentDateValue(const json &jsonFile, std::string key);
QString datetimeToQString(const QDateTime &datetime);
template<typename T>
T getContentValue(const json &jsonFile, const std::string &key);

} // namespace OverallManagerMethods

template<typename T>
class DbData;

template<typename DataObject>
class OverallManager
{
protected:
    QString name;

    virtual DataObject generateInstance(const json &genson) const = 0;
    //    {
    //        DataObject obj;
    //        for (const auto &element : attrMap) {
    //            (obj.*(element.attribute)).setBaseOnJson(genson);
    //        }
    //        return obj;
    //    }

    //    template<typename T, typename Function = decltype(nullptr)>
    //    void setAdditionUpdateParameter(const DbData<T> &data, Function converter = nullptr)
    //    {
    //        auto &param = data.getUpdated();
    //        if (param.has_value()) {
    //            auto &value = param.value();
    //            if (converter) {
    //                dataClient->setAdditionalParameters(data.getName(), converter(value));
    //            } else {
    //                dataClient->setAdditionalParameters(data.getName(), value);
    //            }
    //        }
    //    }
    //    template<typename T, typename Function = decltype(nullptr)>
    //    void setAdditionAddParameter(const DbData<T> &data, Function converter = nullptr)
    //    {
    //        auto &value = data.get();
    //        if (converter) {
    //            dataClient->setAdditionalParameters(data.getName(), converter(value));
    //        } else {
    //            dataClient->setAdditionalParameters(data.getName(), value);
    //        }
    //    }
    template<typename T>
    void setAdditionUpdateParameter(const DbData<T> &data)
    {
        auto &param = data.getUpdated();
        if (param.has_value()) {
            auto &value = param.value();
            dataClient->setAdditionalParameters(data.getName(), value);
        }
    }
    template<typename T>
    void setAdditionAddParameter(const DbData<T> &data)
    {
        auto &value = data.get();
        dataClient->setAdditionalParameters(data.getName(), value);
    }
    template<typename T, typename Function>
    void setAdditionUpdateParameter(const DbData<T> &data, Function converter)
    {
        auto &param = data.getUpdated();
        if (param.has_value()) {
            auto &value = param.value();
            dataClient->setAdditionalParameters(data.getName(), converter(value));
        }
    }
    template<typename T, typename Function>
    void setAdditionAddParameter(const DbData<T> &data, Function converter)
    {
        auto &value = data.get();
        dataClient->setAdditionalParameters(data.getName(), converter(value));
    }

    std::shared_ptr<DataClient> dataClient;

    UrlPath generatePath(int index) const;

    UrlPath generatePath() const;

    QString generateParms(const std::shared_ptr<std::unordered_map<QString, QString>> &map) const;

public:
    explicit OverallManager(QString name_, std::shared_ptr<DataClient> dataClient_);

    virtual void update(const DataObject &object) = 0;
    //    {
    //        for (const auto &element : attrMap) {
    //            if (!element.isConstant) {
    //                auto param = object.*(element.attribute).getUpdated();
    //                if (param.hasValue()) {
    //                    auto res = param.value();
    //                    dataClient->setAdditionalParameters(element.name,
    //                                                        element.converter ? element.converter(res)
    //                                                                          : res);
    //                }
    //            }
    //        }
    //        dataClient->update(generatePath(object.id.get()));
    //    }

    void remove(int index);

    virtual void add(const DataObject &object) = 0;
    //    {
    //        for (const auto &element : attrMap) {
    //            if (!element.isConstant) {
    //                auto res = object.*(element.attribute).get();
    //                dataClient->setAdditionalParameters(element.name,
    //                                                    element.converter ? element.converter(res)
    //                                                                      : res);
    //            }
    //        }
    //        dataClient->add(UrlPath(name));
    //    }

    std::optional<DataObject> get(int index) const;

    std::optional<QList<DataObject>> get() const;
};
