#pragma once

#include <QString>

template<typename EnumType>
struct SwitcherModel
{
    QString text;
    EnumType type;
};
