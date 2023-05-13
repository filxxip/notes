#pragma once

#include "../userconfigcontroller.h"

class RegisterController final : public UserConfigController
{
    Q_OBJECT

    std::shared_ptr<PeopleManager> manager;

public:
    RegisterController(QPointer<CalendarController> calendarController,
                       std::shared_ptr<PeopleManager> peopleManager,
                       QPointer<DialogController> dialogController_,
                       QObject *obj = nullptr);

public slots:
    void onConfirmed() override;
};
