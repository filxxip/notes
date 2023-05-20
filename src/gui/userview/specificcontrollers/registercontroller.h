#pragma once

#include "../userconfigcontroller.h"

class RegisterController final : public EntryController
{
    Q_OBJECT

    Q_PROPERTY(RadioButtonController *radioButtonController MEMBER radioButtonController CONSTANT)
    Q_PROPERTY(CalendarController *calendarController MEMBER calendarController CONSTANT)

    std::shared_ptr<PeopleManager> manager;

protected:
    QPointer<CalendarController> calendarController;
    QPointer<RadioButtonController> radioButtonController;

public:
    RegisterController(std::shared_ptr<PrevEnumViewController> mainViewController_,
                       std::unique_ptr<SingletonObjectManager<Person>> singleLoginPersonManager,
                       std::shared_ptr<PeopleManager> peopleManager,
                       QPointer<DialogController> dialogController_,
                       QObject *obj = nullptr);

public slots:
    void onConfirmed() override;
};
