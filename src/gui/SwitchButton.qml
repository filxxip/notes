//import QtQuick 2.15
//import QtQuick.Controls 2.15

//Row {
//    id: rectangleRow

//    required property QtObject mydata

//    spacing: -mydata.width * 0.1

//    width: mydata.width
//    signal leftClicked
//    signal rightClicked
//    property bool leftIsClicked
//    Button {
//        id: leftButton
//        text: mydata.leftButtonText
//        width: mydata.width * 0.55
//        height: mydata.height
//        z: rectangleRow.leftIsClicked ? 1 : 0
//        background: Rectangle {
//            radius: mydata.radius
//            color: rectangleRow.leftIsClicked ? mydata.disableColor : mydata.enableColor
//        }
//        onReleased: rectangleRow.leftClicked()
//    }
//    Button {
//        id: rightButton
//        text: mydata.rightButtonText
//        width: mydata.width * 0.55
//        height: mydata.height
//        z: rectangleRow.leftIsClicked ? 0 : 1
//        background: Rectangle {
//            radius: mydata.radius
//            color: rectangleRow.leftIsClicked ? mydata.enableColor : mydata.disableColor
//        }
//        onReleased: rectangleRow.rightClicked()
//    }
//}
