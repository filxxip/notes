import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Shapes 1.15
import "../calendar"
import "../qmlutils"
import "../radiobutton"
import "../"
import ModelStatuses 1.0

Item {
    id: mainRectangle
    height: GUIConfig.userEditView.mainRectHeight
    width: GUIConfig.userEditView.mainRectWidth
    Column {
        id: innerRectangle
        anchors.left: mainRectangle.left
        spacing: GUIConfig.userEditView.outerColumnSpacing
        Component {
            id: c1
            Column {
                Component {
                    id: mycomponent
                    DateChooser {
                        fontSize: GUIConfig.userEditView.dateChooserFontSize
                        width: GUIConfig.userEditView.dateChooserWidth
                        height: GUIConfig.userEditView.dateChooserHeight
                        controller: mainUserController.userEditController.calendarController
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
                spacing: GUIConfig.userEditView.listviewSpacing
                UserEditListView {
                    width: mainRectangle.width
                    singleComponentHeight: GUIConfig.userEditView.combinedListViewHeight / count
                    id: listview
                    Component.onCompleted: {
                        itemAtIndex(0).readOnly = true
                        itemAtIndex(1).readOnly = true
                        itemAtIndex(0).clickedSlot = (() => {
                                                          swiperMessage.clickedElement = 0
                                                          swiperMessage.open()
                                                      })
                        itemAtIndex(1).clickedSlot = (() => {
                                                          swiperMessage.clickedElement = 1
                                                          swiperMessage.open()
                                                      })
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
                Row {
                    id: birthdayRow
                    width: mainRectangle.width
                    spacing: GUIConfig.userEditView.birthdayRowSpacing
                    EntryLabel {
                        contentText: GUIConfig.userEditView.birthdayContentText
                        height: birthdayEntry.height
                    }
                    EntryField {
                        width: GUIConfig.userEditView.defaultEntryWidth
                        id: birthdayEntry
                        height: listview.singleComponentHeight
                        clickedSlot: () => swiper.open()
                        placeholder: mainUserController.userEditController.calendarController.niceFormat
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
        }
        Component {
            id: c2
            Column {
                topPadding: GUIConfig.userEditView.guestComponentPadding
                UserEditListView {
                    width: mainRectangle.width
                    singleComponentHeight: GUIConfig.userEditView.combinedGuestListViewHeight
                                           / count
                }
            }
        }

        Loader {
            width: mainRectangle.width
            sourceComponent: switch (mainController.view.userViewType) {
                             case (ModelStatuses.MainUserViews.EDIT_NORMAL):
                                 return c1
                             case (ModelStatuses.MainUserViews.EDIT_GUEST):
                                 return c2
                             }
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter

            spacing: GUIConfig.userEditView.buttonSpacing
            CustomButton {
                width: GUIConfig.userEditView.buttonWidth
                height: GUIConfig.userEditView.buttonHeight
                onReleased: mainUserController.moveDataGloabllyToModel()
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
}
