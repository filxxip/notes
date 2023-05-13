#pragma once

#include "entrycontroller.h"

class UserConfigController : public EntryController
{
    Q_OBJECT
    Q_PROPERTY(RadioButtonController *radioButtonController MEMBER radioButtonController CONSTANT)
    Q_PROPERTY(CalendarController *calendarController MEMBER calendarController CONSTANT)

protected:
    QPointer<CalendarController> calendarController;
    QPointer<RadioButtonController> radioButtonController;

    QString getPartOfPerson(EnumStatus componentEnum) const;

public:
    UserConfigController(QPointer<CalendarController> calendarController,
                         QPointer<DialogController> dialogController_,
                         QObject *obj = nullptr);
};
