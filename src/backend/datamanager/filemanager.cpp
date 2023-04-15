#include "filemanager.h"

QString FileManager::getMainFileSrc() const
{
    QString current = __FILE__;
    current.replace("src/controller/abstract_data_client.cpp", "");
    return current;
}

std::optional<QString> FileManager::readFromFile(const QString &path) const
{
    auto newPath = getMainFileSrc() + path;
    if (!QFileInfo::exists(newPath)) {
        qDebug() << path;
        qDebug() << "File doesn't exist!";
        return {};
    }
    QFile file(newPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file:" << file.errorString();
        return {};
    }
    return file.readAll();
}

void FileManager::writeToFile(const QString &path, const QString &content) const
{
    auto newPath = getMainFileSrc() + path;
    QFile file(newPath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Cannot write data to file";
    }
    QTextStream out(&file);
    out << content;
}

bool FileManager::removeFile(const QString &path) const
{
    QFile file(getMainFileSrc() + path);
    return file.remove();
}
