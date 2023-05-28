#include <QCoreApplication>
#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QString>
#include "gui/statuses.h"
#include "src/backend/datamanager/directobjsmanagers/categories/categoriesmanager.h"
#include "src/backend/datamanager/directobjsmanagers/guidialogs/guidialogmanager.h"
#include "src/backend/datamanager/directobjsmanagers/notes/notesmanager.h"
#include "src/backend/datamanager/directobjsmanagers/people/peoplemanager.h"
#include "src/backend/datamanager/filedataclient.h"
#include "src/backend/datamanager/filedataclientadapter.h"
#include "src/backend/datamanager/serverdataclient.h"
#include "src/gui/maincontroller/maincontroller.h"
#include "src/gui/userview/logcontroller.h"
#include <memory>

#define RUN_QML 1
#define RUN_DATABASE 0

using json = nlohmann::json;
int main(int argc, char *argv[])
{
//    QVariant a = "data";
//    DbData<QString> x{"data"};
//    x = a.value<QString>();
//    qDebug() << "hahaha";
#if RUN_DATABASE
    auto filemanager = GuiDialogsManager(DatabaseCodes::Names::GUI_DIALOGS,
                                         std::make_shared<FileDataClientAdapter>(
                                             std::make_shared<FileDataClient>()));

    //    auto servermanager = GuiDialogsManager(DatabaseCodes::Names::CATEGORIES,
    //                                           std::make_shared<ServerDataClient>());
    auto servermanager = GuiDialogsManager(DatabaseCodes::Names::GUI_DIALOGS,
                                           std::make_shared<ServerDataClient>());
    //    servermanager2.remove(1);

    auto el = filemanager.get();
    for (int i = 1; i < 20; i++) {
        servermanager.remove(i);
    }
    //    if (el.has_value()) {
    //    }

    std::sort(el->begin(), el->end(), [](const auto &el1, const auto &el2) {
        return el1.id.get() < el2.id.get();
    });
    for (auto &e : el.value()) {
        servermanager.add(e);
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
        auto mainController = new MainController(ptr, &engine);

        engine.rootContext()->setContextProperty("mainController", mainController);
        mainController->registerControllers(engine.rootContext());

        engine.load(url);

        return app.exec();
    }
    qDebug() << "Invalid access to database";
#endif
}
