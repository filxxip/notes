import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle{
    signal customClicked
    signal customReleased
    property string contentText
    color : "transparent"

Text {
    id : textField
    text: parent.contentText

    color : "black"
    anchors.centerIn: parent
    MouseArea {
        id :mouseArea
        anchors.fill: parent
        anchors.margins: -3
        hoverEnabled: true

        onPressed: {
            textField.color = "#ac28ed"
            customClicked()
        }
        onReleased: {
//            textField.color = "#85b9e0"
             textField.color = "black"
            customReleased()
        }
        onEntered: {
            textField.color = "#2a6ea2"
        }
        onExited: {
            textField.color = "black"
        }
    }
}
}
