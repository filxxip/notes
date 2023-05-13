#pragma once

#include "../userconfigcontroller.h"

class RegisterController final : public UserConfigController
{
    Q_OBJECT

    PeopleManager manager;

public:
    RegisterController(QPointer<CalendarController> calendarController,
                       std::shared_ptr<DataClient> dataclient_,
                       QPointer<DialogController> dialogController_,
                       QObject *obj = nullptr);

public slots:
    void onConfirmed() override;
};
