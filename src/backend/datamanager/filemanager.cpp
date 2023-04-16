#include "filemanager.h"

std::optional<QFile> FileManager::createFile(const Path &path) const
{
    if (!path.exists()) {
        return {};
    }
    return std::make_optional<QFile>(path.getFullPath());
}

std::optional<QString> FileManager::readFromFile(const Path &path) const
{
    auto file = createFile(path);
    if (!file.has_value() || !file->open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open file";
        return {};
    }
    return file->readAll();
}

void FileManager::writeToFile(const Path &path, const QString &content) const
{
    auto file = createFile(path);
    if (!file.has_value() || !file->open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Cannot write data to file";
        return;
    }
    QTextStream out(&file.value());
    out << content;
}

bool FileManager::removeFile(const Path &path) const
{
    auto file = createFile(path);
    if (!file.has_value() || !file->open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Cannot write data to file";
    }
    return file->remove();
}
