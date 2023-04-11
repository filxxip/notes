import QtQuick 2.15
import QtQuick.Window

import Statuses 1.0

import "src/gui"

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
        spacing: 50
        anchors.centerIn: parent
        SwitchButton {
            id: switcher
            width: GUIConfig.userView.defaultEntryWidth - 20
            anchors.horizontalCenter: parent.horizontalCenter
            height: 40
            leftButtontext: "Log in"
            rightButtonText: "Sign up"
            leftIsClicked: logController.loginActive
            onLeftClicked: logController.loginActive = true
            onRightClicked: logController.loginActive = false
        }
        Rectangle {
            width: GUIConfig.userView.defaultEntryWidth + 100
            height: 500
            radius: 10
            color: "#376945"
            id: viewParent
            Component {
                id: loginView
                LoginView {}
            }
            Component {
                id: registerView
                RegisterView {}
            }

            Loader {
                anchors.centerIn: parent
                sourceComponent: logController.loginActive ? loginView : registerView
            }
        }
    }
}
