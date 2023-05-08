#pragma once

#include "../entrycontroller.h"

class LoginController : public EntryController
{
    Q_OBJECT

    PeopleManager manager; //shared pointer pozniej, ktory bedzie trzymany przez glowny controller

public:
    LoginController(std::shared_ptr<DataClient> dataclient_,
                    QPointer<DialogController> dialogController_,
                    QObject *obj = nullptr);

public slots:
    void onConfirmed() override;
};
