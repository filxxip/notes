import QtQuick 2.15
import QtQuick.Window

//import Statuses 1.0
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
        SwitchButton {
            id: switcher
            anchors.horizontalCenter: parent.horizontalCenter
            leftIsClicked: logController.loginActive
            onLeftClicked: logController.loginActive = true
            onRightClicked: logController.loginActive = false

            mydata: GUIConfig.switchbutton
        }
        Item {
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
    CustomDialog {
        visible: dialogController.visibility
    }
}
