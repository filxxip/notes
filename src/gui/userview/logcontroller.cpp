#include "logcontroller.h"
#include <utility>

namespace {
constexpr const char *REGISTER_CONTROLLER_NAME = "registerController";
constexpr const char *LOGIN_CONTROLLER_NAME = "loginController";
constexpr const char *GUEST_CONTROLLER_NAME = "guestController";
} // namespace

LogController::LogController(std::shared_ptr<DataClient> dataclient_,
                             QPointer<DialogController> dialogController_,
                             QObject *obj)
    : QObject(obj)
{
    controllers = {{EnumStatus::REGISTER,
                    new RegisterController(calendarController, dataclient_, dialogController_, this)},
                   {EnumStatus::LOGIN, new LoginController(dataclient_, dialogController_, this)},
                   {EnumStatus::GUEST, new GuestController(dialogController_, this)}};

    for (const auto &[enumType, name] :
         {std::make_pair(EnumStatus::REGISTER, REGISTER_CONTROLLER_NAME),
          std::make_pair(EnumStatus::GUEST, GUEST_CONTROLLER_NAME),
          std::make_pair(EnumStatus::LOGIN, LOGIN_CONTROLLER_NAME)}) {
        ownerData->insert(name, QVariant::fromValue(controllers[enumType].data()));
    }

    switcherModel = FastModelBuilder<SwitcherModel<EnumStatus>, ModelStatuses::UserViewsRoles>(this)
                        .add(ModelStatuses::UserViewsRoles::TEXT, &SwitcherModel<EnumStatus>::text)
                        .add(ModelStatuses::UserViewsRoles::TYPE, &SwitcherModel<EnumStatus>::type)
                        .build();

    switcherModel->addEntry({"login", EnumStatus::LOGIN});
    switcherModel->addEntry({"register", EnumStatus::REGISTER});
    switcherModel->addEntry({"log as guest", EnumStatus::GUEST});
    connect(this, &LogController::userViewChanged, [this] {
        qDebug() << "xxsdasd";
        emit controllers[EnumStatus::REGISTER]->clear();
    });
}
