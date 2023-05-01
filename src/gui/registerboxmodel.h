#pragma once
#include "customlistviewmodel.h"
#include "statuses.h"

#include <QColor>

struct EntryFieldModel
{
    Statuses::PersonComponents componentEnum;
    QString placeholder;
    QString value = "";
    QColor color = "red";
    bool passwordStatus = false;
};

class RegisterViewModel : public CustomListModel<EntryFieldModel>
{
    Q_OBJECT

public:
    enum Roles { PLACEHOLDER = 0, VALUE, COLOR, PASS_STATUS };

    RegisterViewModel(QObject *parent = nullptr)
        : CustomListModel(parent)
    {
        //        QVector<EntryFieldModel> data;
        //        data.push_back(EntryFieldModel{Statuses::PersonComponents::NAME, "Name..."});
        //        data.push_back(EntryFieldModel{Statuses::PersonComponents::SURNAME, "Surname..."});
        //        data.push_back(EntryFieldModel{Statuses::PersonComponents::EMAIL, "Email..."});
        //        data.push_back(EntryFieldModel{Statuses::PersonComponents::PASSWORD, "Password..."});
        //        data.push_back(EntryFieldModel{Statuses::PersonComponents::COUNTRY, "Country..."});
        //        setEntries(std::move(data));
        ADD_DATA(PLACEHOLDER, placeholder)
        ADD_DATA(VALUE, value)
        ADD_DATA(COLOR, color)
        ADD_DATA(PASS_STATUS, passwordStatus)
    }
    //    Q_INVOKABLE void resetModel()
    //    {
    //        qDebug() << "hello";
    //        //        beginResetModel();
    //        //        endResetModel();
    //    }

    int indexOf(Statuses::PersonComponents componentEnum)
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
