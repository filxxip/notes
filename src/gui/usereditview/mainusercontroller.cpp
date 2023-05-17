#include "mainusercontroller.h"

MainUserController::MainUserController(std::shared_ptr<PrevEnumViewController> mainViewController,
                                       std::shared_ptr<DataClient> dataClient,
                                       QPointer<DialogController> dialogController,
                                       QObject *obj)
    : QObject(obj)
    , manager(std::make_shared<PeopleManager>(DatabaseCodes::Names::PEOPLE, dataClient))
    , loginManager(std::make_unique<IdsManager>(DatabaseCodes::Names::PEOPLE_LOGIN, dataClient),
                   manager)
    , registerManager(std::make_unique<IdsManager>(DatabaseCodes::Names::PEOPLE_REGISTER,
                                                   dataClient),
                      manager)
    , userEditController(
          new UserEditController(mainViewController,
                                 std::make_unique<SingletonObjectManager<Person>>(
                                     std::make_unique<IdsManager>(DatabaseCodes::Names::PEOPLE_LOGOUT,
                                                                  dataClient),
                                     manager),
                                 dialogController,
                                 this))
    , prevViewController(mainViewController)
    , currentViewController(
          ViewControllerGenerators::createSwitcherViewContorller(
              FastModelBuilder<SwitcherModel<EnumStatus>, ModelStatuses::UserViewsRoles>(this)
                  .add(ModelStatuses::UserViewsRoles::TEXT, &SwitcherModel<EnumStatus>::text)
                  .add(ModelStatuses::UserViewsRoles::TYPE, &SwitcherModel<EnumStatus>::type)
                  .build({{"profile", EnumStatus::EDIT}, {"notebook", EnumStatus::NOTEBOOK}}),
              EnumStatus::EDIT,
              this)
              ->getController())
{
    connect(userEditController,
            &UserEditController::updatePersonData,
            this,
            &MainUserController::updatePersonInDatabase);

    connect(userEditController,
            &UserEditController::removePersonData,
            this,
            &MainUserController::removePersonFromDatabase);

    connect(userEditController, &UserEditController::updatePersonData, [this](const auto &person) {
        manager->update(person);
    });

    DatabaseUtilsFunctions::tickWait(
        400,
        [this] {
            tryToUpdateEditView(&loginManager);
            tryToUpdateEditView(&registerManager);
        },
        this);
}

void MainUserController::tryToUpdateEditView(SingletonObjectManager<Person> *manager)
{
    if (manager->isDataAvaible()) {
        userEditController->setNewPerson(manager->get().value());
        prevViewController->setUserViewType(ModelStatuses::MainUserViews::EDIT);
    }
}

void MainUserController::updatePersonInDatabase(const Person &person)
{
    manager->update(person);
}

void MainUserController::removePersonFromDatabase(int index)
{
    manager->remove(index);
}
