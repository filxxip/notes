import QtQuick 2.15
import QtQuick.Window
import QtQuick.Controls 2.15
import ModelStatuses 1.0

import "src/gui"
import "src/gui/customdialog"

Window {
    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop {
                position: 0.0
                color: "#5ed4b1"
            }
        }
    }
    MouseArea {
        anchors.fill: parent
        onClicked: forceActiveFocus()
    }
    width: 800
    height: 640
    visible: true

    Column {
        spacing: 30
        anchors.centerIn: parent

        //        SwitchButton {
        //            id: switcher
        //            anchors.horizontalCenter: parent.horizontalCenter
        //            leftIsClicked: logController.userViewType
        //            onLeftClicked: logController.userViewType = ModelStatuses.UserViews.LOGIN
        //            onRightClicked: logController.userViewType = ModelStatuses.UserViews.REGISTER

        //            mydata: GUIConfig.switchbutton
        //        }
        //        TabBar {
        //            id: tabBar
        //            background: Rectangle {
        //                width: 0
        //                height: 0
        //            }
        //            property var combinedWidth
        //            property var elementHeight
        //            property var controller

        //            Repeater {
        //                model: tabBar.controller.model
        //                TabButton {
        //                    text: model.text
        //                    width: tabBar.combinedWidth / model.count
        //                    height: tabBar.elementHeight
        //                    background: Rectangle {
        //                        color: tabBar.currentIndex == index ? "yellow" : "black"
        //                        anchors.fill: parent
        //                        radius: 3
        //                    }
        //                    onReleased: controller.switched(model.type)
        //                }
        //            }

        //            TabButton {
        //                id: but1
        //                text: "Tab 1"
        //                implicitWidth: 120
        //                implicitHeight: 30
        //                z: tabBar.currentIndex === 0 ? 1 : 0
        //                background: Rectangle {
        //                    color: tabBar.currentItem == but1 ? "yellow" : "black"
        //                    anchors.fill: parent
        //                    radius: 5
        //                    anchors.margins: -5
        //                }
        //            }

        //            TabButton {
        //                id: but2
        //                text: "Tab 2"
        //                implicitWidth: 120
        //                implicitHeight: 30
        //                z: tabBar.currentIndex === 1 ? 1 : 0
        //                background: Rectangle {
        //                    color: tabBar.currentItem == but2 ? "yellow" : "black"
        //                    anchors.fill: parent
        //                    radius: 5
        //                    anchors.margins: -5
        //                }
        //            }

        //            TabButton {
        //                id: but3
        //                text: "Tab 3"
        //                implicitWidth: 120
        //                implicitHeight: 30
        //                z: tabBar.currentIndex === 2 ? 1 : 0
        //                background: Rectangle {
        //                    color: tabBar.currentItem == but3 ? "yellow" : "black"
        //                    anchors.fill: parent
        //                    radius: 5
        //                    anchors.margins: -5
        //                }
        //            }
        //        }
        ButtonSwitcher {
            combinedWidth: 200
            elementHeight: 40
            model: logController.switcherModel
            Component.onCompleted: switched.connect(
                                       logController.onSwitchedChanged)
        }

        LoginView {}
        //        Item {
        //            Component {
        //                id: loginView
        //                LoginView {}
        //            }

        //            //            Component {
        //            //                id: registerView
        //            //                RegisterView {}
        //            //            }
        //            Loader {
        //                anchors.centerIn: parent
        //                sourceComponent: logController.loginActive ? loginView : registerView
        //            }
        //        }
    }
    //    CustomDialog {
    //        visible: dialogController.visibility
    //    }
}
