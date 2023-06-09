pragma Singleton

import QtQuick 2.15

import ModelStatuses 1.0

Item {
    id: guiConfig

    readonly property alias userView: userView

    readonly property alias dateChooser: dateChooser

    readonly property alias colors: colors

    readonly property alias fonts: fonts

    readonly property alias gradients: gradients

    readonly property alias switchbutton: switchbutton

    readonly property alias dialog: dialog

    readonly property alias window: window

    readonly property alias swipeIn: swipeIn

    readonly property alias rightEditViewBar: rightEditViewBar

    readonly property alias userEditView: userEditView

    readonly property alias imagePaths: imagePaths

    readonly property alias colorPicker: colorPicker

    readonly property alias category: category

    readonly property alias notebookListViewElement: notebookListViewElement

    QtObject {
        id: window
        readonly property int width: 800
        readonly property int height: 640
    }

    QtObject {
        id: category

        readonly property int width: 350
        readonly property int height: 370
        readonly property int bottomMargin: 70
        readonly property int spacing: 10
        readonly property int listViewElementHeight: 35
        readonly property real hoverBarOpacity: 0.2

        readonly property int headerHeight: 40
        readonly property string headerText: "Category list empty"
        readonly property int headerRadius: 10

        readonly property int footerHeight: 40
        readonly property int footerWidth: 200
        readonly property int footerMargin: 10
        readonly property string footerText: "Add new category"

        readonly property int loaderHeight: 300
        readonly property int loaderBottomMargin: 70
        readonly property int loaderRightMargin: 70

        readonly property int pickerSpacing: 20
        readonly property string pickerNewNamePlaceholder: "Category name... "
        readonly property real pickerSubmitElementWidthRatio: 0.45
        readonly property real pickerSubmitElementHeightRatio: 0.8
        readonly property int pickerRowSpacing: 5
        readonly property string pickerCreateText: "create"
    }

    QtObject {
        id: notebookListViewElement

        readonly property int rowSpacing: 5
        readonly property int buttonTopMargin: 2
        readonly property int buttonBottomMargin: 2
        readonly property int buttonLeftMargin: 4
        readonly property int buttonWidth: 220
        readonly property int buttonRadius: 10
        readonly property int editButtonMargins: 5
        readonly property real opacityWhenClicked: 0.7

        readonly property int swipeInWidthDelta: 20
        readonly property int swipeInWidthEntryDelta: 30
        readonly property int swipeInDuration: 200
    }

    QtObject {
        id: userEditView

        readonly property int combinedListViewHeight: 200
        readonly property int combinedGuestListViewHeight: 70
        readonly property int outerColumnSpacing: 25

        readonly property int mainRectHeight: 400
        readonly property int mainRectWidth: 500

        readonly property int guestComponentPadding: 130

        readonly property int listviewSpacing: 8
        readonly property int defaultEntryWidth: 300
        readonly property string disabledProperty: "Changing this property disabled"

        readonly property int messagePadding: 20
        readonly property int messageWidth: 300
        readonly property int swipeInComponentWidth: 320
        readonly property int messageSwipeDuration: 300
        readonly property int messageSwipeX: 0

        readonly property int birthdayRowSpacing: -5
        readonly property string birthdayContentText: "Birthday"

        readonly property string resetContentText: "RESET"
        readonly property string saveContentText: "SAVE"

        readonly property int buttonWidth: 130
        readonly property int buttonHeight: 40
        readonly property int buttonSpacing: 100

        readonly property int dateChooserFontSize: 17
        readonly property int dateChooserWidth: 300
        readonly property int dateChooserHeight: 100
        readonly property int dateChooserItemsNumber: 3
        readonly property int dateSwipeDuration: 500

        readonly property int swipeInDateHeight: 100
        readonly property int dateSwipeX: 0
    }

    QtObject {
        id: rightEditViewBar
        readonly property int margins: 30
        readonly property int spacing: 10
        readonly property int padding: 140
        readonly property int width: 180
        readonly property int height: 50
        readonly property int clockMargins: 40

        readonly property string removeAccountText: "Remove account"
        readonly property string logoutText: "Log out"
        readonly property string settingsText: "Settings"
        readonly property string closeAppText: "Close App"
    }

    QtObject {
        id: imagePaths
        readonly property string removeAccount: "qrc:/resources/removeaccount.png"
        readonly property string logout: "qrc:/resources/logout.png"
        readonly property string settings: "qrc:/resources/settings.png"
        readonly property string closeApp: "qrc:/resources/closeapp.png"
        readonly property string loading: "qrc:/resources/loading.png"
        readonly property string editNote: "qrc:/resources/editnote.png"
        readonly property string trashNote: "qrc:/resources/trashnote.png"
        readonly property string reset: "qrc:/resources/reset.png"
        readonly property string set: "qrc:/resources/set.png"
    }

    QtObject {
        id: dateChooser
        readonly property int basicItemNumber: 9
        readonly property int basicHeight: 400
        readonly property int basicTumblerWidth: 130
        readonly property int basicdFontSize: 20
    }

    QtObject {
        id: dialog
        readonly property int width: 0.5 * window.width
        readonly property int height: 0.38 * window.height
        readonly property var gradient: gradients.dialogBoxGradient
        readonly property int borderSize: 3
        readonly property color borderColor: colors.darkRed
        readonly property int mainRectangleHeight: height * 0.7
        readonly property int bottomHeight: height * 0.2
        readonly property real opacityValue: 0.2
        readonly property int titleHeight: mainRectangleHeight * 0.3
        readonly property int contentHeight: mainRectangleHeight * 0.7
        readonly property int rightColumnWidth: 0.7 * width
        readonly property int leftImageWidth: 0.3 * width
        readonly property int itemMargins: 10
        readonly property int imageMargins: 10
    }

    QtObject {
        id: userView
        readonly property var registerView: QtObject {
            readonly property string passwordCharakter: "*"
            readonly property int combinedHeight: 0.36 * userView.height
            readonly property string titleContent: "Register"
            readonly property string checkContent: "SIGN UP"
            readonly property string accessLoginText: "have account? Log in!"
            readonly property int listViewSpacing: 8
        }
        readonly property var loginView: QtObject {
            readonly property int combinedHeight: 0.15 * userView.height
            readonly property int layoutSpacing: 30
            readonly property string titleContent: "Login"
            readonly property string checkContent: "CONFIRM"
            readonly property string accessRegisterText: "new account"
            readonly property string showPasswordText: "show password"
            readonly property int listViewSpacing: 20
        }
        readonly property var guestView: QtObject {
            readonly property int combinedHeight: 0.1 * userView.height
            readonly property string titleContent: "Guest"
            readonly property string checkContent: "CONFIRM"
            readonly property int listViewSpacing: 20
        }
        readonly property var radioButton: QtObject {
            readonly property int combinedHeight: 20
            readonly property int combinedWidth: 40
            readonly property int textHeight: 15
            readonly property int fontSize: 14
            readonly property int spacing: 170 //przerzucic tego radio button do wyzszego scopa bo zarowno edit view korzysta jak i ten
        }

        readonly property var userViewDetails: [loginView, registerView, guestView]

        readonly property real checkButtonWidth: 0.4 * userView.defaultEntryWidth
        readonly property int checkButtonHeight: 40
        readonly property int defaultEntryWidth: 0.75 * width
        readonly property real marginRatio: 0.05
        readonly property int titleHeight: 0.1 * height
        readonly property real titleRatio: 0.8
        readonly property int height: 500
        readonly property int width: 400
        readonly property int layoutSpacing: 30
        readonly property int columnSpacing: 12
        readonly property int accessButtonHeight: 20
        readonly property int accessButtonSpacing: 20
        readonly property int radiusOfMainRectangle: 10
        readonly property int entryFontSize: 16

        readonly property var dateChooser: QtObject {
            readonly property int spacing: 40
            readonly property int height: 300
            readonly property string buttonText: "SELECT"
            readonly property int itemNumber: 7
            readonly property int tumblerWidth: 120
        }
    }

    QtObject {
        id: colorPicker

        readonly property int elementHeight: 40
        readonly property int spacing: 10
        readonly property int rightAngle: 90
        readonly property int sliderColorTextPositionChanged: 170
        readonly property int sliderWidth: 200
        readonly property int innerElementRadius: 10
        readonly property int innerElementWidth: 2
        readonly property real sliderHeightRatio: 0.6
        readonly property int maxColorValue: 255
        readonly property int elementWidth: 300
        //        readonly property int downBarHeight: 40
        //        readonly property int downBarButtonWidth: 40
        readonly property real opacityOnClicked: 0.5
        //        readonly property int downBarResultColorBarWidth: 140
        //        readonly property int downBarResultColorBarHeight: 27
        readonly property int downBarResultColorBarRadius: 4
    }

    QtObject {
        id: fonts

        readonly property string decoratedFont: "TeX Gyre Cursor"
    }

    QtObject {
        id: colors

        readonly property color transparent: "transparent"
        readonly property color white: "white"
        readonly property color black: "black"
        readonly property color red: "red"
        readonly property color grey: "grey"
        readonly property color purple: "#ac28ed"
        readonly property color darkRed: "#5e0515"
        readonly property color backgroundGreen: "#376945"
        readonly property color nearlyWhite: "#aebbd1"
        readonly property color lightOrange: "#ee6c4d"
        readonly property color backgroundcolor: "#5ed4b1"
    }

    QtObject {
        id: gradients

        readonly property var redGradient: Gradient {
            orientation: Gradient.Horizontal
            GradientStop {
                position: 0
                color: "#000000"
            }

            GradientStop {
                position: 1
                color: "#ff0000"
            }
        }
        readonly property var greenGradient: Gradient {
            orientation: Gradient.Horizontal
            GradientStop {
                position: 0
                color: "#000000"
            }

            GradientStop {
                position: 1
                color: "#00ff00"
            }
        }

        readonly property var blueGradient: Gradient {
            orientation: Gradient.Horizontal
            GradientStop {
                position: 0
                color: "#000000"
            }

            GradientStop {
                position: 1
                color: "#0000ff"
            }
        }
        readonly property var disabledButtonGradient: Gradient {
            GradientStop {
                position: 0
                color: "#1f6091"
            }

            GradientStop {
                position: 1
                color: "#17486d"
            }
        }
        readonly property var labelEntryGradient: Gradient {
            orientation: Qt.Horizontal
            GradientStop {
                position: 0
                color: "#ed8179"
            }

            GradientStop {
                position: 1
                color: "red"
            }
        }
        readonly property var enabledButtonGradient: Gradient {
            GradientStop {
                position: 0
                color: "#85b9e0"
            }

            GradientStop {
                position: 1
                color: "#348acb"
            }
        }

        readonly property var dialogBoxGradient: Gradient {
            GradientStop {
                position: 0.8
                color: "#e85b51"
            }

            GradientStop {
                position: 0
                color: "#f22213"
            }
        }
    }
    QtObject {
        id: swipeIn

        readonly property string widthProperty: "width"
        readonly property int radius: 10
        readonly property int defaultPadding: 0
        readonly property int defaultDuration: 1000
        readonly property int buttonWidth: 20
        readonly property string buttonImage: "qrc:/resources/left-arrow.png" //pozniej osobny qtobject
    }

    QtObject {
        id: switchbutton

        readonly property int width: GUIConfig.userView.width - 20
        readonly property int height: 40
        readonly property int radius: 4
        readonly property color disableColor: colors.grey
        readonly property color enableColor: colors.black
    }
}
