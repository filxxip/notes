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
    using EnumStatus = ModelStatuses::InnerUserEditViews;
    using UserSwitcherModel
        = CustomListModel<SwitcherModel<EnumStatus>, ModelStatuses::UserViewsRoles>;

    //    Q_PROPERTY(EnumStatus userViewType MEMBER m_userView NOTIFY userViewChanged)

    //    Q_PROPERTY(UserSwitcherModel *switcherModel MEMBER switcherModel CONSTANT)

    Q_PROPERTY(UserEditController *userEditController MEMBER userEditController CONSTANT)

    Q_PROPERTY(ViewController *view MEMBER currentViewController CONSTANT)

    Q_OBJECT
public:
    explicit MainUserController(QPointer<ViewController> mainViewController,
                                std::shared_ptr<DataClient> dataClient,
                                QPointer<CalendarController> calendarController,
                                QPointer<DialogController> dialogController,
                                QObject *obj = nullptr);

private:
    void tryToUpdateEditView(SingletonObjectManager<Person> *manager);

    QPointer<ViewController> prevViewController;
    QPointer<ViewController> currentViewController;

    //    QPointer<UserSwitcherModel> switcherModel;

    //    EnumStatus m_userView = EnumStatus::EDIT;

    QPointer<UserEditController> userEditController;

    PeopleManager manager;

    SingletonObjectManager<Person> loginManager;

    SingletonObjectManager<Person> registerManager;

    //signals:
    //    void userViewChanged();

    //    void mainViewChanged(ModelStatuses::MainUserViews userView);

private slots:
    void updatePersonInDatabase(const Person &person);

    void removePersonFromDatabase(int index);
};
