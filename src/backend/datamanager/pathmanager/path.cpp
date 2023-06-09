#include "path.h"
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QStringList>

namespace {
constexpr char RELATIVE_PATH[] = "/src/backend/datamanager/pathmanager/path.cpp";
constexpr char HOST[] = "http://127.0.0.1:5000";
constexpr char PATH_FROM_BASE[] = "/data";
constexpr char DELIMETER[] = "/";
} // namespace

Path::Path(const QString &path_)
    : path(path_)
{}

QString Path::getFullPath() const
{
    return getMainFileSrc() + DELIMETER + path;
}

QString Path::getRelativePath() const
{
    return path;
}
Path &Path::addPart(QString string)
{
    path = path + DELIMETER + string;
    return *this;
}
Path &Path::add(QString string)
{
    path += string;
    return *this;
}

QString FilePath::getMainFileSrc() const
{
    QString current = __FILE__;
    current.replace(RELATIVE_PATH, PATH_FROM_BASE);
    return current;
}

FilePath::FilePath(const QString &path_, Type type)
    : Path((type == Type::NORMAL) ? path_ : QString(path_).replace(getMainFileSrc(), ""))
{}

bool FilePath::exists() const
{
    return QFileInfo::exists(getFullPath()); //idk
}

QString FilePath::lastWithoutExtension() const
{
    auto paths = path.split(DELIMETER);
    auto brokenFile = paths.last().split(".");
    return brokenFile.at(0);
}

QString UrlPath::getMainFileSrc() const
{
    return HOST;
}

UrlPath::UrlPath(const QString &path_)
    : Path(path_)
{}

bool UrlPath::exists() const
{
    return true; //idk
}
