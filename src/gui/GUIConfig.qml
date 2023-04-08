pragma Singleton
import QtQuick 2.15

Item {
    id : guiConfig

    readonly property alias userView: userView

    readonly property alias fonts: fonts

    QtObject{
        id : userView

        readonly property int defaultEntryWidth : 300
        readonly property int defaultEntryHeight : 70
    }


    QtObject {
        id: fonts

        readonly property string decoratedFont: "TeX Gyre Cursor"
    }
}
