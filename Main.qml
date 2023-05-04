import QtQuick 2.15
import QtQuick.Window
import QtQuick.Controls 2.15
import QtQuick.Shapes 1.15

import ModelStatuses 1.0

import "src/gui"
import "src/gui/customdialog"
import "src/gui/userview"
import "src/gui/qmlutils"

Window {
    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop {
                position: 0.0
                color: "#5ed4b1"
            }
        }
    }
    MouseArea {
        anchors.fill: parent
        onClicked: forceActiveFocus()
    }
    width: 800
    height: 640
    visible: true
    Dial {

        palette.dark: "red"
        value: 0
        anchors.centerIn: parent
        onValueChanged: {
            canvas.requestPaint()
            console.log(angle)
        }
        from: 0
        id: control
        height: 200
        width: 200
        background: Rectangle {
            Canvas {
                id: canvas
                anchors.fill: parent
                onPaint: {
                    var ctx = getContext("2d")
                    ctx.reset()

                    var centreX = width / 2
                    var centreY = height / 2

                    //                    ctx.beginPath()
                    //                    ctx.fillStyle = "black"
                    //                    ctx.moveTo(centreX, centreY)
                    //                    ctx.arc(centreX, centreY, width / 2,
                    //                            0 + Math.PI * 0.77, Math.PI * control.value * 2
                    //                            * 0.77 + Math.PI * 0.77, false)
                    //                    ctx.lineTo(centreX, centreY)
                    //                    ctx.fill()
                    ctx.beginPath()
                    ctx.fillStyle = "red"
                    ctx.moveTo(centreX, centreY)
                    ctx.arc(centreX, centreY, width / 2,
                            Math.PI * control.value * 2 * 0.77 + Math.PI * 0.77,
                            Math.PI * 2 + Math.PI * 0.77, false)
                    ctx.lineTo(centreX, centreY)
                    ctx.fill()
                }
            }
            x: control.width / 2 - width / 2
            y: control.height / 2 - height / 2
            width: Math.max(64, Math.min(control.width, control.height))
            height: width
            color: "transparent"
            radius: width / 2
            border.color: control.pressed ? "#17a81a" : "#21be2b"
            border.width: 10
            opacity: control.enabled ? 1 : 0.3
        }
        handle: Rectangle {
            id: handleItem
            x: control.background.x + control.background.width / 2 - width / 2
            y: control.background.y + control.background.height / 2 - height / 2
            width: 16
            height: 16
            color: control.pressed ? "#17a81a" : "#21be2b"
            radius: 0
            antialiasing: true
            opacity: control.enabled ? 1 : 0.3
            transform: [
                Translate {
                    y: -Math.min(
                           control.background.width,
                           control.background.height) * 0.5 + handleItem.height / 2
                },
                Rotation {
                    angle: control.angle
                    origin.x: handleItem.width / 2
                    origin.y: handleItem.height / 2
                }
            ]

            ShapePath {
                fillColor: "yellow"
                strokeColor: "blue"
                strokeWidth: 20
                capStyle: ShapePath.RoundCap
                PathAngleArc {
                    centerX: 100
                    centerY: 100
                    radiusX: 100 - 20 / 2
                    radiusY: 100 - 20 / 2
                    startAngle: 135
                    sweepAngle: 180
                }
            }
        }
    }

    //    Dial {
    //        anchors.centerIn: parent
    //        id: control

    //        width: 200
    //        height: 200
    //        from: -20
    //        to: 360
    //        onMoved: console.log(control.position)

    //        background: Rectangle {
    //            x: control.width / 2 - width / 2
    //            y: control.height / 2 - height / 2
    //            width: Math.max(64, Math.min(control.width, control.height))
    //            height: width
    //            color: "transparent"
    //            radius: width / 2
    //            border.color: control.pressed ? "#17a81a" : "#21be2b"
    //            opacity: control.enabled ? 1 : 0.3
    //        }

    //        handle: Rectangle {
    //            id: handleItem
    //            x: control.background.x + control.background.width / 2 - width / 2
    //            y: control.background.y + control.background.height / 2 - height / 2
    //            width: 16
    //            height: 16
    //            color: control.pressed ? "#17a81a" : "#21be2b"
    //            radius: 8
    //            antialiasing: true
    //            opacity: control.enabled ? 1 : 0.3
    //            transform: [
    //                Translate {
    //                    y: -Math.min(
    //                           control.background.width,
    //                           control.background.height) * 0.4 + handleItem.height / 2
    //                },
    //                Rotation {
    //                    angle: control.angle
    //                    origin.x: handleItem.width / 2
    //                    origin.y: handleItem.height / 2
    //                }
    //            ]
    //        }
    //        Dial {
    //            anchors.centerIn: parent
    //            id: control2
    //            width: 140
    //            height: 140
    //            from: -20
    //            to: 360
    //            onMoved: console.log(control.position)

    //            background: Rectangle {
    //                x: control2.width / 2 - width / 2
    //                y: control2.height / 2 - height / 2
    //                width: Math.max(64, Math.min(control2.width, control2.height))
    //                height: width
    //                color: "transparent"
    //                radius: width / 2
    //                border.color: control2.pressed ? "#17a81a" : "#21be2b"
    //                opacity: control2.enabled ? 1 : 0.3
    //            }

    //            handle: Rectangle {
    //                id: handleItem2
    //                x: control2.background.x + control2.background.width / 2 - width / 2
    //                y: control2.background.y + control2.background.height / 2 - height / 2
    //                width: 16
    //                height: 16
    //                color: control2.pressed ? "#17a81a" : "#21be2b"
    //                radius: 8
    //                antialiasing: true
    //                opacity: control2.enabled ? 1 : 0.3
    //                transform: [
    //                    Translate {
    //                        y: -Math.min(
    //                               control2.background.width,
    //                               control2.background.height) * 0.4 + handleItem2.height / 2
    //                    },
    //                    Rotation {
    //                        angle: control2.angle
    //                        origin.x: handleItem2.width / 2
    //                        origin.y: handleItem2.height / 2
    //                    }
    //                ]
    //            }
    //        }
    //    }

    //    LogView {}
}
