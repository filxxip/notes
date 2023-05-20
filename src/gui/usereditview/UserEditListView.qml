import QtQuick 2.15
import "../qmlutils"
import ".."
import "../radiobutton"

ListView {
    id: listview
    property int singleComponentHeight
    interactive: false
    spacing: GUIConfig.userEditView.listviewSpacing
    implicitHeight: contentHeight
    model: mainUserController.userEditController.model

    delegate: Row {
        width: listview.width
        spacing: GUIConfig.userEditView.birthdayRowSpacing
        property alias clickedSlot: entry.clickedSlot
        property alias readOnly: entry.readOnly
        EntryLabel {
            contentText: model.placeholder
            height: entry.height
        }

        EntryField {
            id: entry
            width: GUIConfig.userEditView.defaultEntryWidth
            height: listview.singleComponentHeight
            customcolor: model.color

            onTextChanged: model.value = entry.text

            signal setModelValue
            onSetModelValue: setText(model.value)

            Component.onCompleted: {
                setModelValue()
                mainUserController.userEditController.resetData.connect(
                            setModelValue)
                mainUserController.userEditController.clear.connect(entry.clear)
            }
        }
    }
}
