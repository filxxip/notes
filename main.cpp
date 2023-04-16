 #include <QGuiApplication>
 #include <QQmlApplicationEngine>
#include <iostream>
//#include <jsoncpp/json/json.h>
#include <QColor>
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QString>
#include "gui/log_controller.h"
#include "gui/mycontroller.h"
#include "gui/statuses.h"
#include "src/backend/datamanager/filedataclient.h"
#include "src/backend/datamanager/filedataclientadapter.h"
#include "src/backend/datamanager/pathmanager/path.h"
#include "src/backend/datamanager/serverdataclient.h"
#include "src/controller/abstract_data_client.h"
#include <curl/curl.h>
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
    FileDataClientAdapter adapter(std::make_shared<FileDataClient>());
    ServerDataClient client;
    //    client.setAdditionalParameters("name=Janusz");
    //    adapter.add(UrlPath("people"));
    client.update(UrlPath("people/10"));
    //    qDebug() << QString::fromStdString(adapter.get(UrlPath("people/1")).value().dump());
//    qDebug() << QString::fromStdString(client.get(UrlPath("people/3")).value().dump());
#if RUN_QML
    return app.exec();
#endif
}
