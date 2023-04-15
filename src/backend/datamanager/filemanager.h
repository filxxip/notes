#pragma once
#include <QDir>
#include <QFile>
#include <QString>
#include "dataclient.h"

class FileManager
{
public:
    std::optional<QString> readFromFile(const Path &path) const;

    void writeToFile(const Path &path, const QString &content) const;

    bool removeFile(const Path &path) const;
};
