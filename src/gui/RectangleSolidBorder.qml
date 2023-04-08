import QtQuick 2.12


Item {
    id: rectangleSolidBorder
    anchors.fill: parent

    /** Width of the border */
    property real borderHorizontalWidth: 3
    property real borderVerticalWidth: 3
    /** Color of the border on the top side */
    property string outerColor: "black"

    /** Color of the border on the right side */
    property string innerColor: "black"




    Rectangle{
        id: topBorder
        width: parent.width + borderWidth
        height: borderVerticalWidth
        anchors.bottom: parent.top
        gradient: Gradient{
                      GradientStop { position: 0.0; color: rectangleSolidBorder.outerColor}
                      GradientStop { position: 1.0; color: rectangleSolidBorder.innerColor}
                  }
    }

    Rectangle{
        id: rightBorder
        width: borderHorizontalWidth
        height: parent.height + borderWidth
        gradient: Gradient{
                      GradientStop { position: 0.0; color: rectangleSolidBorder.innerColor}
                      GradientStop { position: 1.0; color: rectangleSolidBorder.outerColor}
                      orientation: Gradient.Horizontal
                  }
        anchors.left: parent.right
    }

    Rectangle{
        id: borderVerticalWidth
        x: parent.x - borderWidth
        width: parent.width + borderWidth
        height: borderWidth
        gradient: Gradient{
                      GradientStop { position: 0.0; color: rectangleSolidBorder.innerColor}
                      GradientStop { position: 1.0; color: rectangleSolidBorder.outerColor}
                  }
        anchors.top: parent.bottom
    }

    Rectangle{
        id: leftBorder
        y: parent.y - borderWidth
        width: borderHorizontalWidth
        height: parent.height + borderWidth
        gradient: Gradient{
                      GradientStop { position: 0.0; color: rectangleSolidBorder.outerColor}
                      GradientStop { position: 0.3; color: rectangleSolidBorder.outerColor}
                      GradientStop { position: 1; color: rectangleSolidBorder.innerColor}
                      orientation: Gradient.Horizontal

                  }
        anchors.right: parent.left
    }
}
