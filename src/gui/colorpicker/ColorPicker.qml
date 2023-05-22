import QtQuick 2.15
import ".."
import "../qmlutils"
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: item
    property var controller
    property int pickerWidth
    property int pickerElementHeight
    width: pickerWidth
    height: 4 * pickerElementHeight + 15

    Component.onCompleted: console.log(categoryController.colorGeneratePicker)

    ColumnLayout {
        TripleColorPicker {
            id: pickers
            controller: item.controller
            pickerWidth: item.pickerWidth
            pickerElementHeight: item.pickerElementHeight
        }
        RowLayout {
            id: resultantBar
            height: pickerElementHeight
            Button {
                Layout.preferredWidth: pickerElementHeight
                Layout.preferredHeight: pickerElementHeight
                background: Rectangle {
                    anchors.fill: parent
                    color: GUIConfig.colors.transparent
                }

                onReleased: controller.color = pickers.combinedColor

                Image {
                    anchors.fill: parent
                    source: GUIConfig.imagePaths.set
                }
                opacity: down ? GUIConfig.colorPicker.opacityOnClicked : 1
            }
            Rectangle {
                Layout.preferredWidth: 0.45 * pickerWidth
                Layout.preferredHeight: 0.7 * pickerElementHeight
                Layout.alignment: Qt.AlignVCenter
                color: pickers.combinedColor
                radius: GUIConfig.colorPicker.downBarResultColorBarRadius
            }
            spacing: 10

            Button {
                opacity: down ? GUIConfig.colorPicker.opacityOnClicked : 1
                Layout.preferredWidth: pickerElementHeight
                Layout.preferredHeight: pickerElementHeight
                background: Rectangle {
                    anchors.fill: parent
                    color: GUIConfig.colors.transparent
                }
                onReleased: pickers.uploadColor(controller.color)

                Image {
                    anchors.fill: parent
                    source: GUIConfig.imagePaths.reset
                }
            }
            Layout.alignment: Qt.AlignHCenter
        }
    }
}
