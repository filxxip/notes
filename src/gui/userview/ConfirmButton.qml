import QtQuick 2.15
import QtQuick.Controls 2.15
import "../qmlutils"
import "../"

Rectangle {
    width: GUIConfig.userView.checkButtonWidth
    height: GUIConfig.userView.checkButtonHeight
    color: GuiConfig.colors.transparent
    required property var configurationObject

    required property var controller
    anchors.horizontalCenter: parent.horizontalCenter
    CustomButton {
        contentText: configurationObject.checkContent
        anchors.fill: parent
        onClicked: controller.confirm()
    }
}
