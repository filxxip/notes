import QtQuick 2.15
import QtQuick.Layouts 1.15
import ModelStatuses 1.0

ColumnLayout {
    spacing: 40
    anchors.centerIn: parent

    signal clickedNewAccount

    TitleBox {
        title: GuiConfig.userView.loginView.titleContent
        width: GUIConfig.userView.defaultEntryWidth
        height: GuiConfig.userView.titleHeight
    }

    Column {
        spacing: GuiConfig.userView.loginView.columnSpacing
        ListView {
            id: listview
            interactive: false
            spacing: GuiConfig.userView.loginView.listViewSpacing
            width: GUIConfig.userView.defaultEntryWidth
            implicitHeight: contentHeight
            model: logController.loginModel
            delegate: EntryField {
                id: entry
                width: GUIConfig.userView.defaultEntryWidth
                height: GuiConfig.userView.loginView.combinedHeight / listview.count
                customcolor: model.color
                placeholder: model.placeholder
                passwordStatus: model.passwordStatus
                activeFocusOnTab: true
            }
        }

        RowLayout {
            width: GUIConfig.userView.defaultEntryWidth
            height: GuiConfig.userView.loginView.accessRegisterButtonHeight
            spacing: GuiConfig.userView.loginView.accessRegisterButtonSpacing

            ButtonText {
                Layout.fillWidth: true
                contentText: GuiConfig.userView.loginView.accessRegisterText
                onCustomReleased: logController.loginActive = false
                height: parent.height
            }
            ButtonText {
                contentText: GuiConfig.userView.loginView.showPasswordText
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
        width: GUIConfig.userView.defaultEntryWidth * GUIConfig.userView.checkButtonRatio
        height: GUIConfig.userView.checkButtonHeight
        color: GuiConfig.colors.transparent
        Layout.alignment: Qt.AlignHCenter
        CustomButton {
            contentText: GuiConfig.userView.loginView.checkContent
            anchors.fill: parent
        }
    }
}
