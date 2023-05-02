import QtQuick 2.15
import QtQuick.Dialogs
import QtQuick.Controls 2.15
import ModelStatuses 1.0

import "../"

Dialog {
    id: customDialog
    readonly property var currentIndex: dialogController.dialogModel.currentIndex
    readonly property var model: dialogController.dialogModel
    property var currentElement: dialogController.dialogModel.get(
                                     dialogController.dialogModel.currentIndex)
    width: GUIConfig.dialog.width
    height: GUIConfig.dialog.height
    closePolicy: Popup.NoAutoClose
    modal: true
    anchors.centerIn: parent
    header: TitleBox {
        title: currentElement.get(ModelStatuses.DialogRoles.TITLE)
        anchors.fill: parent
        Component.onCompleted: {
            console.log("co jest")
            console.log(currentElement.get(ModelStatuses.DialogRoles.TITLE))
        }
    }

    Component.onCompleted: {
        accepted.connect(dialogController.onAccepted)
        rejected.connect(dialogController.onRejected)
    }
    footer: DialogButtonBox {
        alignment: Qt.AlignHCenter
        standardButtons: dialogController.dialogCode
    }
}
