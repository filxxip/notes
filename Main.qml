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
    LogView {}

    //    CustomRadioButton {
    //        controller: buttonController
    //        combinedWidth: 400
    //        combinedHeight: 100
    //        spacing: 40
    //    }
    Button {
        width: 100
        height: 50
        text: "click"
        onClicked: buttonController.setValue(0, true)
    }

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
