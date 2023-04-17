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
#include "src/backend/datamanager/directobjsmanagers/personmanager.h"
#include "src/backend/datamanager/filedataclient.h"
#include "src/backend/datamanager/filedataclientadapter.h"
#include "src/backend/datamanager/pathmanager/path.h"
#include "src/backend/datamanager/serverdataclient.h"
#include "src/controller/abstract_data_client.h"
#include <curl/curl.h>
#include <iostream>
#include <memory>
#include <netinet/in.h>
#include <nlohmann/json.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#define RUN_QML 0
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

    auto myController = new MyController();
    auto logController = new LogController();

    engine.rootContext()->setContextProperty("myController", myController);
    engine.rootContext()->setContextProperty("logController", logController);

    engine.load(url);
#endif
    //    FileDataClientAdapter adapter(std::make_shared<FileDataClient>());
    //    ServerDataClient client;
    PersonManager manager(std::make_shared<ServerDataClient>());
    auto person = manager.get(3);
    person->name = "Jarek";
    person->surname = "Kowalczuk";
    manager.copyParamsFromObjectChanges(person.value());
    manager.update(3);

    //    client.setAdditionalParameters("name=Janusz");
    //    adapter.add(UrlPath("people"));
//    adapter.get(UrlPath("people/1"));
//    qDebug() << QString::fromStdString(adapter.get(UrlPath("people/1")).value().dump());
//    qDebug() << QString::fromStdString(client.get(UrlPath("people/3")).value().dump());
#if RUN_QML
    return app.exec();
#endif
}
