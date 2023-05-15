#pragma once
#include "../../backend/datamanager/directobjsmanagers/guidialogs/guidialog.h"
#include "../../backend/datamanager/directobjsmanagers/guidialogs/guidialogmanager.h"
#include "../statuses.h"

#include <QObject>
#include <QPointer>
#include <QStringLiteral>
#include "../modelutils/customlistmodel.h"
#include "../modelutils/listmodelbuilder.h"
#include <functional>

namespace {
using Model = CustomListModel<GuiDialog, ModelStatuses::DialogRoles>;
using ModelBuilder = FastModelBuilder<GuiDialog, ModelStatuses::DialogRoles>;
} // namespace

namespace DialogCodes { //pozniej bardziej posegregowac
namespace UserViews {
constexpr int EMPTY_NAME_GUEST = 1;
constexpr int LOGIN_INVALID_ACCESS = 2;
constexpr int INVALID_REGISTER_PASSWORD = 3;
constexpr int INVALID_REGISTER_EMAIL = 4;
constexpr int INVALID_REGISTER_PASSWORD_AND_EMAIL = 5;
constexpr int INVALID_FIELDS = 6;
constexpr int REGISTER_NEW_USER_SUCCESS = 7;
constexpr int REGISTER_GUEST_SUCCESS = 8;
constexpr int LOGIN_PERSON_SUCCESS = 9;
constexpr int INVALID_UPDATED_PASSWORD = 10;
constexpr int INVALID_UPDATED_FIELDS = 11;
constexpr int EMAIL_IN_USE = 12;
constexpr int UPDATES_PERSOS_SUCCESS = 13;
constexpr int CHECK_ACCOUNT_REMOVE = 14;
constexpr int ACCOUNT_REMOVE_INFORMATION = 15;
constexpr int LOGOUT = 16;
constexpr int CLOSE_APP = 17;
constexpr int LOGOUT_INFO = 18;
} // namespace UserViews

} // namespace DialogCodes

class DialogController final : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Model *dialogModel MEMBER dialogModel CONSTANT)

    Q_PROPERTY(int currentIndex MEMBER currentIndex NOTIFY indexChanged)

    Q_PROPERTY(bool visibility MEMBER visibility NOTIFY visibilityChanged)

    Q_PROPERTY(int dialogCode READ getDialogCode NOTIFY indexChanged CONSTANT)
private:
    using Status = ModelStatuses::DialogRoles;

    std::unique_ptr<GuiDialogsManager> manager;

    int currentIndex = 0;

    bool visibility = false;

    QPointer<Model> dialogModel;

    int getDialogCode() const;

    void setVisibility(bool value);

public:
    DialogController(std::unique_ptr<GuiDialogsManager> manager_, QObject *obj = nullptr);

    enum class ActivityStatus { ACCEPT, REJECT };

    bool showDialog(int code);

public slots:
    void onAccepted();

    void onRejected();

signals:
    void indexChanged(int index);

    void visibilityChanged(bool visibility);

    void activity(ActivityStatus status);

public:
    void applyConnection(std::function<void(ActivityStatus status)> method,
                         bool afterCurrentConnection = false);
};
