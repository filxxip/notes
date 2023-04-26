#pragma once
#include "dataclient.h"

namespace {
FilePath convertUrlToJsonFilePath(const Path &path);
}

class FileDataClientAdapter : public DataClient
{
    std::shared_ptr<DataClient> dataClient;

    int getDirectoryElementsNumber(const Path &path) const;

    FilePath generatePathWithIndex(const Path &path, int index) const;

public:
    FileDataClientAdapter(std::shared_ptr<DataClient> dataClient_);

    void setAdditionalParameters(const QString &key, int value) override;

    void setAdditionalParameters(const QString &key, const QString &value) override;

    void update(const Path &path) override;

    void remove(const Path &path) override;

    void add(const Path &path) override;

    std::optional<json> get(const Path &path) const override;

    std::optional<json> getGroup(const Path &path) const override;

    void clearFilters() override;

    virtual void setGroupFilter(const json &genson) override;
};
