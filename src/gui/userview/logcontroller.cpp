#include "logcontroller.h"

LogController::LogController()
    : QObject()
{
    models[EnumStatus::REGISTER]->setEntries(
        {{ModelStatuses::PersonComponents::NAME, "Name..."},
         {ModelStatuses::PersonComponents::SURNAME, "Surname..."},
         {ModelStatuses::PersonComponents::EMAIL, "Email..."},
         {ModelStatuses::PersonComponents::PASSWORD, "Password..."},
         {ModelStatuses::PersonComponents::COUNTRY, "Country..."}});

    models[EnumStatus::LOGIN]->setEntries(
        {{ModelStatuses::PersonComponents::EMAIL, "Login..."},
         {ModelStatuses::PersonComponents::PASSWORD, "Password..."}});
    models[EnumStatus::LOGIN]->setData(1, true, ModelStatuses::Roles::PASS_STATUS);

    models[EnumStatus::GUEST]->setEntries(
        {{ModelStatuses::PersonComponents::NAME, "Temporary name..."}});

    connect(this, &LogController::registerObjectInModel, this, &LogController::onRegisteringModel);

    switcherModel
        = FastModelBuilder<SwitcherModel<EnumStatus>, ModelStatuses::UserViewsRoles>()
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
    emit userViewChanged();
}

void LogController::setActivity(bool value)
{
    m_activity_possible = value;
    emit activityStatusChanged();
}

void LogController::onRegisteringModel()
{
    auto &registerModel = models[EnumStatus::REGISTER];

    int passIndex = registerModel->indexOf(ModelStatuses::PersonComponents::PASSWORD);
    auto password = registerModel->data(passIndex, ModelStatuses::Roles::COLOR).value<QString>();

    auto hasNoUppercase = std::none_of(password.begin(), password.end(), [](const QChar &ch) {
        return ch.isUpper(); //moze byc error
    });
    if (hasNoUppercase) {
        auto previousColor = registerModel->data(passIndex, ModelStatuses::Roles::COLOR);
        registerModel->setData<QColor>(passIndex, "black", ModelStatuses::Roles::COLOR);
        setActivity(false);
        QTimer::singleShot(2500, [this, &registerModel, previousColor, passIndex]() {
            registerModel->setData(passIndex, previousColor, ModelStatuses::Roles::COLOR);
            setActivity(true);
        });
    }
}