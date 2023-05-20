import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import ModelStatuses 1.0
import "../"
import "../qmlutils"
import "../calendar"
import "../radiobutton"

Column {

    //Component which is visible when guest login is on
    Component {
        id: loginComponent

        Column {
            spacing: GuiConfig.userView.columnSpacing
            LogViewEntryPart {
                configurationObject: GUIConfig.userView.loginView
                controller: logController.controllers.loginController
            }
            Column {
                spacing: GUIConfig.userView.layoutSpacing
                RowLayout {
                    width: GUIConfig.userView.defaultEntryWidth
                    height: GuiConfig.userView.accessButtonHeight
                    spacing: GuiConfig.userView.accessButtonSpacing

                    ButtonText {
                        Layout.fillWidth: true
                        contentText: GuiConfig.userView.loginView.accessRegisterText
                        onCustomReleased: logController.view.userViewType
                                          = ModelStatuses.UserViews.REGISTER
                        height: parent.height
                    }
                    ButtonText {
                        contentText: GuiConfig.userView.loginView.showPasswordText
                        Layout.fillWidth: true
                        height: parent.height
                        property var element: logController.controllers.loginController.model.get(
                                                  1)
                        onCustomClicked: element.update(
                                             false,
                                             ModelStatuses.Roles.PASSWORD_STATUS)

                        onCustomReleased: element.update(
                                              true,
                                              ModelStatuses.Roles.PASSWORD_STATUS)
                    }
                }
                ConfirmButton {
                    configurationObject: GUIConfig.userView.loginView
                    controller: logController.controllers.loginController
                }
            }
        }
    }

    //Component which is visible when register mode is on
    Component {
        id: registerComponent
        Column {
            property var activeController: logController.controllers.registerController
            spacing: GuiConfig.userView.columnSpacing
            Column {
                spacing: entries.spacing
                LogViewEntryPart {
                    id: entries
                    configurationObject: GUIConfig.userView.registerView
                    controller: activeController
                }
                EntryField {
                    id: birthdayEntry
                    width: entries.width
                    height: entries.singleComponentHeight
                    activeFocusOnTab: true
                    clickedSlot: () => swipeView.currentIndex = 0
                    placeholder: "Birthday: " + activeController.calendarController.niceFormat
                    customcolor: GUIConfig.colors.red
                    readOnly: true
                }

                CustomRadioButton {
                    combinedWidth: GUIConfig.userView.radioButton.combinedWidth
                    combinedHeight: GUIConfig.userView.radioButton.combinedHeight
                    textHeight: GUIConfig.userView.radioButton.textHeight
                    controller: activeController.radioButtonController
                    fontSize: GUIConfig.userView.radioButton.fontSize
                    spacing: GUIConfig.userView.radioButton.spacing
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
            ButtonText {
                contentText: GuiConfig.userView.registerView.accessLoginText
                width: GUIConfig.userView.defaultEntryWidth
                height: GuiConfig.userView.accessButtonHeight
                onCustomReleased: logController.view.userViewType = ModelStatuses.UserViews.LOGIN
            }
            ConfirmButton {
                configurationObject: GUIConfig.userView.registerView
                controller: logController.controllers.registerController
            }
        }
    }

    //Component which is visible when guest model is on
    Component {
        id: guestComponent
        Column {
            spacing: GUIConfig.userView.layoutSpacing
            LogViewEntryPart {
                configurationObject: GUIConfig.userView.guestView
                controller: logController.controllers.guestController
            }
            ConfirmButton {
                configurationObject: GUIConfig.userView.guestView
                controller: logController.controllers.guestController
            }
        }
    }
    //main part of log view
    spacing: GUIConfig.userView.layoutSpacing
    anchors.centerIn: parent
    padding: 20
    ButtonSwitcher {
        enabled: swipeView.currentIndex !== 0
        model: logController.view.switcherModel
        tabSelectorEnum: logController.view.userViewType
        Component.onCompleted: switched.connect(
                                   newstatus => logController.view.userViewType = newstatus)
    }

    Rectangle {
        anchors.horizontalCenter: parent.horizontalCenter
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
                        width: GUIConfig.dateChooser.basicTumblerWidth * 3
                        backgroundColor: GUIConfig.colors.transparent
                        height: GUIConfig.userView.dateChooser.height
                        controller: logController.controllers.registerController.calendarController
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
                    id: column
                    TitleBox {
                        id: titleBox
                        title: GuiConfig.userView.userViewDetails[logController.view.userViewType].titleContent
                        width: GUIConfig.userView.defaultEntryWidth
                        height: GuiConfig.userView.titleHeight
                        Layout.alignment: Qt.AlignHCenter
                    }
                    Loader {
                        id: loader
                        Layout.alignment: Qt.AlignHCenter
                        property var registermap: [loginComponent, registerComponent, guestComponent]
                        sourceComponent: registermap[logController.view.userViewType]
                    }
                }
            }
        }
    }
}
