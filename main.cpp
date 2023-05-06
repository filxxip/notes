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
#include "src/gui/customdialog/dialogcontroller.h"
#include "src/gui/userview/logcontroller.h"
#include <cctype>
#include <chrono>
#include <memory>

#define RUN_QML 1

#define RUN_DATABASE 0

using json = nlohmann::json;
int main(int argc, char *argv[])
{
    QRegularExpression rx(".*@.*\\.com");
    auto x = rx.match("ney@gmail.com");
    qDebug() << x;

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
    auto ptr = std::make_shared<FileDataClientAdapter>(
        std::make_shared<FileDataClient>()); //wszystko qpointer zwykly pointer i rodzic go usuwa
    auto dialogController = new DialogController(ptr, &engine);
    auto logController = new LogController(ptr, dialogController, &engine);
    engine.rootContext()->setContextProperty("logController", logController);
    engine.rootContext()->setContextProperty("dialogController", dialogController);

    engine.load(url);
#endif

#if RUN_DATABASE
    auto filemanager = GuiDialogsManager(
        std::make_shared<FileDataClientAdapter>(std::make_shared<FileDataClient>()));

    auto servermanager = GuiDialogsManager(std::make_shared<ServerDataClient>());
    auto el = servermanager.get();
    for (auto &e : el.value()) {
        filemanager.add(e);
    }
#endif

#if RUN_QML
    return app.exec();
#endif
}
