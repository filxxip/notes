import QtQuick 2.15
import ".."

Column {
    id: column
    readonly property alias red: red
    readonly property alias green: green
    readonly property alias blue: blue

    property var controller

    function uploadColor(color) {
        var myColor = Qt.color(color)

        //        pickers.green.setColor(myColor.g * GUIConfig.colorPicker.maxColorValue)
        //        pickers.red.setColor(myColor.r * GUIConfig.colorPicker.maxColorValue)
        //        pickers.blue.setColor(myColor.b * GUIConfig.colorPicker.maxColorValue)
        pickers.green.setColor(myColor.g)
        pickers.red.setColor(myColor.r)
        pickers.blue.setColor(myColor.b)
    }

    //    readonly property var combinedColor: Qt.rgba(
    //                                             pickers.red.sliderValue
    //                                             / GUIConfig.colorPicker.maxColorValue,
    //                                             pickers.green.sliderValue
    //                                             / GUIConfig.colorPicker.maxColorValue,
    //                                             pickers.blue.sliderValue
    //                                             / GUIConfig.colorPicker.maxColorValue)
    readonly property var combinedColor: Qt.rgba(pickers.red.sliderValue,
                                                 pickers.green.sliderValue,
                                                 pickers.blue.sliderValue)
    Component.onCompleted: {
        if (controller) {
            column.uploadColor(column.controller.color)
            controller.colorChanged.connect(color => {
                                                console.log(color)
                                                console.log("hahahah")
                                                column.uploadColor(color)
                                            })
        }
    }

    spacing: 5
    property var pickerElementHeight
    property var pickerWidth
    SingleColorPicker {
        id: red
        //        customColor: Qt.rgba(sliderValue / GUIConfig.colorPicker.maxColorValue,
        //                             0, 0)
        customColor: Qt.rgba(sliderValue, 0, 0)
        barGradient: GUIConfig.gradients.redGradient
        width: column.pickerWidth
        height: column.pickerElementHeight
    }

    SingleColorPicker {
        id: green
        //        customColor: Qt.rgba(0,
        //                             sliderValue / GUIConfig.colorPicker.maxColorValue,
        //                             0)
        customColor: Qt.rgba(0, sliderValue, 0)
        barGradient: GUIConfig.gradients.greenGradient
        width: column.pickerWidth
        height: column.pickerElementHeight
    }

    SingleColorPicker {
        id: blue
        customColor: Qt.rgba(0, 0, sliderValue)
        //        customColor: Qt.rgba(0, 0,
        //                             sliderValue / GUIConfig.colorPicker.maxColorValue)
        barGradient: GUIConfig.gradients.blueGradient
        width: column.pickerWidth
        height: column.pickerElementHeight
    }
}
