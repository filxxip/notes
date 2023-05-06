import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import ModelStatuses 1.0
import "../"
import "../qmlutils"
import "../calendar"

Column {

    //Component which is visible when guest login is on
    Component {
        id: loginComponent

        Column {
            spacing: GuiConfig.userView.columnSpacing
            LogViewEntryPart {
                configurationObject: GUIConfig.userView.loginView
                entryModel: logController.entryController.model
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
                                         false,
                                         ModelStatuses.Roles.PASSWORD_STATUS)

                    onCustomReleased: element.update(
                                          true,
                                          ModelStatuses.Roles.PASSWORD_STATUS)
                }
            }
        }
    }

    //Component which is visible when register mode is on
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
                    placeholder: "Birhday: " + logController.calendarController.niceFormat
                    customcolor: GUIConfig.colors.red
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

    //Component which is visible when guest model is on
    Component {
        id: guestComponent
        Column {
            spacing: GuiConfig.userView.columnSpacing
            LogViewEntryPart {
                configurationObject: GUIConfig.userView.guestView //pomyslec o podaniu konkretnego modelu np guest, login itd
                entryModel: logController.entryController.model
            }
        }
    }

    //main part of log view
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
        radius: GUIConfig.userView.radiusOfMainRectangle
        color: GUIConfig.colors.backgroundGreen
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
                    spacing: GUIConfig.userView.dateChooser.spacing
                    DateChooser {
                        backgroundColor: GUIConfig.colors.transparent
                        height: GUIConfig.userView.dateChooser.height
                        Component.onCompleted: logController.calendarController.resetGui.connect(
                                                   reset)
                        controller: logController.calendarController
                        itemNumber: GUIConfig.userView.dateChooser.itemNumber
                    }

                    Rectangle {
                        width: GUIConfig.userView.checkButtonWidth
                        height: GUIConfig.userView.checkButtonHeight
                        color: GuiConfig.colors.transparent
                        anchors.horizontalCenter: parent.horizontalCenter
                        CustomButton {
                            contentText: GUIConfig.userView.dateChooser.buttonText
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
