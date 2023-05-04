import QtQuick 2.15
import "../"

Rectangle {
    color: GUIConfig.colors.transparent
    property string title
    property int fontSize
    Text {
        id: innerText
        text: title
        font.family: GUIConfig.fonts.decoratedFont
        font.bold: true
        anchors.centerIn: parent
    }
    Component.onCompleted: fontSize ? fontSize : innerText.font.pointSize = Math.min(
                                          width / innerText.text.length,
                                          height) * GUIConfig.userView.titleRatio
}
