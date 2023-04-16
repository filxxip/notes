#pragma once
#include <QString>
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

    void setAdditionalParameters(const QString &params);

    void update(const Path &path);

    void remove(const Path &path);

    void add(const Path &path);

    std::optional<json> get(const Path &path) const;
};
