import QtQuick 2.15
import QtQuick.Controls 2.15
import "../.."
import ".."
import "../../qmlutils"

import ModelStatuses 1.0

ListView {
    anchors.fill: parent
    id: listview
    spacing: GUIConfig.category.spacing
    clip: true
    model: mainUserController.notesController.model

    delegate: Row {
        Component.onCompleted: console.log(parent)
        //        anchors.right: parent.right
        layoutDirection: Qt.RightToLeft
        width: listview.width
        height: GUIConfig.category.listViewElementHeight
        //        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 5

        property color basicColor: mainUserController.categoryController.model.get(
                                       model.category).get(
                                       ModelStatuses.CategoryRoles.COLOR)
        CustomButton {
            id: button
            contentText: model.title
            width: listview.width * 0.5
            height: 40
            onReleased: console.log("xxx")
            background: Rectangle {
                radius: GUIConfig.category.headerRadius
                anchors.fill: button
                color: button.down ? basicColor : basicColor.lighter()
            }
        }
        Item {
            width: listview.width * 0.45
            height: 40
            ContentLabel {
                contentText: mainUserController.notesController.getNiceDateFormat(
                                 model.releaseDate)
            }
        }
    }
    header: Item {
        visible: listview.model.count === 0
        Component.onCompleted: console.log(mainUserController.notesController)
        height: GUIConfig.category.headerHeight
        anchors.right: parent.right
        anchors.left: parent.left
        ContentLabel {
            contentText: "There is no note in category"
        }
    }
}
