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



#ifndef TMAINWND_H
#define TMAINWND_H


#include <qmqtt.h>
#include <QWidget>


QT_FORWARD_DECLARE_CLASS(QVBoxLayout)


class TMainWnd : public QWidget
{
    Q_OBJECT
public:
    explicit TMainWnd(QWidget *parent = 0);
    ~TMainWnd();

signals:

    void logThiz(const QString &);

    void checkUnCheckAllHeaderlamp(bool);
    void checkUnCheckAllDesklamp(bool);
    void checkUnCheckAllAmbientlamp(bool);
    //
    void uncheckSomeBtns(bool);

public slots:


private slots:

    void connBtnClick(bool);
    void headlampBtnClick(int,bool);
     void motorBtnClick(int,bool);

    void tmrInitFunc();

    void onMqttTcpConnected();
    void onMqttTcpDisconnected();
    void onMqttTcpError(QMQTT::ClientError);
    void onMqttTcpSubscibed(const QString &t, const quint8 qos);
    void onMqttTcpUnsubscibed(const QString &t );
    void onMqttTcpPublished(const QMQTT::Message &m, quint16 mid);
    void onMqttTcpRecived(const QMQTT::Message &m );
    void onMqttTcpPingResp();


    //
    void onMqttTlsConnected();
    void onMqttTlsDisconnected();
    void onMqttTlsError(QMQTT::ClientError);
    //
    void onMqttWsConnected();
    void onMqttWsDisconnected();
    void onMqttWsError(QMQTT::ClientError);
    //
    void onMqttWssConnected();
    void onMqttWssDisconnected();
    void onMqttWssError(QMQTT::ClientError);
    //
    void doSendNow();
    void testQuickSend();

    void rfLedIdCbChged(int);
    void camAddrCbChged(int);
    void camCbChged(int);
    void camSleepClick(bool);
    void mp3CbChged(const QString &);
    void mp3StopCbChged(const QString &);
    void mp3VolumeChged(const QString &);
    void switchHpSkpBtnClick(bool);
    void showPlaylistWnd();
    void playlistStrLsArrived(const QStringList &);
    void stopCurrPlayingList();
    void viscaLeTxtChged(const QString &);
    void viscaLeReturnPressed( );

    void handleHeadlampChged(quint8 idx, quint8 crB, quint8 br);
    void handleDesklampChged(quint8 n,quint8 crB , quint8 br);
    void handleAmbientChged(quint8 n,quint8 crB , quint8 br);
    //
    void wifiBtnClick(int);
    void reEnableWifiBtns();
    //
    void resetartBtnClick();
    void allLampCtlBtnClick(bool isD);
    void miscCmdToBoard();
    //
    void resetCameraClick();

    //
    void setRfLedidBtnClick();

    //
    void showFeedbackWnd();


    void teAppendLog(const QString &l);

private:


    void initData();


    void setupUi();

    void setupMqttSetupLO(QVBoxLayout *);

    void setupLedLightLO(QVBoxLayout *);
    void setupkeyBtnLO(QVBoxLayout *);   
    void setupMotorCtrlLO(QVBoxLayout *);
    void setupInfoPanelLO(QVBoxLayout *);
    //
    void setupTcpConn(bool isC);
    void setupTlsConn(bool isC);
    void setupWsConn(bool isC);
    void setupWssConn(bool isC);
    //
    QWidget * setupMqttTcpWid();
    QWidget * setupMqttTlsWid();
    QWidget * setupMqttWsWid();
    QWidget * setupMqttWssWid();
    //
    void cameraGetReadySent();



     ////////////////////////////////////////
     class PrivateData;
     PrivateData *_d;
     TMainWnd::PrivateData *fetchPrivateData() const;





};

#endif // TMAINWND_H
