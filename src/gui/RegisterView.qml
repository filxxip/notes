import QtQuick 2.15
import QtQuick.Layouts 1.15

ColumnLayout {
    Component.onCompleted: anchors.centerIn = parent
    spacing: GuiConfig.userView.registerView.layoutSpacing
    width: GuiConfig.userView.defaultEntryWidth

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
                placeholder: model.placeholder //poszukac tabulator i ten size zeby jakos automatycznie a nie liczbowo, jakos pomyslec z wyslaniem sygnalu  do updatu, moze tak ze index plus content i tam sobie stworze obiekt person(albo nie) i posprawdzam czy email git i haslo
                //jesli nie to wtedy jakis kolorek poprzez wyslanie sygnalu(moze zmienna sympolizujaca aktywny czerwony kolor qproperty) a jesli git to trzeba sie odezwac do managera servera z prosba o dodanie.
                //i wiadomo tez musze zrobic fajny wybor birthday, jakies scrollbary czy cos takiego
                //                Keys.onTabPressed: listview.incrementCurrentIndex()
                function onRegisterConfirmEnter() {
                    model.value = entry.text
                }
                Component.onCompleted: logController.registerConfirmEnter.connect(
                                           onRegisterConfirmEnter)
            }
        }

        ButtonText {
            contentText: GuiConfig.userView.registerView.accessLoginText
            width: GUIConfig.userView.defaultEntryWidth
            height: GuiConfig.userView.registerView.accessLoginButtonHeight
            onCustomReleased: logController.loginActive = true
        }
    }

    Rectangle {
        width: GUIConfig.userView.defaultEntryWidth * GUIConfig.userView.checkButtonRatio
        height: GUIConfig.userView.checkButtonHeight
        color: GuiConfig.colors.transparent
        Layout.alignment: Qt.AlignHCenter
        CustomButton {
            contentText: GuiConfig.userView.registerView.checkContent
            enabled: logController.registeringPossible
            anchors.fill: parent
            onReleased: {
                logController.registerConfirmEnter()
                logController.registerObjectInModel()
            }
        }
    }
}
