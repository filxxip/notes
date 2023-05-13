import QtQuick 2.15
import QtQuick.Controls 2.15
import "../"

Button {
    property string contentText
    contentItem: Text {
        text: contentText
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
    background: Rectangle {
        radius: 10
        gradient: pressed ? GUIConfig.gradients.enabledButtonGradient : GUIConfig.gradients.disabledButtonGradient
    }
}
