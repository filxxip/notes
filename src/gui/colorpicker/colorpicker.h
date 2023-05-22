#pragma once
#include <QColor>
#include <QDebug>
#include <QObject>
#include <functional>

class ColorPicker : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QColor color MEMBER color NOTIFY colorChanged)

    QColor color;

public:
    ColorPicker(QObject *obj = nullptr);

    Q_INVOKABLE void setColor(const QColor &newColor);

    Q_INVOKABLE void reset();

signals:
    void colorChanged(const QColor &newColor);
};
