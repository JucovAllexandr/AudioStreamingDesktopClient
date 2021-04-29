import QtQuick 2.15

Item {
    property alias source: img.source
    property alias track_text: track_name.text
    property alias album_text: album_name.text
    property alias artist_text: artist_name.text
    property var isSelected: false
    id: root
    clip: true
    function select(){
        isSelected = true
        bck.border.width = 1
        track_name.color = "white"
        album_name.color = "white"
        artist_name.color = "white"
    }

    function unselect(){
        isSelected = false
        bck.border.width = 0
        track_name.color = "#A4A4A4"
        album_name.color = "#A4A4A4"
        artist_name.color = "#A4A4A4"

    }
    //anchors.fill: parent
    Rectangle{
        id: bck
        anchors.fill: root
        color: "#3C3C3C"
        border{
            color: "#18A0FB"
            width: 0
        }
        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onEntered:{
                if(!isSelected){
                parent.border.width = 1
                }
            }
            onExited: {
                if(!isSelected){
                parent.border.width = 0
                }
            }
        }
        Image {
            id: img
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 1
            width: parent.width-2
            height: parent.height - track_name.height - album_name.height - artist_name.height
            fillMode: Image.PreserveAspectFit
        }

        Text {
            id: track_name
            anchors.top: img.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 18
            color: "#A4A4A4"
            font.family: robotoFont.name
        }

        Text {
            id: album_name
            anchors.top: track_name.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 18
            font.family: robotoFont.name
            color: "#A4A4A4"
        }

        Text {
            id: artist_name
            anchors.top: album_name.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 18
            font.family: robotoFont.name
            color: "#A4A4A4"
        }
    }
}
