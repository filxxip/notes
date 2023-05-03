#pragma once
#include "customlistviewmodel.h"
#include "statuses.h"

#include <QColor>

struct EntryFieldModel
{
    ModelStatuses::PersonComponents componentEnum;
    QString placeholder;
    QString value = "";
    QColor color = "red";
    bool passwordStatus = false;
};

class RegisterViewModel : public CustomListModel<EntryFieldModel, ModelStatuses::Roles>
{
public:
    RegisterViewModel(QObject *parent = nullptr)
        : CustomListModel(parent)
    {
        ADD_DATA(ModelStatuses::Roles::PLACEHOLDER, placeholder)
        ADD_DATA(ModelStatuses::Roles::VALUE, value)
        ADD_DATA(ModelStatuses::Roles::COLOR, color)
        ADD_DATA(ModelStatuses::Roles::PASS_STATUS, passwordStatus)
    }
    int indexOf(ModelStatuses::PersonComponents componentEnum)
    {
        auto dist = std::distance(m_data.begin(),
                                  std::find_if(m_data.begin(),
                                               m_data.end(),
                                               [componentEnum](const auto &data) {
                                                   return data.componentEnum == componentEnum;
                                               }));
        return dist == m_data.size() ? -1 : dist;
    }
};
