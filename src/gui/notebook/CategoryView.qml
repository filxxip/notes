import QtQuick 2.15
import QtQuick.Controls 2.15

import ModelStatuses 1.0
import ".."
import "../qmlutils"
import "../colorpicker"
import QtQuick.Layouts 1.15

Item {

    ListView {
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 70
        height: 370
        width: 350
        id: listview
        enabled: true
        spacing: 10
        clip: true
        model: categoryController.model
        delegate: NotebookListViewElement {
            onSwiperOpenedChanged: listview.enabled = !swiperOpened
            width: listview.width
            height: 35

            readonly property var color: model.color
        }
        highlight: Rectangle {
            anchors {
                left: parent ? parent.left : undefined
                right: parent ? parent.right : undefined
            }
            color: listview.currentItem ? listview.currentItem.color : GUIConfig.colors.transparent
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
                onReleased: categoryController.view.userViewType
                            = ModelStatuses.CategoryViewTypes.GENERATE_COLOR
            }
        }
    }
    Loader {
        id: loader
        sourceComponent: switch (categoryController.view.userViewType) {
                         case (ModelStatuses.CategoryViewTypes.EDIT_COLOR):
                             return colorEditPicker
                         case (ModelStatuses.CategoryViewTypes.GENERATE_COLOR):
                             return colorPicker
                         case (ModelStatuses.CategoryViewTypes.BUTTON_LISTS):
                             return emptyComponent
                         case (ModelStatuses.CategoryViewTypes.NONE):
                             return emptyComponent
                         }
        anchors.right: parent.right
        width: GUIConfig.colorPicker.elementWidth
        height: 300
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 70
        anchors.rightMargin: 70
    }

    Component {
        id: emptyComponent
        Item {
            anchors.fill: parent
        }
    }

    Component {
        id: colorPicker
        Column {
            spacing: 20
            anchors.fill: parent
            EntryField {
                id: nameWidget
                width: GUIConfig.colorPicker.elementWidth
                height: GUIConfig.colorPicker.elementHeight
                placeholder: "Category name... "
                customcolor: GUIConfig.colors.red
            }
            TripleColorPicker {
                id: pickers
                pickerWidth: GUIConfig.colorPicker.elementWidth
                pickerElementHeight: GUIConfig.colorPicker.elementHeight
            }
            Row {
                anchors.horizontalCenter: parent.horizontalCenter
                id: resultantBar
                spacing: 5
                Rectangle {
                    width: 0.45 * GUIConfig.colorPicker.elementWidth
                    height: 0.8 * GUIConfig.colorPicker.elementHeight
                    color: pickers.combinedColor
                    radius: 10
                }

                CustomButton {
                    contentText: "create"
                    width: 0.45 * GUIConfig.colorPicker.elementWidth
                    height: 0.8 * GUIConfig.colorPicker.elementHeight
                    onReleased: categoryController.addElement(
                                    nameWidget.text, pickers.combinedColor)
                }
            }
        }
    }
    Component {
        id: colorEditPicker
        ColorPicker {
            modelItem: listview.itemAtIndex(categoryController.editedItem)
            pickerWidth: GUIConfig.colorPicker.elementWidth
            pickerElementHeight: GUIConfig.colorPicker.elementHeight
        }
    }
}
