#pragma once
#include <QDateTime>
#include <QObject>
#include <QPointer>
#include <QProperty>
#include <QQmlPropertyMap>
#include <QTimer>

class ClockController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QQmlPropertyMap *clock MEMBER clock CONSTANT)

    QPointer<QQmlPropertyMap> clock = new QQmlPropertyMap(this);

private:
    QTimer timer{this};
    QDateTime current;

public:
    ClockController(QObject *obj = nullptr)
        : QObject(obj)
    {
        connect(&timer, &QTimer::timeout, this, &ClockController::updateTime);
        timer.start(999);

        this->clock->insert("hour", 0);
        this->clock->insert("minute", 0);
        this->clock->insert("second", 0);

        this->clock->insert("day", 0);
        this->clock->insert("month", 0);
        this->clock->insert("year", 0);

        updateTime();
    }
private slots:

    void updateTime()
    {
        auto currentTime = current.currentDateTime();
        auto time = currentTime.time();
        auto date = currentTime.date();

        this->clock->setProperty("hour", time.hour());
        this->clock->setProperty("minute", time.minute());
        this->clock->setProperty("second", time.second());

        this->clock->setProperty("day", date.day());
        this->clock->setProperty("month", date.month());
        this->clock->setProperty("year", date.year());
    }
};
