//import QtQuick 2.15

//FocusScope {
//    id: root
//    property bool passwordStatus: false
//    property string placeholder
//    property color customcolor
//    readonly property alias text: textInput.text

//    Rectangle {
//        id: outerRect
//        anchors.fill: parent
//        border.color: myController.myModel.color
//        radius: 6
//        TextInput {
//            clip: true
//            id: textInput
//            width: parent.width
//            height: parent.height
//            anchors.fill: parent
//            anchors.leftMargin: GUIConfig.userView.marginRatio * parent.width
//            anchors.rightMargin: GUIConfig.userView.marginRatio * parent.width
//            verticalAlignment: TextInput.AlignVCenter
//            passwordCharacter: GUIConfig.userView.registerView.passwordCharakter
//            echoMode: root.passwordStatus ? TextInput.Password : TextInput.Normal
//            focus: true
//            Text {
//                text: root.placeholder
//                visible: !textInput.text
//                verticalAlignment: parent.verticalAlignment
//                anchors.fill: parent
//            }
//        }
//        color: root.activeFocus ? root.customcolor.darker() : root.customcolor
//    }
//}
