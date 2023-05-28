import QtQuick 2.15
import QtQuick.Controls 2.15

import ModelStatuses 1.0
import "../.."
import "../../qmlutils"
import "../../colorpicker"
import QtQuick.Layouts 1.15

Item {

    ListView {
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.bottomMargin: GUIConfig.category.bottomMargin
        height: GUIConfig.category.height
        width: GUIConfig.category.width
        id: listview
        enabled: true
        spacing: GUIConfig.category.spacing
        clip: true
        model: mainUserController.categoryController.model
        delegate: NotebookListViewElement {
            onSwiperOpenedChanged: listview.enabled = !swiperOpened
            width: listview.width
            height: GUIConfig.category.listViewElementHeight

            readonly property var color: model.color
        }
        highlight: Rectangle {
            anchors {
                left: parent ? parent.left : undefined
                right: parent ? parent.right : undefined
            }

            color: listview.currentItem ? listview.currentItem.color : GUIConfig.colors.transparent
            opacity: GUIConfig.category.hoverBarOpacity
        }

        header: Item {
            visible: listview.model.count === 0
            height: GUIConfig.category.headerHeight
            anchors.right: parent.right
            anchors.left: parent.left
            Label {
                anchors.fill: parent
                Text {
                    anchors.fill: parent
                    text: GUIConfig.category.headerText
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                background: Rectangle {
                    anchors.fill: parent
                    color: GUIConfig.colors.red
                    radius: GUIConfig.category.headerRadius
                }
            }
        }

        footer: Item {
            height: GUIConfig.category.footerHeight
            width: GUIConfig.category.footerWidth
            anchors.horizontalCenter: parent.horizontalCenter
            CustomButton {
                anchors.topMargin: GUIConfig.category.footerMargin
                anchors.fill: parent
                contentText: GUIConfig.category.footerText
                onReleased: mainUserController.categoryController.view.userViewType
                            = ModelStatuses.CategoryViewTypes.GENERATE_COLOR
            }
        }
    }
    Loader {
        id: loader
        sourceComponent: switch (mainUserController.categoryController.view.userViewType) {
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
        height: GUIConfig.category.loaderHeight
        anchors.bottom: parent.bottom
        anchors.bottomMargin: GUIConfig.category.loaderBottomMargin
        anchors.rightMargin: GUIConfig.category.loaderRightMargin
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
            spacing: GUIConfig.category.pickerSpacing
            anchors.fill: parent
            EntryField {
                id: nameWidget
                width: GUIConfig.colorPicker.elementWidth
                height: GUIConfig.colorPicker.elementHeight
                placeholder: GUIConfig.category.pickerNewNamePlaceholder
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
                spacing: GUIConfig.category.pickerRowSpacing
                Rectangle {
                    width: GUIConfig.category.pickerSubmitElementWidthRatio
                           * GUIConfig.colorPicker.elementWidth
                    height: GUIConfig.category.pickerSubmitElementHeightRatio
                            * GUIConfig.colorPicker.elementHeight
                    color: pickers.combinedColor
                    radius: 10
                }

                CustomButton {
                    contentText: GUIConfig.category.pickerCreateText
                    width: GUIConfig.category.pickerSubmitElementWidthRatio
                           * GUIConfig.colorPicker.elementWidth
                    height: GUIConfig.category.pickerSubmitElementHeightRatio
                            * GUIConfig.colorPicker.elementHeight
                    onReleased: mainUserController.categoryController.addElement(
                                    nameWidget.text, pickers.combinedColor)
                }
            }
        }
    }
    Component {
        id: colorEditPicker
        ColorPicker {
            modelItem: listview.itemAtIndex(
                           mainUserController.categoryController.editedItem)
            pickerWidth: GUIConfig.colorPicker.elementWidth
            pickerElementHeight: GUIConfig.colorPicker.elementHeight
        }
    }
}
