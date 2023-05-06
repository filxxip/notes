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
                    onCustomReleased: logController.userViewType = ModelStatuses.UserViews.REGISTER
                    height: parent.height
                }
                ButtonText {
                    contentText: GuiConfig.userView.loginView.showPasswordText
                    Layout.fillWidth: true
                    height: parent.height
                    property var element: logController.entryController.model.get(
                                              1)
                    onCustomClicked: element.update(
                                         false, ModelStatuses.Roles.PASS_STATUS)

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
            Column {
                spacing: entries.spacing
                LogViewEntryPart {
                    id: entries
                    configurationObject: GUIConfig.userView.registerView
                    entryModel: logController.entryController.model

                    valueAssignSignal: logController.entryController.confirm
                }
                EntryField {
                    id: birthdayEntry
                    width: entries.width
                    height: entries.singleComponentHeight
                    activeFocusOnTab: true
                    function foo() {
                        swipeView.currentIndex = 0
                    }

                    clickedSlot: foo
                    placeholder: logController.calendarController.niceFormat
                    customcolor: "red"
                    readOnly: true
                }
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
        enabled: swipeView.currentIndex !== 0
        model: logController.switcherModel
        tabSelectorEnum: logController.userViewType
        Component.onCompleted: switched.connect(logController.onSwitchedChanged)
    }

    Rectangle {
        width: GUIConfig.userView.width
        height: GUIConfig.userView.height
        radius: 10
        color: "#376945"
        id: view
        SwipeView {
            id: swipeView
            currentIndex: 1
            interactive: false
            anchors.fill: view
            clip: true
            Item {
                id: itemColumn
                Column {
                    anchors.centerIn: itemColumn
                    spacing: 40
                    DateChooser {
                        backgroundColor: GUIConfig.colors.transparent
                        height: 300
                        Component.onCompleted: logController.calendarController.resetGui.connect(
                                                   reset)
                    }

                    Rectangle {
                        width: GUIConfig.userView.checkButtonWidth
                        height: GUIConfig.userView.checkButtonHeight
                        color: GuiConfig.colors.transparent
                        anchors.horizontalCenter: parent.horizontalCenter
                        CustomButton {
                            contentText: "SELECT"
                            anchors.fill: parent
                            onClicked: swipeView.currentIndex = 1
                        }
                    }
                }
            }
            Item {
                id: itemLayout
                ColumnLayout {
                    spacing: GUIConfig.userView.layoutSpacing
                    anchors.centerIn: itemLayout
                    TitleBox {
                        title: GuiConfig.userView.userViewDetails[logController.userViewType].titleContent
                        width: GUIConfig.userView.defaultEntryWidth
                        height: GuiConfig.userView.titleHeight
                        Layout.alignment: Qt.AlignHCenter
                    }

                    Loader {
                        Layout.alignment: Qt.AlignHCenter
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
