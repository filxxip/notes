import QtQuick 2.15
import QtQuick.Controls 2.15
import ".."
import "../qmlutils"
import QtQuick.Layouts 1.15

Item {

    ListView {
        height: 300
        width: 300
        id: listview
        //        interactive: true
        spacing: 10
        //        focus: true
        clip: true
        model: categoryController.model
        Component.onCompleted: console.log(categoryController.model.rowCount())
        delegate: NotebookListViewElement {
            modelText: model.title
            readonly property var color: model.color
        }
        highlight: Rectangle {
            anchors {
                left: parent.left
                right: parent.right
            }
            color: listview.currentItem.color
            opacity: 0.2
        }

        footer: Item {
            height: 40
            width: 200
            anchors.horizontalCenter: parent.horizontalCenter
            CustomButton {
                anchors.topMargin: 10
                anchors.fill: parent
                contentText: "Add new category"
            }
        }
    }
}
