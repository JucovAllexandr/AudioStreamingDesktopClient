import QtQuick 2.15

Item {
    id: root

    Rectangle{
        id: main_bar
        anchors.fill: parent
        width: parent.width
        height: parent.height
        radius: 20
        color: "#3C3C3C"
        onWidthChanged: {
            /*TODO: Change loader_bar after resizing*/
            console.log("width changed")
        }
        MouseArea{
            anchors.fill: parent
            hoverEnabled: true

            onEntered: {
                loader_bar.color = "#18A0FB"
                pos_changer.visible = true
            }
            onExited: {
                loader_bar.color = "lightGrey"
                pos_changer.visible = false
            }

            onClicked: {
                console.log(mouse.x)
                loader_bar.width = mouse.x
                pos_changer.x = mouse.x - (pos_changer.width / 2)
            }
        }
    }

    Rectangle{
        id: loader_bar
        anchors.top: parent.top
        anchors.left: parent.left

        height: parent.height
        width: 0
        radius: main_bar.radius
        color: "lightGrey"
    }

    Rectangle{
        id: pos_changer
        visible: false
        anchors.verticalCenter: main_bar.verticalCenter
        radius: 100
        width: main_bar.height * 2
        height: main_bar.height * 2
        x: loader_bar.x-(pos_changer.width / 2)

        MouseArea{
            id: pos_changer_mouse_area
            anchors.fill: parent
            drag.target: pos_changer
            drag.axis: Drag.XAxis
            drag.minimumX:  -(pos_changer.width / 2)
            drag.maximumX: main_bar.width - (pos_changer.width/2)

            onMouseXChanged:  {
                console.log(pos_changer.x + (pos_changer.width/2))
                loader_bar.width = pos_changer.x + (pos_changer.width/2)
            }
        }
    }
}
