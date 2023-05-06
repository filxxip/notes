#include "dialogcontroller.h"
#include <QMessageBox>

DialogController::DialogController(std::shared_ptr<DataClient> dataClient)
    : QObject()
    , manager(dataClient)
{
    dialogModel = ModelBuilder()
                      .add(Status::CONTENT, &GuiDialog::content)
                      .add(Status::IS_OK, &GuiDialog::isOk)
                      .add(Status::IS_YES, &GuiDialog::isYes)
                      .add(Status::IS_NO, &GuiDialog::isNo)
                      .add(Status::TITLE, &GuiDialog::title)
                      .add(Status::PATH, &GuiDialog ::path)
                      .add(Status::FONT_SIZE, &GuiDialog::fontSize)
                      .build();
    GuiDialog dialog;
    dialog.content.set("xxxxfsdgfsdsdxxxfsdgfsdsdxxxfsdgfsdsdxxxfsdgfsdsdxxxfsdgfsdsdxfsdgfsdsdx");
    dialog.title.set("Incorrect Data");
    dialog.isOk.set(true);
    dialog.isYes.set(true);
    dialog.isNo.set(true);
    dialog.path.set("qrc:/resources/information.png");
    dialog.fontSize.set(13);
    dialogModel->addEntry(dialog);
    //        dialogModel->setEntries(manager.get());
}

int DialogController::getDialogCode() const
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
    return code;
}

void DialogController::onAccepted()
{
    emit activity(ActivityStatus::ACCEPT);
    visibility = false;
}

void DialogController::onRejected()
{
    emit activity(ActivityStatus::REJECT);
    visibility = false;
}

void DialogController::applyConnection(std::function<void(ActivityStatus status)> method)
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
