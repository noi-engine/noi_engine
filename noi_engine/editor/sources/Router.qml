pragma Singleton

import QtQuick
import QtQuick.Controls

QtObject {
    property StackView stackView
    property string currentView: ""

    property Connections stackConn: Connections {
        target: stackView

        function onCurrentItemChanged() {
            if (stackView && stackView.currentItem) {
                updateCurrentPath()
            }
        }
    }

    readonly property var routes: ({
        "/": "pages/HomePage.qml",
        "/create": "pages/CreateProjectPage.qml",
        "/editor": "pages/ProjectEditorPage.qml",
        "/test": "pages/OpenglTestPage.qml",
    })

    function updateCurrentPath() {
        currentView = stackView.currentItem.title
    }

    function push(route, props = {}) {
        const page = routes[route]
        if (page){
            stackView.push(page, props)
        }
    }

    function pop() {
        if (stackView.depth > 1){
            stackView.pop()
            return true;
        }

        return false;
    }

    function replace(route, props = {}){
        const page = routes[route]
        if (page) {
            stackView.replace(page, props)
        }
    }
}