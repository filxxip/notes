#pragma once

#include <QPointer>
#include "../../customdialog/dialogcontroller.h"
#include "../entrycontroller.h"

class GuestController final : public EntryController
{
    Q_OBJECT
    std::shared_ptr<PeopleManager> manager;

public:
    GuestController(std::shared_ptr<PrevEnumViewController> mainViewController_,
                    std::unique_ptr<SingletonObjectManager<Person>> singleLoginPersonManager,
                    std::shared_ptr<PeopleManager> peopleManager_,
                    QPointer<DialogController> dialogController_,
                    QObject *obj = nullptr);

public slots:
    void onConfirmed() override;
};
