import QtQuick 2.15
import QtQuick.Controls 2.15
import "../"

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
    height: elementHeight
    contentItem: Row {
        anchors.fill: parent
        Repeater {
            id: repeater
            model: tabbar.model
            TabButton {
                id: tab
                enabled: model.enabled
                Text {
                    text: model.text
                    color: tab.enabled ? GUIConfig.colors.white : GUIConfig.colors.lightOrange
                    anchors.centerIn: parent
                }
                width: tabbar.combinedWidth / repeater.count
                height: tabbar.elementHeight
                anchors.top: repeater.top

                background: Rectangle {
                    property color currentBasicColor: tabbar.currentIndex === model.type ? GUIConfig.switchbutton.enableColor : GUIConfig.switchbutton.disableColor
                    color: tabbar.enabled ? currentBasicColor : currentBasicColor.lighter()
                    anchors.fill: parent
                    radius: GUIConfig.switchbutton.radius
                }
                onReleased: tabbar.switched(model.type)
            }
        }
    }
}
