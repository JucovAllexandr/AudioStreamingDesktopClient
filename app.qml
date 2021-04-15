import QtQuick 2.15

Item {
    id: root
    LeftBar{
        id: leftBar
        width: root.width * 0.20
        height: root.height - 104
    }
    TopBar{
        id: topBar
        anchors.left: leftBar.right
        width: root.width - leftBar.width
        height: root.height * 0.15

    }
    BottomBar{
        id: bottomBar
        y: leftBar.height
        x: 0
        width: root.width
        height: 104
    }

    MainWidget{
        anchors.top: topBar.bottom
        anchors.bottom: bottomBar.top
        anchors.left: leftBar.right
        anchors.right: bottomBar.right
    }
}
