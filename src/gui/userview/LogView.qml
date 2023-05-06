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
                Component.onDestruction: console.log("destruct12" + this)

                ButtonText {
                    Layout.fillWidth: true
                    contentText: GuiConfig.userView.loginView.accessRegisterText
                    onCustomReleased: logController.userViewType = ModelStatuses.UserViews.REGISTER
                    height: parent.height
                    Component.onDestruction: console.log("destruct2" + this)
                }
                ButtonText {
                    contentText: GuiConfig.userView.loginView.showPasswordText
                    Layout.fillWidth: true
                    height: parent.height
                    property var element: logController.entryController.model.get(
                                              1)
                    onCustomClicked: {
                        element.update(false, ModelStatuses.Roles.PASS_STATUS)
                        //                        dialogController.visibility = true
                    }

                    onCustomReleased: element.update(
                                          true, ModelStatuses.Roles.PASS_STATUS)
                    Component.onDestruction: console.log("destruct3" + this)
                }
            }
        }
    }

    signal birtdayEntryChanged(string content)

    Component {
        id: registerComponent

        Column {
            spacing: GuiConfig.userView.columnSpacing
            Component.onDestruction: console.log("destruct4" + this)
            Column {
                spacing: entries.spacing
                Component.onDestruction: console.log("destruct5" + this)
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
                        console.log("hahahhahahahah")
                        swipeView.currentIndex = 0
                    }

                    clickedSlot: foo
                    placeholder: logController.calendarController.niceFormat
                    customcolor: "red"
                    readOnly: true
                    Component.onDestruction: console.log("destruct6" + this)
                }
            }
            ButtonText {
                contentText: GuiConfig.userView.registerView.accessLoginText
                width: GUIConfig.userView.defaultEntryWidth
                height: GuiConfig.userView.accessButtonHeight
                onCustomReleased: logController.userViewType = ModelStatuses.UserViews.LOGIN
                Component.onDestruction: console.log("destruct7" + this)
            }
        }
    }
    Component {
        id: guestComponent
        Column {
            spacing: GuiConfig.userView.columnSpacing
            Component.onDestruction: console.log("destruct8" + this)
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
        Component.onDestruction: console.log("destruct9" + this)
    }

    Rectangle {
        width: GUIConfig.userView.width
        height: GUIConfig.userView.height
        radius: 10
        color: "#376945"
        id: view
        property int t: 1
        Keys.onRightPressed: t = 0
        Keys.onLeftPressed: console.log("left")
        Component.onDestruction: console.log("destruct10" + this)
        SwipeView {
            id: swipeView
            currentIndex: 1
            interactive: false
            anchors.fill: view
            clip: true
            Component.onDestruction: console.log("destruct11" + this)
            Item {
                id: itemColumn
                Component.onDestruction: console.log("destruct12" + this)
                Column {
                    anchors.centerIn: itemColumn
                    spacing: 40
                    Component.onDestruction: console.log("destruct13" + this)
                    DateChooser {
                        backgroundColor: GUIConfig.colors.transparent
                        height: 300
                        function foo() {
                            reset()
                            console.log("fsdfsdf")
                        }
                        Component.onDestruction: console.log(
                                                     "destruct14" + this)

                        //                        Component.onCompleted: logController.calendarController.resetGui.connect(
                        //                                                   foo)
                    }

                    Rectangle {
                        width: GUIConfig.userView.checkButtonWidth
                        height: GUIConfig.userView.checkButtonHeight
                        color: GuiConfig.colors.transparent
                        anchors.horizontalCenter: parent.horizontalCenter
                        Component.onDestruction: console.log(
                                                     "destruc15t" + this)
                        CustomButton {
                            contentText: "SELECT"
                            anchors.fill: parent
                            onClicked: {
                                console.log("fsdfsdf")
                                swipeView.currentIndex = 1
                            }
                            Component.onDestruction: console.log(
                                                         "destruct" + this)
                        }
                    }
                }
            }
            Item {
                id: itemLayout
                ColumnLayout {
                    spacing: GUIConfig.userView.layoutSpacing
                    anchors.centerIn: itemLayout
                    Component.onDestruction: console.log("destruct16" + this)
                    TitleBox {
                        title: GuiConfig.userView.userViewDetails[logController.userViewType].titleContent
                        width: GUIConfig.userView.defaultEntryWidth
                        height: GuiConfig.userView.titleHeight
                        Layout.alignment: Qt.AlignHCenter
                        Component.onDestruction: console.log(
                                                     "destruct17" + this)
                    }

                    Loader {
                        Layout.alignment: Qt.AlignHCenter
                        property var registermap: [registerComponent, loginComponent, guestComponent]
                        sourceComponent: registermap[logController.userViewType]
                        onRegistermapChanged: console.log("register changed")
                        onSourceComponentChanged: console.log(registermap)
                        Component.onDestruction: console.log(
                                                     "destruct18" + this)
                        //                        sourceComponent: registermap[view2.t]
                    }

                    Rectangle {
                        width: GUIConfig.userView.checkButtonWidth
                        height: GUIConfig.userView.checkButtonHeight
                        color: GuiConfig.colors.transparent
                        Layout.alignment: Qt.AlignHCenter
                        Component.onDestruction: console.log(
                                                     "destruct19" + this)
                        CustomButton {
                            enabled: logController.activityPossible
                            contentText: GuiConfig.userView.userViewDetails[logController.userViewType].checkContent
                            anchors.fill: parent
                            onClicked: logController.entryController.confirm()
                            Component.onDestruction: console.log(
                                                         "destruct20" + this)
                        }
                    }
                }
            }
        }
    }
}
