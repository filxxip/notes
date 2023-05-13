#include "entrycontroller.h"
#include <QRegularExpression>
#include <QStringLiteral>
#include "../cpputils/utils.h"

EntryController::EntryController(QPointer<DialogController> dialogController_, QObject *obj)
    : QObject(obj)
    , dialogController(dialogController_)
{
    connect(this, &EntryController::confirm, this, &EntryController::onConfirmed);
}

void EntryController::emitSuccessDialogWithClear(int code, Person person)
{
    emit clear();
    dialogController->showDialog(code);
    dialogController->applyConnection([this, person = std::move(person)](auto status) mutable {
        emit changingViewOperationSuccess(std::move(person));
    });
}
