import QtQuick 2.15
import ".."

Column {
    id: column
    function uploadColor(color) {
        var myColor = Qt.color(color)
        green.setColor(myColor.g)
        red.setColor(myColor.r)
        blue.setColor(myColor.b)
    }
    readonly property var combinedColor: Qt.rgba(red.sliderValue,
                                                 green.sliderValue,
                                                 blue.sliderValue)

    spacing: 5
    property var pickerElementHeight
    property var pickerWidth

    SingleColorPicker {
        id: red
        customColor: Qt.rgba(sliderValue, 0, 0)
        barGradient: GUIConfig.gradients.redGradient
        width: column.pickerWidth
        height: column.pickerElementHeight
    }

    SingleColorPicker {
        id: green
        customColor: Qt.rgba(0, sliderValue, 0)
        barGradient: GUIConfig.gradients.greenGradient
        width: column.pickerWidth
        height: column.pickerElementHeight
    }

    SingleColorPicker {
        id: blue
        customColor: Qt.rgba(0, 0, sliderValue)
        barGradient: GUIConfig.gradients.blueGradient
        width: column.pickerWidth
        height: column.pickerElementHeight
    }
}
