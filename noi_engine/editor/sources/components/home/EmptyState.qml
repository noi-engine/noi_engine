import QtQuick
import QtQuick.Layouts

import noi_engine_editor

Rectangle {
    id: root

    property string icon: ""
    property string title: ""
    property string description: ""

    Layout.fillWidth: true
    Layout.preferredHeight: 180

    radius: 12

    color: Theme.bgSecondary

    border.color: Theme.borderColor

    ColumnLayout {
        anchors.centerIn: parent

        spacing: 8

        MuiIcon {
            Layout.alignment: Qt.AlignHCenter

            name: root.icon

            font.pixelSize: 34

            color: Theme.lightGrey
        }

        Text {
            Layout.alignment: Qt.AlignHCenter

            text: root.title

            font.pixelSize: 15

            color: Theme.darkGrey
        }

        Text {
            Layout.alignment: Qt.AlignHCenter

            text: root.description

            font.pixelSize: 13

            color: Theme.grey
        }
    }
}