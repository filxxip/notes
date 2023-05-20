import QtQuick 2.15

import QtQuick.Controls 2.15
import ModelStatuses 1.0

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
        anchors.margins: GuiConfig.rightEditViewBar.margins
        spacing: GuiConfig.rightEditViewBar.spacing
        bottomPadding: GuiConfig.rightEditViewBar.padding
        anchors.bottom: outerRectangle.bottom
        ButtonWithImage {
            anchors.right: column.right
            width: GuiConfig.rightEditViewBar.width
            height: GuiConfig.rightEditViewBar.height
            buttonText: GUIConfig.rightEditViewBar.removeAccountText
            imagePath: GUIConfig.imagePaths.removeAccount
            onClickedSignal: mainUserController.userEditController.logout()
            visible: mainController.view.userViewType === ModelStatuses.MainUserViews.EDIT_NORMAL
        }
        ButtonWithImage {
            anchors.right: column.right
            width: GuiConfig.rightEditViewBar.width
            height: GuiConfig.rightEditViewBar.height
            buttonText: GUIConfig.rightEditViewBar.logoutText
            imagePath: GUIConfig.imagePaths.logout
            onClickedSignal: mainUserController.userEditController.logout()
        }
        ButtonWithImage {
            anchors.right: column.right
            width: GuiConfig.rightEditViewBar.width
            height: GuiConfig.rightEditViewBar.height
            buttonText: GUIConfig.rightEditViewBar.settingsText
            imagePath: GUIConfig.imagePaths.settings
            onClickedSignal: console.log("settings")
        }
        ButtonWithImage {
            anchors.right: column.right
            width: GuiConfig.rightEditViewBar.width
            height: GuiConfig.rightEditViewBar.height
            buttonText: GUIConfig.rightEditViewBar.closeAppText
            imagePath: GUIConfig.imagePaths.closeApp
            onClickedSignal: mainController.closeApp()
        }
    }
    Clock {
        anchors.right: outerRectangle.right
        anchors.top: outerRectangle.top
        anchors.margins: GuiConfig.rightEditViewBar.clockMargins
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
