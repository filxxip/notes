import QtQuick 2.15

import QtQuick.Controls 2.15

import ".."
import "../calendar"
import "../qmlutils"

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
            model: ListModel {
                ListElement {
                    buttonText: "Remove account"
                    imagePath: "qrc:/resources/removeaccount.png"
                    onClickedSignal: () => mainUserController.userEditController.remove()
                }
                ListElement {
                    buttonText: "Log out"
                    imagePath: "qrc:/resources/logout.png"
                    onClickedSignal: () => mainUserController.userEditController.logout()
                }
                ListElement {
                    buttonText: "Settings"
                    imagePath: "qrc:/resources/settings.png"
                    onClickedSignal: () => console.log("settings")
                }
                ListElement {
                    buttonText: "Close App"
                    imagePath: "qrc:/resources/closeapp.png"
                    onClickedSignal: () => mainController.closeApp()
                }
            }

            delegate: ButtonWithImage {
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

    ButtonSwitcher {
        anchors.left: parent.left
        model: mainUserController.view.switcherModel
        tabSelectorEnum: mainUserController.view.userViewType
        Component.onCompleted: switched.connect(
                                   newstatus => mainUserController.view.userViewType = newstatus)
    }
}
