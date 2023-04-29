import QtQuick 2.15
import QtQuick.Layouts 1.15

ColumnLayout {
    Component.onCompleted: anchors.centerIn = parent
    spacing: 30
    width: GUIConfig.userView.defaultEntryWidth

    TitleBox {
        title: "Sign up"
        width: GUIConfig.userView.defaultEntryWidth
        height: 50
    }
    Column {
        spacing: 10
        ListView {
            interactive: false
            spacing: 20
            height: 200
            width: GUIConfig.userView.defaultEntryWidth
            model: logController.registerModel
            delegate: EntryField {
                width: ListView.view.width // Set the width to fill the available space
                height: 30
                placeholder: model.placeholder //poszukac tabulator i ten size zeby jakos automatycznie a nie liczbowo, jakos pomyslec z wyslaniem sygnalu  do updatu, moze tak ze index plus content i tam sobie stworze obiekt person(albo nie) i posprawdzam czy email git i haslo
                //jesli nie to wtedy jakis kolorek poprzez wyslanie sygnalu(moze zmienna sympolizujaca aktywny czerwony kolor qproperty) a jesli git to trzeba sie odezwac do managera servera z prosba o dodanie.
                //i wiadomo tez musze zrobic fajny wybor birthday, jakies scrollbary czy cos takiego

                //                Keys.onTabPressed: {
                //                    var nextItem = myRepeater.itemAt(index + 1)
                //                    if (nextItem) {
                //                        nextItem.textInput.forceActiveFocus()
                //                    }
                //                }
            }
        }

        //        LoginRepeater {
        //            model: ["Name...", "Surname...", "Email...", "Password...", "Country...", "Birthday..."]
        //            customEntryHeight: 30
        //            customEntryWidth: GUIConfig.userView.defaultEntryWidth
        //        }
        ButtonText {
            contentText: "have account? Log in!"
            width: GUIConfig.userView.defaultEntryWidth
            height: 20
            onCustomReleased: logController.loginActive = true
        }
    }

    Rectangle {
        width: GUIConfig.userView.defaultEntryWidth * 0.3
        height: 40
        color: "transparent"
        Layout.alignment: Qt.AlignHCenter
        CustomButton {
            contentText: "Register"
            anchors.fill: parent
        }
    }
}
