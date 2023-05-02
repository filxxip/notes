#pragma once
#include "../../backend/datamanager/directobjsmanagers/guidialogs/guidialog.h"
#include "../customlistviewmodel.h"
#include "../registerboxmodel.h"
#include "../statuses.h"

#include <QMessageBox>
#include <QObject>
#include <QPointer>
#include <functional>

class DialogViewModel : public CustomListModel<GuiDialog, ModelStatuses::DialogRoles>
{
    Q_OBJECT

public:
    DialogViewModel(QObject *parent = nullptr);
};

class DialogController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(DialogViewModel *dialogModel MEMBER dialogModel CONSTANT)

    Q_PROPERTY(int currentIndex MEMBER currentIndex NOTIFY indexChanged)

    Q_PROPERTY(bool visibility MEMBER visibility NOTIFY visibilityChanged)

    Q_PROPERTY(int dialogCode READ getDialogCode NOTIFY indexChanged CONSTANT)
private:
    using QObject::QObject;

    QPointer<DialogViewModel> dialogModel = new DialogViewModel();

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
