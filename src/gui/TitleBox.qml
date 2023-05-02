import QtQuick 2.15

Rectangle {
    color: GUIConfig.colors.transparent
    property string title
    Text {
        id: innerText
        text: qsTr(title)
        font.family: GUIConfig.fonts.decoratedFont
        font.bold: true
        anchors.centerIn: parent
    }
    Component.onCompleted: {

        innerText.font.pointSize = Math.min(
                    width, height) * GUIConfig.userView.titleRatio
    }
}
