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

    //            anchors.fill: parent
    //            interactive: false

    //            Item {
    UserProfileView {
        id: userEditView
        //        anchors.left: outerRectangle.left
        anchors.centerIn: parent
        anchors.fill: parent
    }
    //    Popup {
    //        x: 400

    //        y: 400
    //        enter: Transition {
    //            NumberAnimation {
    //                property: "width"
    //                from: 0
    //                to: 300
    //                duration: 600
    //            }
    //            //            NumberAnimation {
    //            //                property: "x"
    //            //                from: popp.x + popp.width
    //            //                to: popp.x + 0.5 * popp.width
    //            //                duration: 600
    //            //            }
    //        }
    //        exit: Transition {
    //            NumberAnimation {
    //                property: "width"
    //                from: popp.width
    //                to: 0
    //                duration: 600
    //            }
    //        }
    //        clip: true
    //        contentItem: Rectangle {
    //            color: "red"
    //            Rectangle {
    //                width: 50
    //                height: 50
    //                anchors.right: parent.right
    //                color: "black"
    //            }

    //            width: 300
    //            height: 300
    //        }
    //        id: popp
    //        width: 300
    //        height: 300
    //        //        background: Rectangle {
    //        //            color: "transparent"
    //        //        }
    //    }

    //    CustomRadioButton {
    //        controller: buttonController
    //        combinedWidth: 400
    //        combinedHeight: 100
    //        spacing: 40
    //    }

    //    ListView {
    //        orientation: Qt.Horizontal
    //        width: 200
    //        height: 50
    //        model: ["a","b".]
    //        delegate: RadioButton {
    //            width: 50
    //            height: 50
    //            id: radiobutton
    //            text: modelData
    //            onCheckedChanged: model.checked = checked
    //            opacity: mouseArea.containsMouse ? 0.5 : 1

    //            MouseArea {
    //                id: mouseArea
    //                anchors.fill: parent
    //                cursorShape: containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor
    //            }
    //        }
    //    }

    //            }

    //            Item {
    //        DateChooser {}
    //            }

    //            Component {
    //                id: cmp1
    //                DateChooser {}
    //            }
    //            Component {
    //                id: cmp2
    //                LogView {}
    //            }
}
