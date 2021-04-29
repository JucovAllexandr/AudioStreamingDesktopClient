#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QEventLoop>
#include "auth.h"
#include <QDebug>

Auth::Auth(NetworkManager *net_manager, QObject *parent) : QObject(parent)
{
    networkManager = net_manager;
    connect(networkManager, &NetworkManager::onLoginRequest, this, &Auth::loginRequestReceived);
    connect(networkManager, &NetworkManager::onRegisterRequest, this, &Auth::registerRequestReceived);
}

void Auth::signIn()
{
    networkManager->asyncLogin(_email, _password);
}

void Auth::createAccount()
{
   networkManager->asyncRegister(_email, _password);
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
    return networkManager->syncSecretHello(secret);
}

bool Auth::isAuthenticated()
{
    return authenticated;
}

QString Auth::getSecret()
{
    return secret;
}

void Auth::setAuthenticated(bool val)
{
    authenticated = val;
    emit authenticatedChanged();
}

void Auth::loginRequestReceived(QString secret, QString error)
{
    if(error.isEmpty()){
        this->secret = secret;
        if(networkManager->syncSecretHello(secret)){
            setAuthenticated(true);
            emit signInSuccessed();
        }else{
            emit signInFailed(tr("Secret error"));
        }
    }
    else{
        emit signInFailed(error);
    }
}

void Auth::registerRequestReceived(bool status, QString error)
{
    if(error.isEmpty()){
        if(status){
            emit accountCreated();
        }
        else{
            emit createAccountFailed(tr("Error account creation"));
        }
    }else {
        emit createAccountFailed(error);
    }
}

