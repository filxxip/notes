import QtQuick 2.15
import QtQuick.Layouts 1.15
import ModelStatuses 1.0

ColumnLayout {
    spacing: 40
    anchors.centerIn: parent

    signal clickedNewAccount

    TitleBox {
        title: "Login"
        width: GUIConfig.userView.defaultEntryWidth
        height: GuiConfig.userView.titleHeight
    }

    Column {
        spacing: 12
        ListView {
            id: listview
            interactive: false
            spacing: 20
            width: GUIConfig.userView.defaultEntryWidth
            implicitHeight: contentHeight
            model: logController.loginModel
            delegate: EntryField {
                id: entry
                width: GUIConfig.userView.defaultEntryWidth // Set the width to fill the available space
                height: 80 / listview.count
                customcolor: model.color
                placeholder: model.placeholder
                passwordStatus: model.passwordStatus
                activeFocusOnTab: true
            }
        }

        RowLayout {
            width: GUIConfig.userView.defaultEntryWidth
            height: 40
            spacing: 30

            ButtonText {
                Layout.fillWidth: true
                contentText: "new account"
                onCustomReleased: logController.loginActive = false
                height: parent.height
            }
            ButtonText {
                contentText: "show password"
                Layout.fillWidth: true
                height: parent.height
                property var element: logController.loginModel.get(1)
                onCustomClicked: element.update(false,
                                                ModelStatuses.Roles.PASS_STATUS)

                onCustomReleased: element.update(
                                      true, ModelStatuses.Roles.PASS_STATUS)
            }
        }
    }

    Rectangle {
        width: GUIConfig.userView.defaultEntryWidth * 0.3
        height: 40
        color: "transparent"
        Layout.alignment: Qt.AlignHCenter
        CustomButton {
            contentText: "LOGIN"
            anchors.fill: parent
            onReleased: logController.registerModel.get(0).valuexd = "something"
        }
    }
}
