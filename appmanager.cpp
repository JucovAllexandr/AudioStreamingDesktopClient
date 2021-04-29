#include "appmanager.h"
#include <QQmlContext>

AppManager::AppManager(QQmlApplicationEngine &engine, QObject *parent) : QObject(parent), engine(engine)
{
    networkManager = new NetworkManager(this);
    _auth = new Auth(networkManager, this);
    audioPlayer = new AudioPlayer(this);
    connect(_auth, &Auth::authenticatedChanged, this, &AppManager::initMySongs);
    engine.rootContext()->setContextProperty("AudioPlayer", audioPlayer);
    connect(audioPlayer, &AudioPlayer::endOfAudio, this, [this](){
        mySongs->playNextAudio(audioPlayer);
    });
}

/*void AppManager::setEngine(QQmlApplicationEngine *engine)
{
    this->engine = engine;
    engine->rootContext()->setContextProperty("AudioPlayer", audioPlayer);
}*/

Auth *AppManager::auth(){
    return _auth;
}

void AppManager::connectMySongs()
{
    QObject* songs_object = engine.rootObjects().first()->findChild<QObject*>("MySongsObject");
    QObject::connect(songs_object, SIGNAL(clicked()), this, SLOT(onMySongsClicked()));
}

void AppManager::playMySong(int trackId)
{
    qDebug()<<"playMySong id"<<trackId;
    mySongs->playAudio(trackId, audioPlayer);

}

void AppManager::playNextSong()
{
    mySongs->playNextAudio(audioPlayer);
}

void AppManager::playPrevSong()
{
    mySongs->playPrevAudio(audioPlayer);
}

void AppManager::onMySongsClicked()
{
    mySongs->getSongs();
}

void AppManager::initMySongs()
{
    if(_auth->isAuthenticated()){
        if(mySongs == NULL){
            mySongs = new MySongs(this);
            mySongs->setAuth(_auth);
            mySongs->setNetworkManager(networkManager);
            engine.rootContext()->setContextProperty("MySongsModel", mySongs->songsModel());
            engine.rootContext()->setContextProperty("MySongs", mySongs);
            engine.addImageProvider(QLatin1String("MySongsImageProvider"), mySongs->mySongsImageProvider());
        }
        else{

        }
    }
}
