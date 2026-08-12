import QtQuick
import QtQuick.Layouts

import noi_engine_editor

CustomPage {
    id: root

    title: CurrentProjectManager.name

    Rectangle {
        anchors.fill: parent
        color: Theme.bgPrimary
    }

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 6

        Text {
            Layout.alignment: Qt.AlignHCenter
            text: CurrentProjectManager.name
            font.pixelSize: 24
            font.weight: Font.Bold
            color: Theme.white
        }

        Text {
            Layout.alignment: Qt.AlignHCenter
            text: CurrentProjectManager.path
            font.pixelSize: 13
            color: Theme.grey
        }
    }
}