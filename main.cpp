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
#include "src/backend/datamanager/filedataclientadapter.h"
#include "src/controller/abstract_data_client.h"
#include <curl/curl.h>
#include <netinet/in.h>
#include <nlohmann/json.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

#define RUN_QML 0

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *) userp)->append((char *) contents, size * nmemb);
    return size * nmemb;
}
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    size_t num_bytes = size * nmemb;
    //    std::cout << "Received " << num_bytes << " bytes of data." << std::endl;
    std::cout << "Data: " << std::string(ptr, num_bytes) << std::endl;
    return size * nmemb;
}
namespace {
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
} // namespace
int main1(int argc, char *argv[])
{
    using json = nlohmann::json;
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

//    ServerDataClient dataclient;
//    auto j = dataclient.convertToJson("http://127.0.0.1:5000/people");

//     CURL *curl;
//     CURLcode res;

//     curl = curl_easy_init();

//     if (curl) {
//         curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:5000/people");
//         curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
//         res = curl_easy_perform(curl);
//         std

//         if (res != CURLE_OK) {
//             std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
//         }

//         curl_easy_cleanup(curl);
//     }
//     return 0;
#if RUN_QML
    return app.exec();
#endif
}
//int main2()
//{
//    CURL *curl;
//    CURLcode res;
//    std::string url = "http://127.0.0.1:5000/people/10";
//    std::string response_data;

//    curl = curl_easy_init();
//    qDebug() << "what";
//    if (curl) {
//        qDebug() << "what";
//        // set the URL
//        std::string json_data = R"({"name": "John Doe", "age": 30})";
//        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PATCH");
//        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data.c_str());
//        //        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, "Content-Type: application/json");

//        // set the CURLOPT_WRITEDATA option to point to the response_data string
//        //        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
//        //        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

//        // perform the request
//        res = curl_easy_perform(curl);
//        qDebug() << "Response data: " << QString::fromStdString(response_data);
//        // check for errors
//        if (res != CURLE_OK) {
//            qDebug() << "what";
//            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
//        }

//        // cleanup
//        curl_easy_cleanup(curl);
//    }

//    qDebug() << "Response data: " << QString::fromStdString(response_data);

//    return 0;
//}

#include "src/backend/datamanager/filedataclient.h"
#include "src/backend/datamanager/filedataclientadapter.h"
#include <curl/curl.h>
#include <memory>
#include <stdio.h>
#include <string.h>

static size_t write_callback22(char *ptr, size_t size, size_t nmemb, std::string *userdata)
{
    userdata->append(ptr, size * nmemb);
    return size * nmemb;
}

class Some{

};
#include "src/backend/datamanager/pathmanager/path.h"
int main(int argc, char *argv[])
{
    //    FilePath url = FilePath("somestering");
    //    qDebug() << url.getFullPath();
    //    auto x2 = std::make_shared<FileDataClient>();
    //    auto y = std::make_shared<FileDataClient>();
    FileDataClientAdapter adapter(std::make_shared<FileDataClient>());
    //    adapter.remove(UrlPath("people/6"));
    //    adapter.remove(UrlPath("people/0"));
    //    qDebug() << QString::fromStdString(content.value().dump());
    adapter.setAdditionalParameters("surname=FIlip");
    //    adapter.add(UrlPath("people"));
    adapter.update(UrlPath("people/1"));
    qDebug() << QString::fromStdString(adapter.get(UrlPath("people/1")).value()["name"]);
    //    qDebug() << QString::fromStdString(jaa.value()["name"]);
    //    qDebug() << QString(adapter.get(UrlPath("people/12")).value().dump());
    //    auto p = costam::convertUrlToJsonFilePath(UrlPath("people/12"));
    //    qDebug() << p.getFullPath();
    qDebug() << UrlPath("people/12").getFullPath();
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PATCH");
        curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:5000/people/11");
        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
        struct curl_slist *headers = NULL;
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        std::string result;

        curl_mime *mime;
        curl_mimepart *part;
        mime = curl_mime_init(curl);
        part = curl_mime_addpart(mime);
        curl_mime_name(part, "namee");
        curl_mime_data(part, "Filip", CURL_ZERO_TERMINATED);
        part = curl_mime_addpart(mime);
        curl_mime_name(part, "surname");
        curl_mime_data(part, "xxxx", CURL_ZERO_TERMINATED);
        curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);

        // Set the write function and write data to store the response in the result variable
//        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback22);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);

        res = curl_easy_perform(curl);
        curl_mime_free(mime);
        std::cout << "res: " << result << std::endl;
    }
    curl_easy_cleanup(curl);
    return 0;
}
