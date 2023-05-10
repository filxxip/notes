import QtQuick 2.15
import QtQuick.Controls 2.15

import "../"

Rectangle {
    id: outerRect
    property int fontSize: GUIConfig.dateChooser.basicdFontSize
    required property var controller
    property int itemNumber: GUIConfig.dateChooser.basicItemNumber
    property color backgroundColor: GUIConfig.colors.grey

    function setDate(dayIndex, monthIndex, yearIndex) {
        repeater.itemAt(0).currentIndex = dayIndex
        repeater.itemAt(1).currentIndex = monthIndex
        repeater.itemAt(2).currentIndex = yearIndex
    }

    Component.onCompleted: {
        controller.uploadNewDate.connect(setDate)
        controller.assignCurrent()
    }
    Component.onDestruction: {
        controller.uploadNewDate.disconnect(setDate)
    }

    color: backgroundColor

    Row {
        anchors.fill: parent
        id: row
        Repeater {
            id: repeater
            model: [outerRect.controller.dayModel, outerRect.controller.monthModel, outerRect.controller.yearModel]
            signal dateChanged
            Tumbler {
                id: tumbler
                visibleItemCount: outerRect.itemNumber
                model: modelData
                width: outerRect.width / repeater.model.length
                height: outerRect.height
                delegate: TumblerComponent {
                    text: model.content
                    font.pixelSize: outerRect.fontSize
                }

                onCurrentIndexChanged: repeater.dateChanged()
            }

            function onDateChanged() {
                outerRect.controller.currentDateChanged(
                            repeater.itemAt(0).currentIndex,
                            repeater.itemAt(1).currentIndex,
                            repeater.itemAt(2).currentIndex)
            }

            Component.onCompleted: {
                repeater.dateChanged.connect(onDateChanged)
            }
        }
    }
}
