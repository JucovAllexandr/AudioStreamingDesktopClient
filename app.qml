import QtQuick 2.15

Item {
    property var bottomBarHeight: 90
    id: root

    Component.onCompleted: {
        AppManager.connectMySongs()
    }

    LeftBar{
        id: leftBar
        width: root.width * 0.20
        height: root.height - bottomBarHeight
    }
    TopBar{
        id: topBar
        anchors.left: leftBar.right
        width: root.width - leftBar.width
        height: root.height * 0.05

    }
    BottomBar{
        id: bottomBar
        y: leftBar.height
        x: 0
        width: root.width
        height: bottomBarHeight
    }

    MainWidget{
        anchors.top: topBar.bottom
        anchors.bottom: bottomBar.top
        anchors.left: leftBar.right
        anchors.right: bottomBar.right
    }

}
