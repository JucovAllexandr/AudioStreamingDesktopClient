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

MySongs::MySongs(QObject *parent) : QObject(parent)
{

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

void MySongs::getSongs()
{
    if(auth != NULL){
        if(auth->isAuthenticated()){
            QNetworkRequest request(QUrl(URL+"audio"));
            QNetworkReply *reply = auth->getNetworkManager()->get(request);
        }
    }
}

void MySongs::setAuth(Auth *auth)
{
    this->auth = auth;
}
