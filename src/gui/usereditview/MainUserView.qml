import QtQuick 2.15
import ".."
import "../calendar"
import "../qmlutils"
import "../notebook/category"
import ModelStatuses 1.0

Rectangle {
    color: GUIConfig.colors.transparent
    Loader {
        anchors.topMargin: switcher.height
        anchors.fill: parent
        property var enumType: mainUserController.view.userViewType
        sourceComponent: switch (enumType) {
                         case (ModelStatuses.InnerUserEditViews.EDIT):
                             return profileView
                         case (ModelStatuses.InnerUserEditViews.NOTEBOOK):
                             return categoryView
                         case (ModelStatuses.InnerUserEditViews.NOTEBOOK):
                             return categoryView
                         }
    }

    Component {
        id: profileView
        UserProfileView {
            anchors.centerIn: parent
            anchors.fill: parent
        }
    }

    Component {
        id: categoryView
        CategoryView {
            anchors.centerIn: parent
            anchors.fill: parent
        }
    }

    ButtonSwitcher {
        id: switcher
        anchors.left: parent.left
        model: mainUserController.view.switcherModel
        tabSelectorEnum: mainUserController.view.userViewType
        Component.onCompleted: switched.connect(
                                   newstatus => mainUserController.view.userViewType = newstatus)
    }
}
