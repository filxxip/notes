#pragma once
#include <QString>
#include <memory>
#include <nlohmann/json.hpp>
namespace {
using json = nlohmann::json;
}

class DataClient
{
public:
    enum class Operation { GET, UPDATE, DELETE, ADD };

    virtual void setAdditionalParameters(const QString &) = 0;

    virtual void update(const QString &) const = 0;

    virtual void remove(const QString &) const = 0;

    virtual void add(const QString &) const = 0;

    virtual std::optional<json> get(const QString &) const = 0;
};

class Path
{
public:
    enum class InitType { ABSOLUTE, RELATIVE };

    virtual QString getFullPath() const = 0;
    virtual QString getRelativePath() const = 0;
};

class FilePath : public Path
{
    QString getMainFileSrc() const
    {
        QString current = __FILE__;
        current.replace("src/controller/abstract_data_client.cpp", "");
        return current;
    }

    QString path;

public:
    FilePath(const QString &path_, InitType type = InitType::RELATIVE)
    {
        if (type == InitType::RELATIVE) {
            path = getMainFileSrc() + path_;
        }
        if (type == InitType::ABSOLUTE) {
            path = path_;
        }
    }

    QString getFullPath() const { return path; }

    QString getRelativePath() const { return QString(path).replace(getMainFileSrc(), ""); }

    FilePath &addNumericPart(int number)
    {
        path = path + "/" + QString::number(number) + ".txt";
        return *this;
    }
    FilePath &addStringPart(QString string)
    {
        path = path + "/" + string;
        return *this;
    }
};
