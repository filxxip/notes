#pragma once
#include <QString>
#include "dataclient.h"
#include "filemanager.h"
#include <map>

class FileDataClient : public DataClient
{
    FileManager fileManager;

    mutable std::map<std::string, std::string> additionParams;

public:
    FileDataClient();

    void setAdditionalParameters(const QString &params);

    void update(const QString &path) const;

    void remove(const QString &path) const;

    void add(const QString &path) const;

    std::optional<json> get(const QString &path) const;
};
