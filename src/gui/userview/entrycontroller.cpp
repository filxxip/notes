#include "entrycontroller.h"
#include <QRegularExpression>
#include <QStringLiteral>
#include "../cpputils/utils.h"
#include "src/backend/datamanager/directobjsmanagers/singletonobjectmanager/singletonobjectmanager.h"

EntryController::EntryController(
    std::unique_ptr<SingletonObjectManager<Person>> singleLoginPersonManager_,
    QPointer<DialogController> dialogController_,
    QObject *obj)
    : QObject(obj)
    , singleLoginPersonManager(std::move(singleLoginPersonManager_))
    , dialogController(dialogController_)
{
    connect(this, &EntryController::confirm, this, &EntryController::onConfirmed);
}

void EntryController::emitSuccessDialogWithClear(int code, Person person)
{
    dialogController->showDialog(code);
    dialogController->applyConnection([this, person = std::move(person)](auto status) mutable {
        emit clear();
        singleLoginPersonManager->set(person);
    });
}
