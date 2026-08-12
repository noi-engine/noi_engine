import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import noi_engine_editor

CustomPage {
    id: root

    title: "OpenGL Test"

    Rectangle {
        anchors.fill: parent
        color: Theme.bgPrimary
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 40

        spacing: 24

        ColumnLayout {
            Layout.alignment: Qt.AlignHCenter

            spacing: 6

            Label {
                Layout.alignment: Qt.AlignHCenter

                text: "OpenGL Test"

                font.pixelSize: 28
                font.weight: Font.Bold

                color: Theme.white
            }

            Label {
                Layout.alignment: Qt.AlignHCenter

                text: "Basic OpenGL rendering test"

                font.pixelSize: 14

                color: Theme.darkGrey
            }
        }

        Rectangle {
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: Math.min(root.width - 80, 800)
            Layout.preferredHeight: Math.min(root.height - 220, 500)

            radius: 14

            color: "#080B0A"

            border.color: Theme.borderColor
            border.width: 1

            clip: true

            OpenGLView {
                anchors.fill: parent

                anchors.margins: 1
            }
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter

            spacing: 8

            MuiIcon {
                name: "check_circle"

                font.pixelSize: 18

                color: Theme.primaryColor
            }

            Label {
                text: "OpenGL renderer active"

                font.pixelSize: 13

                color: Theme.darkGrey
            }
        }
    }
}
