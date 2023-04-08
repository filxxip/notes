import QtQuick 2.15
import QtQuick.Layouts 1.15

ColumnLayout {
    anchors.centerIn: parent
    spacing : 30
    width: GUIConfig.userView.defaultEntryWidth

    TitleBox{

        width: parent.width
        height: 50
    }



    EntryField {
        width: parent.width
        height: GUIConfig.userView.defaultEntryHeight
        placeholder: "Login..."
    }

    Item{
        Layout.fillWidth : true
        height: GUIConfig.userView.defaultEntryHeight + 40
        EntryField {
            id : passwordEntry
            width : parent.width
            height : GUIConfig.userView.defaultEntryHeight
            anchors.top: parent.top
            passwordStatus: true
            placeholder: "Password..."

        }

        RowLayout{
            width: parent.width
            height : 40
            anchors.bottom: parent.bottom
            spacing: 30

            ButtonText{
                Layout.fillWidth: true
                contentText: "new account"
                height: parent.height
            }
            ButtonText{
                contentText: "show password"
                Layout.fillWidth: true
                height: parent.height
                onCustomClicked:{
                    passwordEntry.passwordStatus = false
                }
                onCustomReleased: {
                    passwordEntry.passwordStatus = true
                }
            }
        }
    }

    Rectangle{
        width: parent.width*0.3
        height:40
        color : "transparent"
        Layout.alignment: Qt.AlignHCenter
        CustomButton{
            contentText: "LOGIN"
            anchors.fill: parent
        }
    }

}
