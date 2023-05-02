#include "filemanager.h"

std::optional<QFile> FileManager::createFile(const Path &path) const
{
    return std::make_optional<QFile>(path.getFullPath()); //powinien robic check directory
}

std::optional<QFile> FileManager::getFile(const Path &path) const
{
    if (!path.exists()) {
        return {};
    }
    return createFile(path);
}

std::optional<QString> FileManager::readFromFile(const Path &path) const
{
    auto file = getFile(path);
    if (!file.has_value() || !file->open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open file";
        return {};
    }
    return file->readAll();
}

std::optional<QStringList> FileManager::readFromDir(const Path &path) const
{
    auto dir = QDir(path.getFullPath());
    if (dir.exists()) {
        QStringList list;
        for (const auto &name : dir.entryInfoList(QDir::Files)) {
            auto content = readFromFile(FilePath(name.absoluteFilePath(), FilePath::Type::ABSOLUTE));
            if (content.has_value()) {
                list.append(content.value());
            }
        }
        return list;
    }
    return {};
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
    auto file = getFile(path);
    if (!file.has_value() || !file->open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Cannot write data to file";
    }
    return file->remove();
}
