#include "mysongs.h"
#include <QFile>
#include <QDir>
#include <QFileInfoList>
#include <QFileInfo>
#include <QDebug>
#include <QMediaMetaData>
#include <QDataStream>
#include <QEventLoop>
#include <QNetworkRequest>
#include <QNetworkReply>


void MySongs::setCurrentIndexTrackId(int value)
{
    emit currentIndexTrackIdChanged(currentIndexTrackId, value);
    currentIndexTrackId = value;
}

MySongs::MySongs(QObject *parent): QObject(parent)
{
    imageProvider = new MySongsImageProvider(mettaData);
}

void MySongs::loadMP3(QString path)
{
    QDir dir(path);
    QFileInfoList infoList = dir.entryInfoList(QDir::Files);
    qDebug()<<infoList;

    for(auto file = infoList.begin(); file != infoList.end(); file++){
        if(file->fileName().endsWith(".mp3")){
            QMediaPlayer player;
            QFile r_file(file->absoluteFilePath());
            r_file.open(QFile::ReadOnly);
            player.setMedia(QMediaContent(), &r_file);

            QEventLoop loop;
            connect(&player, &QMediaPlayer::metaDataAvailableChanged, &loop, &QEventLoop::exit);
            loop.exec();

            if(player.isMetaDataAvailable()){
                qDebug()<<player.metaData(QMediaMetaData::Title);
                qDebug()<<player.metaData(QMediaMetaData::AlbumArtist);
                qDebug()<<player.metaData(QMediaMetaData::AlbumTitle);
                qDebug()<<player.metaData(QMediaMetaData::ThumbnailImage);

            }

            r_file.close();
        }
    }



}

MySongsImageProvider *MySongs::mySongsImageProvider()
{
    return imageProvider;
}

void MySongs::getSongs()
{
    if(auth != NULL && networkManager != NULL){
        if(auth->isAuthenticated()){
            networkManager->asyncGetAllAudio(auth->getSecret());
        }
    }
}

void MySongs::getAudio(int trackId)
{
    if(auth != NULL && networkManager != NULL){
        if(auth->isAuthenticated()){
            networkManager->asyncAudio(auth->getSecret(), trackId);
        }
    }
}

void MySongs::setAuth(Auth *auth)
{
    this->auth = auth;
}

void MySongs::setNetworkManager(NetworkManager *manager)
{
    networkManager = manager;
    connect(networkManager, &NetworkManager::onGetAllAudioRequest, this, &MySongs::readAllAudioRequest);
    connect(networkManager, &NetworkManager::onAudioRequest, this, &MySongs::readAudio);
}

MySongsModel *MySongs::songsModel()
{
    return &mySongsModel;
}

void MySongs::readAllAudioRequest(QVector<AudioMetta> metta, QString error)
{
    if(error.isEmpty()){
        for(auto mt = metta.begin(); mt != metta.end(); mt++){
            qDebug()<<mt->album;
            qDebug()<<mt->id;
            qDebug()<<mt->title;
            qDebug()<<mt->trackNr;
            qDebug()<<mt->year;
        }
        mettaData = metta;
        mySongsModel.setSongsMetta(mettaData);
    }else{
        qDebug()<<"readAllAudioRequest"<<error;
    }
}

void MySongs::readAudio(int trackId, QByteArray *buffer, QString error)
{
    if(error.isEmpty()){
        audioCache.insert(trackId, buffer);

        emit audioRead(trackId);
    }else
    {
        qDebug()<<"readAudio"<<error;
    }
}

/*QByteArray MySongs::getAudioBuffer(int trackId) const
{
    QByteArray buf;
    for(int i = 0; i < audioBuffer.size();i++){
        if(audioBuffer.at(i).trackId == trackId){
            buf = audioBuffer[i].buf;
        }
    }
    return buf;
}*/

void MySongs::playAudio(int trackId, AudioPlayer *audioPlayer)
{
    audioPlayer->stop();
    if(!audioCache.contains(trackId)){
        getAudio(trackId);
        QNetworkRequest request;
        request.setUrl(QUrl(URL+"audio/"+QString::number(trackId)));
        request.setRawHeader("authorization",auth->getSecret().toUtf8());

        audioPlayer->play(request);
        /*connect(this, &MySongs::audioRead, this, [this,audioPlayer](int trackId){
            if(mettaData.at(currentIndexTrackId).id == trackId){
                audioPlayer->play(getAudioBuffer(trackId));
            }
        });*/
    }else{
        audioPlayer->play(audioCache[trackId]);
    }

    AudioMetta metta;
    for(int i = 0; i < mettaData.size(); i++){
        if(mettaData.at(i).id == trackId){
            metta = mettaData[i];
            setCurrentIndexTrackId(i);
        }
    }

    emit trackChanged(trackId, metta.title, metta.artists.first().name);
}

void MySongs::playNextAudio(AudioPlayer *audioPlayer)
{
    audioPlayer->stop();
    if(currentIndexTrackId < 0){
        setCurrentIndexTrackId(0);
    }else{
        if(currentIndexTrackId + 1 >= mettaData.size()){
            setCurrentIndexTrackId(-1);
        }else{
            setCurrentIndexTrackId(currentIndexTrackId+1);

        }
    }

    if(currentIndexTrackId >= 0){
        playAudio(mettaData[currentIndexTrackId].id, audioPlayer);
    }

}

void MySongs::playPrevAudio(AudioPlayer *audioPlayer)
{
    audioPlayer->stop();
    if(currentIndexTrackId < 0){
        setCurrentIndexTrackId(0);
    }else{
        if(currentIndexTrackId - 1 < 0){
            setCurrentIndexTrackId(-1);
        }else{
            setCurrentIndexTrackId(currentIndexTrackId-1);
        }
    }

    if(currentIndexTrackId >= 0){
        playAudio(mettaData[currentIndexTrackId].id, audioPlayer);
    }
}

AudioMetta MySongs::findByTrackId(int trackId)
{
    AudioMetta metta;
    for(int i = 0; i < mettaData.size(); i++){
        if(mettaData.at(i).id == trackId){
            metta = mettaData[i];
        }
    }

    return metta;
}

MySongsImageProvider::MySongsImageProvider(QVector<AudioMetta> &metta):
    QQuickImageProvider(QQuickImageProvider::Image), metta(metta)
{

}

QImage MySongsImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    int img_id = id.toInt();
    QImage img;
    for (int i = 0; i < metta.size(); i++) {
        if(metta.at(i).id == img_id){
            img = QImage::fromData(QByteArray::fromBase64(metta.at(i).artwork));
            *size = img.size();
            img.scaled(requestedSize);
        }
    }
    return img;
}
