import QtQuick 2.15
import QtQuick.Controls 2.15

Button {
    width: 50
    height: 50
    anchors {
        bottom: parent.bottom
        right: parent.right
    }

    Image {
        id: icon
        source: "src/gui/exit_button.png"
    }
}
