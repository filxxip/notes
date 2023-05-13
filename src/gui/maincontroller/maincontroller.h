#pragma once

#include <QCoreApplication>
#include <QDebug>
#include <QObject>
#include <QPointer>
#include "../customdialog/dialogcontroller.h"

class MainController : public QObject
{
    Q_OBJECT

    QPointer<DialogController> dialogController;

public:
    MainController(QPointer<DialogController> dialogController_, QObject *obj = nullptr);

    Q_INVOKABLE void closeApp();
};
