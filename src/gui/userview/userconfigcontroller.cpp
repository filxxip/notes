#include "userconfigcontroller.h"

namespace {
constexpr const char *FEMALE_TEXT_BUTTON = "female";
constexpr const char *MALE_TEXT_BUTTON = "male";

} // namespace

UserConfigController::UserConfigController(QPointer<CalendarController> calendarController_,
                                           QPointer<DialogController> dialogController_,
                                           QObject *obj)
    : EntryController(dialogController_, obj)
    , calendarController(calendarController_)
{
    radioButtonController = new RadioButtonController({RadioButtonModel(MALE_TEXT_BUTTON, true, 1),
                                                       RadioButtonModel(FEMALE_TEXT_BUTTON,
                                                                        false,
                                                                        1)},
                                                      this);

    connect(this,
            &UserConfigController::clear,
            [this] { //from level of qml also entries are cleared, they react on clear signal
                calendarController->clear();
                radioButtonController->setValue(0, true);
            });
}

QString UserConfigController::getPartOfPerson(EnumStatus componentEnum) const
{
    auto index = model->indexOf(componentEnum);
    return model->data(index, ModelStatuses::Roles::VALUE).value<QString>();
}
