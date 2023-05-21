import QtQuick 2.15
import QtQuick.Window
import QtQuick.Controls 2.15
import QtQuick.Shapes 1.15
import QtQuick.Layouts 1.15
import QtQml 2.3
import ModelStatuses 1.0

import "src/gui/notebook"
import "src/gui"
import "src/gui/customdialog"
import "src/gui/userview"
import "src/gui/qmlutils"
import "src/gui/calendar"
import "src/gui/usereditview"

Window {
    id: window
    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop {
                position: 0.0
                color: GUIConfig.colors.backgroundcolor
            }
        }
    }
    MouseArea {
        anchors.fill: parent
        onClicked: forceActiveFocus()
    }
    width: GUIConfig.window.width
    height: GUIConfig.window.height
    visible: true
    CustomDialog {
        visible: dialogController.visibility
    }
    CategoryView {
        anchors.centerIn: parent
        width: parent.width * 0.5
        height: parent.height * 0.5
    }

    //    Loader {
    //        anchors.fill: parent
    //        property var enumType: mainController.view.userViewType
    //        sourceComponent: switch (enumType) {
    //                         case (ModelStatuses.MainUserViews.BACKGROUND):
    //                             return background
    //                         case (ModelStatuses.MainUserViews.LOG):
    //                             return logView
    //                         case (ModelStatuses.MainUserViews.EDIT_GUEST):
    //                             return userEditView
    //                         case (ModelStatuses.MainUserViews.EDIT_NORMAL):
    //                             return userEditView
    //                         }
    //    }

    //    Component {
    //        id: logView
    //        LogView {
    //            anchors.centerIn: parent
    //            anchors.fill: parent
    //        }
    //    }

    //    Component {
    //        id: background
    //        Rectangle {
    //            color: GUIConfig.colors.grey
    //            anchors.centerIn: parent
    //            anchors.fill: parent
    //            Image {
    //                anchors.centerIn: parent
    //                width: 0.15 * parent.width
    //                height: 0.15 * parent.height
    //                fillMode: Image.PreserveAspectFit
    //                source: GUIConfig.imagePaths.loading
    //            }
    //        }
    //    }
    //    Component {
    //        id: userEditView
    //        UserProfileView {
    //            anchors.centerIn: parent
    //            anchors.fill: parent
    //        }
    //    }
}
