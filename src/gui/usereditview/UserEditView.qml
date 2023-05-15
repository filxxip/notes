import QtQuick 2.15
import "../qmlutils"
import "../radiobutton"
import "../"
import QtQuick.Controls 2.15
import QtQuick.Shapes 1.15
import "../calendar"

Item {
    id: mainRectangle
    height: 400
    width: 400
    Column {
        id: innerRectangle
        anchors.left: mainRectangle.left
        spacing: GUIConfig.userEditView.outerColumnSpacing
        Column {
            spacing: GUIConfig.userEditView.listviewSpacing
            ListView {
                id: listview
                readonly property var entryModel: mainUserController.userEditController.model
                readonly property int singleComponentHeight: GUIConfig.userEditView.combinedListViewHeight / count

                interactive: false
                spacing: GUIConfig.userEditView.listviewSpacing
                width: GUIConfig.userEditView.defaultEntryWidth
                implicitHeight: contentHeight
                model: entryModel
                delegate: Row {
                    spacing: GUIConfig.userEditView.birthdayRowSpacing
                    property alias clickedSlot: entry.clickedSlot
                    EntryLabel {
                        contentText: model.placeholder
                        height: entry.height
                    }

                    EntryField {
                        id: entry
                        width: listview.width
                        height: listview.singleComponentHeight
                        customcolor: model.color
                        onTextChanged: {
                            model.value = entry.text
                            console.log(model.value)
                        }

                        function setModelValue() {
                            setText(model.value)
                        }

                        Component.onCompleted: {
                            setModelValue()
                            mainUserController.userEditController.resetData.connect(
                                        setModelValue)
                            mainUserController.userEditController.clear.connect(
                                        entry.clear)
                        }
                        Component.onDestruction: {
                            mainUserController.userEditController.resetData.disconnect(
                                        setModelValue)
                            mainUserController.userEditController.clear.disconnect(
                                        entry.clear)
                        }
                    }
                }
            }
            Component {
                id: innerSwiperMessage
                Text {
                    text: GUIConfig.userEditView.disabledProperty
                    leftPadding: GUIConfig.userEditView.messagePadding
                    font.pixelSize: GUIConfig.userView.entryFontSize
                    height: listview.singleComponentHeight
                    width: GUIConfig.userEditView.messageWidth
                    verticalAlignment: Text.AlignVCenter
                }
            }
            SwipeInComponent {
                property int clickedElement: 0
                readonly property var element: listview.itemAtIndex(
                                                   clickedElement)
                id: swiperMessage
                innerColor: GUIConfig.colors.grey
                width: GUIConfig.userEditView.swipeInComponentWidth
                duration: GUIConfig.userEditView.messageSwipeDuration
                customContentItem: innerSwiperMessage
                x: GUIConfig.userEditView.messageSwipeX
                height: listview.singleComponentHeight
                y: element ? element.y : 0
            }
            Component.onCompleted: {
                listview.itemAtIndex(0).clickedSlot = (() => {
                                                           swiperMessage.clickedElement = 0
                                                           swiperMessage.open()
                                                       })
                listview.itemAtIndex(1).clickedSlot = (() => {
                                                           swiperMessage.clickedElement = 1
                                                           swiperMessage.open()
                                                       })
            }
            Row {
                id: birthdayRow
                spacing: GUIConfig.userEditView.birthdayRowSpacing
                EntryLabel {
                    contentText: GUIConfig.userEditView.birthdayContentText
                    height: birthdayEntry.height
                }
                EntryField {
                    id: birthdayEntry
                    width: listview.width
                    height: listview.singleComponentHeight
                    clickedSlot: () => swiper.open()

                    placeholder: calendarController.niceFormat
                    customcolor: GUIConfig.colors.red
                    readOnly: true
                }
            }

            CustomRadioButton {
                combinedWidth: GUIConfig.userView.radioButton.combinedWidth
                combinedHeight: GUIConfig.userView.radioButton.combinedHeight
                textHeight: GUIConfig.userView.radioButton.textHeight
                controller: mainUserController.userEditController.radioButtonController
                fontSize: GUIConfig.userView.radioButton.fontSize
                spacing: GUIConfig.userView.radioButton.spacing
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: GUIConfig.userEditView.buttonSpacing
            CustomButton {
                width: GUIConfig.userEditView.buttonWidth
                height: GUIConfig.userEditView.buttonHeight
                onReleased: mainUserController.userEditController.moveDataFromPersonToModel()
                contentText: GUIConfig.userEditView.resetContentText
            }
            CustomButton {
                width: GUIConfig.userEditView.buttonWidth
                height: GUIConfig.userEditView.buttonHeight
                onReleased: mainUserController.userEditController.confirm()
                contentText: GUIConfig.userEditView.saveContentText
            }
        }
    }
    Component {
        id: mycomponent
        DateChooser {
            fontSize: GUIConfig.userEditView.dateChooserFontSize
            width: GUIConfig.userEditView.dateChooserWidth
            height: GUIConfig.userEditView.dateChooserHeight
            controller: calendarController
            itemNumber: GUIConfig.userEditView.dateChooserItemsNumber
        }
    }

    SwipeInComponent {
        id: swiper
        innerColor: GUIConfig.colors.grey
        width: GUIConfig.userEditView.swipeInComponentWidth
        height: GUIConfig.userEditView.swipeInDateHeight
        customContentItem: mycomponent
        duration: GUIConfig.userEditView.dateSwipeDuration
        x: GUIConfig.userEditView.dateSwipeX
        y: birthdayRow.y + 0.5 * birthdayRow.height - 0.5 * height
    }
}
