#include "networkmanager.h"
#include <QJsonDocument>
#include <QJsonObject>
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
        emit onLoginRequest(parseLogin(reply), error);
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
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::exit);
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

void NetworkManager::asyncRegister(QString email, QString pass)
{
    error.clear();
    QNetworkReply *reply = registerRequest(email,pass);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        emit onRegisterRequest(parseRegister(reply), error);
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
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::exit);
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

    return false;
}
