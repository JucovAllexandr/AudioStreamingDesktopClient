#ifndef MYSONGS_H
#define MYSONGS_H

#include <QObject>
#include <mysongsmodel.h>
#include "auth.h"
#include <QNetworkAccessManager>
#include <QMediaPlayer>

class MySongs : public QObject
{
    Q_OBJECT
    Auth *auth = NULL;

public:
    explicit MySongs(QObject *parent = nullptr);
    void loadMP3(QString path);
    void getSongs();
    void setAuth(Auth *auth);
signals:

};

#endif // MYSONGS_H
