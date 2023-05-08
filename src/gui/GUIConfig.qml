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

    QtObject {
        id: window
        readonly property int width: 800
        readonly property int height: 640
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
            readonly property int combinedHeight: 0.4 * userView.height
            readonly property string titleContent: "Register"
            readonly property string checkContent: "SIGN UP"
            readonly property string accessLoginText: "have account? Log in!"
            readonly property int listViewSpacing: 10
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

        readonly property var userViewDetails: [registerView, loginView, guestView]

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

        readonly property var dateChooser: QtObject {
            readonly property int spacing: 40
            readonly property int height: 300
            readonly property string buttonText: "SELECT"
            readonly property int itemNumber: 7
            readonly property int tumblerWidth: 120
        }
    }

    QtObject {
        id: fonts

        readonly property string decoratedFont: "TeX Gyre Cursor"
    }

    QtObject {
        id: colors

        readonly property color transparent: "transparent"
        readonly property color black: "black"
        readonly property color red: "red"
        readonly property color grey: "grey"
        readonly property color purple: "#ac28ed"
        readonly property color darkRed: "#5e0515"
        readonly property color backgroundGreen: "#376945"
        readonly property color nearlyWhite: "#aebbd1"
        readonly property color lightOrange: "#ee6c4d"
    }

    QtObject {
        id: gradients

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
        id: switchbutton

        readonly property int width: GUIConfig.userView.width - 20
        readonly property int height: 40
        readonly property int radius: 4
        readonly property color disableColor: colors.grey
        readonly property color enableColor: colors.black
    }
}
