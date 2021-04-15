import QtQuick 2.15
import QtGraphicalEffects 1.15

Item {
    id:root
    Rectangle{
        id: bkg
        anchors.fill: root
        color: "#222222"



        Rectangle{
            id: btn_play_pause
            anchors.top: bkg.top
            anchors.topMargin: 10
            anchors.horizontalCenter: bkg.horizontalCenter
            color: parent.color
            width: 30
            height: 30



            Image {
                id: img_play
                anchors.fill: parent
                source: "/icons/play-button.svg"
                antialiasing: true
                sourceSize.width: btn_play_pause.width
                sourceSize.height: btn_play_pause.height
                visible: false
            }

            ColorOverlay {
                id: playOverlay
                anchors.fill: img_play
                source: img_play
                color: "lightGrey"
                antialiasing: true
                transformOrigin: Item.Center

            }

            Image {
                id: img_pause
                anchors.fill: parent
                source: "/icons/pause-button.svg"
                antialiasing: true
                sourceSize.width: btn_play_pause.width
                sourceSize.height: btn_play_pause.height
                visible: false
            }

            ColorOverlay {
                id: pauseOverlay
                anchors.fill: img_pause
                source: img_pause
                color: "lightGrey"
                antialiasing: true
                transformOrigin: Item.Center
                visible: false
            }

            MouseArea{
                anchors.fill: btn_play_pause
                hoverEnabled: true
                onClicked: {
                    if(playOverlay.visible){
                        playOverlay.visible = false
                        pauseOverlay.visible = true
                    }else{
                        playOverlay.visible = true
                        pauseOverlay.visible = false
                    }
                }

                onEntered: {
                    playOverlay.color = "white"
                    pauseOverlay.color = "white"
                }

                onExited: {
                    playOverlay.color = "lightGrey"
                    pauseOverlay.color = "lightGrey"
                }
            }

        }

        Rectangle{
            id: btn_prev_track
            anchors.right: btn_play_pause.left
            anchors.verticalCenter: btn_play_pause.verticalCenter
            anchors.rightMargin: 30

            width: 15
            height: 15
            color: parent.color

            Image {
                id: img_prev_track
                anchors.fill: parent
                source: "/icons/prev_track.svg"
                antialiasing: true
                sourceSize.width: parent.width
                sourceSize.height: parent.height
                visible: false
            }

            ColorOverlay {
                id: prev_trackOverlay
                anchors.fill: img_prev_track
                source: img_prev_track
                color: "lightGrey"
                antialiasing: true
                transformOrigin: Item.Center
                visible: true
            }

            MouseArea{
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {

                }

                onEntered: {
                    prev_trackOverlay.color = "white"
                }

                onExited: {
                    prev_trackOverlay.color = "lightGrey"
                }
            }
        }

        Rectangle{
            id: btn_next_track
            anchors.left: btn_play_pause.right
            anchors.verticalCenter: btn_play_pause.verticalCenter
            anchors.leftMargin: 30

            width: 15
            height: 15
            color: parent.color

            Image {
                id: img_next_track
                anchors.fill: parent
                source: "/icons/prev_track.svg"
                antialiasing: true
                sourceSize.width: parent.width
                sourceSize.height: parent.height
                visible: false
            }

            ColorOverlay {
                id: next_trackOverlay
                anchors.fill: parent
                source: img_next_track
                color: "lightGrey"
                antialiasing: true
                transformOrigin: Item.Center
                rotation: 180
                visible: true
            }

            MouseArea{
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {

                }

                onEntered: {
                    next_trackOverlay.color = "white"
                }

                onExited: {
                    next_trackOverlay.color = "lightGrey"
                }
            }
        }

        LoaderBar{
            id: track_loader
            anchors.top: btn_play_pause.bottom
            anchors.topMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width * 0.50
            height: 5
        }

        Rectangle{
            id: btn_audio_volume
            anchors.right: volume_loader.left
            anchors.verticalCenter: track_loader.verticalCenter
            anchors.rightMargin: 10
            width: 20
            height: 20
            color: parent.color

            Image {
                id: img_audio_volume
                anchors.fill: parent
                source: "/icons/audio_volume_icon.svg"
                sourceSize.height: parent.height
                sourceSize.width: parent.width
                visible: false
            }

            ColorOverlay {
                id: audio_volume_trackOverlay
                anchors.fill: parent
                source: img_audio_volume
                color: "#A4A4A4"
                antialiasing: true
            }
        }

        LoaderBar{
            id: volume_loader
            anchors.verticalCenter: btn_audio_volume.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 10
            width: parent.width * 0.10
            height: 5
        }
    }
}
