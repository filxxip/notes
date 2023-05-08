#pragma once

#include "../entrycontroller.h"

class RegisterController : public EntryController
{
    Q_OBJECT
    Q_PROPERTY(int someval MEMBER val CONSTANT)
    Q_PROPERTY(RadioButtonController *radioButtonController MEMBER radioButtonController CONSTANT)
    Q_PROPERTY(CalendarController *calendarController MEMBER calendarController CONSTANT)
    int val = 10;
    PeopleManager manager;

    QPointer<CalendarController> calendarController;
    QPointer<RadioButtonController> radioButtonController;

    QString getPartOfPerson(EnumStatus componentEnum) const;

public:
    RegisterController(QPointer<CalendarController> calendarController,
                       std::shared_ptr<DataClient> dataclient_,
                       QPointer<DialogController> dialogController_,
                       QObject *obj = nullptr);

public slots:
    void onConfirmed() override;
};
