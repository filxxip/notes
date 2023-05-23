import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import ModelStatuses 1.0

import "../qmlutils"
import ".."

RowLayout {
    id: row
    spacing: 5
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
        Layout.topMargin: 2
        Layout.bottomMargin: 2
        Layout.leftMargin: 4
        Layout.preferredWidth: 220
        Layout.fillHeight: true
        background: Rectangle {
            radius: 10
            anchors.fill: button
            color: button.down ? basicColor : basicColor.lighter()
        }
    }

    Button {
        onReleased: {
            swiper.open()
            categoryController.view.userViewType = ModelStatuses.CategoryViewTypes.EDIT_COLOR
            categoryController.editedItem = model.index
        }
        Layout.preferredWidth: height
        Layout.margins: 5
        opacity: down ? 0.7 : 1
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
        opacity: down ? 0.7 : 1
        onReleased: categoryController.remove(model.index)

        Image {
            source: GUIConfig.imagePaths.trashNote
            anchors.fill: parent
        }
    }

    SwipeInComponent {

        id: swiper
        closePolicy: Popup.NoAutoClose

        innerColor: basicColor
        width: row.width - 10
        height: row.height
        customContentItem: Component {
            id: sourceComponent
            EntryField {
                id: entryField
                width: swiper.width - 30
                height: swiper.height
                customcolor: basicColor //todo kwestia zbyt dlugiego tytulul
                Component.onCompleted: {
                    setText(model.title)
                    swiper.aboutToHide.connect(() => {
                                                   categoryController.view.userViewType
                                                   = ModelStatuses.CategoryViewTypes.NONE
                                                   categoryController.changeName(
                                                       text)
                                                   categoryController.editedItem = -1
                                               })
                }
            }
        }
        duration: 400
    }
}
