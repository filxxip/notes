import QtQuick 2.15
import QtQuick.Controls 2.15

import ".."

Label {
    readonly property real absdisplacement: Math.abs(Tumbler.displacement)
    opacity: 1.0 - absdisplacement / (Tumbler.tumbler.visibleItemCount / 2)
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
    font.pixelSize: 14
    color: absdisplacement < 0.5 ? GUIConfig.colors.red : GUIConfig.colors.black
}
