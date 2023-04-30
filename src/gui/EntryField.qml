import QtQuick 2.15

FocusScope {
    id: root
    property bool passwordStatus: false
    property string placeholder
    property color customcolor
    readonly property alias text: textInput.text
    Rectangle {
        id: outerRect
        anchors.fill: parent
        border.color: myController.myModel.color
        radius: 6
        //    radius: myController.myModel.somevalue.get
        //    radius: myController.myData
        //        Component.onCompleted: {
        //            myController.myModel.intdata.value = 10
        //            console.log(myController.myModel.some)
        //            console.log(myController.myData)
        //            console.log(myController.myModel.some.value)
        //            console.log(myController.myModel.intdata.value)
        //        }
        TextInput {
            clip: true
            id: textInput
            width: parent.width
            height: parent.height
            anchors.fill: parent
            anchors.leftMargin: 0.05 * parent.width
            anchors.rightMargin: 0.05 * parent.width
            verticalAlignment: TextInput.AlignVCenter
            passwordCharacter: "*"
            echoMode: outerRect.passwordStatus ? TextInput.Password : TextInput.Normal
            focus: true
            Text {
                text: root.placeholder
                visible: !textInput.text
                verticalAlignment: parent.verticalAlignment
                anchors.fill: parent
            }
        }
        //        color: root.activeFocus ? "#5d6d8f" : "#3b5387"
        color: root.activeFocus ? root.customcolor.darker() : root.customcolor
    }
}
