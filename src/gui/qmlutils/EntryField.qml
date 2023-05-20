import QtQuick 2.15
import "../"

FocusScope {
    id: root
    property bool passwordStatus: false
    property string placeholder
    property color customcolor
    readonly property color secondCustomAnimColor: customcolor.lighter()
    readonly property alias text: textInput.text
    property bool readOnly: false
    property var clickedSlot

    signal setText(string newText)

    Component.onCompleted: setText.connect(newText => textInput.text = newText)
    onActiveFocusChanged: {
        if (myTurnOffAnimation.running || myTurnOnAnimation.running) {
            myTurnOffAnimation.running = !myTurnOffAnimation.running
            myTurnOnAnimation.running = !myTurnOnAnimation.running
        } else {
            (activeFocus ? myTurnOnAnimation : myTurnOffAnimation).start()
        }

        if (focus && clickedSlot) {
            clickedSlot()
        }
    }

    signal clear

    onClear: textInput.text = ""

    ColorAnimation {
        id: myTurnOffAnimation
        target: outerRect
        property: "color"
        from: outerRect.color
        to: customcolor
        duration: 500
    }
    ColorAnimation {
        id: myTurnOnAnimation
        target: outerRect
        property: "color"
        from: outerRect.color
        to: secondCustomAnimColor
        duration: 500
    }
    Rectangle {
        id: outerRect
        anchors.fill: parent
        radius: 6

        TextInput {
            clip: true
            readOnly: root.readOnly
            id: textInput
            width: parent.width
            height: parent.height
            anchors.fill: parent
            anchors.leftMargin: GUIConfig.userView.marginRatio * parent.width
            anchors.rightMargin: GUIConfig.userView.marginRatio * parent.width
            verticalAlignment: TextInput.AlignVCenter
            passwordCharacter: GUIConfig.userView.registerView.passwordCharakter
            echoMode: root.passwordStatus ? TextInput.Password : TextInput.Normal
            font.pixelSize: GUIConfig.userView.entryFontSize

            focus: true
            Text {
                font.pixelSize: GUIConfig.userView.entryFontSize
                text: root.placeholder
                visible: !textInput.text
                verticalAlignment: parent.verticalAlignment
                anchors.fill: parent
            }
        }
        Component.onCompleted: color
                               = root.activeFocus ? root.secondCustomAnimColor : root.customcolor
    }
}
