import QtQuick 2.15
import QtQuick.Controls 2.15

TabBar {
    id: tabbar
    background: Rectangle {
        width: 0
        height: 0
    }
    property int combinedWidth: GUIConfig.switchbutton.width
    property int elementHeight: GUIConfig.switchbutton.height
    required property var model
    required property var tabSelectorEnum
    signal switched(int enumCode)
    currentIndex: tabSelectorEnum
    anchors.horizontalCenter: parent.horizontalCenter

    Repeater {
        id: repeater
        model: tabbar.model
        TabButton {
            text: model.text
            width: tabbar.combinedWidth / repeater.count
            height: tabbar.elementHeight
            background: Rectangle {
                color: tabbar.currentIndex === model.type ? GUIConfig.switchbutton.enableColor : GUIConfig.switchbutton.disableColor
                anchors.fill: parent
                radius: GUIConfig.switchbutton.radius
            }
            onReleased: tabbar.switched(model.type)
        }
    }
}
