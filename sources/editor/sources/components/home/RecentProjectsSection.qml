import QtQuick
import QtQuick.Layouts

import noi_engine_editor

ColumnLayout {
    id: root

    required property var projects

    signal projectClicked(var project)

    readonly property var filteredProjects: {
        const query = searchField.text.trim().toLowerCase()
        if (query.length === 0) return root.projects
        return root.projects.filter(p => p.name.toLowerCase().includes(query))
    }

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

        Item {
            Layout.fillWidth: true
        }

        Text{
            text: qsTr("%n project(s)", "", root.projects.length)

            font.pixelSize: 12

            color: Theme.grey
        }
    }

    SearchField {
        id: searchField

        placeholderText: qsTr("Search projects...")
    }

    Repeater {
        model: root.filteredProjects

        delegate: RecentProjectItem {
            required property var modelData

            Layout.fillWidth: true

            project: modelData

            onClicked: root.projectClicked(modelData)
        }
    }

    EmptyState {
        visible: root.filteredProjects.length === 0

        icon: "folder_off"
        title: qsTr("No recent projects")
        description: qsTr("Create or open a project to get started.")
    }
}