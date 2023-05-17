#pragma once

#include <QCoreApplication>
#include <QDebug>
#include <QObject>
#include <QPointer>
#include <QQmlContext>
#include "../customdialog/dialogcontroller.h"

#include "../cpputils/utils.h"
#include "src/gui/calendar/calendarcontroller.h"
#include "src/gui/calendar/clockcontroller.h"
#include "src/gui/customdialog/dialogcontroller.h"
#include "src/gui/maincontroller/maincontroller.h"
#include "src/gui/radiobutton/radiobuttoncontroller.h"
#include "src/gui/usereditview/mainusercontroller.h"
#include "src/gui/usereditview/usereditcontroller.h"
#include "src/gui/userview/logcontroller.h"

class MainController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(ViewController *view READ getViewController CONSTANT)

    QPointer<DialogController> dialogController;
    QPointer<CalendarController> calendarController;
    QPointer<ClockController> clockController;
    std::shared_ptr<AbstractViewControllerAdapter<ModelStatuses::MainUserViews>> mainUserView;
    LogController logController;
    MainUserController mainUserController;

private:
    QPointer<ViewController> getViewController() const;

public:
    MainController(std::shared_ptr<DataClient> dataClient, QObject *obj = nullptr);

    void registerControllers(QQmlContext *context);

    Q_INVOKABLE void closeApp();
};
