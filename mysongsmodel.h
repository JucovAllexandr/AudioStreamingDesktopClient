#ifndef MYSONGSMODEL_H
#define MYSONGSMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <networkmanager.h>

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
        ArtistNameRole,
        TrackId
    };

    explicit MySongsModel(QObject *parent = nullptr);

    void setSongsMetta(QVector<AudioMetta> &metta);
    int columnCount(const QModelIndex &parent) const override;
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
private:
    QVector<AudioMetta> metta;
};

#endif // MYSONGSMODEL_H
