import QtQuick 2.15
import QtGraphicalEffects 1.15

Item {
    id: root
    property alias text: label.text
    property alias source: icon.source
    property alias iconWidth: icon.width
    property var leftBarButtonWidth: icon.width + label.width + 10

    signal clicked()

    Rectangle{
        anchors.fill: root
        border{
            color: "#18A0FB"
            width: 0
        }
        color: "#00000000"

        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                root.clicked();
                icon_overlay.color = "#18A0FB"
            }
            onEntered:{
                parent.border.width = 1
            }
            onExited: {
                parent.border.width = 0
            }
        }

        Image {
            id: icon
            anchors.left: parent.left
            sourceSize{
                width: parent.height
                height: parent.height
            }
            antialiasing: true
            visible: false
        }

        ColorOverlay {
             id: icon_overlay
             anchors.fill: icon
             source: icon
             color: "#E5E5E5"
             antialiasing: true
        }

        Text {
            id: label
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: icon.right
            anchors.leftMargin: 10
            color: "#E5E5E5"
            font{
                pixelSize: root.height
                family: mohaveFont.name
            }
        }
    }

    function setIconMode()
    {
        label.visible = false
    }
}
