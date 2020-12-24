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



#ifndef TWSCONN_H
#define TWSCONN_H

#include <QObject>
#include <QAbstractSocket>

class TWSConn : public QObject
{
    Q_OBJECT
public:
    explicit TWSConn(QObject *parent = nullptr);

signals:


private slots:

    void tmrInit();

    void connected();
    void disconnected();
    void error(QAbstractSocket::SocketError);



private:

    void doConnect();

};

#endif // TWSCONN_H
