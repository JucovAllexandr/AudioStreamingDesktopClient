#ifndef MYSONGS_H
#define MYSONGS_H

#include <QObject>
#include <mysongsmodel.h>
#include "auth.h"
#include <networkmanager.h>
#include <QMediaPlayer>
#include <mysongsmodel.h>
#include <QQuickImageProvider>
#include <audioplayer.h>
#include <QCache>

class MySongsImageProvider;

struct AudioBuffer{
    int trackId;
    QByteArray buf;
};

class MySongs : public QObject
{
    Q_OBJECT
    Auth *auth = NULL;
    NetworkManager *networkManager = NULL;
    MySongsModel mySongsModel;
    QVector<AudioMetta> mettaData;
    //QVector<AudioBuffer> audioBuffer;
    MySongsImageProvider *imageProvider;
    int currentIndexTrackId = -1;
    QCache<int, QByteArray> audioCache;
public:
    explicit MySongs(QObject *parent = nullptr);
    void loadMP3(QString path);
    MySongsImageProvider *mySongsImageProvider();
    void getSongs();
    void getAudio(int trackId);
    void setAuth(Auth *auth);
    void setNetworkManager(NetworkManager *manager);
    MySongsModel *songsModel();
    /*QByteArray getAudioBuffer(int trackId) const;*/
    void playAudio(int trackId, AudioPlayer *audioPlayer);
    void playNextAudio(AudioPlayer *audioPlayer);
    void playPrevAudio(AudioPlayer *audioPlayer);
    void setCurrentIndexTrackId(int value);

private:
    AudioMetta findByTrackId(int trackId);
private slots:
    void readAllAudioRequest(QVector<AudioMetta> metta, QString error);
    void readAudio(int trackId, QByteArray *buffer, QString error);
signals:
    void audioRead(int trackId);
    void trackChanged(int trackId, QString title, QString artist);
    void currentIndexTrackIdChanged(int oldValue, int newValue);
};

class MySongsImageProvider: public QQuickImageProvider
{
    QVector<AudioMetta> &metta;
    public:
    explicit MySongsImageProvider(QVector<AudioMetta> &metta);
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;
};

#endif // MYSONGS_H
