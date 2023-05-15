#include "filemanager.h"

#include <QFileInfo>
#include <QStringLiteral>

namespace {

bool isFileReadable(std::optional<QFile> &file)
{
    return file.has_value() && file->open(QIODevice::ReadOnly | QIODevice::Text);
}

bool isFileWritable(std::optional<QFile> &file)
{
    return file.has_value() && file->open(QIODevice::WriteOnly | QIODevice::Text);
}

std::optional<QFile> createFile(const Path &path)
{
    return std::make_optional<QFile>(path.getFullPath());
}

std::optional<QFile> getFile(const Path &path)
{
    if (!path.exists()) {
        return {};
    }
    return createFile(path);
}

const auto CANNOT_READ_FILE = QStringLiteral("Cannot open file %1");
const auto CANNOT_WRITE_FILE = QStringLiteral("Cannot write to file %1");

} // namespace

namespace FileManager {

std::optional<QString> readFromFile(const Path &path)
{
    auto file = getFile(path);
    if (!isFileReadable(file)) {
        qDebug() << CANNOT_READ_FILE.arg(path.getFullPath());
        return std::nullopt;
    }
    return file->readAll();
}

std::optional<QStringList> readFromDir(const Path &path)
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
    return std::nullopt;
}

void writeToFile(const Path &path, const QString &content)
{
    auto file = createFile(path);
    if (!isFileWritable(file)) {
        qDebug() << CANNOT_WRITE_FILE.arg(path.getFullPath());
        return;
    }
    QTextStream out(&file.value());
    out << content;
}

bool removeFile(const Path &path)
{
    auto file = getFile(path);
    if (!isFileWritable(file)) {
        qDebug() << CANNOT_WRITE_FILE.arg(path.getFullPath());
        return false;
    }
    return file->remove();
}
} // namespace FileManager
