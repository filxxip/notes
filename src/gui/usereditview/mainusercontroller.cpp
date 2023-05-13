#include "mainusercontroller.h"

MainUserController::MainUserController(QPointer<CalendarController> calendarController,
                                       QPointer<DialogController> dialogController,
                                       QObject *obj)
    : QObject(obj)
    , switcherModel(FastModelBuilder<SwitcherModel<EnumStatus>, ModelStatuses::UserViewsRoles>(this)
                        .add(ModelStatuses::UserViewsRoles::TEXT, &SwitcherModel<EnumStatus>::text)
                        .add(ModelStatuses::UserViewsRoles::TYPE, &SwitcherModel<EnumStatus>::type)
                        .build())
    , userEditController(new UserEditController(calendarController, dialogController, this))
{
    switcherModel->addEntry({"profile", EnumStatus::EDIT});
    switcherModel->addEntry({"notebook", EnumStatus::NOTEBOOK});
}
