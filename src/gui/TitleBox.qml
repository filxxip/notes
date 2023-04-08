import QtQuick 2.15

Rectangle {
    color: "transparent"
    Text {
        id : innerText
        text: qsTr("Login")
        font.family: GUIConfig.fonts.decoratedFont
        font.bold: true
        anchors.centerIn: parent
    }
    Component.onCompleted: {
        innerText.font.pointSize =  Math.min(width, height) * 0.8
    }


}
