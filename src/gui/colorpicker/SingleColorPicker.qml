import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

import ".."

RowLayout {
    id: row
    spacing: GUIConfig.colorPicker.spacing
    readonly property real sliderValue: slider.value / GUIConfig.colorPicker.maxColorValue
    property var customColor
    property var barGradient

    signal setColor(real value)

    Connections {
        target: row
        function onSetColor(value) {
            slider.value = value * GUIConfig.colorPicker.maxColorValue
        }
    }
    Rectangle {
        id: circle
        Layout.fillHeight: true
        Layout.preferredWidth: row.height
        radius: GUIConfig.colorPicker.rightAngle
        color: row.customColor
        Text {
            anchors.fill: parent
            text: parseInt(slider.value)
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            color: slider.value < GUIConfig.colorPicker.sliderColorTextPositionChanged ? GUIConfig.colors.white : GUIConfig.colors.black
        }
    }

    Slider {
        id: slider
        Layout.fillWidth: true
        Layout.preferredHeight: GUIConfig.colorPicker.sliderHeightRatio * row.height
        background: Rectangle {
            anchors.fill: parent
            gradient: barGradient
        }

        from: 0
        value: 0
        to: GUIConfig.colorPicker.maxColorValue
        handle: Rectangle {
            width: GUIConfig.colorPicker.innerElementWidth
            height: slider.height
            color: slider.pressed ? GUIConfig.colors.grey : GUIConfig.colors.grey.lighter()
            x: slider.leftPadding + slider.visualPosition * (slider.availableWidth - width)
            y: slider.topPadding + slider.availableHeight / 2 - height / 2
        }
    }
}
