#pragma once
#include "../../backend/datamanager/directobjsmanagers/guidialogs/guidialog.h"
#include "../../backend/datamanager/directobjsmanagers/guidialogs/guidialogmanager.h"
#include "../customlistviewmodel.h"
#include "../registerboxmodel.h"
#include "../statuses.h"

#include <QObject>
#include <QPointer>
#include "../models/modelaliases.h"
#include "../modelutils/customlistmodel.h"
#include <functional>

namespace {
using Model = CustomListModel<GuiDialog, ModelStatuses::DialogRoles>;
using ModelBuilder = FastModelBuilder<GuiDialog, ModelStatuses::DialogRoles>;
} // namespace

class DialogController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(DialogModelAliases::Model *dialogModel MEMBER dialogModel CONSTANT)

    Q_PROPERTY(int currentIndex MEMBER currentIndex NOTIFY indexChanged)

    Q_PROPERTY(bool visibility MEMBER visibility NOTIFY visibilityChanged)

    Q_PROPERTY(int dialogCode READ getDialogCode NOTIFY indexChanged CONSTANT)
private:
    using Status = ModelStatuses::DialogRoles;

    GuiDialogsManager manager;

    int currentIndex = 0;

    bool visibility = false;

    QPointer<DialogModelAliases::Model> dialogModel;

    int getDialogCode() const;

public:
    DialogController(std::shared_ptr<DataClient> dataClient);

    enum class ActivityStatus { ACCEPT, REJECT };

public slots:
    void onAccepted();

    void onRejected();

signals:
    void indexChanged(int index);

    void visibilityChanged(bool visibility);

    void activity(ActivityStatus status);

public:
    void applyConnection(std::function<void(ActivityStatus status)> method);
};
