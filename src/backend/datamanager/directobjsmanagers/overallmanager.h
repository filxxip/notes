#pragma once

#include <QDate>
#include <QString>
#include <algorithm>
#include <memory>
#include <unordered_map>

#include "../dataclient.h"
#include "../pathmanager/path.h"
#include "basicdatabasedata.h"
#include "basicstructure.h"
#include "people/person.h"

namespace OverallManagerMethods {

QString getContentStrValue(const json &jsonFile, std::string key);
QString getContentIntValue(const json &jsonFile, std::string key);

} // namespace OverallManagerMethods

template<typename DataObject>
class OverallManager
{
    QString name;

protected:
    std::shared_ptr<DataClient> dataClient;

    UrlPath generatePath(int index) const;

    QString generateParms(const std::shared_ptr<std::unordered_map<QString, QString>> &map) const;

public:
    explicit OverallManager(QString name_, std::shared_ptr<DataClient> dataClient_);

    void update(const DataObject &object);

    void remove(int index);

    void add(const DataObject &object);

    virtual std::optional<DataObject> get(int index) const = 0;
};
