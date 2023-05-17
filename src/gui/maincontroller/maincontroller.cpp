#include "maincontroller.h"

namespace {
constexpr const char *CLOSE_APP_MESSAGE = "App closed successfully";
constexpr char DIALOG_CONTROLLER[] = "dialogController";
constexpr char CALENDAR_CONTROLLER[] = "calendarController";
constexpr char CLOCK_CONTROLLER[] = "clockController";
constexpr char LOG_CONTROLLER[] = "logController";
constexpr char MAIN_USER_CONTROLLER[] = "mainUserController";
} // namespace

MainController::MainController(std::shared_ptr<DataClient> dataClient, QObject *obj)
    : QObject(obj)
    , dialogController(
          new DialogController(std::make_unique<GuiDialogsManager>(DatabaseCodes::Names::GUI_DIALOGS,
                                                                   dataClient),
                               this))
    , calendarController(new CalendarController(this))
    , clockController(new ClockController(this))
    , logController(mainUserView, dataClient, calendarController, dialogController, this)
    , mainUserController(mainUserView, dataClient, calendarController, dialogController, this)
    , mainUserView(
          ViewControllerGenerators::createNonSwitcherViewContorller(ModelStatuses::MainUserViews::LOG,
                                                                    this))
{
    mainUserView->setUserViewType(ModelStatuses::MainUserViews::LOG);
}

QPointer<ViewController> MainController::getViewController() const
{
    return mainUserView->getController();
}

void MainController::closeApp()
{
    dialogController->showDialog(DialogCodes::UserViews::CLOSE_APP);

    dialogController->applyConnection([](auto status) {
        if (status == DialogController::ActivityStatus::ACCEPT) {
            qDebug() << CLOSE_APP_MESSAGE;
            QCoreApplication::quit();
        }
    });
}

void MainController::registerControllers(QQmlContext *context)
{
    context->setContextProperty(LOG_CONTROLLER, &logController);
    context->setContextProperty(DIALOG_CONTROLLER, dialogController);
    context->setContextProperty(CALENDAR_CONTROLLER, calendarController);
    context->setContextProperty(CLOCK_CONTROLLER, clockController);
    context->setContextProperty(MAIN_USER_CONTROLLER, &mainUserController);
}
