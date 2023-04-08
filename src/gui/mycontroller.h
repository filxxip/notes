#pragma once

#include <QObject>
#include <QColor>

//class MyController: public QObject {
//    Q_OBJECT
//    Q_PROPERTY(QColor myColor MEMBER myColor NOTIFY myColorChanged)
//public:
//    using QObject::QObject;

//signals:
//    void myColorChanged();

//private:
//    QColor myColor = Qt::yellow;
//};

class MyModel {
Q_GADGET
    Q_PROPERTY(QColor color MEMBER color CONSTANT)
    Q_PROPERTY(QString name MEMBER name CONSTANT)
public:
    QColor color = Qt::darkBlue;
    QString name = "Hello world";
};
Q_DECLARE_METATYPE(MyModel)

class MyController: public QObject {
    Q_OBJECT
    Q_PROPERTY(MyModel myModel MEMBER myModel CONSTANT)
public:
    using QObject::QObject;

    void update() {
        myModel.color = Qt::red;
        myModel.name = "Filip";
        emit updated(myModel);
    }

signals:
    void myColorChanged();
    void updated(const MyModel &);

private:
    MyModel myModel;
};
