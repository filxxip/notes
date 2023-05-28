#pragma once
#include <QObject>
#include <QQmlEngine>
#include "../cpputils/utils.h"
#include "../models/switchermodel.h"
#include "../models/userviewlistmodel.h"
#include "../modelutils/listmodelbuilder.h"
#include "../notebook/categorycontroller.h"
#include "../statuses.h"
#include "../userview/logcontroller.h"
#include "src/backend/datamanager/directobjsmanagers/people/peoplemanager.h"
#include "src/backend/datamanager/directobjsmanagers/singletonobjectmanager/singletonobjectmanager.h"
#include "usereditcontroller.h"
#include <unordered_map>

class MainUserController : public QObject
{
    using PrevEnumViewController = AbstractViewControllerAdapter<ModelStatuses::MainUserViews>;
    using EnumStatus = ModelStatuses::InnerUserEditViews;
    using UserSwitcherModel
        = CustomListModel<SwitcherModel<EnumStatus>, ModelStatuses::UserViewsRoles>;

    Q_PROPERTY(AbstractEditController *userEditController READ getController NOTIFY controllerChanged)

    Q_PROPERTY(CategoryController *categoryController MEMBER categoryController CONSTANT)

    Q_PROPERTY(ViewController *view MEMBER currentViewController CONSTANT)

    Q_OBJECT
public:
    explicit MainUserController(std::shared_ptr<PrevEnumViewController> mainViewController,
                                std::shared_ptr<DataClient> dataClient,
                                QPointer<DialogController> dialogController,
                                QObject *obj = nullptr);

    Q_INVOKABLE virtual void moveDataGloabllyToModel();

private:
    QPointer<AbstractEditController> getController() const;

    template<typename EditController>
    QPointer<EditController> generateController(std::shared_ptr<DataClient> dataClient,
                                                QPointer<DialogController> dialogController)
    {
        return new EditController(prevViewController,
                                  std::make_unique<SingletonObjectManager<Person>>(
                                      std::make_unique<IdsManager>(DatabaseCodes::Names::PEOPLE_LOGOUT,
                                                                   dataClient),
                                      manager),
                                  dialogController,
                                  this);
    }

    void connectControllersSignals(QPointer<AbstractEditController> controller);

    void tryToUpdateEditView(ModelStatuses::UserViews managerType,
                             QPointer<AbstractEditController> controller,
                             ModelStatuses::MainUserViews viewType);

    std::shared_ptr<PrevEnumViewController> prevViewController;

    std::shared_ptr<PeopleManager> manager;

    QPointer<ViewController> currentViewController;

    QPointer<AbstractEditController> userEditController;

    QPointer<AbstractEditController> guestEditController;

    QPointer<CategoryController> categoryController;

    std::unordered_map<ModelStatuses::UserViews, std::unique_ptr<SingletonObjectManager<Person>>>
        emitPersonManagers;

private slots:
    void updatePersonInDatabase(const Person &person);

    void removePersonFromDatabase(int index);

signals:
    void controllerChanged();
};
