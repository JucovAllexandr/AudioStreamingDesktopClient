#include "audioplayer.h"
#include <QBuffer>
#include <QTime>
AudioPlayer::AudioPlayer(QObject *parent) : QObject(parent)
{
    mediaPlayer = new QMediaPlayer(this, QMediaPlayer::StreamPlayback);
    connect(mediaPlayer, &QMediaPlayer::positionChanged, this, &AudioPlayer::changePosition);
    connect(mediaPlayer, &QMediaPlayer::stateChanged, this, &AudioPlayer::changeState);
    connect(mediaPlayer, &QMediaPlayer::mediaStatusChanged, this, &AudioPlayer::changeStatus);
}

void AudioPlayer::play(QByteArray *audio)
{
    QByteArray ad = *audio;
    QBuffer *buffer = new QBuffer(mediaPlayer);
    buffer->setData(*audio);
    buffer->open(QBuffer::ReadOnly);

    mediaPlayer->setMedia(QMediaContent(),buffer);
    mediaPlayer->play();
    qDebug() << "Player error = " << mediaPlayer->errorString();
}

void AudioPlayer::play(QNetworkRequest request)
{
    mediaPlayer->setMedia(request);
    mediaPlayer->play();
}

void AudioPlayer::play()
{
    mediaPlayer->play();
}

void AudioPlayer::pause()
{
    mediaPlayer->pause();
}

void AudioPlayer::stop()
{
    mediaPlayer->stop();
}

void AudioPlayer::setVolume(int volume)
{
    mediaPlayer->setVolume(volume);
}

void AudioPlayer::setPosition(double level)
{
    if(level > 100){
        level = 100;
    }else if(level < 0){
        level = 0;
    }

    if(mediaPlayer->duration() > 0){
        mediaPlayer->setPosition(mediaPlayer->duration() * (level/100));
    }
}

void AudioPlayer::changePosition(qint64 position)
{
    //qDebug()<<"positionChanged"<<position;
    if(mediaPlayer->duration() > 0){
        //qDebug()<<"level"<<(((double)position)/((double)mediaPlayer->duration())) * 100;
        emit positionChanged((((double)position)/((double)mediaPlayer->duration())) * 100.0);
        QTime playTime(0,0,0,0);
        playTime = playTime.addMSecs(position);
        QTime trackTime(0,0,0,0);
        trackTime = trackTime.addMSecs(mediaPlayer->duration());
        //qDebug()<<"playTime"<<playTime.toString("mm:ss");
        //qDebug()<<"trackTime"<<trackTime.toString("mm:ss");
        emit trackTimeChanged(playTime.toString("mm:ss"), trackTime.toString("mm:ss"));
    }
}

void AudioPlayer::changeState(QMediaPlayer::State state)
{
    switch (state) {
    case QMediaPlayer::StoppedState:
        emit stoppedState();
        break;
    case QMediaPlayer::PlayingState:
        emit playingState();
        break;
    case QMediaPlayer::PausedState:
        emit pausedState();
        break;
    }
}

void AudioPlayer::changeStatus(QMediaPlayer::MediaStatus status)
{
    switch (status) {
        case QMediaPlayer::EndOfMedia:
            emit endOfAudio();
        break;
    }
}
