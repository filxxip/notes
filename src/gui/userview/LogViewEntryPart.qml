import QtQuick 2.15
import QtQuick.Controls 2.15
import "../"
import "../qmlutils"

ListView {
    id: listview
    required property var configurationObject
    required property var entryModel
    required property var valueAssignSignal
    interactive: false
    spacing: configurationObject.listViewSpacing
    width: GUIConfig.userView.defaultEntryWidth
    implicitHeight: contentHeight
    model: entryModel
    delegate: EntryField {
        id: entry
        width: listview.width
        height: listview.configurationObject.combinedHeight / listview.count
        customcolor: model.color
        placeholder: model.placeholder
        passwordStatus: model.passwordStatus
        activeFocusOnTab: true
        function foo() {
            model.value = entry.text
        }
        Component.onCompleted: listview.valueAssignSignal.connect(foo)
        Component.onDestruction: listview.valueAssignSignal.disconnect(foo)
    }
}
