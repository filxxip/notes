import QtQuick 2.15
import QtQuick.Controls 2.15

import "../"
import "../qmlutils"

Rectangle {
    id: item
    width: combinedWidth + spacing * (controller.model.rowCount() - 1)
    height: combinedHeight + textHeight
    color: GUIConfig.colors.transparent

    required property var controller
    required property int combinedWidth
    required property int combinedHeight
    required property int textHeight

    property int fontSize: 20
    property int spacing: 20
    ButtonGroup {
        id: group
        exclusive: false
    }
    ButtonGroup {
        id: group1
    }
    ButtonGroup {
        id: group2
    }
    ButtonGroup {
        id: group3
    }

    readonly property var groups: [group, group1, group2, group3]

    ListView {
        spacing: item.spacing
        id: listview
        orientation: Qt.Horizontal
        interactive: false
        anchors.fill: item
        model: controller.model

        function onAssign(index, value) {
            listview.itemAtIndex(index).checked = value
        }

        Component.onCompleted: {
            controller.assign.connect(onAssign)
        }
        Component.onDestruction: controller.assign.disconnect(onAssign)

        delegate: RadioDelegate {
            ButtonGroup.group: item.groups[model.group]
            background: Rectangle {
                anchors.fill: parent
                color: GUIConfig.colors.transparent
            }

            onCheckedChanged: model.value = checked //sprawdzic czy dziala
            width: item.combinedWidth / item.controller.model.rowCount()
            height: item.combinedHeight
            id: radiobutton
            text: model.text
            Component.onCompleted: checked = model.value
            indicator: Rectangle {
                id: innerComponent
                anchors.fill: parent
                border.width: 2
                radius: 0.5 * width
                color: (checked
                        || radiobutton.pressed) ? GUIConfig.colors.lightOrange : GUIConfig.colors.nearlyWhite
                border.color: GUIConfig.colors.grey
                Rectangle {
                    width: 0.9 * innerComponent.width
                    height: 0.9 * innerComponent.height
                    radius: 0.5 * width
                    border.width: 0.05 * innerComponent.width
                    border.color: GUIConfig.colors.grey
                    color: GUIConfig.colors.lightOrange
                    anchors.centerIn: parent
                    visible: checked
                }
            }
            contentItem: Text {
                text: radiobutton.text
                opacity: enabled ? 1.0 : 0.3
                color: radiobutton.down ? GUIConfig.colors.lightOrange : GUIConfig.colors.black
                anchors.top: innerComponent.bottom
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: item.fontSize
            }
        }
    }
}
