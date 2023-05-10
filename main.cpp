#include <QColor>
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QGuiApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QRegularExpression>
#include <QString>
#include "gui/statuses.h"
#include "src/backend/datamanager/directobjsmanagers/categories/categoriesmanager.h"
#include "src/backend/datamanager/directobjsmanagers/guidialogs/guidialogmanager.h"
#include "src/backend/datamanager/directobjsmanagers/notes/notesmanager.h"
#include "src/backend/datamanager/directobjsmanagers/people/peoplemanager.h"
#include "src/backend/datamanager/filedataclient.h"
#include "src/backend/datamanager/filedataclientadapter.h"
#include "src/backend/datamanager/serverdataclient.h"
#include "src/gui/calendar/calendarcontroller.h"
#include "src/gui/calendar/clockcontroller.h"
#include "src/gui/customdialog/dialogcontroller.h"
#include "src/gui/radiobutton/radiobuttoncontroller.h"
#include "src/gui/usereditview/usereditcontroller.h"
#include "src/gui/userview/logcontroller.h"
#include <cctype>
#include <chrono>
#include <memory>

#define RUN_QML 1
#define RUN_DATABASE 0

using json = nlohmann::json;
int main(int argc, char *argv[])
{
#if RUN_DATABASE
    auto filemanager = PeopleManager(
        std::make_shared<FileDataClientAdapter>(std::make_shared<FileDataClient>()));

    auto servermanager = PeopleManager(std::make_shared<ServerDataClient>());

    //    for (int i = 1; i < 200; i++) {
    //        filemanager.remove(i);
    //    }
    auto el = servermanager.get();
    for (auto &e : el.value()) {
        filemanager.add(e);
    }
#endif

#if RUN_QML
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url("qrc:/notesdatabaseproject/Main.qml");
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);


    qmlRegisterUncreatableMetaObject(ModelStatuses::staticMetaObject,
                                     "ModelStatuses",
                                     1,
                                     0,
                                     "ModelStatuses",
                                     "");
    auto fileClient = std::make_shared<FileDataClientAdapter>(std::make_shared<FileDataClient>());
    auto serverClient = std::make_shared<ServerDataClient>();

    auto ptr = fileClient;

    if (ptr->isValid()) {
        auto clockController = new ClockController(&engine);

        auto dialogController = new DialogController(ptr, &engine);
        //        QPointer<CustomListModel<RadioButtonModel, ModelStatuses::RadioButtonRoles>> listmodel
        //            = new CustomListModel<RadioButtonModel, ModelStatuses::RadioButtonRoles>(&engine);
        auto entry1 = RadioButtonModel("text1", false, 1);
        auto entry2 = RadioButtonModel("text2", true, 1);
        auto entry3 = RadioButtonModel("text3", false, 2);
        auto entry4 = RadioButtonModel("text4", false, 2);

        //        listmodel->setEntries({entry1, entry2, entry3, entry4});

        auto buttonController = new RadioButtonController({entry1, entry2, entry3, entry4}, &engine);
        auto userViewController = new UserEditController(new CalendarController(&engine),
                                                         dialogController,
                                                         &engine);

        auto logController = new LogController(ptr, dialogController, &engine);
        engine.rootContext()->setContextProperty("logController", logController);
        engine.rootContext()->setContextProperty("dialogController", dialogController);
        engine.rootContext()->setContextProperty("buttonController", buttonController);
        engine.rootContext()->setContextProperty("userEditController", userViewController);
        engine.rootContext()->setContextProperty("clockController", clockController);

        engine.load(url);

        return app.exec();
    }
    qDebug() << "Invalid access to database";
#endif
}
