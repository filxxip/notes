import QtQuick 2.15

import QtQuick.Controls 2.15

import ".."
import "../calendar"

Rectangle {
    id: outerRectangle
    color: GUIConfig.colors.transparent
    UserEditView {
        id: userEditView
        anchors.left: outerRectangle.left
        anchors.verticalCenter: outerRectangle.verticalCenter
    }
    Column {
        id: column
        anchors.right: outerRectangle.right
        anchors.margins: 30
        spacing: 10
        bottomPadding: 140
        anchors.bottom: outerRectangle.bottom

        Repeater {
            id: repeater

            QtObject {
                id: object1
                readonly property string buttonText: "Remove account"
                readonly property string imagePath: "qrc:/resources/removeaccount.png"
                readonly property var onClickedSignal: userEditController.remove
            }
            QtObject {
                id: object2
                readonly property string buttonText: "Log out"
                readonly property string imagePath: "qrc:/resources/logout.png"
                readonly property var onClickedSignal: userEditController.logout
            }
            QtObject {
                id: object3
                readonly property string buttonText: "Settings"
                readonly property string imagePath: "qrc:/resources/settings.png"
                readonly property var onClickedSignal: console.log("settings")
            }
            QtObject {
                id: object4
                readonly property string buttonText: "Close App"
                readonly property string imagePath: "qrc:/resources/settings.png"
                readonly property var onClickedSignal: console.log("settings")
            }
            property var myModel: [repeater.object1, repeater.object2, repeater.object3, repeater.object4]
            model: myModel
            ButtonWithImage {
                Component.onCompleted: console.log(model.imagePath)
                anchors.right: column.right
                width: 180
                height: 50
                buttonText: model.buttonText
                imagePath: model.imagePath
                onClickedSignal: model.onClickedSignal()
            }
        }
    }
    Clock {
        anchors.right: outerRectangle.right
        anchors.top: outerRectangle.top
        anchors.margins: 40
        controller: clockController
    }
}
