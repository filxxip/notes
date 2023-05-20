#include "userconfigcontroller.h"

namespace {
constexpr const char *FEMALE_TEXT_BUTTON = "female";
constexpr const char *MALE_TEXT_BUTTON = "male";

} // namespace

namespace UserConfigControllerUtils {

QPointer<RadioButtonController> generateRadioButton(QObject *object)
{
    return new RadioButtonController({RadioButtonModel(MALE_TEXT_BUTTON, true, 1),
                                      RadioButtonModel(FEMALE_TEXT_BUTTON, false, 1)},
                                     object);
}

void connectClear(EntryController *obj,
                  QPointer<CalendarController> calendar,
                  QPointer<RadioButtonController> radioButton)
{
    obj->connect(obj, &EntryController::clear, [calendar, radioButton] {
        calendar->clear();
        radioButton->setValue(0, true);
    });
}
} // namespace UserConfigControllerUtils
