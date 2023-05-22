import QtQuick 2.15
import ".."
import "../qmlutils"
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: item
    property var controller

    function uploadColor(color) {
        var myColor = Qt.color(color)
        green.setColor(myColor.g * GUIConfig.colorPicker.maxColorValue)
        red.setColor(myColor.r * GUIConfig.colorPicker.maxColorValue)
        blue.setColor(myColor.b * GUIConfig.colorPicker.maxColorValue)
    }

    Component.onCompleted: {
        controller.colorChanged.connect(uploadColor)
        uploadColor(controller.color)
    }
    ColumnLayout {
        Column {
            spacing: 5
            SingleColorPicker {
                id: red
                customColor: Qt.rgba(
                                 sliderValue / GUIConfig.colorPicker.maxColorValue,
                                 0, 0)
                barGradient: GUIConfig.gradients.redGradient
            }

            SingleColorPicker {
                id: green
                customColor: Qt.rgba(
                                 0,
                                 sliderValue / GUIConfig.colorPicker.maxColorValue,
                                 0)
                barGradient: GUIConfig.gradients.greenGradient
            }

            SingleColorPicker {
                id: blue
                customColor: Qt.rgba(
                                 0, 0,
                                 sliderValue / GUIConfig.colorPicker.maxColorValue)
                barGradient: GUIConfig.gradients.blueGradient
            }
        }
        RowLayout {
            id: resultantBar
            height: GUIConfig.colorPicker.downBarHeight
            readonly property var combinedColor: Qt.rgba(
                                                     red.sliderValue
                                                     / GUIConfig.colorPicker.maxColorValue,
                                                     green.sliderValue
                                                     / GUIConfig.colorPicker.maxColorValue,
                                                     blue.sliderValue
                                                     / GUIConfig.colorPicker.maxColorValue)

            Button {
                Layout.preferredWidth: GUIConfig.colorPicker.downBarButtonWidth
                Layout.preferredHeight: GUIConfig.colorPicker.downBarHeight
                background: Rectangle {
                    anchors.fill: parent
                    color: GUIConfig.colors.transparent
                }

                onReleased: controller.colorChanged(resultantBar.combinedColor)

                Image {
                    anchors.fill: parent
                    source: GUIConfig.imagePaths.set
                }
                opacity: down ? GUIConfig.colorPicker.opacityOnClicked : 1
            }
            Rectangle {
                Layout.preferredWidth: GUIConfig.colorPicker.downBarResultColorBarWidth
                Layout.preferredHeight: GUIConfig.colorPicker.downBarResultColorBarHeight
                Layout.alignment: Qt.AlignVCenter
                color: resultantBar.combinedColor
                radius: GUIConfig.colorPicker.downBarResultColorBarRadius
            }
            spacing: 10

            Button {
                opacity: down ? GUIConfig.colorPicker.opacityOnClicked : 1
                Layout.preferredWidth: GUIConfig.colorPicker.downBarButtonWidth
                Layout.preferredHeight: GUIConfig.colorPicker.downBarHeight
                background: Rectangle {
                    anchors.fill: parent
                    color: GUIConfig.colors.transparent
                }
                onReleased: item.uploadColor(controller.color)

                Image {
                    anchors.fill: parent
                    source: GUIConfig.imagePaths.reset
                }
            }
            Layout.alignment: Qt.AlignHCenter
        }
    }
}
