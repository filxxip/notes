import QtQuick 2.15
import QtQuick.Controls 2.15
import "../"
import "../qmlutils"

ListView {
    id: listview
    required property var configurationObject
    required property var entryModel
    required property var valueAssignSignal
    readonly property int singleComponentHeight: configurationObject.combinedHeight / count
    interactive: false
    spacing: configurationObject.listViewSpacing
    width: GUIConfig.userView.defaultEntryWidth
    implicitHeight: contentHeight
    model: entryModel
    delegate: EntryField {
        id: entry
        width: listview.width
        height: singleComponentHeight
        customcolor: model.color
        placeholder: model.placeholder
        passwordStatus: model.passwordStatus
        activeFocusOnTab: true
        function foo() {
            console.log("kurwa")
            model.value = entry.text
        }
        Component.onCompleted: listview.valueAssignSignal.connect(foo)
        Component.onDestruction: {
            listview.valueAssignSignal.disconnect(foo)
            console.log("XDD" + this)
        }
    }
}
