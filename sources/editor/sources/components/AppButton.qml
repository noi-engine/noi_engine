import QtQuick
import QtQuick.Layouts

import noi_engine_editor

Rectangle {
    id: root

    property string text: ""
    property string icon: ""
    property bool primary: false

    signal clicked()

    implicitWidth: contentRow.implicitWidth + 28
    implicitHeight: 40

    radius: 10

    color: {
        if (primary) return mouseArea.pressed ? Theme.primaryDark : Theme.primaryColor
        return mouseArea.containsMouse ? Theme.bgTertiary : Theme.bgSecondary
    }

    border.color: primary ? "transparent" : Theme.borderColor
    border.width: primary ? 0 : 1

    Behavior on color {
        ColorAnimation { duration: 120 }
    }

    RowLayout {
        id: contentRow

        anchors.centerIn: parent

        spacing: 6

        MuiIcon {
            visible: root.icon.length > 0

            name: root.icon

            font.pixelSize: 16

            color: root.primary ? Theme.black : Theme.white
        }

        Text {
            text: root.text

            font.pixelSize: 13
            font.weight: Font.DemiBold

            color: root.primary ? Theme.black : Theme.white
        }
    }

    MouseArea {
        id: mouseArea

        anchors.fill: parent

        hoverEnabled: true

        cursorShape: Qt.PointingHandCursor

        onClicked: root.clicked()
    }
}
