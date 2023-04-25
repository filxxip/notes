#pragma once
#include "dataclient.h"
#include "filemanager.h"
#include <map>

class FileDataClient final : public DataClient
{
    FileManager fileManager;

    json addedParams;

    void performWritingToFile(const json &content, const Path &path);

    std::optional<json> performGetter(const std::optional<QString> &list) const;

public:
    FileDataClient();

    void setAdditionalParameters(const QString &key, int value) override;

    void setAdditionalParameters(const QString &key, const QString &value) override;

    void update(const Path &path) override;

    void remove(const Path &path) override;

    void add(const Path &path) override;

    std::optional<json> get(const Path &path) const override;

    std::optional<json> getGroup(const Path &path) const override;
};
