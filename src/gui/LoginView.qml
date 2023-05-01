import QtQuick 2.15
import QtQuick.Layouts 1.15
import Statuses 1.0

ColumnLayout {
    spacing: 40
    anchors.centerIn: parent

    signal clickedNewAccount

    TitleBox {
        title: "Login"
        width: GUIConfig.userView.defaultEntryWidth
        height: 50
    }
    ListModel {}

    Column {
        spacing: 12
        ListModel {
            id: fruitModel

            ListElement {
                name: "Apple"
                cost: 2.45
            }
            ListElement {
                name: "Orange"
                cost: 3.25
            }
            ListElement {
                name: "Banana"
                cost: 1.95
            }
        }
        Rectangle {
            width: 200
            height: 200

            ListModel {}

            Component {
                id: fruitDelegate
                Row {
                    spacing: 10
                    Text {
                        text: name
                    }
                    Text {
                        text: '$' + cost
                    }
                }
            }

            ListView {
                anchors.fill: parent
                model: fruitModel
                delegate: fruitDelegate
            }

            Component.onCompleted: console.log(fruitModel.get(1))
        }
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
                Keys.onTabPressed: listview.incrementCurrentIndex()
                Component.onCompleted: {
                    console.log(logController.registerModel.get(0).value)
                    console.log(logController.registerModel.get(0)["value"])
                    console.log(logController.registerModel.get(0)[value])
                    //                    logController.registerModel.meth()
                    console.log(model + "xxx")
                }

                //                function onRegisterConfirmEnter() {
                //                    model.value = entry.text
                //                }
                //                Component.onCompleted: logController.registerConfirmEnter.connect(
                //                                           onRegisterConfirmEnter)
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
                onCustomClicked: {
                    console.log(logController.loginModel.update)
                    logController.loginModel.update(0, "Helll",
                                                    Statuses.Roles.PLACEHOLER)
                    //                    console.log(logController.loginModel)
                    //                    logController.loginModel.items.get(1).passwordStatus = false
                    //                    listview.model.get(1).passwordStatus = false
                    //                    logController.loginModel[1].passwordStatus = false
                    //                    myController.myModel.name += "el"
                }
                onCustomReleased: {

                    //                    logController.loginModel.at(1).passwordStatus = true
                }
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
