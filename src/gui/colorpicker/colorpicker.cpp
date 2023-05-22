#include "colorpicker.h"

ColorPicker::ColorPicker(QObject *obj)
    : QObject(obj)
{
    connect(this, &ColorPicker::colorChanged, [this](const auto &newcolor) { color = newcolor; });
}

void ColorPicker::setColor(const QColor &newColor)
{
    emit colorChanged(newColor);
}
