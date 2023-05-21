import QtQuick 2.15

Item {

    ListView {
        height: 500
        interactive: true
        spacing: 10
        model: categoryController.model
        Component.onCompleted: console.log(categoryController.model.rowCount())
        delegate: NotebookListViewElement {
            modelText: model.title
        }
    }
}
