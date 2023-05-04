//#pragma once
//#include <QDebug>
//#include <QModelIndex>
//#include <QObject>
//#include <QPointer>
//#include <QTimer>
//#include "registerboxmodel.h"

//template<typename EnumType>
//struct SwitcherModel
//{
//    QString text;
//    EnumType type;
//};

//class LogController : public QObject
//{
//    Q_OBJECT
//    Q_PROPERTY(ModelStatuses::UserViews userViewType MEMBER m_userView NOTIFY userViewChanged)
//    Q_PROPERTY(RegisterViewModel *userModel READ getUserModel NOTIFY userViewChanged CONSTANT)
//    Q_PROPERTY(
//        CustomListModel<SwitcherModel<ModelStatuses::UserViews>, ModelStatuses::UserViewsRoles>
//            *switcherModel MEMBER switcherModel CONSTANT)
//    Q_PROPERTY(bool activityPossible MEMBER m_activity_possible NOTIFY activityStatusChanged)

//public:
//    LogController();

//signals:
//    void loginActiveChanged(); //jak sie zrobi operator= to moze ten person i template bedzie dzialac

//private:
//    ModelStatuses::UserViews m_userView = ModelStatuses::UserViews::LOGIN;
//    bool m_loginActive = true;
//    bool m_activity_possible = true;
//    QPointer<RegisterViewModel> registerModel = new RegisterViewModel();
//    QPointer<RegisterViewModel> loginModel = new RegisterViewModel();
//    QPointer<RegisterViewModel> guestModel = new RegisterViewModel();
//    QPointer<RegisterViewModel> userModel;
//    QPointer<CustomListModel<SwitcherModel<ModelStatuses::UserViews>, ModelStatuses::UserViewsRoles>>
//        switcherModel;

//    void setActivity(bool value);

//    QPointer<RegisterViewModel> getUserModel() const
//    {
//        if (m_userView == ModelStatuses::UserViews::LOGIN) {
//            return loginModel;
//        }
//        if (m_userView == ModelStatuses::UserViews::REGISTER) {
//            return registerModel;
//        }
//        return guestModel;
//    }

//private slots:
//    void onRegisteringModel();
//public slots:
//    void onSwitchedChanged(ModelStatuses::UserViews s)
//    {
//        qDebug() << s;
//        m_userView = s;
//        emit userViewChanged(m_userView);
//        if (s == ModelStatuses::UserViews::LOGIN) {
//            qDebug() << "hello";
//        } else {
//            qDebug() << "xD";
//        }
//    }

//signals:
//    void confirmEnter();
//    void registerObjectInModel();
//    void activityStatusChanged();

//    void userViewChanged(ModelStatuses::UserViews newView);
//};
