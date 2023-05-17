#include "logcontroller.h"
#include "specificcontrollers/guestcontroller.h"
#include "specificcontrollers/logincontroller.h"
#include "specificcontrollers/registercontroller.h"
#include <utility>

namespace {
constexpr const char *REGISTER_CONTROLLER_NAME = "registerController";
constexpr const char *LOGIN_CONTROLLER_NAME = "loginController";
constexpr const char *GUEST_CONTROLLER_NAME = "guestController";

constexpr char LOGIN_TEXT[] = "login";
constexpr char REGISTER_TEXT[] = "register";
constexpr char GUEST_TEXT[] = "log as guest";

std::unique_ptr<SingletonObjectManager<Person>> generateController(
    std::shared_ptr<DataClient> dataClient, DatabaseCodes::Names code)
{
    return std::make_unique<SingletonObjectManager<Person>>(
        std::make_unique<PeopleManager>(DatabaseCodes::namesMap.at(code), dataClient));
}

} // namespace

LogController::LogController(
    std::shared_ptr<AbstractViewControllerAdapter<ModelStatuses::MainUserViews>> mainViewController,
    std::shared_ptr<DataClient> dataClient,
    QPointer<CalendarController> calendarController_,
    QPointer<DialogController> dialogController_,

    QObject *obj)
    : QObject(obj)
    , prevViewController(mainViewController)
    , calendarController(calendarController_)
    , logoutManager(std::make_unique<PeopleManager>(DatabaseCodes::namesMap.at(
                                                        DatabaseCodes::Names::PEOPLE_LOGOUT),
                                                    dataClient))
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
    auto ptr = std::make_shared<PeopleManager>(DatabaseCodes::namesMap.at(
                                                   DatabaseCodes::Names::PEOPLE),
                                               dataClient);
    controllers
        = {{EnumStatus::REGISTER,
            new RegisterController(generateController(dataClient,
                                                      DatabaseCodes::Names::PEOPLE_REGISTER),
                                   calendarController,
                                   ptr,
                                   dialogController_,
                                   this)},
           {EnumStatus::LOGIN,
            new LoginController(generateController(dataClient, DatabaseCodes::Names::PEOPLE_LOGIN),
                                ptr,
                                dialogController_,
                                this)},
           {EnumStatus::GUEST,
            new GuestController(generateController(dataClient, DatabaseCodes::Names::PEOPLE_LOGIN),
                                dialogController_,
                                this)}};

    for (const auto &[enumType, name] :
         {std::make_pair(EnumStatus::REGISTER, REGISTER_CONTROLLER_NAME),
          std::make_pair(EnumStatus::GUEST, GUEST_CONTROLLER_NAME),
          std::make_pair(EnumStatus::LOGIN, LOGIN_CONTROLLER_NAME)}) {
        ownerData->insert(name, QVariant::fromValue(controllers[enumType].data()));
    }

    //    switcherModel = FastModelBuilder<SwitcherModel<EnumStatus>, ModelStatuses::UserViewsRoles>(this)
    //                        .add(ModelStatuses::UserViewsRoles::TEXT, &SwitcherModel<EnumStatus>::text)
    //                        .add(ModelStatuses::UserViewsRoles::TYPE, &SwitcherModel<EnumStatus>::type)
    //                        .build();

    //    switcherModel->addEntry({LOGIN_TEXT, EnumStatus::LOGIN});
    //    switcherModel->addEntry({REGISTER_TEXT, EnumStatus::REGISTER});
    //    switcherModel->addEntry({GUEST_TEXT, EnumStatus::GUEST});

    DatabaseUtilsFunctions::tickWait(
        400,
        [this] {
            if (logoutManager.isDataAvaible()) {
                auto obj = logoutManager.get();
                prevViewController->setUserViewType(ModelStatuses::MainUserViews::LOG);
                //                emit mainViewChanged(ModelStatuses::MainUserViews::LOG);
            }
        },
        this);
}

//LogController::EnumStatus LogController::getUserView() const
//{
//    return m_userView;
//}

//void LogController::setUserView(EnumStatus newView)
//{
//    emit controllers[m_userView]->clear();
//    m_userView = newView;
//    emit userViewChanged();
//}
