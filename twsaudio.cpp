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


#include <QtCore>

#include <QWebSocket>


#include "twsaudio.h"

TWsAudio::TWsAudio(QObject *parent) : QObject(parent)
{

    myWs = new QWebSocket;

    connect(myWs, &QWebSocket::connected, this, &TWsAudio::onConnected);
    connect(myWs, &QWebSocket::disconnected, this, &TWsAudio::onDisconnect);
    connect(myWs, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(wsError(QAbstractSocket::SocketError)));

    connect( myWs, QOverload<const QList<QSslError>&>::of(&QWebSocket::sslErrors),
            this, &TWsAudio::onSslErrors);


   // myWs->open(QUrl(QStringLiteral("ws://192.168.11.178:8888"))) ;

   // myWs->open(QUrl(QStringLiteral("ws://wss1.langrensha.game:9595"))) ;

    qDebug() << " ws open.......";

    myWs->open(QUrl(QStringLiteral("ws://192.168.10.149:9595?token=2"))) ;




}

void TWsAudio::wsError(QAbstractSocket::SocketError e)
{
    qDebug() << e;
}

void TWsAudio::onSslErrors(const QList<QSslError> &errors)
{
    qDebug() << errors;

    // WARNING: Never ignore SSL errors in production code.
    // The proper way to handle self-signed certificates is to add a custom root
    // to the CA store.

    myWs->ignoreSslErrors();
}

void TWsAudio::onConnected()
{
    qDebug() << __func__;

    connect(myWs, &QWebSocket::textMessageReceived,
            this, &TWsAudio::onTextMessageReceived);

    connect(myWs, &QWebSocket::binaryMessageReceived,
            this, &TWsAudio::onBinaryMessageReceived);



  //  myWs  ->sendTextMessage(QStringLiteral("Hello, world!"));
}

void TWsAudio::onDisconnect()
{
    qDebug() <<     myWs->errorString();
    qDebug() << myWs->closeReason();
    qDebug() << myWs->closeCode();
    qDebug() << __func__;
}

void TWsAudio::onTextMessageReceived(const QString &str)
{
    qDebug() << "Txt msg arrived: " << str;
}


static QByteArray pcmBa;


void TWsAudio::onBinaryMessageReceived(const QByteArray &ba)
{
    //qDebug() << "ba msg arrived: " << ba.toHex();


#if 0
    static bool isOk = false;


    if(isOk ) return;


    if (pcmBa.size() > 640 * 1000) {
            isOk = true;

            QFile pcmFile("pcmRaw.raw");
            if(pcmFile.open(QIODevice::WriteOnly))
            {
                pcmFile.write(pcmBa);
            }
    }

    pcmBa.append(ba);

#endif
    qDebug() << "ba size: " << ba.size()  ;

}


// play -t raw -r 32k -e signed -b 16 -c 1 pcmRaw.pcm










