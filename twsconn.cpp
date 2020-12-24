/**************************************************************************
**   Copyright @ 2014 TOOTzoe.com
**   Special keywords: zoe 7/5/2020 2020
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


#include <QtWebSockets/QtWebSockets>
#include <QDebug>

#include "twsconn.h"

TWSConn::TWSConn(QObject *parent) : QObject(parent)
{


    QTimer::singleShot(0,this, SLOT(tmrInit()));
}



void TWSConn::tmrInit()
{
    doConnect();
}

void TWSConn::doConnect()
{

    QWebSocket *mWebSocket = new QWebSocket();
    connect(mWebSocket, SIGNAL(connected()), this, SLOT(connected()));
    connect(mWebSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(mWebSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));

    QString username = "testmqtt_langrensha";
    QString passwd = "ErZDb07XXfZMlk7";

    QString passkey = username + ":" + passwd;
    QByteArray passDat = passkey.toLocal8Bit().toBase64();
    QString heaserDat = "Basic " + passDat;

////    example for set http request.........tootzoe, DON'T Delete
    QNetworkRequest lRequest(QUrl("ws://testemqx.langrensha.game/ws/"));
    lRequest.setRawHeader("Predix-Zone-Id", "langrensha-tootzoe-id");
    lRequest.setRawHeader("Content-Type", "application/json");
    lRequest.setRawHeader("Authorization", heaserDat.toLocal8Bit());
    lRequest.setRawHeader("Access-Control-Allow-Origin", "*");
   // lRequest.setRawHeader("Content-Length", postDataSize);

    mWebSocket->open(lRequest);
}


void TWSConn::connected()
{
    qDebug() << __func__;




}

void TWSConn::disconnected()
{
    qDebug() << __func__;

}


void TWSConn::error(QAbstractSocket::SocketError err)
{
    qDebug() << __func__ << "  err: " << err ;

}





