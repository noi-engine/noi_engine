import QtQuick

import noi_engine_editor

Text {
    id: root

    required property string name

    text: IconLoader.mui(name)
    font.family: CustomFont.mui()
}
