import QtQuick 2.15
import QtQuick.Dialogs
import QtQuick.Controls 2.15
import ModelStatuses 1.0
import "../"

Dialog {
    background: Rectangle {
        gradient: GUIConfig.dialog.gradient
        border.color: GUIConfig.dialog.borderColor
        border.width: GUIConfig.dialog.borderSize
    }

    id: customDialog
    property var currentElement: dialogController.dialogModel.get(
                                     dialogController.dialogModel.currentIndex)
    width: GUIConfig.dialog.width
    height: GUIConfig.dialog.height

    closePolicy: Popup.NoAutoClose
    modal: true
    anchors.centerIn: parent

    contentItem: Rectangle {
        color: GUIConfig.colors.transparent
        anchors.fill: parent
        Row {
            anchors.fill: parent
            Rectangle {
                height: GUIConfig.dialog.mainRectangleHeight
                width: GUIConfig.dialog.leftImageWidth
                color: GUIConfig.colors.transparent
                Image {
                    anchors.fill: parent
                    anchors.margins: GUIConfig.dialog.imageMargins
                    source: currentElement.get(ModelStatuses.DialogRoles.PATH)
                    fillMode: Image.PreserveAspectFit
                }
            }
            Column {
                width: GUIConfig.dialog.rightColumnWidth
                height: GUIConfig.dialog.mainRectangleHeight
                TitleBox {
                    title: currentElement.get(ModelStatuses.DialogRoles.TITLE)
                    width: parent.width
                    height: GUIConfig.dialog.titleHeight
                }
                Item {
                    id: item
                    width: parent.width - GUIConfig.dialog.itemMargins
                    height: GUIConfig.dialog.contentHeight
                    Rectangle {
                        id: textRect
                        opacity: GUIConfig.dialog.opacityValue
                        anchors.fill: item
                    }
                    Text {
                        text: currentElement.get(
                                  ModelStatuses.DialogRoles.CONTENT)
                        width: item.width
                        anchors.centerIn: item
                        font.pixelSize: currentElement.get(
                                            ModelStatuses.DialogRoles.FONT_SIZE)
                        wrapMode: Text.Wrap
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }
            }
        }
    }

    Component.onCompleted: {
        accepted.connect(dialogController.onAccepted)
        rejected.connect(dialogController.onRejected)
    }
    footer: DialogButtonBox {
        background: Rectangle {
            color: GUIConfig.colors.transparent
        }
        height: GUIConfig.dialog.bottomHeight
        width: parent.width
        alignment: Qt.AlignHCenter
        standardButtons: dialogController.dialogCode
    }
}
