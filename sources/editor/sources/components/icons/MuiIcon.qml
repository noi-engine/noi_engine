import QtQuick

import noiengine

Text {
    id: root

    required property string name

    text: IconLoader.mui(name)
    font.family: CustomFont.mui()
}
