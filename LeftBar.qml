import QtQuick 2.15

Item {
    id: root
    property var buttonWidth: width - 20
    property var buttonHeight: height * 0.05
    property var pressX: 0
    property var changeX: 0
    property var changeWidth: 0
    Rectangle {
        id: mainRec
        anchors.fill: root
        color: "#282828"

        FontLoader { id: mohaveFont; source: "/fonts/Mohave/ttf/Mohave-Regular.ttf" }

        Rectangle{
            id: resizeBar
            anchors.right: mainRec.right
            anchors.top: mainRec.top
            anchors.bottom: mainRec.bottom
            width: 5
            color: "#161616"

            MouseArea {
                id: mouseArea
                cursorShape: "SplitHCursor"
                anchors.fill: parent
                onPressed:{
                    pressX = mouse.x

                }

                onPositionChanged: {
                    changeX = pressX - mouse.x
                    changeWidth = root.width - changeX
                    console.log(buttonWidth)
                    if(hotButton.leftBarButtonWidth >= root.width){
                        hotButton.setIconMode()
                        root.width = hotButton.iconWidth + 40
                    }
                    else
                    {
                        root.width = changeWidth
                    }
                }

                onReleased: {
                    pressX = 0
                    changeX = 0
                }
            }

            Rectangle{
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width
                height: 1
                color: "#18A0FB"
            }

            Rectangle{
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: 3
                width: parent.width
                height: 1
                color: "#18A0FB"
            }

            Rectangle{
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: -3
                width: parent.width
                height: 1
                color: "#18A0FB"
            }
        }

        Column{
            id: column
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 10
            spacing: 20

            LeftBarButton{
                id: hotButton
                width: buttonWidth
                height: buttonHeight
                text: "Hot"
                source: "/icons/hot.svg"
            }

            LeftBarButton{
                width: buttonWidth
                height: buttonHeight
                text: "Home"
                source: "/icons/home.svg"
            }

            LeftBarButton{
                width: buttonWidth
                height: buttonHeight
                text: "Browse"
                source: "/icons/browse.svg"
            }

            LeftBarButton{
                width: buttonWidth
                height: buttonHeight
                text: "My Library"
            }

            LeftBarButton{
                width: buttonWidth
                height: buttonHeight
                text: "Songs"
                source: "/icons/songs.svg"
            }

            LeftBarButton{
                width: buttonWidth
                height: buttonHeight
                text: "Albums"
                source: "/icons/albums.svg"
            }

            LeftBarButton{
                width: buttonWidth
                height: buttonHeight
                text: "Artists"
                source: "/icons/artists.svg"
            }
        }
    }
}
