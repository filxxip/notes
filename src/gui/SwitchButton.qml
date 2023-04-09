import QtQuick 2.15
import QtQuick.Controls 2.15

Row {
    id : rectangleRow
    width : 100
    height: 30
    spacing: -width*0.1
    property string leftButtontext
    property string rightButtonText
    signal leftButtonClicked
    signal rightButtonClicked
    property bool leftIsClicked :false
    Button {
        id: leftButton
        text: rectangleRow.leftButtontext
        width: rectangleRow.width*0.55
        height: rectangleRow.height
        z : rectangleRow.leftIsClicked?1:0
        background: Rectangle {
            radius: 10
            color: rectangleRow.leftIsClicked?"black":"grey"
        }
        onClicked: {
            rectangleRow.leftIsClicked = true
            rectangleRow.leftButtonClicked()

        }
    }
    Button {
        id: rightButton
        text: rectangleRow.rightButtonText
        width: rectangleRow.width*0.55
        height: rectangleRow.height
        z : rectangleRow.leftIsClicked?0:1
        background: Rectangle {
            radius: 10
            color: rectangleRow.leftIsClicked?"grey":"black"
        }
        onClicked: {
            rectangleRow.leftIsClicked = false
            rectangleRow.rightButtonClicked()
    }}
}
