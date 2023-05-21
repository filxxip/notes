import QtQuick 2.15
import QtQuick.Controls 2.15

import "../qmlutils"
import ".."

Row {
    id: row
    height: 40

    property var modelText

    CustomButton {
        id: button
        property color basicColor: model.color
        contentText: modelText
        height: row.height - 2 * row.anchors.margins
        width: 200
        background: Rectangle {
            radius: 10
            color: button.down ? button.basicColor : button.basicColor.lighter()
        }
    }

    Button {
        onReleased: swiper.open()
        width: height
        opacity: down ? 0.7 : 1
        background: Rectangle {
            color: GUIConfig.colors.transparent
            anchors.fill: parent
        }

        height: row.height - 2 * row.anchors.margins
        Image {
            source: GUIConfig.imagePaths.editNote
            anchors.fill: parent
        }
    }
    Button {
        height: row.height - 2 * row.anchors.margins
        width: height
        background: Rectangle {
            color: GUIConfig.colors.transparent
            anchors.fill: parent
        }
        opacity: down ? 0.7 : 1
        onReleased: console.log("aaa")
        Image {
            source: GUIConfig.imagePaths.trashNote
            anchors.fill: parent
        }
    }

    SwipeInComponent {
        id: swiper
        innerColor: button.basicColor
        width: row.width - 10
        height: row.height
        customContentItem: Component {
            id: sourceComponent
            EntryField {
                id: entryField
                width: swiper.width - 30
                height: swiper.height
                customcolor: swiper.innerColor
                Component.onCompleted: {
                    setText(modelText)
                }
                onTextChanged: modelText = text
            }
        }
        duration: 400
    }
}
