import QtQuick 2.15
import "../qmlutils"

Rectangle {
    ListView {
        id: listview
        required property var configurationObject
        readonly property var entryModel: userViewController.userViewModel
        signal clearAll
        readonly property int singleComponentHeight: configurationObject.combinedHeight / count

        interactive: false
        spacing: configurationObject.listViewSpacing
        width: GUIConfig.userView.defaultEntryWidth
        implicitHeight: contentHeight
        model: entryModel
        delegate: Row {



            EntryField {
                id: entry
                width: listview.width
                height: singleComponentHeight
                customcolor: model.color
                onTextChanged: model.value = entry.text //?
            }
        }
    }
}
