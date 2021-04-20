#include "mysongsmodel.h"

MySongsModel::MySongsModel(QObject *parent): QAbstractListModel(parent)
{
    for(int i = 0; i < 100; i++){
        songs_data.push_back(Songs("/icons/Album-sample.jpg",
                                   "TrackName"+QString::number(i),
                                   "AlbumName"+QString::number(i),
                                   "ArtistName"+QString::number(i)));
    }
}

int MySongsModel::columnCount(const QModelIndex &parent) const
{
    return songs_data.size();

}

int MySongsModel::rowCount(const QModelIndex &parent) const
{
    return songs_data.size();
}

QVariant MySongsModel::data(const QModelIndex &index, int role) const
{
    QVariant d;
    switch (role) {
    case ImgSourceRole:
        d = songs_data.at(index.row()).img_source;
        break;
    case TrackNameRole:
        d = songs_data.at(index.row()).track_name;
        break;
    case AlbumNameRole:
        d = songs_data.at(index.row()).album_name;
        break;
    case ArtistNameRole:
        d = songs_data.at(index.row()).artist_name;
        break;
    }

    return d;
}

QHash<int, QByteArray> MySongsModel::roleNames() const
{
    QHash<int, QByteArray>  d;
    d[ImgSourceRole] = "img_source";
    d[TrackNameRole] = "track_name";
    d[AlbumNameRole] = "album_name";
    d[ArtistNameRole] = "artist_name";
    return  d;
}
