import QtQuick 2.15
import QtQuick.Window

import Statuses 1.0

import "src/gui"

Window{
    Rectangle {
        anchors.fill : parent
        gradient: Gradient {
               GradientStop { position: 0.0; color: "#5ed4b1" }
           }
        }
    MouseArea {
            anchors.fill: parent
            onClicked: forceActiveFocus()
        }
    width: 640
    height: 480
    visible: true

    Component.onCompleted: {
        console.log(Statuses.MyStatus.First)
    }
    LoginView{

    }
}
