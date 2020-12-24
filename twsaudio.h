/**************************************************************************
**   Copyright @ 2014 TOOTzoe.com
**   Special keywords: zoe 3/8/2020 2020
**   Environment variables:
**
**
**
**   E-mail : toot@tootzeo.com
**   Tel    : 13802205042
**   Website: http://www.tootzoe.com
**
**************************************************************************/



#ifdef Q_CC_MSVC
#pragma execution_character_set("UTF-8")
#endif


//------------------------------------------------------------------------



#ifndef TWSAUDIO_H
#define TWSAUDIO_H

#include <QObject>
#include <QAbstractSocket>
#include <QtNetwork/QSslError>

class QWebSocket;

class TWsAudio : public QObject
{
    Q_OBJECT
public:
    explicit TWsAudio(QObject *parent = nullptr);

signals:


private Q_SLOTS:
    void onConnected();
    void onDisconnect();
    void onTextMessageReceived(const QString &message);
    void onBinaryMessageReceived(const QByteArray &ba);

    void wsError(QAbstractSocket::SocketError error);
    void onSslErrors(const QList<QSslError> &errors);


private:


    QWebSocket *myWs;





};

#endif // TWSAUDIO_H
