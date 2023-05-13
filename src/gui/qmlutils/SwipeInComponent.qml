import QtQuick 2.15
import QtQuick.Controls 2.15
import "../"

Popup {
    id: popup
    required property var customContentItem
    property int leftButtonPadding: GUIConfig.swipeIn.defaultPadding
    property int duration: GUIConfig.swipeIn.defaultDuration
    property color innerColor
    enter: Transition {
        NumberAnimation {
            property: GUIConfig.swipeIn.widthProperty
            from: 0
            to: internal.basicWidth
            duration: popup.duration
        }
    }
    exit: Transition {
        NumberAnimation {
            property: GUIConfig.swipeIn.widthProperty
            from: popup.width
            to: 0
            duration: popup.duration * popup.width / internal.basicWidth
        }
    }
    clip: true
    modal: true
    focus: true
    QtObject {
        id: internal
        property int basicWidth
    }

    Component.onCompleted: internal.basicWidth = width
    contentItem: Rectangle {
        Rectangle {
            anchors.left: mainRect.left
            width: mainRect.radius
            anchors.top: mainRect.top
            anchors.bottom: mainRect.bottom
            color: mainRect.color
        }

        id: mainRect
        radius: GUIConfig.swipeIn.radius
        color: innerColor
        anchors.fill: parent
        Loader {
            anchors.right: button.left
            sourceComponent: popup.customContentItem
            anchors.rightMargin: popup.leftButtonPadding
        }
        Button {
            id: button
            height: parent.height
            width: GUIConfig.swipeIn.buttonWidth
            anchors.right: parent.right
            onReleased: popup.close()
            Image {
                anchors.fill: parent
                source: GUIConfig.swipeIn.buttonImage
                fillMode: Image.PreserveAspectFit
            }
            background: Rectangle {
                anchors.fill: parent
                color: innerColor
                radius: GUIConfig.swipeIn.radius
            }
        }
    }
    background: Rectangle {
        color: GUIConfig.colors.transparent
    }
}
