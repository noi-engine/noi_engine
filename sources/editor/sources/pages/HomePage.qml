import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import noi_engine_editor

CustomPage {
    id: root

    title: qsTr("HomePage")

    RecentProjectsModel {
        id: recentProjectsModel
    }

    Rectangle {
        anchors.fill: parent
        color: Theme.bgPrimary
    }

    Flickable {
        id: flickable

        anchors.fill: parent

        anchors.leftMargin: root.width >= 1200 ? 48 : 24
        anchors.rightMargin: root.width >= 1200 ? 48 : 24
        anchors.topMargin: root.height >= 700 ? 40 : 24
        anchors.bottomMargin: root.height >= 700 ? 40 : 24

        contentWidth: flickable.width
        contentHeight: contentColumn.implicitHeight

        clip: true
        boundsBehavior: Flickable.StopAtBounds

        ScrollBar.vertical: ScrollBar {
            policy: ScrollBar.AsNeeded
        }

        ColumnLayout {
            id: contentColumn

            width: Math.min(flickable.width, 1500)
            anchors.horizontalCenter: parent.horizontalCenter

            spacing: 30

            HeroHeader {
                Layout.fillWidth: true
            }

            QuickActionsRow {
                Layout.fillWidth: true
                onCreateProjectRequested: {
                    console.log("HelloWorld");
                    RecentProjectsManager.addProject("Nouveau Projet", "/home/user/Projects/NouveauProjet")
                }
                onOpenProjectRequested: {}
            }

            RecentProjectsSection {
                Layout.fillWidth: true
                model: recentProjectsModel
                onProjectClicked: (path) => {
                    console.log("Ouverture du projet:", path)
                }
            }

            Item {
                Layout.preferredHeight: 20
                Layout.fillWidth: true
            }
        }
    }
}