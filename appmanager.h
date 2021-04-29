#ifndef APPMANAGER_H
#define APPMANAGER_H

#include <QObject>
#include <networkmanager.h>
#include <auth.h>
#include <mysongs.h>
#include <QQmlApplicationEngine>
#include <audioplayer.h>
class AppManager : public QObject
{
    Q_OBJECT

    NetworkManager *networkManager = NULL;
    Auth *_auth = NULL;
    MySongs *mySongs = NULL;
    QQmlApplicationEngine &engine;
    AudioPlayer *audioPlayer;
public:
    explicit AppManager(QQmlApplicationEngine &engine, QObject *parent = nullptr);
    //void setEngine(QQmlApplicationEngine *engine);
    Auth *auth();
    Q_INVOKABLE void connectMySongs();
    Q_INVOKABLE void playMySong(int trackId);
    Q_INVOKABLE void playNextSong();
    Q_INVOKABLE void playPrevSong();
public slots:
    void onMySongsClicked();
private slots:
    void initMySongs();
signals:

};

#endif // APPMANAGER_H
