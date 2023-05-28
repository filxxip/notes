import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import ModelStatuses 1.0

import "../../qmlutils"
import "../.."

RowLayout {
    id: row
    spacing: GUIConfig.notebookListViewElement.rowSpacing
    readonly property ListView __lv: ListView.view
    readonly property var swiperOpened: swiper.opened
    readonly property color basicColor: model.color

    HoverHandler {
        onHoveredChanged: {
            if (hovered) {
                __lv.currentIndex = model.index
            }
        }
    }

    CustomButton {
        id: button
        contentText: model.title
        Layout.topMargin: GUIConfig.notebookListViewElement.buttonTopMargin
        Layout.bottomMargin: GUIConfig.notebookListViewElement.buttonBottomMargin
        Layout.leftMargin: GUIConfig.notebookListViewElement.buttonLeftMargin
        Layout.preferredWidth: GUIConfig.notebookListViewElement.buttonWidth
        Layout.fillHeight: true
        background: Rectangle {
            radius: GUIConfig.notebookListViewElement.buttonRadius
            anchors.fill: button
            color: button.down ? basicColor : basicColor.lighter()
        }
    }

    Button {
        onReleased: {
            swiper.open()
            mainUserController.categoryController.view.userViewType
                    = ModelStatuses.CategoryViewTypes.EDIT_COLOR
            mainUserController.categoryController.editedItem = model.index
        }
        Layout.preferredWidth: height
        Layout.margins: GUIConfig.notebookListViewElement.editButtonMargins
        opacity: down ? GUIConfig.notebookListViewElement.opacityWhenClicked : 1
        background: Rectangle {
            color: GUIConfig.colors.transparent
            anchors.fill: parent
        }

        Layout.fillHeight: true
        Image {
            source: GUIConfig.imagePaths.editNote
            anchors.fill: parent
        }
    }
    Button {
        Layout.fillHeight: true
        Layout.preferredWidth: height

        background: Rectangle {
            color: GUIConfig.colors.transparent
            anchors.fill: parent
        }
        opacity: down ? GUIConfig.notebookListViewElement.opacityWhenClicked : 1
        onReleased: mainUserController.categoryController.remove(model.index)

        Image {
            source: GUIConfig.imagePaths.trashNote
            anchors.fill: parent
        }
    }

    SwipeInComponent {

        id: swiper
        closePolicy: Popup.NoAutoClose

        innerColor: basicColor
        width: row.width - GUIConfig.notebookListViewElement.swipeInWidthDelta
        height: row.height
        customContentItem: Component {
            id: sourceComponent
            EntryField {
                id: entryField
                width: swiper.width - GUIConfig.notebookListViewElement.swipeInWidthEntryDelta
                height: swiper.height
                customcolor: basicColor //todo kwestia zbyt dlugiego tytulul
                Component.onCompleted: {
                    setText(model.title)
                    swiper.aboutToHide.connect(() => {
                                                   mainUserController.categoryController.view.userViewType = ModelStatuses.CategoryViewTypes.NONE
                                                   mainUserController.categoryController.changeName(
                                                       text)
                                                   mainUserController.categoryController.editedItem
                                                   = -1
                                               })
                }
            }
        }
        duration: GUIConfig.notebookListViewElement.swipeInDuration
    }
}
