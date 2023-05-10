#pragma once

#include <QPointer>
#include "../../customdialog/dialogcontroller.h"
#include "../entrycontroller.h"

class GuestController final : public EntryController
{
    Q_OBJECT
public:
    GuestController(QPointer<DialogController> dialogController_, QObject *obj = nullptr);

public slots:
    void onConfirmed() override;
};
