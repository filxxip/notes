#pragma once

#include <QString>

class Path
{
protected:
    QString path;

    virtual QString getMainFileSrc() const = 0;

public:
    Path(const QString &path_);

    QString getFullPath() const;

    QString getRelativePath() const;

    virtual Path &addPart(QString string);

    virtual Path &add(QString string);

    virtual bool exists() const = 0;
};

class FilePath : public Path
{
protected:
    QString getMainFileSrc() const override;

public:
    enum class Type { ABSOLUTE, NORMAL };

    FilePath(const QString &path_, Type type = Type::NORMAL);

    QString lastWithoutExtension() const;

    bool exists() const override;
};

class UrlPath : public Path
{
protected:
    QString getMainFileSrc() const override;

public:
    UrlPath(const QString &path_);

    bool exists() const override;
};
