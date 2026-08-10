pragma Singleton

import QtQuick
import QtQuick.Controls.Material

QtObject {
    readonly property color bgPrimary: "#f3f3f3"
    readonly property color borderColor: "#e9eaf5"

    readonly property color primaryColor: "#4F55AE"
    readonly property color primaryLightAColor: "#7C82D1"
    readonly property color primaryLightBColor: "#DDE0FF"
    readonly property color primaryLightCColor: "#F5F6FF"

    readonly property color gradientStart: "#4F55AE"
    readonly property color gradientEnd: "#7C82D1"

    readonly property color black: "#1a1c1e"
    readonly property color grey: "#bbbbbb"
    readonly property color white: "#ffffff"

    function setup(){
        Material.theme = Material.Light
        Material.accent = primaryColor
    }

    function darker(color){
        return Qt.darker(color, 1.2)
    }

    function lighter(color){
        return Qt.lighter(color, 1.2)
    }
}
