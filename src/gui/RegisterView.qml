import QtQuick 2.15
import QtQuick.Layouts 1.15

ColumnLayout {
    Component.onCompleted: anchors.centerIn = parent
    spacing : 30
    width: GUIConfig.userView.defaultEntryWidth

    TitleBox{
        title: "Sign up"
        width: GUIConfig.userView.defaultEntryWidth
        height: 50
    }
    Column{
       spacing : 10
        LoginRepeater{
            model : ["Name...", "Surname...", "Email...", "Password...", "Age...", "Country...", "Birthday..."]
            customEntryHeight: 30
            customEntryWidth: GUIConfig.userView.defaultEntryWidth
        }

        ButtonText{
            contentText: "have account? Log in!"
            width : GUIConfig.userView.defaultEntryWidth
            height: 20
            onCustomClicked:{
                console.log("show login view")
            }
        }
    }

    Rectangle{
        width: GUIConfig.userView.defaultEntryWidth*0.3
        height:40
        color : "transparent"
        Layout.alignment: Qt.AlignHCenter
        CustomButton{
            contentText: "Register"
            anchors.fill: parent
        }
    }

}
