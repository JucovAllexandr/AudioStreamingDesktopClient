#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QEventLoop>
#include "auth.h"
#include <QDebug>

Auth::Auth(QObject *parent) : QObject(parent)
{
    networkManager = new QNetworkAccessManager(this);
}

void Auth::signIn()
{
    QNetworkRequest request;
    request.setUrl(QUrl(URL+"login"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonDocument doc;
    QJsonObject root;

    root["email"] = _email;
    root["password"] = _password;

    doc.setObject(root);

    QNetworkReply *reply = networkManager->post(request, doc.toJson());

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        qDebug()<<reply->error();
        QByteArray array = reply->readAll();
        qDebug()<<array;

        QJsonDocument doc(QJsonDocument::fromJson(array));
        QJsonObject jobj = doc.object();

        int replyCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();


        switch (replyCode) {
        case 200: {
            QByteArray signInSecret = reply->rawHeader("authorization");
            qDebug()<<signInSecret;
            if(checkSecret(signInSecret)){
                qDebug()<<"true secret";
                secret = signInSecret;
                emit signInSuccessed();
                setAuthenticated(true);
            }else
            {
                qDebug()<<"false secret";
                emit signInFailed(tr("Authorisation failed"));
            }

        }break;

        case 403: {
            if(jobj.contains("status")){
                if(jobj["status"].toInt() == 403)
                {
                    emit signInFailed(tr("Authorisation failed: email or password incorrect"));
                }
            }
        } break;

        default:
            emit signInFailed(tr("Authorisation failed"));
            break;
        }

        reply->close();
        reply->deleteLater();
    } );
}

void Auth::createAccount()
{
    QNetworkRequest request;
    request.setUrl(QUrl(URL+"register"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonDocument doc;
    QJsonObject root;

    root["email"] = _email;
    root["password"] = _password;

    doc.setObject(root);

    QNetworkReply *reply = networkManager->post(request, doc.toJson());

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        qDebug()<<reply->error();
        QByteArray array = reply->readAll();
        qDebug()<<array;

        QJsonDocument doc(QJsonDocument::fromJson(array));
        QJsonObject jobj = doc.object();

        int replyCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

        switch (replyCode) {
        case 200: {
            emit accountCreated();
        }break;

        case 403: {
            if(jobj.contains("status")){
                if(jobj["status"].toInt() == 403)
                {
                    emit createAccountFailed(tr("Registration failed: email already used or account already created"));
                }
            }
        } break;

        default:
            emit createAccountFailed(tr("Registration failed"));
            break;
        }


        reply->close();
        reply->deleteLater();
    } );
}

QString Auth::email()
{
    return _email;
}

void Auth::setEmail(const QString &email)
{
    _email = email;
    emit onEmailChanged();
}

QString Auth::password()
{
    return _password;
}

void Auth::setPassword(const QString &pass)
{
    _password = pass;
    emit onPasswordChanged();
}

bool Auth::checkSecret(const QByteArray &secret)
{
    QNetworkRequest request;
    request.setUrl(QUrl(URL+"secret-hello"));
    request.setRawHeader("authorization",secret);
    QNetworkReply *reply = networkManager->get(request);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    int replyCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    reply->deleteLater();

    return ((replyCode == 200) ? true : false);
}

bool Auth::isAuthenticated()
{
    return authenticated;
}

void Auth::setAuthenticated(bool val)
{
    authenticated = val;
    emit authenticatedChanged();
}

QNetworkAccessManager *Auth::getNetworkManager()
{
    return networkManager;
}
