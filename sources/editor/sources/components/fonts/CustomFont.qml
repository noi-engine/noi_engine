pragma Singleton

import QtQuick

QtObject {
    id: root

    readonly property FontLoader muiSymbols: FontLoader {
        source: "qrc:/fonts/Material_Symbols_Outlined/font.ttf"
    }

    function mui(){
        return muiSymbols.name;
    }
}
