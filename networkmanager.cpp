#include "networkmanager.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QEventLoop>

NetworkManager::NetworkManager(QObject *parent) : QObject(parent)
{
    networkManager = new QNetworkAccessManager(this);
}

bool NetworkManager::isHasError()
{
    return !error.isEmpty();
}

void NetworkManager::asyncLogin(QString email, QString pass)
{
    error.clear();

    QNetworkReply *reply = loginRequest(email, pass);

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        QString tmp = parseLogin(reply);
        emit onLoginRequest(tmp, error);
        reply->close();
        reply->deleteLater();
    } );
}

QString NetworkManager::syncLogin(QString email, QString pass)
{
    QString secret;
    error.clear();

    QNetworkReply *reply = loginRequest(email, pass);

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    secret = parseLogin(reply);

    reply->close();
    reply->deleteLater();

    return secret;
}

QNetworkReply *NetworkManager::loginRequest(QString email, QString pass)
{
    QNetworkRequest request;
    request.setUrl(QUrl(URL+"login"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonDocument doc;
    QJsonObject root;

    root["email"] = email;
    root["password"] = pass;

    doc.setObject(root);

    return networkManager->post(request, doc.toJson());
}

QNetworkReply *NetworkManager::audioRequest(QString secret, int trackId)
{
    QNetworkRequest request;
    request.setUrl(QUrl(URL+"audio/"+QString::number(trackId)));
    request.setRawHeader("authorization",secret.toUtf8());
    return networkManager->get(request);
}

void NetworkManager::asyncRegister(QString email, QString pass)
{
    error.clear();
    QNetworkReply *reply = registerRequest(email,pass);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        bool tmp = parseRegister(reply);
        emit onRegisterRequest(tmp, error);
        reply->close();
        reply->deleteLater();
    } );
}

bool NetworkManager::syncRegister(QString email, QString pass)
{
    bool status = false;
    error.clear();
    QNetworkReply *reply = registerRequest(email,pass);

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    status = parseRegister(reply);

    reply->close();
    reply->deleteLater();

    return status;
}

QNetworkReply *NetworkManager::registerRequest(QString email, QString pass)
{
    QNetworkRequest request;
    request.setUrl(QUrl(URL+"register"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonDocument doc;
    QJsonObject root;

    root["email"] = email;
    root["password"] = pass;

    doc.setObject(root);

    return networkManager->post(request, doc.toJson());
}

void NetworkManager::asyncSecretHello(QString secret)
{
    error.clear();
    QNetworkReply *reply = secretHelloRequest(secret);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        bool tmp = parseSecretHello(reply);
        emit onSecretHelloRequest(tmp, error);
        reply->close();
        reply->deleteLater();
    } );
}

bool NetworkManager::syncSecretHello(QString secret)
{
    bool status = false;
    error.clear();
    QNetworkReply *reply = secretHelloRequest(secret);

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    status = parseSecretHello(reply);

    reply->close();
    reply->deleteLater();

    return status;
}

QNetworkReply *NetworkManager::secretHelloRequest(QString secret)
{
    QNetworkRequest request;
    request.setUrl(QUrl(URL+"secret-hello"));
    request.setRawHeader("authorization",secret.toUtf8());
    return networkManager->get(request);
}

void NetworkManager::asyncGetAllAudio(QString secret)
{
    error.clear();
    QNetworkReply *reply = getAllAudioRequest(secret);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        QVector<AudioMetta> tmp = parseGetAllAudio(reply);
        emit onGetAllAudioRequest(tmp, error);
        reply->close();
        reply->deleteLater();
    } );
}

QVector<AudioMetta> NetworkManager::syncGetAllAudio(QString secret)
{
    QVector<AudioMetta> metta;
    error.clear();
    QNetworkReply *reply = getAllAudioRequest(secret);

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    metta = parseGetAllAudio(reply);

    reply->close();
    reply->deleteLater();

    return metta;
}

void NetworkManager::asyncAudio(QString secret, int trackId)
{
    error.clear();
    QNetworkReply *reply = audioRequest(secret, trackId);
    connect(reply, &QNetworkReply::finished, this, [this, reply, trackId]() {
        QByteArray *tmp = parseAudio(reply);
        emit onAudioRequest(trackId, tmp, error);
        reply->close();
        reply->deleteLater();
    } );
}

