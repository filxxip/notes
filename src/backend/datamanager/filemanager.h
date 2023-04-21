#pragma once
#include <QDir>
#include <QFile>
#include <QString>
#include "dataclient.h"
#include <optional>

class FileManager
{
    std::optional<QFile> createFile(const Path &path) const;

    std::optional<QFile> getFile(const Path &path) const;

public:
    std::optional<QString> readFromFile(const Path &path) const;

    void writeToFile(const Path &path, const QString &content) const;

    bool removeFile(const Path &path) const;
};
