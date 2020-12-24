/**************************************************************************
**   Copyright @ 2014 TOOTzoe.com
**   Special keywords:  2020 2020
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

#include <QtWidgets>

#include "tmqttfeedbackwnd.h"

TMqttFeedbackWnd::TMqttFeedbackWnd(const QString &svrname,
                                   quint16 svrPort,
                                   const QString &uname,
                                   const QString &pwd,
                                   const QString &topic,
                                   QWidget *parent)
    : QWidget(parent)
    ,mSvrName(svrname)
    ,mSvrPort(svrPort)
    ,mUsrname(uname)
    ,mPasswd(pwd)
    ,mToptic(topic)
{

    setWindowTitle(tr("远端服务器信息"));
    setupUI();
    resize(800,600);

    QTimer::singleShot(500,this, SLOT(tmrInit()));
}

TMqttFeedbackWnd::~TMqttFeedbackWnd()
{
    mSubscriber->disconnectFromHost();
    qDebug() << __func__;
}

void TMqttFeedbackWnd::closeEvent(QCloseEvent *)
{
    deleteLater();
}

void TMqttFeedbackWnd::setupUI()
{
    QVBoxLayout *mainLO = new QVBoxLayout;

     remoteMsgTe = new QTextEdit;
     remoteMsgTe->setReadOnly(true);
    mainLO ->addWidget( remoteMsgTe);


    setLayout(mainLO);
}

void TMqttFeedbackWnd::tmrInit()
{

    mSubscriber = new QMQTT::Client(  );

    mSubscriber->setHostName(mSvrName);
    mSubscriber->setPort(mSvrPort);
    mSubscriber->setUsername(mUsrname );
    mSubscriber->setPassword(mPasswd.toUtf8());


     mSubscriber->setKeepAlive(30);
    mSubscriber->setCleanSession(true);

    connect(mSubscriber, SIGNAL(connected()), SLOT(onMqttConnected()));
    connect(mSubscriber, SIGNAL(disconnected()), SLOT(onMqttDisconnected()));
    connect(mSubscriber, SIGNAL(subscribed(QString)), SLOT(onSubscribed(QString )));
    connect(mSubscriber, &QMQTT::Client::received, this, &TMqttFeedbackWnd::onSubsReceived);
   // connect(mSubscriber, SIGNAL(error(QMQTT::ClientError)), SLOT(onMqttError(QMQTT::ClientError)));


    mSubscriber->connectToHost();

    qDebug() << "mSvrName:" <<mSvrName
            << "mSvrPort:" << mSvrPort
            << "mUsrname:" << mUsrname
            << "mPasswd:" << mPasswd
                ;

    connect(this, SIGNAL(logThiz(QString)), SLOT(teAppendLog(QString)));


    QTimer *myTmr = new QTimer(this);
    myTmr->setInterval(1000);
    connect(myTmr,&QTimer::timeout , this,  &TMqttFeedbackWnd::tmrFired);
    myTmr->start();

}

void TMqttFeedbackWnd::onMqttConnected()
{
    emit logThiz(" >>>>>>>>>>>>>>>>>> Mqtt Connnected.........");

    mSubscriber->subscribed(mToptic , 2);



}

void TMqttFeedbackWnd::onMqttDisconnected()
{
    emit logThiz(" >>>>>>>>>>>>>>>>>> Mqtt Disconnected.........");
}

void TMqttFeedbackWnd::onSubscribed(const QString &t )
{
    emit logThiz("Subscribed :  " + t  + " ........ ");
}

void TMqttFeedbackWnd::onSubsReceived(const QMQTT::Message &msg)
{
    QString msgStr = QString::fromUtf8(msg.payload());

    qDebug() << " got msg: " << msgStr;

    emit logThiz("got msg:  " + msgStr);
}

void TMqttFeedbackWnd::tmrFired()
{
    static int hzf =1;
    qDebug() << __func__ << hzf++;
}

void TMqttFeedbackWnd::teAppendLog(const QString &l)
{
    remoteMsgTe->append(tr("%1: %2")
                            .arg(QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss"))
                            .arg(l)
                            );
}



