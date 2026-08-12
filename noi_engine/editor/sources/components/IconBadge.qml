import QtQuick

import noi_engine_editor

Rectangle {
    id: root

    property string icon: ""
    property real iconSize: 21
    property color badgeColor: Theme.primaryLightB
    property color iconColor: Theme.primaryColor

    width: 40
    height: 40

    radius: 9

    color: root.badgeColor

    MuiIcon {
        anchors.centerIn: parent

        name: root.icon

        font.pixelSize: root.iconSize

        color: root.iconColor
    }
}