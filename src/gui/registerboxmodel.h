#pragma once
#include "customlistviewmodel.h"

struct EntryFieldModel
{
    QString placeholder;
    QString value = "";
};

class RegisterViewModel : public CustomListModel<EntryFieldModel>
{
    Q_OBJECT

public:
    enum Roles { PLACEHOLDER, VALUE };

    RegisterViewModel(QObject *parent = nullptr)
        : CustomListModel(parent)
    {
        QVector<EntryFieldModel> data;
        data.push_back(EntryFieldModel{"Name..."});
        data.push_back(EntryFieldModel{"Surname..."});
        data.push_back(EntryFieldModel{"Email..."});
        data.push_back(EntryFieldModel{"Password..."});
        data.push_back(EntryFieldModel{"Country..."});
        setEntries(std::move(data));
        ADD_DATA(PLACEHOLDER, placeholder)
        ADD_DATA(VALUE, value)
    }
};
