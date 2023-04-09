import QtQuick 2.15

Rectangle {
    id : outerRect
    property bool passwordStatus: false
    property string placeholder
    property alias textInput : textInput
//    border.color: myController.myModel.color

    radius: 10

    TextInput {
        clip: true
        id : textInput
        width : parent.width
        height : parent.height
        anchors.fill: parent
        anchors.leftMargin: 0.05*parent.width
        anchors.rightMargin: 0.05*parent.width
        verticalAlignment: TextInput.AlignVCenter
        passwordCharacter: "*"
        echoMode: outerRect.passwordStatus ? TextInput.Password : TextInput.Normal
        Text{
//            text : myController.myModel.name
            text : outerRect.placeholder

            visible: !textInput.text
            verticalAlignment: parent.verticalAlignment
            anchors.fill: parent
        }
    }
    color: textInput.activeFocus?"#5d6d8f":"#3b5387"
}
