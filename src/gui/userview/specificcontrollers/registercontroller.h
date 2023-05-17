#pragma once

#include "../userconfigcontroller.h"

class RegisterController final : public UserConfigController
{
    Q_OBJECT

    std::shared_ptr<PeopleManager> manager;

public:
    RegisterController(std::shared_ptr<PrevEnumViewController> mainViewController_,
                       std::unique_ptr<SingletonObjectManager<Person>> singleLoginPersonManager,
                       std::shared_ptr<PeopleManager> peopleManager,
                       QPointer<DialogController> dialogController_,
                       QObject *obj = nullptr);

public slots:
    void onConfirmed() override;
};
