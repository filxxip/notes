import QtQuick 2.15
import ".."
import QtQuick.Controls 2.15

Label {
    anchors.fill: parent
    property var contentText
    Text {
        anchors.fill: parent
        text: contentText
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
    background: Rectangle {
        anchors.fill: parent
        color: GUIConfig.colors.red
        radius: GUIConfig.category.headerRadius
    }
}
