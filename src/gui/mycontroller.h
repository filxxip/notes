//#pragma once

//#include <QColor>
//#include <QObject>
//#include "../backend/datamanager/directobjsmanagers/basicdatabasedata.h"

////class MyController: public QObject {
////    Q_OBJECT
////    Q_PROPERTY(QColor myColor MEMBER myColor NOTIFY myColorChanged)
////public:
////    using QObject::QObject;

////signals:
////    void myColorChanged();

////private:
////    QColor myColor = Qt::yellow;
////};

//class MyModel
//{
//    Q_GADGET
//    Q_PROPERTY(QColor color MEMBER color CONSTANT)
//    Q_PROPERTY(QString name MEMBER name CONSTANT)
//    Q_PROPERTY(MyIntData *intdata MEMBER intdata CONSTANT)

//    //    Q_PROPERTY(ConstIntData somevalue MEMBER somevalue CONSTANT)
//public:
//    MyIntData *intdata = new MyIntData("name");
//    QColor color = Qt::darkBlue;
//    QString name = "Hello world";
//    //    ConstIntData somevalue{"vvv"};
//};
//Q_DECLARE_METATYPE(MyModel)

//class MyController: public QObject {
//    Q_OBJECT
//    Q_PROPERTY(MyModel myModel MEMBER myModel CONSTANT)
//    //    Q_PROPERTY(IntData myData MEMBER myData CONSTANT)
//public:
//    using QObject::QObject;

//    void update()
//    {
//        myModel.color = Qt::red;
//        myModel.name = "Filip";
//        //        myModel.somevalue.set(20);
//        emit updated(myModel);
//    }

//signals:
//    void myColorChanged();
//    void updated(const MyModel &);

//private:
//    MyModel myModel;
//    IntData myData{"name"};
//};
