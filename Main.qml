import QtQuick 2.15
import QtQuick.Window
import QtQuick.Controls 2.15
import QtQuick.Shapes 1.15
import QtQuick.Layouts 1.15
import QtQml 2.3
import ModelStatuses 1.0
import QtQuick.Dialogs

import "src/gui/colorpicker"

import "src/gui/notebook"
import "src/gui"
import "src/gui/customdialog"
import "src/gui/userview"
import "src/gui/qmlutils"
import "src/gui/calendar"
import "src/gui/usereditview"

Window {
    id: window
    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop {
                position: 0.0
                color: GUIConfig.colors.backgroundcolor
            }
        }
    }
    MouseArea {
        anchors.fill: parent
        onClicked: forceActiveFocus()
    }
    width: GUIConfig.window.width
    height: GUIConfig.window.height
    visible: true
    CustomDialog {
        visible: dialogController.visibility
    }
    CategoryView {
        anchors.centerIn: parent
        anchors.fill: parent
    }
    //    ColorDialog {
    //        id: colorDialog
    //        colorDialog.
    //        title: "Please choose a color"
    //        onAccepted: {
    //            console.log("You chose: " + colorDialog.selectedColor)
    //            Qt.quit()
    //        }
    //        onRejected: {
    //            console.log("Canceled")
    //            Qt.quit()
    //        }
    //        Component.onCompleted: visible = true
    //    }
    //    ColorPicker {
    //        anchors.centerIn: parent
    //        controller: categoryController.colorPicker
    //        //        width: 300
    //    }
    //    Column {

    //        SingleColorPicker {
    //            id: red
    //            width: 200
    //            height: 50
    //            //            customColor: Qt.rgba(sliderValue / 255, 0, 0)
    //            barGradient: GUIConfig.gradients.redGradient
    //        }
    //        SingleColorPicker {
    //            id: red2
    //            width: 200
    //            height: 50
    //            //            customColor: Qt.rgba(sliderValue / 255, 0, 0)
    //            barGradient: GUIConfig.gradients.redGradient
    //        }
    //        //        SingleColorPicker {
    //        //            id: red3
    //        //            //            customColor: Qt.rgba(sliderValue / 255, 0, 0)
    //        //            barGradient: GUIConfig.gradients.redGradient
    //        //        }
    //    }

    //    RowLayout {
    //        id: row
    //        spacing: 10
    //        height: 40
    //        width: 300
    //        readonly property int sliderValue: slider.value
    //        property var customColor: Qt.rgba(sliderValue, 0, 0)
    //        anchors.centerIn: parent

    //        signal setColor(int value)

    //        function onSetColor(value) {
    //            slider.value = value
    //        }

    //        Rectangle {
    //            Layout.fillHeight: true
    //            Layout.preferredWidth: height
    //            radius: 90
    //            color: row.customColor
    //            Text {
    //                anchors.fill: parent
    //                text: row.sliderValue
    //                horizontalAlignment: Text.AlignHCenter
    //                verticalAlignment: Text.AlignVCenter
    //                color: slider.value < 123 ? "white" : "black"
    //            }
    //        }

    //        Slider {
    //            id: slider
    //            Layout.preferredWidth: 200
    //            Layout.preferredHeight: 0.5 * row.height
    //            background: Rectangle {
    //                anchors.fill: parent
    //                gradient: GUIConfig.gradients.redGradient
    //            }

    //            from: 0
    //            value: 0
    //            to: 255
    //            handle: Rectangle {
    //                width: 2
    //                height: slider.height * 1.2
    //                radius: 10
    //                color: slider.pressed ? "gray" : "lightgray"
    //                x: slider.leftPadding + slider.visualPosition * (slider.availableWidth - width)
    //                y: slider.topPadding + slider.availableHeight / 2 - height / 2
    //            }
    //        }
    //    }

    //    Loader {
    //        anchors.fill: parent
    //        property var enumType: mainController.view.userViewType
    //        sourceComponent: switch (enumType) {
    //                         case (ModelStatuses.MainUserViews.BACKGROUND):
    //                             return background
    //                         case (ModelStatuses.MainUserViews.LOG):
    //                             return logView
    //                         case (ModelStatuses.MainUserViews.EDIT_GUEST):
    //                             return userEditView
    //                         case (ModelStatuses.MainUserViews.EDIT_NORMAL):
    //                             return userEditView
    //                         }
    //    }

    //    Component {
    //        id: logView
    //        LogView {
    //            anchors.centerIn: parent
    //            anchors.fill: parent
    //        }
    //    }

    //    Component {
    //        id: background
    //        Rectangle {
    //            color: GUIConfig.colors.grey
    //            anchors.centerIn: parent
    //            anchors.fill: parent
    //            Image {
    //                anchors.centerIn: parent
    //                width: 0.15 * parent.width
    //                height: 0.15 * parent.height
    //                fillMode: Image.PreserveAspectFit
    //                source: GUIConfig.imagePaths.loading
    //            }
    //        }
    //    }
    //    Component {
    //        id: userEditView
    //        UserProfileView {
    //            anchors.centerIn: parent
    //            anchors.fill: parent
    //        }
    //    }
}
