import QtQuick 2.15

import "../qmlutils"

import ".."

Item {
    id: item
    property string imagePath
    property string buttonText
    signal clickedSignal
    Rectangle {
        anchors.fill: parent
        id: rectangle
        radius: 6
        gradient: GUIConfig.gradients.enabledButtonGradient
        opacity: 0.4
    }
    Row {
        id: row
        padding: 5
        anchors.margins: 3
        anchors.fill: rectangle
        anchors.right: rectangle.right
        LayoutMirroring.enabled: true
        spacing: 10
        Image {
            id: img
            height: row.height - 2 * row.anchors.margins
            source: imagePath
            fillMode: Image.PreserveAspectFit
        }
        CustomButton {
            width: item.width - img.width - 20
            height: row.height - 2 * row.anchors.margins
            contentText: buttonText
            onReleased: item.clickedSignal()
        }
    }
}
