#pragma once
#include <QColor>
#include <QDebug>
#include <QObject>
#include <functional>

class ColorPicker : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QColor color MEMBER color NOTIFY colorChanged)
    Q_PROPERTY(bool globalMode MEMBER globalMode NOTIFY globalModeChanged)

    QColor color;
    bool globalMode = false;

public:
    ColorPicker(QObject *obj = nullptr);

    Q_INVOKABLE void setColor(const QColor &newColor);

    Q_INVOKABLE void reset();

signals:
    void colorChangedLocally(const QColor &newColor);

    void colorChanged(const QColor &newColor);

    void globalModeChanged(bool mode);
};
