#include "userconfigcontroller.h"

namespace {
constexpr const char *FEMALE_TEXT_BUTTON = "female";
constexpr const char *MALE_TEXT_BUTTON = "male";

} // namespace

UserConfigController::UserConfigController(
    std::shared_ptr<PrevEnumViewController> mainViewController_,
    std::unique_ptr<SingletonObjectManager<Person>> singleLoginPersonManager,
    QPointer<DialogController> dialogController_,
    QObject *obj)
    : EntryController(mainViewController_,
                      std::move(singleLoginPersonManager),
                      dialogController_,
                      obj)
    , calendarController(new CalendarController(this))
{
    radioButtonController = new RadioButtonController({RadioButtonModel(MALE_TEXT_BUTTON, true, 1),
                                                       RadioButtonModel(FEMALE_TEXT_BUTTON,
                                                                        false,
                                                                        1)},
                                                      this);

    //from level of qml also entries are cleared, they react on clear signal
    connect(this, &EntryController::clear, [this] {
        calendarController->clear();
        radioButtonController->setValue(0, true);
    });
}

QString UserConfigController::getPartOfPerson(EnumStatus componentEnum) const
{
    auto index = model->indexOf(componentEnum);
    return model->data(index, ModelStatuses::Roles::VALUE).value<QString>();
}
