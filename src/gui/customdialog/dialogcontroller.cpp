#include "dialogcontroller.h"
#include <QMessageBox>
#include "../cpputils/utils.h"

namespace {
constexpr const char *INVALID_ACCESS = "Incorrect data accesss!";
const auto ACCESS_TO_DIALOG_ERROR = QStringLiteral(
    "Access to dialog code : %1 denied or is invalid. Check your database or data files.");
} // namespace

DialogController::DialogController(std::shared_ptr<GuiDialogsManager> manager_, QObject *obj)
    : QObject(obj)
    , manager(manager_)
{
    dialogModel = ModelBuilder()
                      .add(Status::CONTENT, &GuiDialog::content)
                      .add(Status::IS_OK, &GuiDialog::isOk)
                      .add(Status::IS_YES, &GuiDialog::isYes)
                      .add(Status::IS_NO, &GuiDialog::isNo)
                      .add(Status::TITLE, &GuiDialog::title)
                      .add(Status::PATH, &GuiDialog ::path)
                      .add(Status::FONT_SIZE, &GuiDialog::fontSize)
                      .add(Status::ID, &GuiDialog::id)
                      .build();
    auto values = manager->get();
    if (values.has_value()) {
        dialogModel->setEntries(values.value());
    } else {
        qDebug() << INVALID_ACCESS;
    }
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

void DialogController::setVisibility(bool value)
{
    visibility = value;
    emit visibilityChanged(value);
}

void DialogController::onAccepted()
{
    emit activity(ActivityStatus::ACCEPT);
    setVisibility(false);
}

void DialogController::onRejected()
{
    emit activity(ActivityStatus::REJECT);
    setVisibility(false);
}

bool DialogController::showDialog(int code)
{
    auto newPotentialIndex = DatabaseUtilsFunctions::convertCodeToIndex(code,
                                                                        this->dialogModel,
                                                                        Status::ID,
                                                                        ACCESS_TO_DIALOG_ERROR.arg(
                                                                            QString::number(code)));
    if (newPotentialIndex.has_value()) {
        currentIndex = newPotentialIndex.value();
        emit indexChanged(currentIndex);
        setVisibility(true);
        return true;
    }
    return false;
}

void DialogController::applyConnection(std::function<void(ActivityStatus status)> method,
                                       bool afterCurrentConnection)
{
    connect(
        this,
        &DialogController::activity,
        this,
        [this, method = std::move(method)](ActivityStatus status) { method(status); },
        static_cast<Qt::ConnectionType>(
            (afterCurrentConnection ? Qt::QueuedConnection : Qt::AutoConnection)
            | Qt::SingleShotConnection)); //same as 258
}
