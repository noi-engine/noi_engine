pragma Singleton

import QtQuick
import QtQuick.Controls.Material

QtObject {
    readonly property color bgPrimary: "#101412"
    readonly property color bgSecondary: "#171C19"
    readonly property color bgTertiary: "#1D2420"

    readonly property color borderColor: "#29332E"

    readonly property color primaryColor: "#35C98A"
    readonly property color primaryDark: "#249B6B"
    readonly property color primaryLightA: "#63D9A5"
    readonly property color primaryLightB: "#173D2E"
    readonly property color primaryLightC: "#1A3028"

    readonly property color gradientStart: "#249B6B"
    readonly property color gradientEnd: "#35C98A"

    readonly property color black: "#0B0E0D"
    readonly property color darkGrey: "#AAB5AF"
    readonly property color grey: "#75827B"
    readonly property color lightGrey: "#4F5B55"
    readonly property color white: "#F4F8F6"

    readonly property color success: "#35C98A"
    readonly property color warning: "#E0A84B"
    readonly property color error: "#E05B5B"

    function setup() {
        Material.theme = Material.Dark
        Material.accent = primaryColor
        Material.primary = primaryColor
    }

    function darker(color) {
        return Qt.darker(color, 1.2)
    }

    function lighter(color) {
        return Qt.lighter(color, 1.2)
    }
}