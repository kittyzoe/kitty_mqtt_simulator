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



#ifndef TMQTTFEEDBACKWND_H
#define TMQTTFEEDBACKWND_H


#include <qmqtt.h>
#include <QWidget>

QT_FORWARD_DECLARE_CLASS(QTextEdit)

class TMqttFeedbackWnd : public QWidget
{
    Q_OBJECT
public:
    explicit TMqttFeedbackWnd(const QString &svrname,
                              quint16 svrPort,
                              const QString &uname,
                              const QString &pwd,
                              const QString &topic,
                              QWidget *parent = 0);
    ~TMqttFeedbackWnd();

signals:


    void logThiz(const QString &);

public slots:

protected:
    void closeEvent(QCloseEvent *) Q_DECL_OVERRIDE;

private slots:
    void tmrInit();


    void onMqttConnected();
    void onMqttDisconnected();
    void onSubscribed(const QString & );
    void onSubsReceived(const QMQTT::Message &);
    //
  //  onMqttError(QMQTT::ClientError);

    void tmrFired();


    void teAppendLog(const QString &l);

private:
    void setupUI();




    QTextEdit *remoteMsgTe;



    QMQTT::Client *mSubscriber;

    QString mUsrname;
    QString mPasswd;
    QString mSvrName;
    quint16 mSvrPort;
    QString mToptic;




};

#endif // TMQTTFEEDBACKWND_H
