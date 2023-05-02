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

#define REGISTER_MANAGER(cls) template class OverallManager<cls>;

namespace OverallManagerMethods {
template<typename T>
QString codeTypeToQString(const T &object);

} // namespace OverallManagerMethods

template<typename T>
class DbData;

template<typename DataObject>
class OverallManager
{
protected:
    QString name;

    virtual DataObject generateInstance(const json &genson) const = 0;
    template<typename T>
    void setAdditionUpdateParameter(const DbData<T> &data)
    {
        auto &param = data.getUpdated();
        if (param.has_value()) {
            json j;
            //            json genson;

            //            genson[data.getName().toStdString()] = param.value();
            dataClient->setAdditionalParameters(data);
            //            dataClient->setAdditionalParameters(data.getName(), param.value())
        }
    }
    template<typename T>
    void setAdditionAddParameter(const DbData<T> &data)
    {
        //        json genson;
        //        genson[data.getName().toStdString()] = data.get();
        dataClient->setAdditionalParameters(data);
        //        dataClient->setAdditionalParameters(data.getName(), data.get());
    }
    //    template<typename T, typename Function>
    //    void setAdditionUpdateParameter(const DbData<T> &data, Function converter)
    //    {
    //        auto &param = data.getUpdated();
    //        if (param.has_value()) {
    //            json genson;
    //            genson[data.getName().toStdString()] = converter(param.value()).toStdString();
    //            dataClient->setAdditionalParameters(genson);
    //            //            dataClient->setAdditionalParameters(data.getName(), converter(param.value()));
    //        }
    //    }
    //    template<typename T, typename Function>
    //    void setAdditionAddParameter(const DbData<T> &data, Function converter)
    //    {
    //        json genson;
    //        genson[data.getName().toStdString()] = converter(data.get()).toStdString();
    //        dataClient->setAdditionalParameters(genson);
    //        //        dataClient->setAdditionalParameters(data.getName(), converter(data.get()));
    //    }

    std::shared_ptr<DataClient> dataClient;

    UrlPath generatePath(int index) const;

    UrlPath generatePath() const;

    QString generateParms(const std::shared_ptr<std::unordered_map<QString, QString>> &map) const;

public:
    explicit OverallManager(QString name_, std::shared_ptr<DataClient> dataClient_);

    virtual void update(const DataObject &object) = 0;

    void remove(int index);

    virtual void add(const DataObject &object) = 0;

    std::optional<DataObject> get(int index) const;

    std::optional<QList<DataObject>> getFiltered(const json &genson) const;

    std::optional<QList<DataObject>> get() const;
};
