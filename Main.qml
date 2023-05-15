import QtQuick 2.15
import QtQuick.Window
import QtQuick.Controls 2.15
import QtQuick.Shapes 1.15
import QtQuick.Layouts 1.15
import QtQml 2.3
import ModelStatuses 1.0

import "src/gui"
import "src/gui/customdialog"
import "src/gui/userview"
import "src/gui/qmlutils"
import "src/gui/calendar"
import "src/gui/usereditview"

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
    CustomDialog {
        visible: dialogController.visibility
    }

    //            Item {
    //    UserProfileView {
    //        id: userEditView
    //        //        anchors.left: outerRectangle.left
    //        anchors.centerIn: parent
    //        anchors.fill: parent
    //    }
    //    }
    //    LogView {}
    Loader {
        anchors.fill: parent
        property var map: [logView, userView]
        sourceComponent: map[mainController.userView]
    }
    Component {
        id: logView
        LogView {
            anchors.centerIn: parent
            anchors.fill: parent
        }
    }
    Component {
        id: userView
        UserProfileView {
            id: userEditView
            //        anchors.left: outerRectangle.left
            anchors.centerIn: parent
            anchors.fill: parent
        }
    }
}
