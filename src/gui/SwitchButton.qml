import QtQuick 2.15
import QtQuick.Controls 2.15

Row {
    id: rectangleRow
    width: 100
    height: 30
    spacing: -width * 0.1
    property string leftButtontext
    property string rightButtonText
    signal leftClicked
    signal rightClicked
    property bool leftIsClicked
    Button {
        id: leftButton
        text: rectangleRow.leftButtontext
        width: rectangleRow.width * 0.55
        height: rectangleRow.height
        z: rectangleRow.leftIsClicked ? 1 : 0
        background: Rectangle {
            radius: 10

            color: rectangleRow.leftIsClicked ? "black" : "grey"
        }
        onReleased: rectangleRow.leftClicked()
    }
    Button {
        id: rightButton
        text: rectangleRow.rightButtonText
        width: rectangleRow.width * 0.55
        height: rectangleRow.height
        z: rectangleRow.leftIsClicked ? 0 : 1
        background: Rectangle {
            radius: 10
            color: rectangleRow.leftIsClicked ? "grey" : "black"
        }
        onReleased: rectangleRow.rightClicked()
    }
}
