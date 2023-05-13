#include "maincontroller.h"

namespace {
constexpr const char *CLOSE_APP_MESSAGE = "App closed successfully";
}

MainController::MainController(QPointer<DialogController> dialogController_, QObject *obj)
    : QObject(obj)
    , dialogController(dialogController_)
{}

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
