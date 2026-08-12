import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

import noi_engine_editor

CustomPage {
    id: root

    title: qsTr("Create Project")

    ProjectCreator {
        id: projectCreator

        onProjectCreated: (name, path) => {
            RecentProjectsManager.addProject(name, path)
            Router.replace("/")
        }

        onProjectCreationFailed: (reason) => {
            errorLabel.text = reason
            errorLabel.visible = true
        }
    }

    FolderDialog {
        id: folderDialog

        onAccepted: {
            locationField.text = selectedFolder.toString().replace("file://", "")
        }
    }

    Rectangle {
        anchors.fill: parent
        color: Theme.bgPrimary
    }

    ColumnLayout {
        anchors.centerIn: parent

        width: Math.min(parent.width - 80, 560)

        spacing: 22

        ColumnLayout {
            spacing: 6

            Text {
                text: qsTr("Create a new project")
                font.pixelSize: 26
                font.weight: Font.Bold
                color: Theme.white
            }

            Text {
                text: qsTr("Choose a name and a location for your project.")
                font.pixelSize: 13
                color: Theme.darkGrey
            }
        }

        ColumnLayout {
            Layout.fillWidth: true
            spacing: 6

            Text {
                text: qsTr("Project name")
                font.pixelSize: 13
                color: Theme.darkGrey
            }

            TextField {
                id: nameField

                Layout.fillWidth: true
                Layout.preferredHeight: 44

                text: "NewProject"

                color: Theme.white
                font.pixelSize: 14

                background: Rectangle {
                    radius: 10
                    color: Theme.bgSecondary
                    border.color: Theme.borderColor
                    border.width: 1
                }
            }
        }

        ColumnLayout {
            Layout.fillWidth: true
            spacing: 6

            Text {
                text: qsTr("Location")
                font.pixelSize: 13
                color: Theme.darkGrey
            }

            RowLayout {
                Layout.fillWidth: true
                spacing: 10

                TextField {
                    id: locationField

                    Layout.fillWidth: true
                    Layout.preferredHeight: 44

                    text: SettingsManager.defaultProjectsPath

                    color: Theme.white
                    font.pixelSize: 13

                    background: Rectangle {
                        radius: 10
                        color: Theme.bgSecondary
                        border.color: Theme.borderColor
                        border.width: 1
                    }
                }

                AppButton {
                    text: qsTr("Browse")
                    icon: "folder_open"

                    onClicked: folderDialog.open()
                }
            }
        }

        CheckBox {
            id: defaultFolderCheckBox

            text: qsTr("Set as default projects folder")
        }

        Text {
            id: errorLabel

            visible: false

            Layout.fillWidth: true

            wrapMode: Text.WordWrap

            color: Theme.error
            font.pixelSize: 12
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.topMargin: 10

            spacing: 12

            Item { Layout.fillWidth: true }

            AppButton {
                text: qsTr("Cancel")
                onClicked: Router.replace("/")
            }

            AppButton {
                text: qsTr("Create Project")
                primary: true

                onClicked: {
                    if (nameField.text.trim() === "") {
                        errorLabel.text = qsTr("Project name cannot be empty")
                        errorLabel.visible = true
                        return
                    }

                    if (defaultFolderCheckBox.checked) {
                        SettingsManager.defaultProjectsPath = locationField.text
                    }

                    projectCreator.createProject(nameField.text.trim(), locationField.text)
                }
            }
        }
    }
}