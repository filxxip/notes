#pragma once

#include <QString>

#include "../statuses.h"

struct EntryFieldModel
{
    ModelStatuses::PersonComponents componentEnum;
    QString placeholder;
    QString value = "";
    QColor color = "red";
    bool passwordStatus = false;
};
