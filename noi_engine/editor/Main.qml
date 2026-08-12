import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import noi_engine_editor

ApplicationWindow {
    id: root

    visible: true
    color: Theme.bgPrimary

    StackView { id: stackView; anchors.fill: parent }

    Component.onCompleted: {
        Router.stackView = stackView

        Theme.setup()

        Router.replace("/");
    }
}
