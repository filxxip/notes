import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    signal customClicked
    signal customReleased
    property string contentText
    color: "transparent"

    Text {
        id: textField
        text: parent.contentText

        color: mouseArea.pressed ? "#ac28ed" : "black"
        anchors.centerIn: parent
        MouseArea {
            id: mouseArea
            anchors.fill: parent
            anchors.margins: -3
            hoverEnabled: true

            onPressed: {
                customClicked()
            }
            onReleased: {
                customReleased()
            }
        }
    }
}
