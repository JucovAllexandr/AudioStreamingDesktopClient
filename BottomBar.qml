import QtQuick 2.15
import QtGraphicalEffects 1.15

Item {
    id:root
    FontLoader { id: robotoFont; source: "/fonts/Roboto/Roboto-Regular.ttf" }

    Connections{
        target: MySongs
        function onTrackChanged(trackId, title, artist){
            textTitle.text = title
            textArtist.text = artist
        }
    }
    Connections{
        target: AudioPlayer

        function onPositionChanged(level){
            //console.log(level)
            track_loader.setLoad(level)
        }

        function onTrackTimeChanged(playTime, trackTime){
            textPlayTime.text = playTime
            textTrackTime.text = trackTime
        }

        function onStoppedState(){
            track_loader.setLoad(0);
            playOverlay.visible = true
            pauseOverlay.visible = false
        }

        function onPlayingState(){
            playOverlay.visible = false
            pauseOverlay.visible = true
        }

        function onPausedState(){
            playOverlay.visible = true
            pauseOverlay.visible = false
        }
    }

    Rectangle{
        id: bkg
        anchors.fill: root
        color: "#222222"

        Text{
            id: textTitle
            anchors.left: bkg.left
            anchors.top: bkg.top
            anchors.topMargin: 10
            anchors.leftMargin: 10
            width: implicitWidth
            height: implicitHeight
            font.family: robotoFont.name
            font.pixelSize: 16
            color: "white"

        }

        Text{
            id: textArtist
            anchors.left: bkg.left
            anchors.top: textTitle.bottom
            anchors.topMargin: 10
            anchors.leftMargin: 10
            width: implicitWidth
            height: implicitHeight
            font.family: robotoFont.name
            font.pixelSize: 12
            color: "white"
        }

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
                        AudioPlayer.play()
                        playOverlay.visible = false
                        pauseOverlay.visible = true
                    }else{                
                        AudioPlayer.pause()
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
                    AppManager.playPrevSong()
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
                    AppManager.playNextSong()
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

            onPositionChanged: {
                console.log("onPositionChanged "+level)
                AudioPlayer.setPosition(level)
            }
        }

        Text{
            id: textPlayTime
            anchors.right: track_loader.left
            anchors.verticalCenter: track_loader.verticalCenter
            anchors.rightMargin: 10
            width: implicitWidth
            height: implicitHeight
            text: "00:00"
            font.family: robotoFont.name
            color: "#A4A4A4"
        }

        Text{
            id: textTrackTime
            anchors.left: track_loader.right
            anchors.verticalCenter: track_loader.verticalCenter
            anchors.leftMargin: 10
            width: implicitWidth
            height: implicitHeight
            text: "00:00"
            font.family: robotoFont.name
            color: "#A4A4A4"
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

            Component.onCompleted: {
                volume_loader.setLoad(100);
            }

            onPositionChanged: {
                AudioPlayer.setVolume(level)
            }
        }
    }
}
