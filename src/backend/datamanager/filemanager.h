#pragma once

#include "dataclient.h"

#include <QDir>
#include <QFile>
#include <QStringList>

#include <optional>

namespace FileManager {
std::optional<QString> readFromFile(const Path &path);

std::optional<QStringList> readFromDir(const Path &path);

void writeToFile(const Path &path, const QString &content);

bool removeFile(const Path &path);
} // namespace FileManager
