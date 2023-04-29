import QtQuick 2.15
import QtQuick.Layouts 1.15

ColumnLayout {
    spacing: 40
    anchors.centerIn: parent

    signal clickedNewAccount

    TitleBox {
        title: "Login"
        width: GUIConfig.userView.defaultEntryWidth
        height: 50
    }

    Column {
        Column {
            spacing: 20

            EntryField {
                width: GUIConfig.userView.defaultEntryWidth
                height: 40
                placeholder: "Login..."

                Keys.onTabPressed: {
                    passwordEntry.textInput.forceActiveFocus()
                }
            }
            EntryField {
                id: passwordEntry
                width: GUIConfig.userView.defaultEntryWidth
                height: 40
                passwordStatus: true
                placeholder: "Password..."
            }
        }
        RowLayout {
            width: GUIConfig.userView.defaultEntryWidth
            height: 40
            spacing: 30

            ButtonText {
                Layout.fillWidth: true
                contentText: "new account"
                onCustomReleased: logController.loginActive = false
                height: parent.height
            }
            ButtonText {
                contentText: "show password"
                Layout.fillWidth: true
                height: parent.height
                onCustomClicked: {
                    passwordEntry.passwordStatus = false
                    myController.myModel.name += "el"
                }
                onCustomReleased: {
                    passwordEntry.passwordStatus = true
                }
            }
        }
    }
    Rectangle {
        width: GUIConfig.userView.defaultEntryWidth * 0.3
        height: 40
        color: "transparent"
        Layout.alignment: Qt.AlignHCenter
        CustomButton {
            contentText: "LOGIN"
            anchors.fill: parent
        }
    }
}
