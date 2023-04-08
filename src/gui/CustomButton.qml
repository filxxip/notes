import QtQuick 2.15
import QtQuick.Controls 2.15

Button {
    property string contentText: ""
    contentItem: Text {
        text: contentText
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        }
    background: Rectangle{
        radius: 10
        gradient: Gradient {
                GradientStop { position: 0; color: pressed?"#85b9e0":"#1f6091" }
                GradientStop { position: 1; color: pressed?"#348acb":"#17486d" }
            }
    }

}
