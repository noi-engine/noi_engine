import QtQuick
import QtQuick.Layouts

import noi_engine_editor

ColumnLayout {
    id: root

    Layout.fillWidth: true

    spacing: 7

    RowLayout {
        spacing: 12

        MuiIcon {
            name: "deployed_code"

            font.pixelSize: 42

            color: Theme.primaryColor
        }

        Text {
            text: qsTr("Noi Engine")

            font.pixelSize: root.width >= 1200 ? 40 : 34
            font.weight: Font.Bold

            color: Theme.white
        }
    }

    Text {
        text: qsTr("Build worlds. Create experiences. Ship your game.")

        font.pixelSize: 15

        color: Theme.darkGrey
    }
}