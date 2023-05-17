#include "logcontroller.h"
#include "specificcontrollers/guestcontroller.h"
#include "specificcontrollers/logincontroller.h"
#include "specificcontrollers/registercontroller.h"
#include "src/backend/datamanager/directobjsmanagers/ids/idsmanager.h"
#include <utility>

namespace {
constexpr const char *REGISTER_CONTROLLER_NAME = "registerController";
constexpr const char *LOGIN_CONTROLLER_NAME = "loginController";
constexpr const char *GUEST_CONTROLLER_NAME = "guestController";

constexpr char LOGIN_TEXT[] = "login";
constexpr char REGISTER_TEXT[] = "register";
constexpr char GUEST_TEXT[] = "log as guest";

std::unique_ptr<SingletonObjectManager<Person>> generateController(
    std::shared_ptr<PeopleManager> ptr,
    std::shared_ptr<DataClient> dataClient,
    DatabaseCodes::Names code)
{
    return std::make_unique<SingletonObjectManager<Person>>(std::make_unique<IdsManager>(code,
                                                                                         dataClient),
                                                            ptr);
}

} // namespace

LogController::LogController(std::shared_ptr<PrevEnumViewController> mainViewController,
                             std::shared_ptr<DataClient> dataClient,
                             QPointer<DialogController> dialogController_,
                             QObject *obj)
    : QObject(obj)
    , prevViewController(mainViewController)
    , logoutManager(std::make_unique<IdsManager>(DatabaseCodes::Names::PEOPLE_LOGOUT, dataClient),
                    std::make_shared<PeopleManager>(DatabaseCodes::Names::PEOPLE, dataClient))
    , logViewController(
          ViewControllerGenerators::createSwitcherViewContorller(
              FastModelBuilder<SwitcherModel<EnumStatus>, ModelStatuses::UserViewsRoles>(this)
                  .add(ModelStatuses::UserViewsRoles::TEXT, &SwitcherModel<EnumStatus>::text)
                  .add(ModelStatuses::UserViewsRoles::TYPE, &SwitcherModel<EnumStatus>::type)
                  .build({{LOGIN_TEXT, EnumStatus::LOGIN},
                          {REGISTER_TEXT, EnumStatus::REGISTER},
                          {GUEST_TEXT, EnumStatus::GUEST}}),
              EnumStatus::LOGIN,
              this)
              ->getController())
{
    auto ptr = std::make_shared<PeopleManager>(DatabaseCodes::Names::PEOPLE, dataClient);
    controllers = {
        {EnumStatus::REGISTER,
         new RegisterController(mainViewController,
                                generateController(ptr,
                                                   dataClient,
                                                   DatabaseCodes::Names::PEOPLE_REGISTER),
                                ptr,
                                dialogController_,
                                this)},
        {EnumStatus::LOGIN,
         new LoginController(mainViewController,
                             generateController(ptr, dataClient, DatabaseCodes::Names::PEOPLE_LOGIN),
                             ptr,
                             dialogController_,
                             this)},
        {EnumStatus::GUEST,
         new GuestController(mainViewController,
                             generateController(ptr, dataClient, DatabaseCodes::Names::PEOPLE_LOGIN),
                             dialogController_,
                             this)}};

    for (const auto &[enumType, name] :
         {std::make_pair(EnumStatus::REGISTER, REGISTER_CONTROLLER_NAME),
          std::make_pair(EnumStatus::GUEST, GUEST_CONTROLLER_NAME),
          std::make_pair(EnumStatus::LOGIN, LOGIN_CONTROLLER_NAME)}) {
        ownerData->insert(name, QVariant::fromValue(controllers[enumType].data()));
    }

    connect(logViewController, &ViewController::userViewTypeChanged, [this] {
        emit controllers[EnumStatus::REGISTER]->clear();
    });

    DatabaseUtilsFunctions::tickWait(
        400,
        [this] {
            if (logoutManager.isDataAvaible()) {
                auto obj = logoutManager.get();
                prevViewController->setUserViewType(ModelStatuses::MainUserViews::LOG);
            }
        },
        this);
}
