pragma Singleton

import QtQuick
import "IconLoaderCreator.js" as JSIconLoader

QtObject {
    readonly property var muiIconLoader: JSIconLoader.getLoader("mui")

    function mui(iconName){
        return muiIconLoader.get(iconName);
    }
}
