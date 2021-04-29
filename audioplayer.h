#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QMediaPlaylist>
class AudioPlayer : public QObject
{
    Q_OBJECT

    QMediaPlayer *mediaPlayer;
public:
    explicit AudioPlayer(QObject *parent = nullptr);
    void play(QByteArray *audio);
    void play(QNetworkRequest request);
    Q_INVOKABLE void play();
    Q_INVOKABLE void pause();
    void stop();
    Q_INVOKABLE void setVolume(int volume);
    Q_INVOKABLE void setPosition(double level);
private slots:
    void changePosition(qint64 position);
    void changeState(QMediaPlayer::State state);
    void changeStatus(QMediaPlayer::MediaStatus status);
signals:
    void positionChanged(double level);
    void trackTimeChanged(QString playTime, QString trackTime);
    void stoppedState();
    void playingState();
    void pausedState();
    void endOfAudio();
};

#endif // AUDIOPLAYER_H
