import QtQuick 2.15
import QtQuick.Layouts 1.15
import ModelStatuses 1.0

Rectangle {
    width: GUIConfig.userView.width
    height: GUIConfig.userView.height
    radius: 10
    color: "#376945"
    id: view
    property var type: logController.userViewType
    ColumnLayout {
        spacing: GUIConfig.userView.layoutSpacing
        anchors.centerIn: view
        Component.onCompleted: console.log(type)
        TitleBox {
            Component.onCompleted: console.log(
                                       GuiConfig.userView.userViewDetails[type])
            title: GuiConfig.userView.userViewDetails[type].titleContent
            width: GUIConfig.userView.defaultEntryWidth
            height: GuiConfig.userView.titleHeight
        }

        Column {
            spacing: GuiConfig.userView.columnSpacing
            ListView {
                id: listview
                interactive: false
                spacing: GuiConfig.userView.loginView.listViewSpacing
                width: GUIConfig.userView.defaultEntryWidth
                implicitHeight: contentHeight
                model: logController.userModel
                delegate: EntryField {
                    id: entry
                    width: GUIConfig.userView.defaultEntryWidth
                    height: GuiConfig.userView.userViewDetails[type].combinedHeight / listview.count
                    customcolor: model.color
                    placeholder: model.placeholder
                    passwordStatus: model.passwordStatus
                    activeFocusOnTab: true
                    function foo() {
                        model.value = entry.text
                    }

                    Component.onCompleted: logController.confirmEnter.connect(
                                               foo) //torepair
                }
            }

            RowLayout {
                width: GUIConfig.userView.defaultEntryWidth
                height: GuiConfig.userView.accessButtonHeight
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
                    property var element: logController.userModel.get(1)
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
