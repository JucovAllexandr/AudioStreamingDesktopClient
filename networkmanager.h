#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#define URL QString("http://45.132.107.112:8080/")

class NetworkManager : public QObject
{
    Q_OBJECT
    QNetworkAccessManager *networkManager;

public:
    explicit NetworkManager(QObject *parent = nullptr);
    void asyncLogin(QString email, QString pass);
    QString syncLogin(QString email, QString pass);
private:
    QString parseLogin();
signals:
    void onLoginRequest(QString secret);
};

#endif // NETWORKMANAGER_H
