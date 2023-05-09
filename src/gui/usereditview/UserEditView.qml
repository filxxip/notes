import QtQuick 2.15
import "../qmlutils"
import "../radiobutton"
import "../"
import QtQuick.Controls 2.15
import QtQuick.Shapes 1.15
import "../calendar"

//to do
Rectangle {
    Column {
        spacing: listview.spacing + 30
        Column {
            spacing: listview.spacing
            enabled: !dateActive //cos nie dziala
            ListView {
                id: listview
                property var configurationObject: GUIConfig.userView.registerView
                readonly property var entryModel: userEditController.model
                signal clearAll
                readonly property int singleComponentHeight: configurationObject.combinedHeight
                                                             / count

                interactive: false
                spacing: configurationObject.listViewSpacing
                width: GUIConfig.userView.defaultEntryWidth
                implicitHeight: contentHeight
                model: entryModel
                delegate: Row {
                    spacing: -5
                    EntryLabel {
                        contentText: model.placeholder
                        height: entry.height
                    }

                    EntryField {
                        id: entry
                        width: listview.width
                        height: listview.singleComponentHeight
                        customcolor: model.color
                        onTextChanged: model.value = entry.text //?

                        function setModelValue() {
                            setText(model.value)
                        }

                        Component.onCompleted: {
                            setModelValue()
                            userEditController.resetData.connect(setModelValue)
                        }
                        Component.onDestruction: userEditController.resetData.disconnect(
                                                     setModelValue)
                    }
                }
            }
            Row {
                id: birthdayRow
                spacing: -5
                EntryLabel {
                    contentText: "Birthday"
                    height: birthdayEntry.height
                }
                EntryField {
                    id: birthdayEntry
                    width: listview.width
                    height: listview.singleComponentHeight
                    clickedSlot: () => dateActive = true
                    placeholder: userEditController.calendarController.niceFormat
                    customcolor: GUIConfig.colors.red
                    readOnly: true
                }
            }

            CustomRadioButton {
                combinedWidth: GUIConfig.userView.radioButton.combinedWidth
                combinedHeight: GUIConfig.userView.radioButton.combinedHeight
                textHeight: GUIConfig.userView.radioButton.textHeight
                controller: userEditController.radioButtonController
                fontSize: GUIConfig.userView.radioButton.fontSize
                spacing: GUIConfig.userView.radioButton.spacing
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 100
            CustomButton {
                width: 130
                height: 40
                onReleased: userEditController.moveDataFromPersonToModel()
                contentText: "RESET"
            }
            CustomButton {
                width: 130
                height: 40
                onReleased: console.log("2")
                contentText: "SAVE"
            }
        }
    }
    property bool dateActive: false
    onDateActiveChanged: datePathAnimation.running = true
    PathAnimation {
        id: datePathAnimation
        target: dateChooser
        duration: 1000
        path: Path {
            id: myPath
            startX: dateChooser.x
            startY: dateChooser.y
            PathLine {
                x: dateActive ? -10 : -dateChooser.width //i dont know why sometimes really fast
                y: dateChooser.y
            }
        }
    }
    Rectangle {
        id: dateChooser
        x: -width
        y: birthdayRow.y + 0.5 * birthdayRow.height - 0.5 * height
        width: 320
        height: 100
        radius: 10
        color: GUIConfig.colors.grey
        Row {
            anchors.fill: parent
            DateChooser {
                fontSize: 17
                width: 300
                height: 100
                //                Component.onCompleted: userEditController.calendarController.resetGui.connect(
                //                                           //w logview tez chyba active contrller do wyrzucenia
                //                                           reset)
                controller: userEditController.calendarController
                itemNumber: 3
            }
            Button {
                height: 100
                width: 20
                onReleased: dateActive = false
                enabled: !datePathAnimation.running
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
