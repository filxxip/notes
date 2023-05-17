#pragma once
#include <QObject>
#include <QQmlEngine>
#include "../cpputils/utils.h"
#include "../models/switchermodel.h"
#include "../models/userviewlistmodel.h"
#include "../modelutils/listmodelbuilder.h"
#include "../statuses.h"
#include "../userview/logcontroller.h"
#include "src/backend/datamanager/directobjsmanagers/people/peoplemanager.h"
#include "src/backend/datamanager/directobjsmanagers/singletonobjectmanager/singletonobjectmanager.h"
#include "usereditcontroller.h"

class MainUserController : public QObject
{
    using PrevEnumViewController = AbstractViewControllerAdapter<ModelStatuses::MainUserViews>;
    using EnumStatus = ModelStatuses::InnerUserEditViews;
    using UserSwitcherModel
        = CustomListModel<SwitcherModel<EnumStatus>, ModelStatuses::UserViewsRoles>;

    Q_PROPERTY(UserEditController *userEditController MEMBER userEditController CONSTANT)

    Q_PROPERTY(ViewController *view MEMBER currentViewController CONSTANT)

    Q_OBJECT
public:
    explicit MainUserController(std::shared_ptr<PrevEnumViewController> mainViewController,
                                std::shared_ptr<DataClient> dataClient,
                                QPointer<DialogController> dialogController,
                                QObject *obj = nullptr);

private:
    void tryToUpdateEditView(SingletonObjectManager<Person> *manager);

    std::shared_ptr<PrevEnumViewController> prevViewController;

    std::shared_ptr<PeopleManager> manager;

    QPointer<ViewController> currentViewController;

    QPointer<UserEditController> userEditController;

    SingletonObjectManager<Person> loginManager;

    SingletonObjectManager<Person> registerManager;

private slots:
    void updatePersonInDatabase(const Person &person);

    void removePersonFromDatabase(int index);
};
