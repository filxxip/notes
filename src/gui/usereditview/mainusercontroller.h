#pragma once
#include <QObject>
#include "../models/switchermodel.h"
#include "../models/userviewlistmodel.h"
#include "../modelutils/listmodelbuilder.h"
#include "../statuses.h"

class MainUserController : public QObject
{
    using EnumStatus = ModelStatuses::InnerUserEditViews;
    using UserSwitcherModel
        = CustomListModel<SwitcherModel<EnumStatus>, ModelStatuses::InnerUserEditViews>;

    Q_PROPERTY(EnumStatus userViewType MEMBER m_userView NOTIFY userViewChanged)

    Q_PROPERTY(UserSwitcherModel *switcherModel MEMBER switcherModel CONSTANT)

    Q_OBJECT
public:
    MainUserController(QObject *obj = nullptr)
        : QObject(obj)
    {
        switcherModel = FastModelBuilder<SwitcherModel<EnumStatus>, EnumStatus>(this)
                            .add(EnumStatus::EDIT, &SwitcherModel<EnumStatus>::text)
                            .build();
        switcherModel->addEntry({"profile", EnumStatus::EDIT});
        switcherModel->addEntry({"pro3file", EnumStatus::EDIT});
        switcherModel->addEntry({"pro4file", EnumStatus::EDIT});
        switcherModel->addEntry({"prof5ile", EnumStatus::EDIT});
    }

private:
    QPointer<UserSwitcherModel> switcherModel;

    EnumStatus m_userView = EnumStatus::EDIT;
signals:
    void userViewChanged();
};
