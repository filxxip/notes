#include "mainusercontroller.h"

MainUserController::MainUserController(QPointer<ViewController> mainViewController,
                                       std::shared_ptr<DataClient> dataClient,
                                       QPointer<CalendarController> calendarController,
                                       QPointer<DialogController> dialogController,
                                       QObject *obj)
    : QObject(obj)
    , manager(DatabaseCodes::namesMap.at(DatabaseCodes::Names::PEOPLE), dataClient)
    , loginManager(std::make_unique<PeopleManager>(DatabaseCodes::namesMap.at(
                                                       DatabaseCodes::Names::PEOPLE_LOGIN),
                                                   dataClient))
    , registerManager(std::make_unique<PeopleManager>(DatabaseCodes::namesMap.at(
                                                          DatabaseCodes::Names::PEOPLE_REGISTER),
                                                      dataClient))
    , userEditController(new UserEditController(
          std::make_unique<SingletonObjectManager<Person>>(
              std::make_unique<PeopleManager>(DatabaseCodes::namesMap.at(
                                                  DatabaseCodes::Names::PEOPLE_LOGOUT),
                                              dataClient)),
          calendarController,
          dialogController,
          this))
    , prevViewController(mainViewController)
    , currentViewController(new ViewSwitcherController(
          FastModelBuilder<SwitcherModel<EnumStatus>, ModelStatuses::UserViewsRoles>(this)
              .add(ModelStatuses::UserViewsRoles::TEXT, &SwitcherModel<EnumStatus>::text)
              .add(ModelStatuses::UserViewsRoles::TYPE, &SwitcherModel<EnumStatus>::type)
              .build({{"profile", EnumStatus::EDIT}, {"notebook", EnumStatus::NOTEBOOK}}),
          QVariant::fromValue(EnumStatus::EDIT),
          this))
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
        
        qDebug() << person.surname.get();
        manager.update(person);
    });

    DatabaseUtilsFunctions::tickWait(
        400,
        [this] {
            tryToUpdateEditView(&loginManager);
            tryToUpdateEditView(&registerManager);
        },
        this);

    //    switcherModel->addEntry({"profile", EnumStatus::EDIT});
    //    switcherModel->addEntry({"notebook", EnumStatus::NOTEBOOK});
}

void MainUserController::tryToUpdateEditView(SingletonObjectManager<Person> *manager)
{
    if (manager->isDataAvaible()) {
        userEditController->setNewPerson(manager->get().value());
        prevViewController->setUserViewType(QVariant::fromValue(ModelStatuses::MainUserViews::EDIT));
        //        emit mainViewChanged(ModelStatuses::MainUserViews::EDIT);
    }
}

void MainUserController::updatePersonInDatabase(const Person &person)
{
    manager.update(person);
}

void MainUserController::removePersonFromDatabase(int index)
{
    manager.remove(index);
}
