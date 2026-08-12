import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import noi_engine_editor

Rectangle {
    id: root

    property alias text: textField.text
    property string placeholderText: qsTr("Search...")

    signal cleared()

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
            id: textField

            Layout.fillWidth: true

            placeholderText: root.placeholderText
            placeholderTextColor: Theme.grey

            background: Item {}

            font.pixelSize: 13

            color: Theme.white
        }

        MuiIcon {
            visible: textField.text.length > 0

            name: "close"

            font.pixelSize: 18

            color: Theme.grey

            MouseArea {
                anchors.fill: parent

                cursorShape: Qt.PointingHandCursor

                onClicked: {
                    textField.clear()
                    root.cleared()
                }
            }
        }
    }
}