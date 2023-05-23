#include "colorpicker.h"

ColorPicker::ColorPicker(QObject *obj)
    : QObject(obj)
{}

void ColorPicker::setColor(const QColor &newColor)
{
    qDebug() << "cost am";
    qDebug() << newColor;
    qDebug() << newColor.name();
    color = newColor;
    emit colorChangedLocally(newColor);
    if (globalMode) {
        emit colorChanged(newColor);
    }
}

void ColorPicker::reset()
{
    globalMode = false;
    setColor("black");
}
//void ColorPicker::applyColorChangedActivity(std::function<void()> func)
//{
//    afterColorChangedActivity = std::move(func);
//}
