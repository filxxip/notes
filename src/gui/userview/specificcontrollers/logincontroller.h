#pragma once

#include "../entrycontroller.h"

class LoginController final : public EntryController
{
    Q_OBJECT

    std::shared_ptr<PeopleManager> manager;

public:
    LoginController(std::unique_ptr<SingletonObjectManager<Person>> singleLoginPersonManager_,
                    std::shared_ptr<PeopleManager> peopleManager,
                    QPointer<DialogController> dialogController_,
                    QObject *obj = nullptr);

public slots:
    void onConfirmed() override;
};
