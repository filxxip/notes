#include "logcontroller.h"

LogController::LogController()
    : QObject()
{
    //    QVector<EntryFieldModel> dataRegister;
    //    dataRegister.push_back(EntryFieldModel{ModelStatuses::PersonComponents::NAME, "Name..."});
    //    dataRegister.push_back(EntryFieldModel{ModelStatuses::PersonComponents::SURNAME, "Surname..."});
    //    dataRegister.push_back(EntryFieldModel{ModelStatuses::PersonComponents::EMAIL, "Email..."});
    //    dataRegister.push_back(
    //        EntryFieldModel{ModelStatuses::PersonComponents::PASSWORD, "Password..."});
    //    dataRegister.push_back(EntryFieldModel{ModelStatuses::PersonComponents::COUNTRY, "Country..."});
    //    registerModel->setEntries(std::move(dataRegister));

    //    QVector<EntryFieldModel> dataLogin;
    //    dataLogin.push_back(EntryFieldModel{ModelStatuses::PersonComponents::EMAIL, "Login..."});
    //    auto entry = EntryFieldModel{ModelStatuses::PersonComponents::PASSWORD, "Password..."};
    //    entry.passwordStatus = true;
    //    dataLogin.push_back(std::move(entry));
    //    loginModel->setEntries(std::move(dataLogin));

    //    QVector<EntryFieldModel> guestData;
    //    guestData.push_back(EntryFieldModel{ModelStatuses::PersonComponents::NAME, "Temporary name..."});
    //    guestModel->setEntries(std::move(guestData));

    //    connect(this, &LogController::registerObjectInModel, this, &LogController::onRegisteringModel);
    //    using Status = SwitcherModel<ModelStatuses::UserViews>; //
    //    switcherModel = FastModelBuilder<Status, ModelStatuses::UserViewsRoles>()
    //                        .add(ModelStatuses::UserViewsRoles::TEXT,
    //                             &SwitcherModel<ModelStatuses::UserViews>::text,
    //                             "text")
    //                        .add(ModelStatuses::UserViewsRoles::TYPE,
    //                             &SwitcherModel<ModelStatuses::UserViews>::type,
    //                             "type")
    //                        .build();
    //    SwitcherModel<ModelStatuses::UserViews> switcher;
    //    switcher.text = "login";
    //    switcher.type = ModelStatuses::UserViews::LOGIN;

    //    switcherModel->addEntry(std::move(switcher));
    //    SwitcherModel<ModelStatuses::UserViews> switcher2;
    //    switcher2.text = "register";
    //    switcher2.type = ModelStatuses::UserViews::REGISTER;
    //    switcherModel->addEntry(std::move(switcher2));
    //    switcher2.text = "log as guest";
    //    switcher2.type = ModelStatuses::UserViews::GUEST;
    //    switcherModel->addEntry(std::move(switcher2));

    models[EnumStatus::LOGIN]->setEntries(
        {{ModelStatuses::PersonComponents::NAME, "Name..."},
         {ModelStatuses::PersonComponents::SURNAME, "Surname..."},
         {ModelStatuses::PersonComponents::EMAIL, "Email..."},
         {ModelStatuses::PersonComponents::PASSWORD, "Password..."},
         {ModelStatuses::PersonComponents::COUNTRY, "Country..."}});

    models[EnumStatus::REGISTER]->setEntries(
        {{ModelStatuses::PersonComponents::EMAIL, "Login..."},
         {ModelStatuses::PersonComponents::PASSWORD, "Password...", true}});

    models[EnumStatus::GUEST]->setEntries(
        {{ModelStatuses::PersonComponents::NAME, "Temporary name..."}});

    connect(this, &LogController::registerObjectInModel, this, &LogController::onRegisteringModel);

    switcherModel
        = FastModelBuilder<Status, ModelStatuses::UserViewsRoles>()
              .add(ModelStatuses::UserViewsRoles::TEXT, &SwitcherModel<EnumStatus>::text, "text")
              .add(ModelStatuses::UserViewsRoles::TYPE, &SwitcherModel<EnumStatus>::type, "type")
              .build();

    switcherModel->addEntry({"login", EnumStatus::LOGIN});
    switcherModel->addEntry({"register", EnumStatus::REGISTER});
    switcherModel->addEntry({"log as guest", EnumStatus::GUEST});
}

void LogController::onSwitchedChanged(ModelStatuses::UserViews s)
{
    m_userView = s;
    emit userViewChanged(m_userView);
}

void LogController::setActivity(bool value)
{
    m_activity_possible = value;
    emit activityStatusChanged();
}

void LogController::onRegisteringModel()
{
    int passIndex = registerModel->indexOf(ModelStatuses::PersonComponents::PASSWORD);
    auto password = registerModel->data(passIndex, ModelStatuses::Roles::COLOR).value<QString>();
    if (std::none_of(password.begin(), password.end(), [](const QChar &ch) {
            return ch.isUpper();
        })) {
        auto previousColor = registerModel->data(passIndex, ModelStatuses::Roles::COLOR);
        registerModel->setData<QColor>(passIndex, "black", ModelStatuses::Roles::COLOR);
        setActivity(false);
        QTimer::singleShot(2500, [this, previousColor, passIndex]() {
            registerModel->setData(passIndex, previousColor, ModelStatuses::Roles::COLOR);
            setActivity(true);
        });
    }
}