QNetworkReply *NetworkManager::getAllAudioRequest(QString secret)
{
    QNetworkRequest request;
    request.setUrl(QUrl(URL+"audio"));
    request.setRawHeader("authorization",secret.toUtf8());
    return networkManager->get(request);
}

QString NetworkManager::parseLogin(QNetworkReply *reply)
{
    QString secret;
    qDebug()<<reply->error();
    QByteArray array = reply->readAll();
    qDebug()<<array;

    QJsonDocument doc(QJsonDocument::fromJson(array));
    QJsonObject jobj = doc.object();

    int replyCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();


    switch (replyCode) {
    case 200: {
        secret = reply->rawHeader("authorization");
        qDebug()<<secret;

    }break;

    case 403: {
        if(jobj.contains("status")){
            if(jobj["status"].toInt() == 403)
            {
                error = tr("Authorisation failed: email or password incorrect");
            }
        }
    } break;

    default:
        error = reply->errorString();
        break;
    }

    return secret;
}

bool NetworkManager::parseRegister(QNetworkReply *reply){
    bool accepted = false;
    qDebug()<<reply->error();
    QByteArray array = reply->readAll();
    qDebug()<<array;

    QJsonDocument doc(QJsonDocument::fromJson(array));
    QJsonObject jobj = doc.object();

    int replyCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    switch (replyCode) {
    case 200: {
        accepted = true;
    }break;

    case 403: {
        if(jobj.contains("status")){
            if(jobj["status"].toInt() == 403)
            {
                error = tr("Registration failed: email already used or account already created");
            }
        }
    } break;

    default:
        error = reply->errorString();
        break;
    }

    return accepted;
}

bool NetworkManager::parseSecretHello(QNetworkReply *reply)
{
    bool status = false;
    int replyCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    switch (replyCode) {
    case 200:
        status = true;
        break;
    default:
        error = reply->errorString();
        break;
    }

    return status;
}

QVector<AudioMetta> NetworkManager::parseGetAllAudio(QNetworkReply *reply)
{
    QVector<AudioMetta> mettaData;
    qDebug()<<reply->error();
    QByteArray array = reply->readAll();
    //qDebug()<<array;

    QJsonDocument doc(QJsonDocument::fromJson(array));
    QJsonArray jarray = doc.array();

    int replyCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    switch (replyCode) {
    case 200:
    {
        for(auto jobj = jarray.begin(); jobj != jarray.end(); jobj++){
            AudioMetta metta;
            metta.id = QJsonValue(*jobj)["id"].toInt();
            metta.album = QJsonValue(*jobj)["album"].toString();
            metta.artwork = QJsonValue(*jobj)["artwork"].toVariant().toByteArray();
            metta.title = QJsonValue(*jobj)["title"].toString();
            metta.trackNr = QJsonValue(*jobj)["trackNr"].toString();
            metta.year = QJsonValue(*jobj)["year"].toString();
            QJsonArray artists = QJsonValue(*jobj)["artists"].toArray();

            for(auto artist = artists.begin(); artist != artists.end(); artist++){
                AudioMettaTuple tuple;
                tuple.id = QJsonValue(*artist)["id"].toInt();
                tuple.name = QJsonValue(*artist)["name"].toString();
                metta.artists.push_back(tuple);
            }

            QJsonArray genres = QJsonValue(*jobj)["genres"].toArray();

            for(auto genre = genres.begin(); genre != genres.end(); genre++){
                AudioMettaTuple tuple;
                tuple.id = QJsonValue(*genre)["id"].toInt();
                tuple.name = QJsonValue(*genre)["name"].toString();
                metta.genres.push_back(tuple);
            }
            mettaData.push_back(metta);
        }
    }
        break;
    default:
        error = reply->errorString();
        break;
    }

    return mettaData;
}

QByteArray *NetworkManager::parseAudio(QNetworkReply *reply)
{
    qDebug()<<reply->error();
    QByteArray *array = new QByteArray();

    int replyCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    switch (replyCode) {
    case 200:
            *array = reply->readAll();
        break;
    default:
        error = reply->errorString();
        break;
    }

    return array;
}
