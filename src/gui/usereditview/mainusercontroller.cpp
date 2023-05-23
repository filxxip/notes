#include "mainusercontroller.h"

namespace {

constexpr char PROFILE_TITLE[] = "profile";
constexpr char NOTEBOOK_TITLE[] = "notebook";
constexpr char EDITOR_TITLE[] = "text editor";
constexpr char PERSON_GLOBAL_ERROR_MESSAGE[]
    = "Invalid person request, none person is set or access data is invalid.";
constexpr int TICK_TIME = 150;

template<typename EditController, typename PrevEnumViewController>
QPointer<EditController> generateLogoutController(
    std::shared_ptr<PrevEnumViewController> mainViewController,
    std::shared_ptr<DataClient> dataClient,
    std::shared_ptr<PeopleManager> manager,
    QPointer<DialogController> dialogController,
    QObject *obj)
{
    return new EditController(mainViewController,
                              std::make_unique<SingletonObjectManager<Person>>(
                                  std::make_unique<IdsManager>(DatabaseCodes::Names::PEOPLE_LOGOUT,
                                                               dataClient),
                                  manager),
                              dialogController,
                              obj);
}
} // namespace

void MainUserController::moveDataGloabllyToModel()
{
    auto controller = getController();
    auto id = controller->getPersonId();
    if (id.has_value()) {
        if (auto person = manager->get(id.value()); person.has_value()) {
            controller->setNewPerson(person.value());
            return;
        }
    }
    qDebug() << PERSON_GLOBAL_ERROR_MESSAGE;
}

MainUserController::MainUserController(std::shared_ptr<PrevEnumViewController> mainViewController,
                                       std::shared_ptr<DataClient> dataClient,
                                       QPointer<DialogController> dialogController,
                                       QObject *obj)
    : QObject(obj)
    , manager(std::make_shared<PeopleManager>(DatabaseCodes::Names::PEOPLE, dataClient))
    , userEditController(generateController<UserEditController>(dataClient, dialogController))
    , guestEditController(generateController<GuestEditController>(dataClient, dialogController))
    , prevViewController(mainViewController)
    , currentViewController(
          ViewControllerGenerators::createSwitcherViewContorller(
              FastModelBuilder<SwitcherModel<EnumStatus>, ModelStatuses::UserViewsRoles>(this)
                  .add(ModelStatuses::UserViewsRoles::TEXT, &SwitcherModel<EnumStatus>::text)
                  .add(ModelStatuses::UserViewsRoles::TYPE, &SwitcherModel<EnumStatus>::type)
                  .add(ModelStatuses::UserViewsRoles::ENABLED, &SwitcherModel<EnumStatus>::enabled)
                  .build({{PROFILE_TITLE, EnumStatus::EDIT},
                          {NOTEBOOK_TITLE, EnumStatus::NOTEBOOK},
                          {EDITOR_TITLE, EnumStatus::TEXT_EDITOR, false}}),
              EnumStatus::EDIT,
              this)
              ->getController())
{
    emitPersonManagers[ModelStatuses::UserViews::LOGIN]
        = std::make_unique<SingletonObjectManager<Person>>(
            std::make_unique<IdsManager>(DatabaseCodes::Names::PEOPLE_LOGIN, dataClient), manager);
    emitPersonManagers[ModelStatuses::UserViews::REGISTER]
        = std::make_unique<SingletonObjectManager<Person>>(
            std::make_unique<IdsManager>(DatabaseCodes::Names::PEOPLE_REGISTER, dataClient),
            manager);
    emitPersonManagers[ModelStatuses::UserViews::GUEST]
        = std::make_unique<AutoRemoveSingleObjectManager<Person>>(
            std::make_unique<IdsManager>(DatabaseCodes::Names::PEOPLE_GUEST, dataClient), manager);

    connectControllersSignals(userEditController);
    connectControllersSignals(guestEditController);

    DatabaseUtilsFunctions::tickWait(
        TICK_TIME,
        [this] {
            tryToUpdateEditView(ModelStatuses::UserViews::LOGIN,
                                userEditController,
                                ModelStatuses::MainUserViews::EDIT_NORMAL);
            tryToUpdateEditView(ModelStatuses::UserViews::REGISTER,
                                userEditController,
                                ModelStatuses::MainUserViews::EDIT_NORMAL);
            tryToUpdateEditView(ModelStatuses::UserViews::GUEST,
                                guestEditController,
                                ModelStatuses::MainUserViews::EDIT_GUEST);
        },
        this);
    connect(prevViewController->getController(), &ViewController::userViewTypeChanged, [this] {
        emit controllerChanged();
    });
}

void MainUserController::connectControllersSignals(QPointer<AbstractEditController> controller)
{
    connect(controller,
            &AbstractEditController::updatePersonData,
            this,
            &MainUserController::updatePersonInDatabase);

    connect(controller,
            &AbstractEditController::removePersonData,
            this,
            &MainUserController::removePersonFromDatabase);

    connect(controller, &AbstractEditController::updatePersonData, [this](const auto &person) {
        manager->update(person);
    });
}

QPointer<AbstractEditController> MainUserController::getController() const
{
    auto t = prevViewController->getUserViewType();
    if (t == ModelStatuses::MainUserViews::EDIT_GUEST) {
        return guestEditController;
    }
    if (t == ModelStatuses::MainUserViews::EDIT_NORMAL) {
        return userEditController;
    }
    return nullptr;
}

void MainUserController::tryToUpdateEditView(ModelStatuses::UserViews managerType,
                                             QPointer<AbstractEditController> controller,
                                             ModelStatuses::MainUserViews viewType)
{
    if (SingletonObjectManager<Person>::status
        == SingletonObjectManager<Person>::Status::WAIT_FOR_LOAD) {
        return;
    }
    if (emitPersonManagers.contains(managerType)
        && emitPersonManagers[managerType]->isDataAvaible()) {
        controller->setNewPerson(emitPersonManagers[managerType]->get().value());
        prevViewController->setUserViewType(viewType);
    }
}

void MainUserController::updatePersonInDatabase(const Person &person)
{
    manager->update(person);
}

void MainUserController::removePersonFromDatabase(int index)
{
    manager->remove(index);
    qDebug() << "Object is removed";
}
