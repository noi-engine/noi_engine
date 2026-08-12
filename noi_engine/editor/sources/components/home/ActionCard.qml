import QtQuick
import QtQuick.Layouts

import noi_engine_editor

Rectangle {
    id: root

    property string icon: ""
    property string title: ""
    property string description: ""
    property string actionText: ""
    property bool primary: false

    signal clicked()

    Layout.fillWidth: true
    Layout.minimumWidth: 280
    Layout.preferredHeight: 155

    radius: 14

    color: root.primary ? Theme.primaryColor : Theme.bgSecondary

    border.color: root.primary ? "transparent" : Theme.borderColor
    border.width: root.primary ? 0 : 1

    MouseArea {
        anchors.fill: parent

        cursorShape: Qt.PointingHandCursor

        onClicked: root.clicked()
    }

    ColumnLayout {
        anchors.fill: parent

        anchors.margins: 24

        spacing: 8

        RowLayout {
            spacing: 11

            MuiIcon {
                name: root.icon

                font.pixelSize: 30

                color: root.primary ? Theme.black : Theme.primaryColor
            }

            Text {
                text: root.title

                font.pixelSize: 20
                font.weight: Font.DemiBold

                color: root.primary ? Theme.black : Theme.white
            }
        }

        Text {
            Layout.fillWidth: true

            text: root.description

            wrapMode: Text.WordWrap

            font.pixelSize: 13

            color: root.primary ? "#D8F8E9" : Theme.darkGrey
        }

        Item {
            Layout.fillHeight: true
        }

        RowLayout {
            spacing: 5

            Text {
                text: root.actionText

                font.pixelSize: 13
                font.weight: Font.DemiBold

                color: root.primary ? Theme.black : Theme.primaryColor
            }

            MuiIcon {
                name: "arrow_forward"

                font.pixelSize: 18

                color: root.primary ? Theme.black : Theme.primaryColor
            }
        }
    }
}