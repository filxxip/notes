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

    LoginView {}
}
