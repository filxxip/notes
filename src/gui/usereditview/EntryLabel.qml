import QtQuick 2.15
import QtQuick.Controls 2.15
import ".."

Label {
    id: label
    required property string contentText
    width: GUIConfig.userView.defaultEntryWidth / 2

    background: Rectangle {
        anchors.fill: parent
        gradient: GUIConfig.gradients.labelEntryGradient
    }
    verticalAlignment: Label.AlignVCenter

    Text {
        anchors.fill: parent
        text: label.contentText
        anchors.leftMargin: 5
        font.pixelSize: GUIConfig.userView.entryFontSize
        verticalAlignment: parent.verticalAlignment
    }
}
