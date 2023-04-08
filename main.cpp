 #include <QGuiApplication>
 #include <QQmlApplicationEngine>
#include <iostream>
//#include <jsoncpp/json/json.h>
#include <QJsonObject>
#include <QString>
#include <string>
#include <QJsonDocument>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <QDebug>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "gui/statuses.h"
#include <QColor>
#include <QObject>
#include "gui/mycontroller.h"


int main(int argc, char *argv[]) {
////    MyClass obj;
////    connect(&obj, &MyClass::mySignal, [](const QJsonObject & jsonData){
////    QString value1 = jsonData["key1"].toString();
////    int value2 = jsonData["key2"].toInt();
////    });


//    // Connect to the Python server
//    int sock = socket(AF_INET, SOCK_STREAM, 0);
//    struct sockaddr_in serv_addr;
//    serv_addr.sin_family = AF_INET;
//    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
//    serv_addr.sin_port = htons(9100);
//    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

//    // Send a signal to retrieve a record from the database
//    std::cout<<"what"<<std::endl;
//    QJsonObject signal;
////    signal["id"] ="2";
//    signal["operation"] ="list";
//    signal["table"] = "People";
////    QJsonObject obj;
////    obj["name"] = "Filip";
////    obj["age"] = 20;
////    obj["surname"] = "Polto";
////    obj["country"] = "Poland";
////    obj["email"] = "f.po@gmail.com";
////    obj["password"] = "pass";
////    obj["birthday"] = "2003-09-13";
////    signal["attributes"] = obj;
//    qDebug()<<signal["id"].toString().size();
//    QJsonDocument doc(signal);
//    std::cout<<"what"<<std::endl;
//    QString strJson(doc.toJson(QJsonDocument::Compact));
//    std::cout<<"what"<<std::endl;
//    send(sock, strJson.toStdString().c_str(), strJson.length(), 0);

//    // Receive the record as a JSON object
//    char buffer[1024];
////    recv(sock, buffer, sizeof(buffer), 0);
//   auto num= read(sock,buffer, 10240);
//    std::cout<<"what"<<std::endl;
//    std::cout<<buffer<<std::endl;
//   std::cout<<num<<std::endl;
//    buffer[num] = '\0';
//    QString jsonString(buffer);
//    qDebug()<<jsonString;
//    auto json = QJsonDocument::fromJson(jsonString.toUtf8()).object();
////    reader.parse(buffer, buffer + strlen(buffer), response);
////    std::cout<<json<<std::endl;

//    // Print the record information
////    std::cout << "Connection: " << json[0]["connection"].toString().toStdString() << std::endl;
////    std::cout << "Title: " << json[0]["title"].toString().toStdString() << std::endl;
////    std::cout << "Content: " << json[0]["content"].toString().toStdString() << std::endl;
////    std::cout << "Age: " << json[0]["age"].toInt() << std::endl;
////    std::cout << "Pass: " << json[0]["password"].toString().toStdString() << std::endl;

//    // Close the socket
    
//     close(sock);
//     shutdown(sock, SHUT_RDWR);

//    return 0;

     QGuiApplication app(argc, argv);

     QQmlApplicationEngine engine;
     const QUrl url("qrc:/notesdatabaseproject/Main.qml");
     QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
         &app, []() { QCoreApplication::exit(-1); },
         Qt::QueuedConnection);
     qmlRegisterUncreatableMetaObject(Statuses::staticMetaObject, "Statuses", 1, 0, "Statuses", "");
     auto myController = new MyController();
     engine.rootContext()->setContextProperty("myController", myController);
     engine.load(url);

     return app.exec();
}
