#pragma once
#include <QString>
#include "dataclient.h"

namespace costam {
FilePath convertUrlToJsonFilePath(const Path &path);
}
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

    void update(const Path &path) const;

    void remove(const Path &path) const;

    void add(const Path &path) const;

    std::optional<json> get(const Path &path) const;
};
