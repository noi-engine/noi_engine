import QtQuick
import QtQuick.Layouts

import noi_engine_editor

Rectangle {
    id: root

    required property var project

    signal clicked()

    Layout.fillWidth: true
    Layout.preferredHeight: 74

    radius: 11

    color: mouseArea.containsMouse ? Theme.primaryLightC : Theme.bgSecondary
    border.color: mouseArea.containsMouse ? Theme.primaryDark : Theme.borderColor
    border.width: 1

    Behavior on color {
        ColorAnimation { duration: 120 }
    }

    Behavior on border.color {
        ColorAnimation { duration: 120 }
    }

    MouseArea {
        id: mouseArea

        anchors.fill: parent

        hoverEnabled: true

        cursorShape: Qt.PointingHandCursor

        onClicked: root.clicked()
    }

    RowLayout {
        anchors.fill: parent

        anchors.leftMargin: 16
        anchors.rightMargin: 16

        spacing: 14

        IconBadge {
            icon: "folder"
        }

        ColumnLayout {
            Layout.fillWidth: true

            spacing: 3

            Text {
                text: root.project.name

                font.pixelSize: 14
                font.weight: Font.DemiBold

                color: Theme.white
            }

            Text {
                Layout.fillWidth: true

                text: root.project.path

                elide: Text.ElideMiddle

                font.pixelSize: 12

                color: Theme.grey
            }
        }

        Text {
            text: root.project.date

            font.pixelSize: 12

            color: Theme.grey
        }

        MuiIcon {
            name: "chevron_right"

            font.pixelSize: 20

            color: mouseArea.containsMouse ? Theme.primaryColor : Theme.lightGrey
        }
    }
}