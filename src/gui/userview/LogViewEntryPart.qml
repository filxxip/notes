import QtQuick 2.15
import QtQuick.Controls 2.15
import "../"
import "../qmlutils"

ListView {
    id: listview
    property var configurationObject

    //controller of type entryController
    required property var controller

    property var entryModel: controller.model
    Component.onCompleted: controller.clear.connect(clearAll)

    signal clearAll
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
        onTextChanged: model.value = entry.text
        Component.onCompleted: clearAll.connect(entry.clear)
    }
}
