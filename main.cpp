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
#include <QString>
#include "gui/log_controller.h"
#include "gui/mycontroller.h"
#include "gui/statuses.h"
#include "src/backend/datamanager/directobjsmanagers/categories/categoriesmanager.h"
#include "src/backend/datamanager/directobjsmanagers/notes/notesmanager.h"
#include "src/backend/datamanager/directobjsmanagers/people/peoplemanager.h"
#include "src/backend/datamanager/filedataclient.h"
#include "src/backend/datamanager/filedataclientadapter.h"
#include "src/backend/datamanager/serverdataclient.h"
#include "src/gui/customlistviewmodel.h"
#include <chrono>
#include <memory>
#define RUN_QML 1
using json = nlohmann::json;
int main(int argc, char *argv[])
{
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
    qmlRegisterUncreatableMetaObject(Statuses::staticMetaObject, "Statuses", 1, 0, "Statuses", "");
    qmlRegisterUncreatableType<CustomType>("QMLAbstractModelListItems",
                                           1,
                                           0,
                                           "CustomType",
                                           "Not createable from qml");
    qmlRegisterUncreatableType<CustomQVariant>("QMLAbstractModelListItems",
                                               1,
                                               0,
                                               "CustomQVariant",
                                               "Not createable from qml");
    qRegisterMetaType<CustomType>();
    //    qRegisterMetaType<DbData<int>>("DbData<int>");

    auto myController = new MyController();
    auto logController = new LogController();

    engine.rootContext()->setContextProperty("myController", myController);
    engine.rootContext()->setContextProperty("logController", logController);

    engine.load(url);
#endif
    //sprawdzic czy napewno aby sie updatuje to co trzeba, dlaczego id pobrane jest w stringu a nie it z servera
    auto filemanager = NotesManager(
        std::make_shared<FileDataClientAdapter>(std::make_shared<FileDataClient>()));

    auto servermanager = NotesManager(std::make_shared<ServerDataClient>());
    auto el = filemanager.getFiltered(json{{"category", "21"}});
    qDebug() << el->size();
    for (const auto &e : el.value()) {
        qDebug() << e.category.get();
    }
#if RUN_QML
    return app.exec();
#endif
}
