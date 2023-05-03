import QtQuick 2.15
import QtQuick.Layouts 1.15

Rectangle {
    width: GUIConfig.userView.width
    height: GUIConfig.userView.height
    radius: 10
    color: "#376945"
    id: view
    ColumnLayout {
        spacing: GuiConfig.userView.layoutSpacing
        anchors.centerIn: view

        TitleBox {
            title: GuiConfig.userView.registerView.titleContent
            width: GuiConfig.userView.defaultEntryWidth
            height: GuiConfig.userView.titleHeight
        }
        Column {
            spacing: GuiConfig.userView.registerView.columnSpacing
            ListView {
                id: listview
                interactive: false
                spacing: GuiConfig.userView.registerView.listViewSpacing
                width: GUIConfig.userView.defaultEntryWidth
                implicitHeight: contentHeight
                model: logController.registerModel
                delegate: EntryField {
                    id: entry
                    activeFocusOnTab: true
                    width: GUIConfig.userView.defaultEntryWidth
                    height: GuiConfig.userView.registerView.combinedHeight / listview.count
                    customcolor: model.color
                    placeholder: model.placeholder
                    passwordStatus: model.passwordStatus
                    function foo() {
                        model.value = entry.text
                    }

                    Component.onCompleted: logController.confirmEnter.connect(
                                               foo)
                }
            }

            ButtonText {
                contentText: GuiConfig.userView.registerView.accessLoginText
                width: GUIConfig.userView.defaultEntryWidth
                height: GuiConfig.userView.accessButtonHeight
                onCustomReleased: logController.loginActive = true
            }
        }

        Rectangle {
            width: GUIConfig.userView.checkButtonWidth
            height: GUIConfig.userView.checkButtonHeight
            color: GuiConfig.colors.transparent
            Layout.alignment: Qt.AlignHCenter
            CustomButton {
                contentText: GuiConfig.userView.registerView.checkContent
                enabled: logController.activityPossible
                anchors.fill: parent
                onReleased: {
                    logController.confirmEnter()
                    logController.registerObjectInModel()
                }
            }
        }
    }
}
