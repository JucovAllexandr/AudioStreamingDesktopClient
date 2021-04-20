#ifndef MYSONGSMODEL_H
#define MYSONGSMODEL_H

#include <QObject>
#include <QAbstractListModel>

class MySongsModel: public QAbstractListModel
{
public:
    struct Songs{
        QString img_source;
        QString track_name;
        QString album_name;
        QString artist_name;

        Songs(){}
        Songs(QString img_source, QString track_name, QString album_name, QString artist_name):
        img_source(img_source), track_name(track_name), album_name(album_name), artist_name(artist_name)
        {

        }
    };

    enum MySongsRoles {
        ImgSourceRole = Qt::UserRole + 1,
        TrackNameRole,
        AlbumNameRole,
        ArtistNameRole
    };
    explicit MySongsModel(QObject *parent = nullptr);

    int columnCount(const QModelIndex &parent) const override;
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
private:
    QVector<Songs> songs_data;
};

#endif // MYSONGSMODEL_H
