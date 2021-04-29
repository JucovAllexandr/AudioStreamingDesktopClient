#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#define URL QString("http://45.132.107.112:8080/")

struct AudioMettaTuple{
    int id;
    QString name;
};

struct AudioMetta{
    int id;
    QString title;
    QString album;
    QString trackNr;
    QString year;

    QVector<AudioMettaTuple> artists;
    QVector<AudioMettaTuple> genres;

    QByteArray artwork;
};

class NetworkManager : public QObject
{
    Q_OBJECT
    QNetworkAccessManager *networkManager;
    QString error;

public:
    explicit NetworkManager(QObject *parent = nullptr);
    bool isHasError();

    void asyncLogin(QString email, QString pass);
    QString syncLogin(QString email, QString pass);

    void asyncRegister(QString email, QString pass);
    bool syncRegister(QString email, QString pass);

    void asyncSecretHello(QString secret);
    bool syncSecretHello(QString secret);

    void asyncGetAllAudio(QString secret);
    QVector<AudioMetta> syncGetAllAudio(QString secret);

    void asyncAudio(QString secret, int trackId);
    QNetworkReply *audioRequest(QString secret, int trackId);
private:
    QNetworkReply *getAllAudioRequest(QString secret);
    QNetworkReply *secretHelloRequest(QString secret);
    QNetworkReply *registerRequest(QString email, QString pass);
    QNetworkReply *loginRequest(QString email, QString pass);

    QString parseLogin(QNetworkReply *reply);
    bool parseRegister(QNetworkReply *reply);
    bool parseSecretHello(QNetworkReply *reply);
    QVector<AudioMetta> parseGetAllAudio(QNetworkReply *reply);
    QByteArray *parseAudio(QNetworkReply *reply);

signals:
    void onLoginRequest(QString secret, QString error);
    void onRegisterRequest(bool status, QString error);
    void onSecretHelloRequest(bool status, QString error);
    void onGetAllAudioRequest(QVector<AudioMetta> metta, QString error);
    void onAudioRequest(int trackId, QByteArray *buffer, QString error);
};

#endif // NETWORKMANAGER_H
