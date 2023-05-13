#pragma once
#include <QDateTime>
#include <QObject>
#include <QPointer>
#include <QProperty>
#include <QQmlPropertyMap>
#include <QTimer>
#include "../cpputils/utils.h"

class ClockController final : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QQmlPropertyMap *clock MEMBER clock CONSTANT)

    QPointer<QQmlPropertyMap> clock = new QQmlPropertyMap(this);

private:
    QTimer timer{this};
    QDateTime current;

public:
    ClockController(QObject *obj = nullptr);

private slots:

    void updateTime();
};
