#ifndef AUTH_H
#define AUTH_H

#include <QObject>
#include <networkmanager.h>
//#include <qqml.h>

#define URL QString("http://45.132.107.112:8080/")

class Auth : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY onEmailChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY onPasswordChanged)
    Q_PROPERTY(bool authenticated READ isAuthenticated WRITE setAuthenticated NOTIFY authenticatedChanged)
    //Q_PROPERTY(QString signInError READ signInError WRITE setSignInError NOTIFY onSignInFailed)
    //QML_ELEMENT

    QString _email;
    QString _password;
    QString secret;
    bool authenticated = false;

public:
    explicit Auth(NetworkManager *net_manager, QObject *parent = nullptr);
    Q_INVOKABLE void signIn();
    Q_INVOKABLE void createAccount();
    QString email();
    void setEmail(const QString &email);
    QString password();
    void setPassword(const QString &pass);
    bool checkSecret(const QByteArray &secret);
    bool isAuthenticated();
    QString getSecret();
    void setAuthenticated(bool val);

private:
    NetworkManager *networkManager;
private slots:
    void loginRequestReceived(QString secret, QString error);
    void registerRequestReceived(bool status, QString error);
    /*void secretHelloRequestReceived(bool status, QString error);
    void getAllAudioRequestReceived(AudioMetta metta, QString error);*/

signals:
    void onEmailChanged();
    void onPasswordChanged();
    void accountCreated();
    void signInSuccessed();
    void signInFailed(QString error);
    void createAccountFailed(QString error);
    void authenticatedChanged();
};

#endif // AUTH_H
