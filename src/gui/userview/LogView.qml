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
                id: entries
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
            Component.onCompleted: {
                function foo() {
                    swipeView.currentIndex = 0
                }

                entries.itemAtIndex(5).clickedSlot = foo
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


    /*Com/*ponent {
        id: swiper

        SwipeView {
            Column {
                id: outerColumn
                spacing: GUIConfig.userView.layoutSpacing
                Loader {
                    //                Layout.alignment: Qt.AlignHCenter
                    property var registermap: [registerComponent, loginComponent, guestComponent]
                    sourceComponent: registermap[logController.userViewType]
                }

                Rectangle {
                    width: GUIConfig.userView.checkButtonWidth
                    height: GUIConfig.userView.checkButtonHeight
                    color: GuiConfig.colors.transparent
                    anchors.horizontalCenter: outerColumn.horizontalCenter
                    CustomButton {
                        enabled: logController.activityPossible
                        contentText: GuiConfig.userView.userViewDetails[logController.userViewType].checkContent
                        anchors.fill: parent
                        onClicked: logController.entryController.confirm()
                    }
                    //                }
                }
            }
            Column {
                id: outerColumn2
                spacing: GUIConfig.userView.layoutSpacing
                DateChooser {}

                Rectangle {
                    width: GUIConfig.userView.checkButtonWidth
                    height: GUIConfig.userView.checkButtonHeight
                    color: GuiConfig.colors.transparent
                    //                    anchors.horizontalCenter: outerColumn.horizontalCenter
                    CustomButton {
                        contentText: "SELECT"
                        anchors.fill: parent
                        onClicked: console.log("zatwierdzam")
                    }
                }
            }
        }
    }*/
    spacing: 30
    anchors.centerIn: parent
    ButtonSwitcher {
        enabled: swipeView.currentIndex !== 0
        model: logController.switcherModel
        tabSelectorEnum: logController.userViewType
        Component.onCompleted: switched.connect(logController.onSwitchedChanged)
    }

    //    Rectangle {
    //        id: par
    //        width: GUIConfig.userView.width
    //        height: GUIConfig.userView.height
    Rectangle {
        //o ten rectangle ma zostac
        //            anchors.fill: parent
        width: GUIConfig.userView.width
        height: GUIConfig.userView.height
        radius: 10
        color: "#376945"
        id: view

        //        SwipeView {
        //            //ten swipe nizej, zeby background zielony zostawal w tle, i ogarnac problem z tym pozostaloscia po lewej prawej
        //            id: swipeView
        //            currentIndex: 0
        //            interactive: true
        //            anchors.fill: view
        //            anchors.centerIn: view
        //            DateChooser {}
        //        SwipeView {
        //            id: swipeView
        //            currentIndex: 0
        //            interactive: true
        //            anchors.fill: view
        //            clip: true
        //            anchors.centerIn: view
        //            DateChooser {}
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
                    }

                    Rectangle {
                        width: GUIConfig.userView.checkButtonWidth
                        height: GUIConfig.userView.checkButtonHeight
                        color: GuiConfig.colors.transparent
                        anchors.horizontalCenter: parent.horizontalCenter
                        CustomButton {
                            contentText: "SELECT"
                            anchors.fill: parent
                            onClicked: {
                                swipeView.currentIndex = 1
                            }
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
