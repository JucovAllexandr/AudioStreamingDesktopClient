#include "mysongsmodel.h"

MySongsModel::MySongsModel(QObject *parent): QAbstractListModel(parent)
{
    /*for(int i = 0; i < 100; i++){
        songs_data.push_back(Songs("/icons/Album-sample.jpg",
                                   "TrackName"+QString::number(i),
                                   "AlbumName"+QString::number(i),
                                   "ArtistName"+QString::number(i)));
    }*/
}

void MySongsModel::setSongsMetta(QVector<AudioMetta> &metta)
{
    beginResetModel();
    this->metta = metta;
    endResetModel();
}

int MySongsModel::columnCount(const QModelIndex &parent) const
{
    return metta.size();

}

int MySongsModel::rowCount(const QModelIndex &parent) const
{
    return metta.size();
}

QVariant MySongsModel::data(const QModelIndex &index, int role) const
{
    QVariant d;
    switch (role) {
    case TrackId:
        d = metta.at(index.row()).id;
        break;
    case ImgSourceRole:
        d = "image://MySongsImageProvider/"+QString::number(metta.at(index.row()).id);
        break;
    case TrackNameRole:
        d = metta.at(index.row()).title;
        break;
    case AlbumNameRole:
        d = metta.at(index.row()).album;
        break;
    case ArtistNameRole:
        d = metta.at(index.row()).artists.first().name;
        break;
    }

    return d;
}

QHash<int, QByteArray> MySongsModel::roleNames() const
{
    QHash<int, QByteArray>  d;
    d[TrackId] = "trackId";
    d[ImgSourceRole] = "img_source";
    d[TrackNameRole] = "track_name";
    d[AlbumNameRole] = "album_name";
    d[ArtistNameRole] = "artist_name";
    return  d;
}
