import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import noi_engine_editor

ColumnLayout {
    id: root

    required property var model

    signal projectClicked(string path)

    Layout.fillWidth: true
    spacing: 15

    RowLayout {
        Layout.fillWidth: true
        spacing: 10

        MuiIcon {
            name: "history"
            font.pixelSize: 24
            color: Theme.primaryColor
        }

        Text {
            text: qsTr("Recent Projects")
            font.pixelSize: 21
            font.weight: Font.DemiBold
            color: Theme.white
        }

        Item { Layout.fillWidth: true }

        Text {
            text: qsTr("%n project(s)", "", repeater.count)
            font.pixelSize: 12
            color: Theme.grey
        }
    }

    SearchField {
        id: searchField
        placeholderText: qsTr("Search projects...")
    }

    Repeater {
        id: repeater
        model: root.model

        delegate: RecentProjectItem {
            required property string name
            required property string path
            required property string lastOpened
            required property int index

            projectName: name
            projectPath: path
            projectDate: lastOpened

            Layout.fillWidth: true

            visible: searchField.text.trim() === "" ||
                     name.toLowerCase().includes(searchField.text.trim().toLowerCase())

            height: visible ? implicitHeight : 0

            onClicked: root.projectClicked(path)
        }
    }

    EmptyState {
        visible: repeater.count === 0

        icon: "folder_off"
        title: qsTr("No recent projects")
        description: qsTr("Create or open a project to get started.")
    }
}