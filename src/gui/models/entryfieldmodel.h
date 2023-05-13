#pragma once

#include <QColor>
#include <QString>

#include "../statuses.h"

struct EntryFieldModel
{
    ModelStatuses::PersonComponents componentEnum;
    QString placeholder;
    QString value;
    QColor color{Qt::GlobalColor::red};
    bool passwordStatus = false;
};
