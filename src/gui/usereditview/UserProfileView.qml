import QtQuick 2.15

import QtQuick.Controls 2.15

import ".."

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
        bottomPadding: 200
        anchors.bottom: outerRectangle.bottom
        ButtonWithImage {
            width: 180
            height: 50
            buttonText: "Remove account"
            imagePath: "qrc:/resources/removeaccount.png"
            onClickedSignal: userEditController.remove()
        }
        ButtonWithImage {
            anchors.right: column.right
            width: 120
            height: 50
            buttonText: "Log out"
            imagePath: "qrc:/resources/logout.png"
            onClickedSignal: userEditController.logout()
        }
    }
}
