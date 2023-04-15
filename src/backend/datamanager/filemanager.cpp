#include "filemanager.h"

//QString FileManager::getMainFileSrc() const
//{
//    QString current = __FILE__;
//    current.replace("src/controller/abstract_data_client.cpp", "");
//    return current;
//}

std::optional<QString> FileManager::readFromFile(const Path &path) const
{
    if (!QFileInfo::exists(path.getFullPath())) {
        return {};
    }
    QFile file(path.getFullPath());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return {};
    }
    return file.readAll();
}

void FileManager::writeToFile(const Path &path, const QString &content) const
{
    readFromFile(path);
    auto p = path.getFullPath();
    QFile file(path.getFullPath());
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Cannot write data to file";
    }
    QTextStream out(&file);
    out << content;
}

bool FileManager::removeFile(const Path &path) const
{
    QFile file(path.getFullPath());
    qDebug() << "xxx";
    return file.remove();
}
