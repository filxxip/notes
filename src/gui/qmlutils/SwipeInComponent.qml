import QtQuick 2.15
import QtQuick.Controls 2.15
import "../"

Popup {
    property int startXPosition
    property int startYPosition

    property int endXPosition
    property int endYPosition

    property var innerComponent

    property int duration: 1000

    property int w: 270

    property bool isActive: false

    enter: Transition {
        NumberAnimation {
            property: "x"
            from: 0
            to: 270
            duration: rectangle.duration
        }
    }
    exit: Transition {
        NumberAnimation {
            property: "x"
            from: 270
            to: 0
            duration: rectangle.duration
        }
    }

    //    onIsActiveChanged: datePathAnimation.running = true
    id: rectangle
    x: 100
    y: 100
    width: 100
    height: height
    //    radius: 10
    //    color: GUIConfig.colors.grey
    Component.onCompleted: width += 20
    contentItem: Rectangle {
        color: GUIConfig.colors.grey
        radius: 10

        //        PathAnimation {
        //            id: datePathAnimation
        //            target: rectangle
        //            duration: rectangle.duration
        //            path: Path {
        //                id: myPath
        //                startX: rectangle.x
        //                startY: rectangle.y
        //                PathLine {
        //                    x: isActive ? endXPosition : startXPosition
        //                    y: isActive ? endYPosition : startYPosition
        //                }
        //            }
        //        }
        anchors.fill: parent
        Row {
            anchors.fill: parent

            //            Loader {
            //                sourceComponent: innerComponent
            //            }
            Button {
                height: rectangle.height
                width: 20
                onReleased: rectangle.close()
                //                enabled: !datePathAnimation.running
                Image {
                    anchors.fill: parent
                    source: "qrc:/resources/left-arrow.png"
                    fillMode: Image.PreserveAspectFit
                }
                background: Rectangle {
                    anchors.fill: parent
                    color: GUIConfig.colors.transparent
                }
            }
        }
    }
}
