#pragma once
#include "dataclient.h"
#include "filemanager.h"
#include <map>

class FileDataClient final : public DataClient
{
    FileManager fileManager;

    std::map<std::string, std::string> additionParams;

    void performWritingToFile(json content, const Path &path);

public:
    FileDataClient();

    void setAdditionalParameters(const QString &params) override;

    void update(const Path &path) override;

    void remove(const Path &path) override;

    void add(const Path &path) override;

    std::optional<json> get(const Path &path) const override;
};
