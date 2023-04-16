#pragma once
#include <QString>
#include "dataclient.h"
#include "filemanager.h"
#include <map>

class FileDataClient : public DataClient
{
    FileManager fileManager;

    std::map<std::string, std::string> additionParams;

    void performWritingToFile(json content, const Path &path);

public:
    FileDataClient();

    void setAdditionalParameters(const QString &params);

    void update(const Path &path);

    void remove(const Path &path);

    void add(const Path &path);

    std::optional<json> get(const Path &path) const;
};
