#pragma once
#include "../../backend/datamanager/directobjsmanagers/guidialogs/guidialog.h"
#include "../customlistviewmodel.h"
#include "../registerboxmodel.h"
#include "../statuses.h"

#include <QMessageBox>
#include <QObject>
#include <QPointer>
#include <functional>

//class DialogViewModel : public CustomListModel<GuiDialog, ModelStatuses::DialogRoles>
//{
//    Q_OBJECT

//public:
//    DialogViewModel(QObject *parent = nullptr);
//};
//DialogViewModel::DialogViewModel(QObject *parent)
//    : CustomListModel(parent)
//{
//    ADD_DATA(ModelStatuses::DialogRoles::CONTENT, content)
//    ADD_DATA(ModelStatuses::DialogRoles::IS_OK, isOk)
//    ADD_DATA(ModelStatuses::DialogRoles::IS_YES, isYes)
//    ADD_DATA(ModelStatuses::DialogRoles::IS_NO, isNo)
//    ADD_DATA(ModelStatuses::DialogRoles::TITLE, title)
//    ADD_DATA(ModelStatuses::DialogRoles::PATH, path)
//    ADD_DATA(ModelStatuses::DialogRoles::FONT_SIZE, fontSize)
//    GuiDialog dialog;
//    dialog.content.set("xxxxfsdgfsdsdxxxfsdgfsdsdxxxfsdgfsdsdxxxfsdgfsdsdxxxfsdgfsdsdxfsdgfsdsdx");
//    dialog.title.set("Incorrect Data");
//    dialog.isOk.set(true);
//    dialog.isYes.set(true);
//    dialog.isNo.set(true);
//    dialog.path.set("qrc:/resources/information.png");
//    dialog.fontSize.set(13);
//    addEntry(dialog);
//}
class DialogController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(CustomListModel<GuiDialog, ModelStatuses::DialogRoles> *dialogModel MEMBER
                   dialogModel CONSTANT)

    Q_PROPERTY(int currentIndex MEMBER currentIndex NOTIFY indexChanged)

    Q_PROPERTY(bool visibility MEMBER visibility NOTIFY visibilityChanged)

    Q_PROPERTY(int dialogCode READ getDialogCode NOTIFY indexChanged CONSTANT)
private:
    using Status = ModelStatuses::DialogRoles;

public:
    DialogController()
        : QObject()
    {
        FastModelBuilder<GuiDialog, ModelStatuses::DialogRoles> builder;

        dialogModel = builder.add(Status::CONTENT, &GuiDialog::content, "content")
                          .add(Status::IS_OK, &GuiDialog::isOk, "isOk")
                          .add(Status::IS_YES, &GuiDialog::isYes, "isYes")
                          .add(Status::IS_NO, &GuiDialog::isNo, "isNo")
                          .add(Status::TITLE, &GuiDialog::title, "title")
                          .add(Status::PATH, &GuiDialog::path, "path")
                          .add(Status::FONT_SIZE, &GuiDialog::fontSize, "fontSize")
                          .build();
        GuiDialog dialog;
        dialog.content.set(
            "xxxxfsdgfsdsdxxxfsdgfsdsdxxxfsdgfsdsdxxxfsdgfsdsdxxxfsdgfsdsdxfsdgfsdsdx");
        dialog.title.set("Incorrect Data");
        dialog.isOk.set(true);
        dialog.isYes.set(true);
        dialog.isNo.set(true);
        dialog.path.set("qrc:/resources/information.png");
        dialog.fontSize.set(13);
        dialogModel->addEntry(dialog);
    }

private:
    QPointer<CustomListModel<GuiDialog, ModelStatuses::DialogRoles>> dialogModel;

    int currentIndex = 0;
    bool visibility = false;

    int getDialogCode() const
    {
        int code = 0;
        if (dialogModel->data(currentIndex, ModelStatuses::DialogRoles::IS_YES).value<bool>()) {
            code |= QMessageBox::Yes;
        }
        if (dialogModel->data(currentIndex, ModelStatuses::DialogRoles::IS_NO).value<bool>()) {
            code |= QMessageBox::No;
        }
        if (dialogModel->data(currentIndex, ModelStatuses::DialogRoles::IS_OK).value<bool>()) {
            code |= QMessageBox::Ok;
        }
        return code; //cos z tym indeksem outofrange pomyslec i pierdzieli sie undefined, cos chyba nie tak z ta zamiana na qvariant, pomyslec o innuym macro, napewno wtedy bedzie gdzialac conversja
        //jak qvariant sie stworzy na bazie metody get z dbdata np a nie od razu z dbdata
    }

public:
    enum class ActivityStatus { ACCEPT, REJECT };

public slots:
    void onAccepted()
    {
        emit activity(ActivityStatus::ACCEPT);
        visibility = false;
    }

    void onRejected()
    {
        emit activity(ActivityStatus::REJECT);
        visibility = false;
    }

signals:
    void indexChanged(int index);
    void visibilityChanged(bool visibility);

    void activity(ActivityStatus status);

public:
    void applyConnection(std::function<void(ActivityStatus status)> method)
    {
        auto connection = new QMetaObject::Connection;
        *connection = connect(this,
                              &DialogController::activity,
                              [this, method = std::move(method), connection](ActivityStatus status) {
                                  disconnect(*connection);
                                  delete connection;
                                  method(status);
                              });
    }
};
