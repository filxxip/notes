import QtQuick 2.15
import QtQuick.Controls 2.15

import "../"

Rectangle {
    id: outerRect
    property int tumblerWidth: GUIConfig.dateChooser.tumblerWidth
    property int fontSize: GUIConfig.dateChooser.fontSize
    property var controller: logController.calendarController
    property int itemNumber: GUIConfig.dateChooser.itemNumber
    property color backgroundColor: GUIConfig.colors.grey
    signal reset
    onReset: {
        repeater.itemAt(0).currentIndex = 0
        repeater.itemAt(1).currentIndex = 0
        repeater.itemAt(2).currentIndex = 0
    }

    height: GUIConfig.dateChooser.height
    width: tumblerWidth * 3
    color: backgroundColor

    Component {
        id: delegateComponent
        Label {
            text: model.content
            opacity: 1.0 - Math.abs(
                         Tumbler.displacement) / (Tumbler.tumbler.visibleItemCount / 2)
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            //            visible: model.visibility
            font.family: outerRect.fontSize
        }
    }

    Row {
        anchors.fill: parent
        id: row
        Repeater {
            id: repeater
            model: [outerRect.controller.dayModel, outerRect.controller.monthModel, outerRect.controller.yearModel]
            //            model: [20, 40, 60]
            signal dateChanged
            Tumbler {
                visibleItemCount: outerRect.itemNumber
                model: modelData
                width: outerRect.tumblerWidth
                height: outerRect.height
                delegate: delegateComponent
                wrap: false
                id: tum
                //                Component.onCompleted: {
                //                    console.log(model + "moddddddddddddddddddd")
                //                    for (var i = 0; i < tum.model; i++) {
                //                        console.log("ustawiam")
                //                        positionViewAtIndex(i, Tumbler.Center)
                //                    }
                //                }
                onCurrentIndexChanged: {

                    //                    repeater.itemAt(2).positionViewAtIndex(repeater.itemAt(
                    //                                                               2).currentIndex,
                    //                                                           Tumbler.Center)
                    //                    if (index === 0) {
                    //                        console.log("xxx")
                    //                        var ia = repeater.itemAt(2).currentIndex
                    //                        if (currentIndex % 2) {
                    //                            repeater.itemAt(2).model = 30
                    //                        } else {
                    //                            repeater.itemAt(2).model = 60
                    //                        }
                    //                        console.log("wkonuje snapappaa")
                    //                        //                        repeater.itemAt(2).positionViewAtIndex(ia,
                    //                        //                                                               Tumbler.Center)
                    //                        repeater.itemAt(2).currentIndex = ia
                    //                        //                        repeater.itemAt(2).currentIndex = ia
                    //                    }
                    repeater.dateChanged()
                }
            }

            //            function foo(value) {
            //                itemAt(0).currentIndex = value - 1
            //            }
            function onDateChanged() {
                outerRect.controller.currentDateChanged(
                            repeater.itemAt(0).currentIndex + 1,
                            repeater.itemAt(1).currentIndex + 1,
                            repeater.itemAt(2).currentIndex + 1901)
            }

            Component.onCompleted: {
                repeater.dateChanged.connect(onDateChanged)
            }
        }
    }
}
