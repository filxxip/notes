#pragma once

#include "dataclient.h"

#include <QDir>
#include <QFile>
#include <QStringList>

#include <optional>

namespace FileManager {
std::optional<QString> readFromFile(const Path &path) const;

std::optional<QStringList> readFromDir(const Path &path) const;

void writeToFile(const Path &path, const QString &content) const;

bool removeFile(const Path &path) const;
} // namespace FileManager

// @todo Remove class and replace by the namespace

class FileManager final
{
    std::optional<QFile> createFile(
        const Path &path) const; // @todo Should be inside the anon namespace in the source file

    std::optional<QFile> getFile(
        const Path &path) const; // @todo Should be inside the anon namespace in the source file

public:
    std::optional<QString> readFromFile(const Path &path) const;

    std::optional<QStringList> readFromDir(const Path &path) const;

    void writeToFile(const Path &path, const QString &content) const;

    bool removeFile(const Path &path) const;
};
