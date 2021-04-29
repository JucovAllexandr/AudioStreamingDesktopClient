import QtQuick 2.15

Item {
    id: root
    property var isPositionChanging: false
    property var _load: 0
    signal positionChanged(real level)

    function setLoad(load){
        if(isPositionChanging == false){
            if(load > 100) {
                load = 100
            }else if(load < 0){
                load = 0
            }

            _load = load

            loader_bar.width = main_bar.width * (load/100)
            pos_changer.x = (loader_bar.x-(pos_changer.width / 2)) + loader_bar.width
        }
    }

    Rectangle{
        id: main_bar
        anchors.fill: parent
        width: parent.width
        height: parent.height
        radius: 20
        color: "#3C3C3C"
        onWidthChanged: {
            /*TODO: Change loader_bar after resizing*/
            setLoad(_load)
            //console.log("width changed")
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
                //console.log(mouse.x)
                loader_bar.width = mouse.x
                pos_changer.x = mouse.x - (pos_changer.width / 2)
                root.positionChanged((loader_bar.width / main_bar.width) * 100.0)
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
                isPositionChanging = true
                //console.log(pos_changer.x + (pos_changer.width/2))
                loader_bar.width = pos_changer.x + (pos_changer.width/2)
                console.log("onMouseXChanged "+((loader_bar.width / main_bar.width) * 100.0))
                root.positionChanged((loader_bar.width / main_bar.width) * 100.0)
            }

            onReleased: {
                isPositionChanging = false
            }
        }
    }
}
