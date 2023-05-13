#pragma once

#include <QColor>
#include <QString>

#include "../statuses.h"

struct EntryFieldModel
{
    ModelStatuses::PersonComponents componentEnum;
    QString placeholder;
    QString value = "";   // @todo What is that?
    QColor color = "red"; // @todo Should be Qt.Color.red
    bool passwordStatus = false;
};
