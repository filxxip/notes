import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import ModelStatuses 1.0
import "../"
import "../qmlutils"
import "../calendar"

Column {

    Component {
        id: loginComponent

        Column {
            spacing: GuiConfig.userView.columnSpacing
            LogViewEntryPart {
                configurationObject: GUIConfig.userView.loginView
                entryModel: logController.entryController.model
                valueAssignSignal: logController.entryController.confirm
            }
            RowLayout {
                width: GUIConfig.userView.defaultEntryWidth
                height: GuiConfig.userView.accessButtonHeight
                spacing: GuiConfig.userView.accessButtonSpacing

                ButtonText {
                    Layout.fillWidth: true
                    contentText: GuiConfig.userView.loginView.accessRegisterText
                    onCustomReleased: {
                        logController.userViewType = ModelStatuses.UserViews.REGISTER
                    }
                    height: parent.height
                }
                ButtonText {
                    contentText: GuiConfig.userView.loginView.showPasswordText
                    Layout.fillWidth: true
                    height: parent.height
                    property var element: logController.entryController.model.get(
                                              1)
                    onCustomClicked: {
                        element.update(false, ModelStatuses.Roles.PASS_STATUS)
                        dialogController.visibility = true
                    }

                    onCustomReleased: element.update(
                                          true, ModelStatuses.Roles.PASS_STATUS)
                }
            }
        }
    }
    Component {
        id: registerComponent
        Column {
            spacing: GuiConfig.userView.columnSpacing
            LogViewEntryPart {
                configurationObject: GUIConfig.userView.registerView
                entryModel: logController.entryController.model
                valueAssignSignal: logController.entryController.confirm
            }
            ButtonText {
                contentText: GuiConfig.userView.registerView.accessLoginText
                width: GUIConfig.userView.defaultEntryWidth
                height: GuiConfig.userView.accessButtonHeight
                onCustomReleased: logController.userViewType = ModelStatuses.UserViews.LOGIN
            }
        }
    }
    Component {
        id: guestComponent
        Column {
            spacing: GuiConfig.userView.columnSpacing
            LogViewEntryPart {
                configurationObject: GUIConfig.userView.guestView
                entryModel: logController.entryController.model //lepiej gdyby podac wprost dany controller
                valueAssignSignal: logController.entryController.confirm
            }
        }
    }

    spacing: 30
    anchors.centerIn: parent
    ButtonSwitcher {
        model: logController.switcherModel
        tabSelectorEnum: logController.userViewType
        Component.onCompleted: switched.connect(logController.onSwitchedChanged)
    }
    Rectangle {
        id: par
        width: GUIConfig.userView.width
        height: GUIConfig.userView.height
        SwipeView {
            //ten swipe nizej, zeby background zielony zostawal w tle, i ogarnac problem z tym pozostaloscia po lewej prawej
            id: swipeView
            currentIndex: 0
            anchors.fill: par

            DateChooser {}

            Rectangle {
                //o ten rectangle ma zostac
                //            anchors.fill: parent
                radius: 10
                color: "#376945"
                id: view
                ColumnLayout {
                    spacing: GUIConfig.userView.layoutSpacing
                    anchors.centerIn: view
                    TitleBox {
                        title: GuiConfig.userView.userViewDetails[logController.userViewType].titleContent
                        width: GUIConfig.userView.defaultEntryWidth
                        height: GuiConfig.userView.titleHeight
                    }
                    Loader {
                        property var registermap: [registerComponent, loginComponent, guestComponent]
                        sourceComponent: registermap[logController.userViewType]
                    }

                    Rectangle {
                        width: GUIConfig.userView.checkButtonWidth
                        height: GUIConfig.userView.checkButtonHeight
                        color: GuiConfig.colors.transparent
                        Layout.alignment: Qt.AlignHCenter
                        CustomButton {
                            enabled: logController.activityPossible
                            contentText: GuiConfig.userView.userViewDetails[logController.userViewType].checkContent
                            anchors.fill: parent
                            onClicked: logController.entryController.confirm()
                        }
                    }
                }
            }
        }
    }
}
