#pragma once

#include <QDate>
#include <QString>
#include <algorithm>
#include <memory>
#include <unordered_map>

class BasicDatabaseData
{
protected:
    QString __name__;

public:
    BasicDatabaseData(QString name);

    virtual void set(QString newvalue) = 0;

    virtual BasicDatabaseData &operator=(QString other) noexcept;

    virtual const QString &get() const = 0;
};

class IDDatabaseData final : public BasicDatabaseData
{
protected:
    QString value;

public:
    using BasicDatabaseData::operator=;

    IDDatabaseData(QString name);

    void set(QString newvalue) override;

    const QString &get() const override;
};

class DatabaseData final : public BasicDatabaseData
{
    std::shared_ptr<std::unordered_map<QString, QString>> updatedKeyMap;
    std::shared_ptr<std::unordered_map<QString, QString>> keyMap;
    bool canbeupdated = false;

    void updateMap(const QString &val, std::shared_ptr<std::unordered_map<QString, QString>> &map);

public:
    using BasicDatabaseData::operator=;

    DatabaseData(QString name,
                 std::shared_ptr<std::unordered_map<QString, QString>> updatedkeyMap_,
                 std::shared_ptr<std::unordered_map<QString, QString>> keyMap_);

    const QString &get() const override;

    void set(QString newvalue) override;
};
