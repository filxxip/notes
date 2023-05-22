#pragma once
#include <QColor>
#include <QDebug>
#include <QObject>

class ColorPicker : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QColor color MEMBER color CONSTANT)

    QColor color;

public:
    ColorPicker(QObject *obj = nullptr);

    void setColor(const QColor &newColor);

signals:
    void colorChanged(const QColor &newColor);
};
