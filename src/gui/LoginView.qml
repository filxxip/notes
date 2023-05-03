import QtQuick 2.15
import QtQuick.Layouts 1.15
import ModelStatuses 1.0

Rectangle {
    width: GUIConfig.userView.width
    height: GUIConfig.userView.height
    radius: 10
    color: "#376945"
    id: view
    ColumnLayout {
        spacing: GUIConfig.userView.layoutSpacing
        anchors.centerIn: view
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
                    function foo() {
                        model.value = entry.text
                    }

                    Component.onCompleted: logController.confirmEnter.connect(
                                               foo)
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
                    onCustomClicked: {
                        element.update(false, ModelStatuses.Roles.PASS_STATUS)
                        dialogController.visibility = true
                    }

                    onCustomReleased: element.update(
                                          true, ModelStatuses.Roles.PASS_STATUS)
                }
            }
        }

        Rectangle {
            width: GUIConfig.userView.checkButtonWidth
            height: GUIConfig.userView.checkButtonHeight
            color: GuiConfig.colors.transparent
            Layout.alignment: Qt.AlignHCenter
            CustomButton {
                enabled: logController.activityPossible
                contentText: GuiConfig.userView.loginView.checkContent
                anchors.fill: parent
            }
        }
    }
}
