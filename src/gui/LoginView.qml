import QtQuick 2.15
import QtQuick.Layouts 1.15
import ModelStatuses 1.0

Column {
    spacing: 30
    anchors.centerIn: parent
    ButtonSwitcher {
        model: logController.switcherModel
        tabSelectorEnum: logController.userViewType
        Component.onCompleted: switched.connect(logController.onSwitchedChanged)
    }
    Rectangle {
        width: GUIConfig.userView.width
        height: GUIConfig.userView.height
        radius: 10
        color: "#376945"
        id: view
        property var type: logController.userViewType //order of type enum and equivalent config data should be same
        ColumnLayout {
            spacing: GUIConfig.userView.layoutSpacing
            anchors.centerIn: view
            TitleBox {
                title: GuiConfig.userView.userViewDetails[view.type].titleContent
                width: GUIConfig.userView.defaultEntryWidth
                height: GuiConfig.userView.titleHeight
            }

            Column {
                spacing: GuiConfig.userView.columnSpacing
                ListView {
                    id: listview
                    interactive: false
                    spacing: GuiConfig.userView.userViewDetails[view.type].listViewSpacing
                    width: GUIConfig.userView.defaultEntryWidth
                    implicitHeight: contentHeight
                    model: logController.userModel
                    delegate: EntryField {
                        id: entry
                        width: GUIConfig.userView.defaultEntryWidth
                        height: GuiConfig.userView.userViewDetails[view.type].combinedHeight
                                / listview.count
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
                    height: GuiConfig.userView.accessButtonHeight
                    spacing: GuiConfig.userView.accessButtonSpacing
                    visible: view.type === ModelStatuses.UserViews.LOGIN
                    ButtonText {
                        Layout.fillWidth: true
                        contentText: GuiConfig.userView.loginView.accessRegisterText
                        onCustomReleased: logController.userViewType
                                          = ModelStatuses.UserViews.REGISTER
                        height: parent.height
                    }
                    ButtonText {
                        contentText: GuiConfig.userView.loginView.showPasswordText
                        Layout.fillWidth: true
                        height: parent.height
                        property var element: logController.userModel.get(1)
                        onCustomClicked: {
                            element.update(false,
                                           ModelStatuses.Roles.PASS_STATUS)
                            dialogController.visibility = true
                        }

                        onCustomReleased: element.update(
                                              true,
                                              ModelStatuses.Roles.PASS_STATUS)
                    }
                }

                ButtonText {
                    contentText: GuiConfig.userView.registerView.accessLoginText
                    width: GUIConfig.userView.defaultEntryWidth
                    height: GuiConfig.userView.accessButtonHeight
                    onCustomReleased: logController.userViewType = ModelStatuses.UserViews.LOGIN
                    visible: view.type === ModelStatuses.UserViews.REGISTER
                }
            }

            Rectangle {
                width: GUIConfig.userView.checkButtonWidth
                height: GUIConfig.userView.checkButtonHeight
                color: GuiConfig.colors.transparent
                Layout.alignment: Qt.AlignHCenter
                CustomButton {
                    enabled: logController.activityPossible
                    contentText: GuiConfig.userView.userViewDetails[view.type].checkContent
                    anchors.fill: parent
                }
            }
        }
    }
}
