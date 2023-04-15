#pragma once
#include <QString>
#include "dataclient.h"

class FileDataClientAdapter : public DataClient
{
public:
    std::shared_ptr<DataClient> dataClient;

    int getDirectoryElementsNumber(const QString &path) const;

    QString generatePathWithIndex(const QString &path, int index) const;

    QString convertUrlToDirectoryPath(const QString &path) const;

public:
    FileDataClientAdapter(std::shared_ptr<DataClient> dataClient_);

    void setAdditionalParameters(const QString &params);

    void update(const QString &path) const;

    void remove(const QString &path) const;

    void add(const QString &path) const;

    std::optional<json> get(const QString &path) const;
};
