import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import noi_engine_editor

CustomPage {
    id: root

    title: "MainPage"

    property var recentProjects: [
        {
            name: "Space Explorer",
            path: "~/Projects/SpaceExplorer",
            date: "Today"
        },
        {
            name: "My First Game",
            path: "~/Projects/MyFirstGame",
            date: "Yesterday"
        },
        {
            name: "Platformer",
            path: "~/Projects/Platformer",
            date: "3 days ago"
        },
        {
            name: "Test Project",
            path: "~/Projects/TestProject",
            date: "Last week"
        }
    ]

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

        contentWidth: width
        contentHeight: contentColumn.height

        clip: true

        boundsBehavior: Flickable.StopAtBounds

        ScrollBar.vertical: ScrollBar {
            policy: ScrollBar.AsNeeded
        }

        ColumnLayout {
            id: contentColumn

            width: Math.min(
                flickable.width,
                1500
            )

            anchors.horizontalCenter: parent.horizontalCenter

            spacing: 30

            ColumnLayout {
                Layout.fillWidth: true

                spacing: 7

                RowLayout {
                    spacing: 12

                    MuiIcon {
                        name: "deployed_code"

                        font.pixelSize: 42

                        color: Theme.primaryColor
                    }

                    Label {
                        text: "Noi Engine"

                        font.pixelSize: root.width >= 1200 ? 40 : 34
                        font.weight: Font.Bold

                        color: Theme.white
                    }
                }

                Label {
                    text: "Build worlds. Create experiences. Ship your game."

                    font.pixelSize: 15

                    color: Theme.darkGrey
                }
            }

            RowLayout {
                Layout.fillWidth: true

                spacing: 18

                Rectangle {
                    Layout.fillWidth: true
                    Layout.minimumWidth: 280
                    Layout.preferredHeight: 155

                    radius: 14

                    color: Theme.primaryColor

                    MouseArea {
                        anchors.fill: parent

                        cursorShape: Qt.PointingHandCursor

                        onClicked: {
                        }
                    }

                    ColumnLayout {
                        anchors.fill: parent

                        anchors.margins: 24

                        spacing: 8

                        RowLayout {
                            spacing: 11

                            MuiIcon {
                                name: "add_circle"

                                font.pixelSize: 30

                                color: Theme.black
                            }

                            Label {
                                text: "Create a Project"

                                font.pixelSize: 20
                                font.weight: Font.DemiBold

                                color: Theme.black
                            }
                        }

                        Label {
                            Layout.fillWidth: true

                            text: "Start a new project and build your next experience with Noi Engine."

                            wrapMode: Text.WordWrap

                            font.pixelSize: 13

                            color: "#D8F8E9"
                        }

                        Item {
                            Layout.fillHeight: true
                        }

                        RowLayout {
                            spacing: 5

                            Label {
                                text: "Get started"

                                font.pixelSize: 13
                                font.weight: Font.DemiBold

                                color: Theme.black
                            }

                            MuiIcon {
                                name: "arrow_forward"

                                font.pixelSize: 18

                                color: Theme.black
                            }
                        }
                    }
                }

                Rectangle {
                    Layout.fillWidth: true
                    Layout.minimumWidth: 280
                    Layout.preferredHeight: 155

                    radius: 14

                    color: Theme.bgSecondary

                    border.color: Theme.borderColor
                    border.width: 1

                    MouseArea {
                        anchors.fill: parent

                        cursorShape: Qt.PointingHandCursor

                        onClicked: {
                        }
                    }

                    ColumnLayout {
                        anchors.fill: parent

                        anchors.margins: 24

                        spacing: 8

                        RowLayout {
                            spacing: 11

                            MuiIcon {
                                name: "folder_open"

                                font.pixelSize: 30

                                color: Theme.primaryColor
                            }

                            Label {
                                text: "Open a Project"

                                font.pixelSize: 20
                                font.weight: Font.DemiBold

                                color: Theme.white
                            }
                        }

                        Label {
                            Layout.fillWidth: true

                            text: "Open an existing Noi Engine project from your computer."

                            wrapMode: Text.WordWrap

                            font.pixelSize: 13

                            color: Theme.darkGrey
                        }

                        Item {
                            Layout.fillHeight: true
                        }

                        RowLayout {
                            spacing: 5

                            Label {
                                text: "Browse projects"

                                font.pixelSize: 13
                                font.weight: Font.DemiBold

                                color: Theme.primaryColor
                            }

                            MuiIcon {
                                name: "arrow_forward"

                                font.pixelSize: 18

                                color: Theme.primaryColor
                            }
                        }
                    }
                }
            }

            ColumnLayout {
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

                    Label {
                        text: "Recent Projects"

                        font.pixelSize: 21
                        font.weight: Font.DemiBold

                        color: Theme.white
                    }

                    Item {
                        Layout.fillWidth: true
                    }

                    Label {
                        text: root.recentProjects.length + " projects"

                        font.pixelSize: 12

                        color: Theme.grey
                    }
                }

                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 46

                    radius: 10

                    color: Theme.bgSecondary

                    border.color: Theme.borderColor
                    border.width: 1

                    RowLayout {
                        anchors.fill: parent

                        anchors.leftMargin: 14
                        anchors.rightMargin: 14

                        spacing: 9

                        MuiIcon {
                            name: "search"

                            font.pixelSize: 20

                            color: Theme.grey
                        }

                        TextField {
                            id: searchField

                            Layout.fillWidth: true

                            placeholderText: "Search projects..."
                            placeholderTextColor: Theme.grey

                            background: Item {}

                            font.pixelSize: 13

                            color: Theme.white
                        }

                        MuiIcon {
                            visible: searchField.text.length > 0

                            name: "close"

                            font.pixelSize: 18

                            color: Theme.grey

                            MouseArea {
                                anchors.fill: parent

                                cursorShape: Qt.PointingHandCursor

                                onClicked: {
                                    searchField.clear()
                                }
                            }
                        }
                    }
                }

                Repeater {
                    model: root.recentProjects

                    delegate: Rectangle {
                        required property var modelData

                        Layout.fillWidth: true
                        Layout.preferredHeight: 74

                        radius: 11

                        color: projectMouse.containsMouse
                               ? Theme.primaryLightC
                               : Theme.bgSecondary

                        border.color: projectMouse.containsMouse
                                      ? Theme.primaryDark
                                      : Theme.borderColor

                        border.width: 1

                        Behavior on color {
                            ColorAnimation {
                                duration: 120
                            }
                        }

                        Behavior on border.color {
                            ColorAnimation {
                                duration: 120
                            }
                        }

                        MouseArea {
                            id: projectMouse

                            anchors.fill: parent

                            hoverEnabled: true

                            cursorShape: Qt.PointingHandCursor

                            onClicked: {
                            }
                        }

                        RowLayout {
                            anchors.fill: parent

                            anchors.leftMargin: 16
                            anchors.rightMargin: 16

                            spacing: 14

                            Rectangle {
                                Layout.preferredWidth: 40
                                Layout.preferredHeight: 40

                                radius: 9

                                color: Theme.primaryLightB

                                MuiIcon {
                                    anchors.centerIn: parent

                                    name: "folder"

                                    font.pixelSize: 21

                                    color: Theme.primaryColor
                                }
                            }

                            ColumnLayout {
                                Layout.fillWidth: true

                                spacing: 3

                                Label {
                                    text: modelData.name

                                    font.pixelSize: 14
                                    font.weight: Font.DemiBold

                                    color: Theme.white
                                }

                                Label {
                                    Layout.fillWidth: true

                                    text: modelData.path

                                    elide: Text.ElideMiddle

                                    font.pixelSize: 12

                                    color: Theme.grey
                                }
                            }

                            Label {
                                text: modelData.date

                                font.pixelSize: 12

                                color: Theme.grey
                            }

                            MuiIcon {
                                name: "chevron_right"

                                font.pixelSize: 20

                                color: projectMouse.containsMouse
                                       ? Theme.primaryColor
                                       : Theme.lightGrey
                            }
                        }
                    }
                }

                Rectangle {
                    visible: root.recentProjects.length === 0

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

                            name: "folder_off"

                            font.pixelSize: 34

                            color: Theme.lightGrey
                        }

                        Label {
                            Layout.alignment: Qt.AlignHCenter

                            text: "No recent projects"

                            font.pixelSize: 15

                            color: Theme.darkGrey
                        }

                        Label {
                            Layout.alignment: Qt.AlignHCenter

                            text: "Create or open a project to get started."

                            font.pixelSize: 13

                            color: Theme.grey
                        }
                    }
                }
            }

            Item {
                Layout.preferredHeight: 20
            }
        }
    }
}