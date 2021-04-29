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

      /*  Component {
            id: highlight
            Item{
            gridView.currentItem.children[0].select()
            }
        }*/

        Component {
            id: songDelegate
            Column {

                TrackElement{
                    width: gridCellWidth
                    height: gridCellHeight
                    source: img_source
                    track_text: track_name
                    album_text: album_name
                    artist_text: artist_name

                    MouseArea{
                        anchors.fill: parent

                        onClicked: {
                            AppManager.playMySong(trackId)
                        }
                    }
                }
                //Text { text: " Fruit: " + name; color: fruit.ListView.view.fruit_color }
                //Text { text: " Cost: $" + cost }
                //Text { text: " Language: " + fruit.ListView.view.model.language }
            }
        }

        Connections{
            target: MySongs

            function onCurrentIndexTrackIdChanged(oldValue, newValue){
                if(oldValue >= 0){
                    gridView.itemAtIndex(oldValue).children[0].unselect()
                }

                if(newValue >= 0){
                    gridView.currentIndex = newValue
                    gridView.itemAtIndex(newValue).children[0].select()

                }


            }
        }


        GridView {
            id: gridView
            anchors.fill: parent
            anchors.margins: 10
            cellWidth: gridCellWidth + gridCellSpace
            cellHeight: gridCellHeight + gridCellSpace
            clip: true
            model: MySongsModel
            delegate: songDelegate


            onHighlightItemChanged: {
                gridView.currentItem.children[0].select()
            }
        }
    }
}
