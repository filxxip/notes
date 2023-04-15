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

    void update(const Path &path) const;

    void remove(const Path &path) const;

    void add(const Path &path) const;

    std::optional<json> get(const Path &path) const;
};
