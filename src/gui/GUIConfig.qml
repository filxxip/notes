pragma Singleton

import QtQuick 2.15

Item {
    id: guiConfig

    readonly property alias userView: userView

    readonly property alias colors: colors

    readonly property alias fonts: fonts

    readonly property alias gradients: gradients

    readonly property alias switchbutton: switchbutton

    QtObject {
        id: userView
        readonly property var registerView: QtObject {
            readonly property string passwordCharakter: "#"
            readonly property int listViewSpacing: 12
            readonly property int columnSpacing: 12
            readonly property int combinedHeight: 200
            readonly property int layoutSpacing: 30
            readonly property string titleContent: "Register"
        }

        readonly property int defaultEntryWidth: 300
        readonly property int defaultEntryHeight: 70
        readonly property real marginRatio: 0.05
        readonly property string passwordCharakter: "#"
        readonly property int loginSpacing: 20
        readonly property int passwordSpacing: 12
        readonly property int titleHeight: 50
        readonly property int combinedLoginHeight: 80
        readonly property int combinedRegisterHeight: 200
    }

    QtObject {
        id: fonts

        readonly property string decoratedFont: "TeX Gyre Cursor"
    }

    QtObject {
        id: colors

        readonly property color transparent: "transparent"
        readonly property color black: "black"
        readonly property color grey: "grey"
        readonly property color purple: "#ac28ed"
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
    }

    QtObject {
        id: switchbutton

        readonly property string leftButtonText: "Log in"
        readonly property string rightButtonText: "Sign up"
        readonly property int width: GUIConfig.userView.defaultEntryWidth - 20
        readonly property int height: 40
        readonly property int radius: 10
        readonly property color enableColor: colors.grey
        readonly property color disableColor: colors.black
    }
}
