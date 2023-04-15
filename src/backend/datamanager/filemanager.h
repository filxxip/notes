#pragma once
#include <QDir>
#include <QFile>
#include <QString>

class FileManager
{
    QString getMainFileSrc() const;

public:
    std::optional<QString> readFromFile(const QString &path) const;

    void writeToFile(const QString &path, const QString &content) const;

    bool removeFile(const QString &path) const;
};
