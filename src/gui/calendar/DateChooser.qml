import QtQuick 2.15
import QtQuick.Controls 2.15

import "../"

Rectangle {
    id: outerRect
    property int tumblerWidth: GUIConfig.dateChooser.basicTumblerWidth
    property int fontSize: GUIConfig.dateChooser.basicdFontSize
    required property var controller
    property int itemNumber: GUIConfig.dateChooser.basicItemNumber
    property color backgroundColor: GUIConfig.colors.grey
    signal reset
    onReset: {
        repeater.itemAt(0).currentIndex = 0
        repeater.itemAt(1).currentIndex = 0
        repeater.itemAt(2).currentIndex = 0
    }

    height: GUIConfig.dateChooser.basicHeight
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
            font.pixelSize: outerRect.fontSize
        }
    }

    Row {
        anchors.fill: parent
        id: row
        Repeater {
            id: repeater
            model: [outerRect.controller.dayModel, outerRect.controller.monthModel, outerRect.controller.yearModel]
            signal dateChanged
            Tumbler {
                visibleItemCount: outerRect.itemNumber
                model: modelData
                width: outerRect.tumblerWidth
                height: outerRect.height
                delegate: delegateComponent
                wrap: false
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
