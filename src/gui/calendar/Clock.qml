import QtQuick 2.15
import QtQuick.Controls 2.15

import ".."

Item {
    id: outerItem
    width: 120
    height: 70
    required property var controller
    Rectangle {
        id: item
        anchors.fill: outerItem
        gradient: GUIConfig.gradients.enabledButtonGradient
        opacity: 0.4
        radius: 10
    }
    Column {
        anchors.fill: item
        topPadding: 5
        anchors.right: parent.right
        Row {
            id: row

            readonly property var controllersData: [outerItem.controller.clock.hour, outerItem.controller.clock.minute, outerItem.controller.clock.second]
            Repeater {
                id: repeater
                model: [24, 60, 60]
                Tumbler {
                    visibleItemCount: 2
                    spacing: 2
                    model: modelData
                    width: 40
                    height: 40
                    delegate: TumblerComponent {
                        font.italic: true
                        font.bold: true
                        text: index > 9 ? index : "0" + index
                        font.pixelSize: 18
                    }

                    currentIndex: row.controllersData[index]
                }
            }
        }

        Text {
            width: 120
            height: 20
            text: outerItem.controller.clock.fullDate
            font.pixelSize: 14
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
            font.italic: true
            rightPadding: 10
        }
    }
}
