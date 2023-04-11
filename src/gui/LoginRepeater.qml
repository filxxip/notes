import QtQuick 2.15

Repeater {
    id: myRepeater
    property int customEntryHeight
    property int customEntryWidth
    delegate: EntryField {
        width: myRepeater.customEntryWidth
        height: myRepeater.customEntryHeight
        placeholder: modelData
        Keys.onTabPressed: {
            var nextItem = myRepeater.itemAt(index + 1)
            if (nextItem) {
                nextItem.textInput.forceActiveFocus()
            }
        }
    }
}
