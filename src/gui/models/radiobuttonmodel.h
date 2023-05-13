#pragma once
#include <QString>

struct RadioButtonModel
{
    QString text;
    bool value;
    int group; //0 -> individual group, 1, 2, 3 combined group
};
