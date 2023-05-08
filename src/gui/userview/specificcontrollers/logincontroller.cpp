#include "logincontroller.h"

namespace {

constexpr const char *DOUBLE_EMAIL
    = "This is email is not unique in database or your data files. Check it and fix this issue.";

} // namespace

LoginController::LoginController(std::shared_ptr<DataClient> dataclient_,
                                 QPointer<DialogController> dialogController_,
                                 QObject *obj)
    : EntryController(dialogController_, obj)
    , manager(dataclient_)
{
    model->setEntries({{EnumStatus::EMAIL, "Login..."}, {EnumStatus::PASSWORD, "Password..."}});
    model->setData(1, true, ModelStatuses::Roles::PASSWORD_STATUS);
}

void LoginController::onConfirmed()
{
    auto name = model->data(0, ModelStatuses::Roles::VALUE).toString();
    auto password = model->data(1, ModelStatuses::Roles::VALUE).toString();
    auto personWithGiveEmail = manager.getFiltered({{"email", name.toStdString()}});
    if (personWithGiveEmail.has_value() && personWithGiveEmail->size() > 1) {
        qDebug() << DOUBLE_EMAIL;
        return;
    }

    if (personWithGiveEmail->size() == 1 && personWithGiveEmail->at(0).password == password) {
        emitSuccessDialogWithClear(DialogCodes::UserViews::LOGIN_PERSON_SUCCESS,
                                   personWithGiveEmail->at(0));
    } else {
        dialogController->showDialog(DialogCodes::UserViews::LOGIN_INVALID_ACCESS);
    }
}
