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
#include <chrono>
#include <memory>
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
    //sprawdzic czy napewno aby sie updatuje to co trzeba, dlaczego id pobrane jest w stringu a nie it z servera
    auto filemanager = PeopleManager(
        std::make_shared<FileDataClientAdapter>(std::make_shared<FileDataClient>()));

    auto servermanager = PeopleManager(std::make_shared<ServerDataClient>());
    qDebug() << servermanager.get(5).value().name.get();
    auto l = filemanager.get(125);
    l->birthday = QDateTime(QDate(2004, 04, 29), QTime(1, 1, 1));
    l->name = "Pliska";
    filemanager.add(l.value());
    //    / for (auto &per : l.value())
    //    {
    //        filemanager.add(per);
    //    }
    //    FileManager m;
    //    auto list = m.readFromDir(FilePath("people"));
    //    for (auto &el : list.value()) {
    //        qDebug() << el;
    //    }
    //    auto second = CategoriesManager(
    //        std::make_shared<FileDataClientAdapter>(std::make_shared<FileDataClient>()));
    //    PersonManager manager(
    //        std::make_shared<FileDataClientAdapter>(std::make_shared<FileDataClient>()));
    //    for (int i = 0; i < 20; i++) {
    //        auto person = servermanager.get(i + 1);
    //        person->releaseDate = "2003-10-10";
    //        filemanager.add(person.value());
    //    }

    //    auto start = std::chrono::high_resolution_clock::now();
    //    for (int i = 0; i < 25; i++) {
    //        auto x = manager.get(i + 1);
    //    }
    //    auto end = std::chrono::high_resolution_clock::now();
    //    std::chrono::duration<double> elapsed = end - start;
    //    std::cout << "Time measured: " << elapsed.count() << " seconds." << std::endl;
    //    auto note = manager.get(1);
    //    note->creationDate = "2003-10-20";
    //    note->name = "Give me freedomplease";
    //    second.add(note.value());

#if RUN_QML
    return app.exec();
#endif
}
