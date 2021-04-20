import QtQuick 2.15

Item {
    property var gridCellWidth: 200
    property var gridCellHeight: 200
    property var gridCellSpace: 10
    id: root
    FontLoader { id: robotoFont; source: "/fonts/Roboto/Roboto-Regular.ttf" }
    Rectangle{
        anchors.fill: root
        color: "#3C3C3C"

        ListModel {
            id: fruitModel
            property string language: "en"
            ListElement {
                img_source: "/icons/Album-sample.jpg"
                track_name: "Track1"
                album_name: "Album1"
                artist_name: "Artist1"
            }
            ListElement {
                img_source: "/icons/Album-sample.jpg"
                track_name: "Track2"
                album_name: "Album2"
                artist_name: "Artist2"
            }
            ListElement {
                img_source: "/icons/Album-sample.jpg"
                track_name: "Track3"
                album_name: "Album3"
                artist_name: "Artist3"
            }
        }

        Component {
            id: fruitDelegate
            Column {

                TrackElement{
                    width: gridCellWidth
                    height: gridCellHeight
                    source: img_source
                    track_text: track_name
                    album_text: album_name
                    artist_text: artist_name
                }
                //Text { text: " Fruit: " + name; color: fruit.ListView.view.fruit_color }
                //Text { text: " Cost: $" + cost }
                //Text { text: " Language: " + fruit.ListView.view.model.language }
            }
        }

        GridView {
            anchors.fill: parent
            anchors.margins: 10
            cellWidth: gridCellWidth + gridCellSpace
            cellHeight: gridCellHeight + gridCellSpace
            clip: true
            model: MySongsModel
            delegate: fruitDelegate
        }
    }
}
