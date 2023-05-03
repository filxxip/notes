import QtQuick 2.15
import QtQuick.Controls 2.15

TabBar {
    id: tabBar
    background: Rectangle {
        width: 0
        height: 0
    }
    required property int combinedWidth
    required property int elementHeight
    required property var model
    signal switched(int enumCode)

    Repeater {
        id: repeater
        model: tabBar.model
        TabButton {
            text: model.text
            width: tabBar.combinedWidth / repeater.count
            height: tabBar.elementHeight
            background: Rectangle {
                color: tabBar.currentIndex == index ? "yellow" : "black"
                anchors.fill: parent
                radius: 3
            }
            onReleased: tabBar.switched(model.type)
        }
    }
}
