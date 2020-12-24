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
#include <QtNetwork>
#include <QWebSocket>

#include "tmainwnd.h"
#include "tlampbasicwid.h"
#include "tmqttfeedbackwnd.h"
#include "twsconn.h"
#include "tplaylistwnd.h"



class TMainWnd::PrivateData{
public:

    QLineEdit *mqttTcpSvrLe;
    QLineEdit *mqttTlsSvrLe;
    QLineEdit *mqttWsSvrLe;
    QLineEdit *mqttWssSvrLe;

    QLineEdit *mqttTcpPortLe;
    QLineEdit *mqttTlsPortLe;
    //


    QLineEdit *mqttUsernameLe;
    QLineEdit *mqttPasswdLe;
    QLineEdit *mqttTopicLe;
    //
    QLineEdit *wifiSsidLe;
    QLineEdit *wifiPasswdLe;
    QLineEdit *boardNumLe;

    QComboBox *delayCb;


    QStringList mp3NameStrLs;
    QLineEdit *mp3RepeatLe;
    QStringList mCrNameLs;

    //
    QLineEdit *resultStrLe;
    QTextEdit *remoteMsgTe;
    //
    QLineEdit *viscaCmdLe;
    //
   QButtonGroup*  wifiBtnsGp;
   //
   QTabWidget *tabWid;


    quint8 cameraNum;
    quint8 cameraPreset;

    quint8 rfLedIdNum;
    quint8 audioVol;

    QMQTT::Client *mqttTcpPublisher;
    QMQTT::Client *mqttTlsPublisher;
    QMQTT::Client *mqttWsPublisher;
    QMQTT::Client *mqttWssPublisher;

    bool isDiscardBtnEvt;
};



quint32 fetchTs(){
    return (quint32)(QDateTime::currentDateTime().toMSecsSinceEpoch() % 10000000000);
}


TMainWnd::TMainWnd(QWidget *parent) : QWidget(parent)
,_d(new PrivateData)
{

    initData();
    setupUi();

    resize(1200 , 700);

    qDebug() << QDateTime::fromSecsSinceEpoch(1595492042);

}

TMainWnd::~TMainWnd()
{
    delete _d;
}


void TMainWnd::initData()
{

    _d->cameraNum = 1;
    _d->rfLedIdNum = 1;
    _d->cameraPreset =0;
    _d->audioVol = 60;
    _d->isDiscardBtnEvt =false;

   _d->mqttTcpPublisher = nullptr;
   _d->mqttTlsPublisher= nullptr;
    _d->mqttWsPublisher= nullptr;
    _d->mqttWssPublisher= nullptr;



    _d->mCrNameLs << "black"
                  <<   "red" << "green" << "yellow"
                  <<   "blue" << "purple" << "cyan"
                  << "white"
                     ;
#if 1
    _d->mp3NameStrLs     
    << "321"
    << "all_ready"
    << "aowu"
    << "bang"
    << "boom"
    << "cong"
    << "day"
    << "daybg1"
    << "die1"
    << "die2"
    << "die3"
    << "die4"
    << "ding"
    << "gameover1"
    << "gameover2"
    << "gameover3"
    << "gameover4"
    << "gameover5"
    << "identity"
    << "jxl0"
    << "jxl1"
    << "jxl2"
    << "lastnight"
    << "ll0"
    << "ll1"
    << "ll2"
    << "ll3"
    << "lmr0"
    << "lmr1"
    << "makesure"
    << "mss0"
    << "mss1"
    << "night"
    << "nightbg1"
    << "nightbg2"
    << "num1"
    << "num2"
    << "num3"
    << "num4"
    << "num5"
    << "num6"
    << "num7"
    << "num8"
    << "num9"
    << "num10"
    << "num11"
    << "num12"
    << "num13"
    << "num14"
    << "num15"
    << "num16"
    << "nw0"
    << "nw1"
    << "operate"
    << "pk"
    << "policebroken"
    << "policechange"
    << "policelose"
    << "policenohave"
    << "policeorder"
    << "policeorderleft"
    << "policeorderright"
    << "policequit"
    << "policestart"
    << "policesucc"
    << "qbt0"
    << "qbt1"
    << "ready"
    << "ready1"
    << "safeday"
    << "safenight"
    << "smr0"
    << "smr1"
    << "speak"
    << "speakasc"
    << "speakdesc"
    << "speakfinish"
    << "speaklastword"
    << "speaklastword1"
    << "speaklastwordnohave"
    << "speaklimittime"
    << "speakstop"
    << "speakstop1"
    << "speakstop3"
    << "start"
    << "sw0"
    << "sw1"
    << "sxg0"
    << "sxg1"
    << "tls0"
    << "tls1"
    << "votes"
    << "waitskill"
    << "yyj0"
    << "yyj1"
    << "test"
    ;
#else
    _d->mp3NameStrLs
            << "1"
            << "10"
            << "11"
            << "12"
            << "13"
            << "14"
            << "15"
            << "16"
            << "2"
            << "3"
            << "4"
            << "5"
            << "6"
            << "7"
            << "8"
            << "9"
            << "B-M-ApostleAction"
            << "B-M-ApostleSleep"
            << "B-M-ApostleWakeUp"
            << "BadManTransfiguration"
            << "BanishResult"
            << "BlackWolfAction"
            << "BlackWolfCV"
            << "BlackWolfSkillVoice"
            << "BlackWolfSleep"
            << "BlackWolfWakeUp"
            << "BloodMoonApostleCV"
            << "Chief-Campaign"
            << "Chief-Speak"
            << "ChiefConclude"
            << "ChiefElection"
            << "ChiefLeft"
            << "ChiefOrderSpeak"
            << "ChiefRight"
            << "ChiefTransfer"
            << "CountDown"
            << "D-HunterAction"
            << "D-HunterSkillVoice"
            << "D-HunterSleep"
            << "D-HunterWakeUp"
            << "DemonHunterCV"
            << "GameStart"
            << "GargoyleAction"
            << "GargoyleCV"
            << "GargoyleSleep"
            << "GargoyleWakeUp"
            << "GetShotVoice"
            << "GoodManTransfiguration"
            << "GoodManwin"
            << "GuardAction"
            << "GuardCV"
            << "GuardSkillVoice"
            << "GuardSleep"
            << "GuardWakeUp"
            << "HunterAction"
            << "HunterCV"
            << "HunterSkillVoice"
            << "HunterSleep"
            << "HunterWakeUp"
            << "IdiotAction"
            << "IdiotCV"
            << "IdiotSleep"
            << "IdiotWakeUp"
            << "KilledResult"
            << "KilledVoice"
            << "KnightAction"
            << "KnightCV"
            << "KnightSkillVoice"
            << "KnightSleep"
            << "KnightWakeUp"
            << "LossChief"
            << "M-WolfAction"
            << "M-WolfMechanical_Wolf"
            << "M-WolfSleep"
            << "MartyrdomVoice"
            << "MechanicalWolfCV"
            << "NightComming"
            << "NightMusic"
            << "Num1"
            << "Num10"
            << "Num11"
            << "Num12"
            << "Num13"
            << "Num14"
            << "Num15"
            << "Num16"
            << "Num2"
            << "Num3"
            << "Num4"
            << "Num5"
            << "Num6"
            << "Num7"
            << "Num8"
            << "Num9"
            << "NumX-BeBanished"
            << "NumX-BeKilled"
            << "NumX-ChiefElection"
            << "NumX-LastWords"
            << "NumX-LaunchSkill"
            << "NumX-QuitChief"
            << "NumX-SelfExplosion"
            << "NumX-Speak"
            << "NumXOutGameOver"
            << "PhychicAction"
            << "PhychicSleep"
            << "PhychicWakeUp"
            << "Prophet-PsychicSkillVoice"
            << "ProphetAction"
            << "ProphetCV"
            << "ProphetSleep"
            << "ProphetWakeUp"
            << "PsychicCV"
            << "QuitChief"
            << "RelaxMusic"
            << "RipChief"
            << "SafeNight"
            << "SelfExplosion"
            << "SkipSpeak"
            << "SpeakOrder-"
            << "T-KeeperAction"
            << "T-KeeperSleep"
            << "T-KeeperWakeUp"
            << "TimeAlarmVoice"
            << "TombKeeperCV"
            << "VillagerAction"
            << "VillagerCV"
            << "VillagerSleep"
            << "VillagerWakeUp"
            << "VoteDraw"
            << "VoteResult"
            << "VoteStart"
            << "WakeUpPlease"
            << "WhiteWolfAction"
            << "WhiteWolfCV"
            << "WhiteWolfSkillVoice"
            << "WhiteWolfSleep"
            << "WhiteWolfWakeUp"
            << "WitchAction"
            << "WitchCV"
            << "WitchSkillVoice"
            << "WitchSleep"
            << "WitchWakeUp"
            << "WolfAction"
            << "WolfBeartySkillVoice"
            << "WolfBeartyWakeUp"
            << "WolfBeautyAction"
            << "WolfBeautyCV"
            << "WolfBeautySleep"
            << "WolfCV"
            << "WolfMusic"
            << "WolfSleep"
            << "WolfWakeUp"
            << "WolfWin"
            << "WolvesCV1"
            << "click"
    ;
#endif

    QTimer::singleShot(0, this , SLOT(tmrInitFunc()));


}

void TMainWnd::tmrInitFunc()
{
#if 0

    _d->mqttPublisher = new QMQTT::Client(QHostAddress ("47.107.158.130"),31883);
//  #else
     QList<QHostAddress> addrLs= QHostInfo::fromName("emqxsz.langrensha.game").addresses();
     if(addrLs.size() > 0 )
         setupMqtt();


 #endif


     connect(this, SIGNAL(logThiz(QString)), SLOT(teAppendLog(QString)));


}


void TMainWnd::setupUi()
{

    setWindowTitle(tr("langrensha协议模拟器 —— Ver:1.0.0_%1")
                   .arg( (TOOTBUILDDATE) ));

    QVBoxLayout *mainLO = new QVBoxLayout;
    mainLO->setMargin(2);
    mainLO->setSpacing(0);

    setupMqttSetupLO(mainLO);

    setupLedLightLO(mainLO);

    setupMotorCtrlLO(mainLO);


    setupInfoPanelLO(mainLO);


    setLayout(mainLO);

}

void TMainWnd::setupMqttSetupLO(QVBoxLayout *mlo)
{
    QGroupBox *mqttGpb  = new QGroupBox( tr("Mqtt设置"));
    QHBoxLayout *mainGpbLO = new QHBoxLayout;
    mainGpbLO->setMargin(2);
    mainGpbLO->setSpacing(5);


    QGridLayout *leftGridLO = new QGridLayout;
    leftGridLO->setMargin(2);
    leftGridLO->setSpacing(2);


    QStringList lbStrLs;
    lbStrLs
             <<  tr("用户名:")
              <<  tr("密码:")
               <<  tr("主题:")
                   ;
    QList<QLabel*> lbWidLs;
    for(int i = 0 ; i < lbStrLs.size() ; i ++){
        QLabel *lb = new QLabel(lbStrLs.at(i));
        lbWidLs << lb;
    }

#define LO_WID_SPACEING 8


#if 0
    _d->mqttUsernameLe = new QLineEdit(QString("mqtt_langrensha"));
    _d->mqttPasswdLe = new QLineEdit(QString("pCZNqunT0JYfSWg"));
#else
    _d->mqttUsernameLe = new QLineEdit(QString("testmqtt_langrensha"));
    _d->mqttPasswdLe = new QLineEdit(QString("ErZDb07XXfZMlk7"));
#endif
    leftGridLO->addWidget(lbWidLs.at(0), 0,0,1,1);
    leftGridLO->addWidget(_d->mqttUsernameLe , 0,1,1,1);
    leftGridLO->addWidget(lbWidLs.at(1), 1,0,1,1);
    leftGridLO->addWidget(_d->mqttPasswdLe, 1,1,1,1);

    //
    _d->mqttTopicLe = new QLineEdit(QString("langrensha-room-03"));
    leftGridLO->addWidget(lbWidLs.at(2), 2,0,1,1);
    leftGridLO->addWidget(_d->mqttTopicLe, 2,1,1,1);

    mainGpbLO->addLayout(leftGridLO, 20);
    //



    _d->tabWid = new QTabWidget();
    _d->tabWid->addTab(setupMqttTcpWid(), QString("Mqtt-tcp"));
    _d->tabWid->addTab(setupMqttTlsWid(), QString("Mqtt-tls"));
    _d->tabWid->addTab(setupMqttWsWid(), QString("Mqtt-ws"));
    _d->tabWid->addTab(setupMqttWssWid(), QString("Mqtt-wss"));


    mainGpbLO->addWidget(_d->tabWid , 60);



    QVBoxLayout *rightBtnLO1 = new QVBoxLayout;
    rightBtnLO1->setMargin(2);
    rightBtnLO1->setSpacing(2);
    //
    QPushButton *connBtn = new QPushButton(tr("开始连接"));
    connBtn->setCheckable(true);
    rightBtnLO1->addWidget(connBtn);
    connect(connBtn,SIGNAL(clicked(bool)), SLOT(connBtnClick(bool)));


    QPushButton *feedbackBtn = new QPushButton(tr("接收远端数据"));
    rightBtnLO1->addWidget(feedbackBtn);
    connect(feedbackBtn,SIGNAL(released()), SLOT(showFeedbackWnd()));

    mainGpbLO->addLayout(rightBtnLO1);

    mqttGpb->setLayout(mainGpbLO);
    mlo->addWidget(mqttGpb);

    connBtn->setFocus();
}

QWidget * TMainWnd::setupMqttTcpWid()
{
    QWidget *mainWid = new QWidget;
    QHBoxLayout *mainGpbLO = new QHBoxLayout;
    mainGpbLO->setMargin(2);
    mainGpbLO->setSpacing(5);


     _d->mqttTcpSvrLe = new QLineEdit(QString("testemqx.langrensha.game"));
      // _d->mqttTcpSvrLe = new QLineEdit(QString("emqx.langrensha.game"));

      _d->mqttTcpPortLe = new QLineEdit(QString("31883"));
      _d->mqttTcpPortLe->setMaximumWidth(50);
      _d->mqttTcpPortLe->setInputMask("99999");
      //
      mainGpbLO->addWidget(new QLabel(tr("主机:")));
      mainGpbLO->addWidget(_d->mqttTcpSvrLe);
      mainGpbLO->addWidget(new QLabel(tr("端口:")));
      mainGpbLO->addWidget(_d->mqttTcpPortLe);
      mainGpbLO->addSpacing(LO_WID_SPACEING);



     mainWid->setLayout(mainGpbLO);
    return  mainWid;
}


QWidget * TMainWnd::setupMqttTlsWid()
{
    QWidget *mainWid = new QWidget;
    QGridLayout *mainGpbLO = new QGridLayout;
    mainGpbLO->setSpacing(2);
    mainGpbLO->setMargin(2);



    QStringList lbStrLs;
    lbStrLs <<  tr("主机:")
             <<  tr("端口:")
              <<  tr("TLS版本:")
               <<  tr("认证类型:")

                <<  tr("CA文件:")
                 <<  tr("认证文件:")
                  <<  tr("客户key文件:")
                   <<  tr("客户key口令:")
                   ;
    QList<QLabel*> lbWidLs;
    for(int i = 0 ; i < lbStrLs.size() ; i ++){
        QLabel *lb = new QLabel(lbStrLs.at(i));
        lbWidLs << lb;
    }



    _d->mqttTlsSvrLe = new QLineEdit(QString("testemqx.langrensha.game"));
      //  _d->mqttTlsSvrLe = new QLineEdit(QString("47.56.210.54"));

      _d->mqttTlsPortLe = new QLineEdit(QString("31883"));
      _d->mqttTlsPortLe->setMaximumWidth(50);
      _d->mqttTlsPortLe->setInputMask("99999");
      //
      mainGpbLO->addWidget(lbWidLs.at(0) , 0 , 0 , 1 , 1 );
      mainGpbLO->addWidget(_d->mqttTlsSvrLe , 0 , 1 , 1 , 1 );
      mainGpbLO->addWidget(lbWidLs.at(1) , 1 , 0 , 1 , 1 );
      mainGpbLO->addWidget(_d->mqttTlsPortLe, 1 , 1 , 1 , 1);
    //
      QComboBox *tlsVerCb = new QComboBox;
      QStringList tlsVerStrLs;
      tlsVerStrLs << QString("Auto")
                  << QString("TlsV1.2")
                  << QString("TlsV1.1")
                  << QString("TlsV1")
                  << QString("TlsV3")
                  << QString("TlsV1.3")
                     ;
      tlsVerCb->addItems(tlsVerStrLs);
    //
      QComboBox *tlsCetiTypeCb = new QComboBox;
      QStringList tlsCetiTypeStrLs;
      tlsCetiTypeStrLs << QString("Self signed")
                  << QString("CA certificate")
                  << QString("CA signed server")
                     ;
      tlsCetiTypeCb->addItems(tlsCetiTypeStrLs);

      mainGpbLO->addWidget(lbWidLs.at(2) , 0 , 2 , 1 , 1 );
      mainGpbLO->addWidget( tlsVerCb , 0 , 3 , 1 , 1 );
      mainGpbLO->addWidget(lbWidLs.at(3) , 1 , 2 , 1 , 1 );
      mainGpbLO->addWidget(tlsCetiTypeCb, 1 , 3 , 1 , 1);

      //
      QPushButton *caFileBtn = new QPushButton(tr("选择文件"));
      QPushButton *cliCertFileBtn = new QPushButton(tr("选择文件"));
      mainGpbLO->addWidget(lbWidLs.at(4) , 0 , 4 , 1 , 1 );
      mainGpbLO->addWidget( caFileBtn , 0 , 5 , 1 , 1 );
      mainGpbLO->addWidget(lbWidLs.at(5) , 1 , 4 , 1 , 1 );
      mainGpbLO->addWidget(cliCertFileBtn, 1 , 5 , 1 , 1);
      //
      QPushButton *cliKeyFileBtn = new QPushButton(tr("选择文件"));
      QLineEdit *cliKeyPasscodeLe = new QLineEdit();
      mainGpbLO->addWidget(lbWidLs.at(6) , 0 , 6 , 1 , 1 );
      mainGpbLO->addWidget( cliKeyFileBtn , 0 , 7 , 1 , 1 );
      mainGpbLO->addWidget(lbWidLs.at(7) , 1 , 6 , 1 , 1 );
      mainGpbLO->addWidget(cliKeyPasscodeLe, 1 , 7 , 1 , 1);



     mainWid->setLayout(mainGpbLO);
    return  mainWid;
}


QWidget * TMainWnd::setupMqttWsWid()
{
    QWidget *mainWid = new QWidget;
    QHBoxLayout *mainGpbLO = new QHBoxLayout;
    mainGpbLO->setMargin(2);
    mainGpbLO->setSpacing(5);


    _d->mqttWsSvrLe = new QLineEdit(QString("testemqx.langrensha.game/ws/"));


    mainGpbLO->addWidget(new QLabel(tr("主机:")));
    mainGpbLO->addWidget(_d->mqttWsSvrLe);

    mainWid->setLayout(mainGpbLO);
    return  mainWid;
}

QWidget * TMainWnd::setupMqttWssWid()
{

    QWidget *mainWid = new QWidget;
    QGridLayout *mainGpbLO = new QGridLayout;
    mainGpbLO->setSpacing(2);
    mainGpbLO->setMargin(2);



    QStringList lbStrLs;
    lbStrLs <<  tr("主机:")
              <<  tr("TLS版本:")
               <<  tr("认证类型:")

                <<  tr("CA文件:")
                 <<  tr("认证文件:")
                  <<  tr("客户key文件:")
                   <<  tr("客户key口令:")
                   ;
    QList<QLabel*> lbWidLs;
    for(int i = 0 ; i < lbStrLs.size() ; i ++){
        QLabel *lb = new QLabel(lbStrLs.at(i));
        lbWidLs << lb;
    }



    _d->mqttWssSvrLe = new QLineEdit(QString("testemqx.langrensha.game/ws/"));

      //
      mainGpbLO->addWidget(lbWidLs.at(0) , 0 , 0 , 1 , 1 );
      mainGpbLO->addWidget(_d->mqttWssSvrLe , 0 , 1 , 1 , 1 );

    //
      QComboBox *tlsVerCb = new QComboBox;
      QStringList tlsVerStrLs;
      tlsVerStrLs << QString("Auto")
                  << QString("TlsV1.2")
                  << QString("TlsV1.1")
                  << QString("TlsV1")
                  << QString("TlsV3")
                  << QString("TlsV1.3")
                     ;
      tlsVerCb->addItems(tlsVerStrLs);
    //
      QComboBox *tlsCetiTypeCb = new QComboBox;
      QStringList tlsCetiTypeStrLs;
      tlsCetiTypeStrLs << QString("Self signed")
                  << QString("CA certificate")
                  << QString("CA signed server")
                     ;
      tlsCetiTypeCb->addItems(tlsCetiTypeStrLs);

      mainGpbLO->addWidget(lbWidLs.at(1) , 0 , 2 , 1 , 1 );
      mainGpbLO->addWidget( tlsVerCb , 0 , 3 , 1 , 1 );
      mainGpbLO->addWidget(lbWidLs.at(2) , 1 , 2 , 1 , 1 );
      mainGpbLO->addWidget(tlsCetiTypeCb, 1 , 3 , 1 , 1);

      //
      QPushButton *caFileBtn = new QPushButton(tr("选择文件"));
      QPushButton *cliCertFileBtn = new QPushButton(tr("选择文件"));
      mainGpbLO->addWidget(lbWidLs.at(3) , 0 , 4 , 1 , 1 );
      mainGpbLO->addWidget( caFileBtn , 0 , 5 , 1 , 1 );
      mainGpbLO->addWidget(lbWidLs.at(4) , 1 , 4 , 1 , 1 );
      mainGpbLO->addWidget(cliCertFileBtn, 1 , 5 , 1 , 1);
      //
      QPushButton *cliKeyFileBtn = new QPushButton(tr("选择文件"));
      QLineEdit *cliKeyPasscodeLe = new QLineEdit();
      mainGpbLO->addWidget(lbWidLs.at(5) , 0 , 6 , 1 , 1 );
      mainGpbLO->addWidget( cliKeyFileBtn , 0 , 7 , 1 , 1 );
      mainGpbLO->addWidget(lbWidLs.at(6) , 1 , 6 , 1 , 1 );
      mainGpbLO->addWidget(cliKeyPasscodeLe, 1 , 7 , 1 , 1);



     mainWid->setLayout(mainGpbLO);
    return  mainWid;
}



void TMainWnd::setupLedLightLO(QVBoxLayout *mlo)
{

    QGroupBox *ledLightGpb  = new QGroupBox( );
    QVBoxLayout *mainGpbLO = new QVBoxLayout;
    mainGpbLO->setMargin(2);
    mainGpbLO->setSpacing(0);



    /////

    QHBoxLayout *headerLightHLO = new QHBoxLayout;
    headerLightHLO->setSpacing(2);
    headerLightHLO->setMargin(2);



    QGridLayout *btnAllCtlVLO = new QGridLayout;
    btnAllCtlVLO->setSpacing(2);
    btnAllCtlVLO->setMargin(2);
    QPushButton *restartBtn = new QPushButton(tr("重新开局"));
    restartBtn->setMaximumWidth(88);
    connect(restartBtn, &QPushButton::released , this, &TMainWnd::resetartBtnClick);


    btnAllCtlVLO->addWidget(restartBtn , 0,0 , 1,1);

    QStringList allLedStrLs;

    allLedStrLs << tr("全部顶灯") << QString("allHeaderlamp")
                << tr("全部桌灯") << QString("allDesklamp")
                << tr("全部环境灯")  << QString("allAmbientlamp")
                   ;

    QList<QPushButton *> tmpBtnLs;
    for(int i = 0 ; i < allLedStrLs.size() ; i += 2){
        QPushButton *pusBtn = new QPushButton(allLedStrLs.at(i));
        pusBtn->setMaximumWidth(88);
        pusBtn->setCheckable(true);
        pusBtn->setObjectName(allLedStrLs.at(i+1));
        connect(pusBtn, &QPushButton::toggled, this, &TMainWnd::allLampCtlBtnClick);
        connect(this, &TMainWnd::uncheckSomeBtns ,pusBtn, &QPushButton::setChecked  );
        tmpBtnLs << pusBtn;
    }

    btnAllCtlVLO->addWidget(tmpBtnLs.at(0) , 0,1, 1,1);
    btnAllCtlVLO->addWidget(tmpBtnLs.at(1) , 1,0, 1,1);
    btnAllCtlVLO->addWidget(tmpBtnLs.at(2) , 1,1, 1,1);



    QStringList delayStr;
    for(int dd = 0  ; dd <=200; dd += 10)
        delayStr << QString::number(dd);

    for(int dd = 300  ; dd <=2000; dd += 100)
        delayStr << QString::number(dd);

    _d->delayCb = new QComboBox;
    _d->delayCb->addItems(delayStr);
    _d->delayCb->setEditable(true);
    _d->delayCb->setMaximumWidth(64);

    btnAllCtlVLO->addWidget(new QLabel("延时:") , 0,2, 1,1);
    btnAllCtlVLO->addWidget(_d->delayCb , 1,2, 1,1);


    headerLightHLO->addLayout(btnAllCtlVLO);
    ///
    headerLightHLO->addSpacing(50);


    QGroupBox *headlampGpb  = new QGroupBox(tr("顶灯") );
    QHBoxLayout *btnLO = new QHBoxLayout();
    btnLO->setMargin(2);

    QButtonGroup *headlampBtnGp = new QButtonGroup();
    headlampBtnGp->setExclusive(false);
    int i ;
    for(  i = 1; i < 17 ; i ++){
        QPushButton *btn = new QPushButton(QString("%1").arg(i));
        btn->setMaximumWidth(36);
        btn->setCheckable(true);
        headlampBtnGp->addButton(btn,i);
        btnLO->addWidget(btn);
        connect(this, &TMainWnd::checkUnCheckAllHeaderlamp, btn, &QPushButton::setChecked);
    }

    connect(headlampBtnGp,SIGNAL(buttonToggled(int,bool)),SLOT(headlampBtnClick(int,bool)));

//    btnLO->addSpacing(18);
//    QPushButton *btnAllLed = new QPushButton(tr("全部"));
//    btnAllLed->setMaximumWidth(66);
//    btnAllLed->setCheckable(true);
//    headlampBtnGp->addButton(btnAllLed,0);
//    btnLO->addWidget(btnAllLed);
//    ///

    headlampGpb->setLayout(btnLO);

    headerLightHLO->addWidget(headlampGpb);

    mainGpbLO->addLayout(headerLightHLO);






    ////
    QGroupBox *desklampGpb  = new QGroupBox(tr("桌灯") );
    QHBoxLayout *dlampLO = new QHBoxLayout();
    dlampLO->setMargin(2);
    dlampLO->setSpacing(1);
    for(int i = 1 ; i < 17 ; i ++){
        TDeskLampWid *lwid = new TDeskLampWid(i);
        connect(lwid , SIGNAL(deskLampChged(quint8,quint8,quint8))
                ,SLOT(handleDesklampChged(quint8,quint8,quint8)));

        connect(this, &TMainWnd::checkUnCheckAllDesklamp, lwid, &TDeskLampWid::chkUnchkAllDesklamp);
        dlampLO->addWidget(lwid);
    }

    desklampGpb->setLayout(dlampLO);
    mainGpbLO->addWidget(desklampGpb);
    /////


    QHBoxLayout *midHLo = new QHBoxLayout;
    midHLo->setMargin(2);
    midHLo->setSpacing(1);

    QGroupBox *ambientlampGpb  = new QGroupBox(tr("环境灯") );
    QHBoxLayout *hlampLO = new QHBoxLayout();
    hlampLO->setMargin(2);
    hlampLO->setSpacing(1);
    for(int i = 1 ; i < 5 ; i ++){
        TAmbientLampWid *lwid = new TAmbientLampWid(i);
        connect(lwid , SIGNAL(ambientLampChged(quint8,quint8,quint8))
                ,SLOT(handleAmbientChged(quint8,quint8,quint8)));


        connect(this, &TMainWnd::checkUnCheckAllAmbientlamp,
                lwid, &TAmbientLampWid::chkUnchkAllAmbientlamp);
        hlampLO->addWidget(lwid);
    }

    ambientlampGpb->setLayout(hlampLO);
    midHLo->addWidget(ambientlampGpb);
    ///////////////////////////////

    QGroupBox *musicGpb  = new QGroupBox(tr("Mp3控制"));

    QGridLayout *mp3GridLO = new QGridLayout;
    mp3GridLO->setSpacing(2);
    mp3GridLO->setAlignment(Qt::AlignRight);

    mp3GridLO->addWidget(new QLabel(tr("播放: ")) ,0,0,1,1);


    QComboBox *mp3ListCb = new QComboBox();
    mp3ListCb->setMinimumWidth(170);
    mp3ListCb->addItems(_d->mp3NameStrLs);
    connect(mp3ListCb, SIGNAL(activated(QString)), SLOT(mp3CbChged(QString)));
    mp3GridLO ->addWidget(mp3ListCb ,  0,1,1,1);
    //
    mp3GridLO->addWidget(new QLabel(tr("停止: ")) ,1,0,1,1);
    QComboBox *mp3StopListCb = new QComboBox();
    mp3StopListCb->setMinimumWidth(170);
    mp3StopListCb->addItem("(allstop)");
    mp3StopListCb->addItems(_d->mp3NameStrLs);
    connect(mp3StopListCb, SIGNAL(activated(QString)), SLOT(mp3StopCbChged(QString)));
    mp3GridLO ->addWidget(mp3StopListCb ,  1,1,1,1);
    //
    mp3GridLO->addWidget(new QLabel(tr(" 音量: ")) ,0,2,1,1);
    QComboBox *mp3VolumeCb = new QComboBox();
    mp3VolumeCb->setMaximumWidth(60);
    mp3GridLO ->addWidget(mp3VolumeCb ,  0,3,1,1);

    for(int v = 0 ; v <= 100 ; v+= 5)
        mp3VolumeCb->addItem(QString::number(v));


    mp3VolumeCb->setCurrentIndex(12);
    connect(mp3VolumeCb, SIGNAL(activated(QString)), SLOT(mp3VolumeChged(QString)));

    //
    QPushButton *hPSpkBtn = new QPushButton(tr("耳机输出"));
    QPushButton *playlistBtn = new QPushButton(tr("设定连播"));
    hPSpkBtn->setCheckable(true);
    hPSpkBtn->setMaximumWidth(60);
    playlistBtn->setMaximumWidth(60);
    mp3GridLO ->addWidget(hPSpkBtn ,  1,2,1,1);
    mp3GridLO ->addWidget(playlistBtn ,  1,3,1,1);

    connect(hPSpkBtn, &QPushButton::toggled,this, &TMainWnd::switchHpSkpBtnClick);
    connect(playlistBtn, &QPushButton::clicked,this, &TMainWnd::showPlaylistWnd);



    _d->mp3RepeatLe = new QLineEdit("0");
    _d->mp3RepeatLe->setMaximumWidth(32);
    mp3GridLO ->addWidget(_d->mp3RepeatLe ,  0,4,1,1);


   musicGpb -> setLayout(mp3GridLO);
   midHLo->addWidget(musicGpb);

   ///////////////////////////////

   QGroupBox *rfLedGpb  = new QGroupBox(tr("无线 led 灯"));

   QGridLayout *rfLedGridLO = new QGridLayout;
   rfLedGridLO->setSpacing(2);
   rfLedGridLO->setMargin(1);

   QComboBox *rfIdCb = new QComboBox();
   for(int i = 1 ; i < 17 ; i ++)
       rfIdCb->addItem(QString::number(i));

   connect(rfIdCb, SIGNAL(activated(int)), SLOT(rfLedIdCbChged(int)));

   rfLedGridLO->addWidget(new QLabel(tr("ID号: ")) ,0,0,1,1);
   rfLedGridLO->addWidget(rfIdCb ,0,1,1,1);

   QPushButton *setidBtn = new QPushButton(tr("设置ID"));
   setidBtn->setMaximumWidth(80);
   rfLedGridLO->addWidget(setidBtn ,1,0,1,2);

   connect(setidBtn, &QPushButton::clicked, this, &TMainWnd::setRfLedidBtnClick);

  rfLedGpb -> setLayout(rfLedGridLO);
  midHLo->addWidget(rfLedGpb);


   /////////////////////////////////////////////////////////////
   QGroupBox *wifiGpb  = new QGroupBox(tr("Wifi控制"));

   QHBoxLayout *wifiHLO = new QHBoxLayout();
   wifiHLO->setSpacing(1);
   wifiHLO->setMargin(2);

   QGridLayout *gridLO = new QGridLayout;
   gridLO->setSpacing(1);
   gridLO->setMargin(2);


   QStringList lbStrLs;
   lbStrLs <<  tr("Wifi名称:")
            <<  tr("密码:")
             <<  tr("板卡号:")
                  ;
   QList<QLabel*> lbWidLs;
   for(int i = 0 ; i < lbStrLs.size() ; i ++){
       QLabel *lb = new QLabel(lbStrLs.at(i));
       lbWidLs << lb;
   }


   _d->wifiSsidLe = new QLineEdit();
   _d->wifiPasswdLe = new QLineEdit();   
   _d->wifiPasswdLe->setPlaceholderText(tr("长度大于8个英文字母"));

   gridLO->addWidget(lbWidLs.at(0),0,0,1,1);
   gridLO->addWidget(_d->wifiSsidLe,0,1,1,1);

   gridLO->addWidget(lbWidLs.at(1),1,0,1,1);
   gridLO->addWidget(_d->wifiPasswdLe,1,1,1,1);

   _d->boardNumLe = new QLineEdit();
   _d->boardNumLe->setInputMask("999");

   gridLO->addWidget(lbWidLs.at(2),0,2,1,1);
   gridLO->addWidget(_d->boardNumLe,0,3,1,1);

   QHBoxLayout* hLO2a = new QHBoxLayout;
   hLO2a->setSpacing(1);
   hLO2a->setMargin(1);
   QPushButton *setWifiBtn = new QPushButton(tr("设置Wifi"));
   setWifiBtn->setObjectName(QLatin1String("setwifipara"));
   QPushButton *rebootBtn = new QPushButton(tr("重启板卡"));
   rebootBtn->setObjectName(QLatin1String("rebootboard"));
   hLO2a->addWidget(setWifiBtn);
   hLO2a->addWidget(rebootBtn);

   connect(setWifiBtn,&QPushButton::released, this, &TMainWnd::miscCmdToBoard);
    connect(rebootBtn,&QPushButton::released, this, &TMainWnd::miscCmdToBoard);


   gridLO->addLayout(hLO2a, 1, 2, 1,2);


   wifiHLO->addLayout(gridLO);


   QVBoxLayout *wifiVLO = new QVBoxLayout;
   wifiVLO->setSpacing(1);
   wifiVLO->setMargin(2);

   _d->wifiBtnsGp = new QButtonGroup;
   QPushButton *btnSta = new QPushButton(tr("切换为终端(Sta)"));
   QPushButton *btnAp = new QPushButton(tr("切换为热点(Ap)"));
  // btnSta->setCheckable(true);
  // btnAp->setCheckable(true);
   _d->wifiBtnsGp->addButton(btnSta,1);
   _d->wifiBtnsGp->addButton(btnAp,2);
   connect(_d->wifiBtnsGp, SIGNAL(buttonReleased(int)), SLOT(wifiBtnClick(int)));


   wifiVLO->addWidget(btnSta);
   wifiVLO->addWidget(btnAp);

   wifiHLO->addLayout(wifiVLO);

  wifiGpb -> setLayout(wifiHLO);
  midHLo->addWidget(wifiGpb, 30);
  /////////////////////////////////////////////////////////////



    mainGpbLO->addLayout(midHLo);

    ledLightGpb->setLayout(mainGpbLO);
    mlo->addWidget(ledLightGpb,10);

}

void TMainWnd::setupkeyBtnLO(QVBoxLayout *mlo)
{

    QGroupBox *keyBtnGpb  = new QGroupBox(tr("按键"));


    mlo->addWidget(keyBtnGpb);
}



void TMainWnd::setupMotorCtrlLO(QVBoxLayout *mlo)
{
    QHBoxLayout *mlo1 = new QHBoxLayout;
    mlo1->setMargin(2);
    mlo1->setSpacing(2);
    mlo->addLayout(mlo1);

    QGroupBox *motorCtrlGpb  = new QGroupBox(tr("马达控制"));

    QHBoxLayout *hLO = new QHBoxLayout;
    hLO->setMargin(2);
    hLO->setSpacing(4);

    QButtonGroup *motorBtnGp = new QButtonGroup();
    motorBtnGp->setExclusive(false);

    for( int i = 1; i < 17 ; i ++){
        QPushButton *btn = new QPushButton(QString("%1").arg(i));
        btn->setMaximumWidth(32);
        btn->setCheckable(true);
        motorBtnGp->addButton(btn,i);
        hLO->addWidget(btn);
    }

    connect(motorBtnGp,SIGNAL(buttonToggled(int,bool)),SLOT(motorBtnClick(int,bool)));

     motorCtrlGpb->setLayout(hLO);
     mlo1->addWidget(motorCtrlGpb );


     ////////////////////////////////////////////////////////



     QGroupBox *cameraCtrlGpb  = new QGroupBox(tr("摄像机控制"));

     QHBoxLayout *hLO1 = new QHBoxLayout;
     hLO1->setSpacing(1);
     hLO1->setMargin(2);


     hLO1->addWidget(new QLabel(tr("摄像机地址: ")));
     QStringList addrLs;
     for(int i = 1 ; i < 5 ; i ++)
         addrLs<< QString::number(i);

     QComboBox *camAddrCb = new QComboBox();
     camAddrCb->addItems(addrLs);
     connect(camAddrCb, SIGNAL(activated(int)), SLOT(camAddrCbChged(int)));
     hLO1 ->addWidget(camAddrCb);
     ////

     hLO1->addSpacing(10);
     hLO1->addWidget(new QLabel(tr("预设位: ")));
     QStringList valLs;
     for(int i = 0 ; i < 255 ; i ++)
         valLs<< QString::number(i);

     QComboBox *camPresetValCb = new QComboBox();
     camPresetValCb->addItems(valLs);
     connect(camPresetValCb, SIGNAL(activated(int)), SLOT(camCbChged(int)));
     hLO1 ->addWidget(camPresetValCb);
     //
     hLO1->addSpacing(10);
     QPushButton *camPwrBtn = new QPushButton(tr("休眠"));
     camPwrBtn->setMaximumWidth(36);
     camPwrBtn->setCheckable(true);
     connect(camPwrBtn,&QPushButton::toggled, this, &TMainWnd::camSleepClick);
     hLO1->addWidget(camPwrBtn);


     //
     hLO1->addSpacing(10);
     hLO1->addWidget(new QLabel(tr("VISCA协议: ")));
     _d->viscaCmdLe = new QLineEdit;
     QString myMask;
     myMask  .fill('H',50);
     _d->viscaCmdLe->setInputMask(myMask);
     connect(_d->viscaCmdLe,SIGNAL(textChanged(QString)), SLOT(viscaLeTxtChged(QString)) );

     connect(_d->viscaCmdLe,SIGNAL(returnPressed()), SLOT(viscaLeReturnPressed()) );
     hLO1->addWidget(_d->viscaCmdLe);

     //
     QPushButton *resetCamBtn = new QPushButton(tr("复位摄像机"));
     resetCamBtn->setFocusPolicy(Qt::NoFocus);
     connect(resetCamBtn, SIGNAL(released()) , SLOT(resetCameraClick()));
     hLO1 ->addWidget(resetCamBtn);

     cameraCtrlGpb->setLayout(hLO1);
     mlo1->addWidget(cameraCtrlGpb );



}


void TMainWnd::setupInfoPanelLO(QVBoxLayout *mlo)
{
    QGroupBox *infoGpb  = new QGroupBox( tr("信息栏"));
    QVBoxLayout *mainGpbLO = new QVBoxLayout;
    mainGpbLO->setMargin(2);
    mainGpbLO->setSpacing(0);

    QHBoxLayout *hLO1 = new QHBoxLayout();
    hLO1->setMargin(2);
    hLO1->addWidget(new QLabel(tr("发送内容:")));
    _d->resultStrLe = new QLineEdit();
    QFont fn = _d->resultStrLe->font();
    fn.setPixelSize(20);
    _d->resultStrLe->setFont(fn);
    hLO1->addWidget(_d->resultStrLe);
    QPushButton *reSendBtn = new QPushButton(tr("重  发"));
    connect(reSendBtn, SIGNAL(released()), SLOT(doSendNow()));
    // connect(reSendBtn, SIGNAL(released()), SLOT(testQuickSend()));
    hLO1->addSpacing(32);
    hLO1->addWidget(reSendBtn);

    mainGpbLO->addLayout(hLO1);

    QGroupBox *gpb1 = new QGroupBox(tr("日记"));
    QHBoxLayout *vLO1 = new QHBoxLayout();
    gpb1->setLayout(vLO1);
    _d->remoteMsgTe = new QTextEdit;
    _d->remoteMsgTe->setReadOnly(true);
    vLO1 ->addWidget(_d->remoteMsgTe);
    QPushButton* cleanBtn = new QPushButton(tr("清  除"));
    connect(cleanBtn,SIGNAL(released()), _d->remoteMsgTe, SLOT(clear()));
    vLO1->addWidget(cleanBtn);
    mainGpbLO->addWidget(gpb1);


    infoGpb->setLayout(mainGpbLO);
    mlo->addWidget(infoGpb,10);

}

void TMainWnd::connBtnClick(bool isC)
{
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    if(!btn) return;


    int tabIdx =  _d->tabWid->currentIndex();

//    if(!_d->mqttPublisher){
//        QMessageBox::warning(this,tr("错误!") , tr("未能连接mqtt服务器, 请检查网络后重新打开本程序...."));
//        return;
//    }

    _d->tabWid->setEnabled(!isC);
    btn->setText(isC ? tr("断开连接") : tr("开始连接"));

    switch (tabIdx) {
    case 0:   // tcp
            setupTcpConn(isC);
        break;
    case 1:  // tls
        setupTlsConn(isC);
        break;
    case 2:  // ws
        setupWsConn(isC);
        break;
    case 3:  // wss
        setupWssConn(isC);
        break;
    default:
        break;
    }



}


void TMainWnd::setupTcpConn(bool isC)
{

    if(isC){
        _d->mqttTcpPublisher = new QMQTT::Client();

        QHostAddress hAddr (_d->mqttTcpSvrLe->text());

        if(hAddr.isNull())
         _d->mqttTcpPublisher->setHostName(_d->mqttTcpSvrLe->text());
        else
         _d->mqttTcpPublisher->setHost(hAddr);

        _d->mqttTcpPublisher->setPort(_d->mqttTcpPortLe->text().toInt());

        _d->mqttTcpPublisher->setUsername(_d->mqttUsernameLe->text());
        _d->mqttTcpPublisher->setPassword(_d->mqttPasswdLe->text().toUtf8());
       // _d->mqttTcpPublisher->setClientId(QString("langrensha-%1").arg(QDateTime::currentDateTime().toSecsSinceEpoch()));
        _d->mqttTcpPublisher->setClientId(getCliId());
        _d->mqttTcpPublisher->setKeepAlive(30);


        _d->mqttTcpPublisher->setCleanSession(true);

        connect(_d->mqttTcpPublisher, SIGNAL(connected()), SLOT(onMqttTcpConnected()));

        connect(_d->mqttTcpPublisher, SIGNAL(disconnected()), SLOT(onMqttTcpDisconnected()));
        connect(_d->mqttTcpPublisher, SIGNAL(error(QMQTT::ClientError)), SLOT(onMqttTcpError(QMQTT::ClientError)));


        _d->mqttTcpPublisher->connectToHost();

    }else{
        _d->mqttTcpPublisher->disconnectFromHost();
        _d->mqttTcpPublisher->deleteLater();
        _d->mqttTcpPublisher = nullptr;
    }

}

void TMainWnd::setupTlsConn(bool isC)
{

    if(isC){

        _d->mqttTlsPublisher = new QMQTT::Client();

        QHostAddress hAddr (_d->mqttTlsSvrLe->text());

        if(hAddr.isNull())
         _d->mqttTlsPublisher->setHostName(_d->mqttTlsSvrLe->text());
        else
         _d->mqttTlsPublisher->setHost(hAddr);

        _d->mqttTlsPublisher->setPort(_d->mqttTlsPortLe->text().toInt());

        QSslConfiguration sslConfig = QSslConfiguration::defaultConfiguration();

        _d->mqttTlsPublisher->setSslConfiguration(sslConfig);


        _d->mqttTlsPublisher->setUsername(_d->mqttUsernameLe->text());
        _d->mqttTlsPublisher->setPassword(_d->mqttPasswdLe->text().toUtf8());
        //_d->mqttTlsPublisher->setClientId(QString("langrensha-%1").arg(QDateTime::currentDateTime().toSecsSinceEpoch()));
        _d->mqttTlsPublisher->setClientId(getCliId());
        _d->mqttTlsPublisher->setKeepAlive(30);


        _d->mqttTlsPublisher->setCleanSession(true);

        connect(_d->mqttTlsPublisher, SIGNAL(connected()), SLOT(onMqttTlsConnected()));

        connect(_d->mqttTlsPublisher, SIGNAL(disconnected()), SLOT(onMqttTlsDisconnected()));
        connect(_d->mqttTlsPublisher, SIGNAL(error(QMQTT::ClientError)), SLOT(onMqttTlsError(QMQTT::ClientError)));

        connect(_d->mqttTlsPublisher, &QMQTT::Client::sslErrors, [&](const QList<QSslError>& errors){
            qDebug() << "tls ssl error: " << errors;
            _d->mqttTlsPublisher->ignoreSslErrors();
        } );


        _d->mqttTlsPublisher->connectToHost();

    }else{
        _d->mqttTlsPublisher->disconnectFromHost();
        _d->mqttTlsPublisher->deleteLater();
        _d->mqttTlsPublisher = nullptr;
    }

}

void TMainWnd::setupWsConn(bool isC)
{

    if(isC){

        QString hostStr = _d->mqttWsSvrLe->text();
        if(!hostStr.startsWith("ws://"))
            hostStr.prepend("ws://");


        _d->mqttWsPublisher = new QMQTT::Client(hostStr
                                                , "awesome-mqtt-ws"
                                                ,QWebSocketProtocol::VersionLatest
                                                );


        _d->mqttWsPublisher->setUsername(_d->mqttUsernameLe->text());
        _d->mqttWsPublisher->setPassword(_d->mqttPasswdLe->text().toUtf8());
       // _d->mqttWsPublisher->setClientId(QString("langrensha-%1").arg(QDateTime::currentDateTime().toSecsSinceEpoch()));
        _d->mqttWsPublisher->setClientId(getCliId());
        _d->mqttWsPublisher->setKeepAlive(30);



        _d->mqttWsPublisher->setCleanSession(true);

        connect(_d->mqttWsPublisher, SIGNAL(connected()), SLOT(onMqttWsConnected()));

        connect(_d->mqttWsPublisher, SIGNAL(disconnected()), SLOT(onMqttWsDisconnected()));
        connect(_d->mqttWsPublisher, SIGNAL(error(QMQTT::ClientError)), SLOT(onMqttWsError(QMQTT::ClientError)));


        _d->mqttWsPublisher->connectToHost();

    }else{
        _d->mqttWsPublisher->disconnectFromHost();
        _d->mqttWsPublisher->deleteLater();
        _d->mqttWsPublisher = nullptr;
    }

}

void TMainWnd::setupWssConn(bool isC)
{
    if(isC){

        QString hostStr = _d->mqttWssSvrLe->text();
        if(!hostStr.startsWith("ws://"))
            hostStr.prepend("ws://");


        QSslConfiguration sslConfig = QSslConfiguration::defaultConfiguration();
       // sslConfig.setProtocol();

        _d->mqttWssPublisher = new QMQTT::Client(hostStr
                                                , "awesome-mqtt-ws"
                                                ,QWebSocketProtocol::VersionLatest
                                                ,sslConfig
                                                );


        _d->mqttWssPublisher->setUsername(_d->mqttUsernameLe->text());
        _d->mqttWssPublisher->setPassword(_d->mqttPasswdLe->text().toUtf8());
        //_d->mqttWssPublisher->setClientId(QString("langrensha-%1").arg(QDateTime::currentDateTime().toSecsSinceEpoch()));
        _d->mqttWssPublisher->setClientId(getCliId());
        _d->mqttWssPublisher->setKeepAlive(30);

        _d->mqttWssPublisher->setCleanSession(true);

        connect(_d->mqttWssPublisher, SIGNAL(connected()), SLOT(onMqttWssConnected()));

        connect(_d->mqttWssPublisher, SIGNAL(disconnected()), SLOT(onMqttWssDisconnected()));
        connect(_d->mqttWssPublisher, SIGNAL(error(QMQTT::ClientError)), SLOT(onMqttWssError(QMQTT::ClientError)));
        connect(_d->mqttWssPublisher, &QMQTT::Client::sslErrors, [&](const QList<QSslError>& errors){
            qDebug() << "wss ssl error: " << errors;
            _d->mqttWssPublisher->ignoreSslErrors();
        } );

        _d->mqttWssPublisher->connectToHost();

    }else{
        _d->mqttWssPublisher->disconnectFromHost();
        _d->mqttWssPublisher->deleteLater();
        _d->mqttWssPublisher = nullptr;
    }
}

void TMainWnd::headlampBtnClick(int idx, bool isD)
{

    if(_d->isDiscardBtnEvt ) return;

  //  qDebug() << "idx: " << idx << "  isD : " << isD;
    _d->resultStrLe->setText(QString("{\"device\":\"headlamp\", \"number\":\"%1\",\"step\":%2,\"color\":\"white\",\"delay\":%3,\"timestamp\":%4}")
                             .arg(idx)
                             .arg(isD ? 100 : 0)
                             .arg(_d->delayCb->currentText())
                             .arg(fetchTs() )
                             );

    QTimer::singleShot(0,this, SLOT(doSendNow()));
}

void TMainWnd::handleDesklampChged(quint8 idx, quint8 crB, quint8 br)
{

    if(_d->isDiscardBtnEvt ) return;

    if(crB >= _d->mCrNameLs.size()) return;

    _d->resultStrLe->setText(QString("{\"device\":\"desklamp\", \"number\":\"%1\",\"step\":%2, \"color\":\"%3\",\"delay\":%4,\"timestamp\":%5}")
                             .arg(idx)                             
                             .arg(br)
                             .arg(_d->mCrNameLs.at(crB))
                             .arg(_d->delayCb->currentText())
                             .arg(fetchTs() )
                             );

    QTimer::singleShot(0,this, SLOT(doSendNow()));
}

void TMainWnd::handleAmbientChged(quint8 idx, quint8 crB, quint8 br)
{
    if(_d->isDiscardBtnEvt ) return;
    if(crB >= _d->mCrNameLs.size()) return;

    _d->resultStrLe->setText(QString("{\"device\":\"ambient\", \"number\":\"%1\",\"step\":%2,\"color\":\"%3\",\"delay\":%4,\"timestamp\":%5}")
                             .arg(idx)                             
                             .arg(br)
                             .arg(_d->mCrNameLs.at(crB))
                             .arg(_d->delayCb->currentText())
                             .arg(fetchTs() )
                             );

    QTimer::singleShot(0,this, SLOT(doSendNow()));
}

void TMainWnd::wifiBtnClick(int idx)
{

    bool isOk;
    int boardNum = _d->boardNumLe->text().toUInt(&isOk);

    if( !isOk){
        QMessageBox::warning(this,tr("错误!"), tr("请正确填写目标板卡号...."));
        return;
    }

    //  qDebug() << "idx: " << idx << "  isD : " << isD;
      _d->resultStrLe->setText(QString("{\"device\":\"wifi\", \"operate\":\"%1\", \"boardno\":%2, \"delay\":0 }")
                               .arg(idx == 1 ? "sta" : "ap")
                               .arg(boardNum)
                               );

       QTimer::singleShot(0,this, SLOT(doSendNow()));

       foreach (QAbstractButton *b, _d->wifiBtnsGp->buttons()) {
           b->setEnabled(false);
       }

    QTimer::singleShot(10,this, SLOT(reEnableWifiBtns()));
}

void TMainWnd::reEnableWifiBtns()
{
    foreach (QAbstractButton *b, _d->wifiBtnsGp->buttons()) {
        b->setEnabled(true);
    }
}

void TMainWnd::motorBtnClick(int idx, bool isD)
{

  //  qDebug() << "idx: " << idx << "  isD : " << isD;
    _d->resultStrLe->setText(QString("{\"device\":\"badge\", \"number\":%1, \"step\":\"%2\",\"color\":\"white\", \"delay\":0,\"timestamp\":%3}")
                             .arg(idx)
                             .arg(isD ? 100 : 0)
                             .arg(fetchTs())
                             );

    QTimer::singleShot(0,this, SLOT(doSendNow()));
}


void TMainWnd::setRfLedidBtnClick()
{
    _d->resultStrLe->setText(QString("{\"device\":\"rflamp\", \"number\":%1, \"operate\":\"setid\", \"delay\":0 }")
                             .arg(_d->rfLedIdNum)
                             );

    QTimer::singleShot(0,this, SLOT(doSendNow()));
}

void TMainWnd::rfLedIdCbChged(int i)
{
    _d->rfLedIdNum = i + 1;

}

void TMainWnd::camAddrCbChged(int v)
{
    _d->cameraNum = v + 1;
   cameraGetReadySent();
}

void TMainWnd::resetCameraClick()
{
    QFont fn = font();
    fn.setPixelSize(32);
    fn.setBold(true);
    QToolTip::setFont(fn);

    QPalette pal = palette();
    pal.setColor(QPalette::Inactive, QPalette::ToolTipText, Qt::red);


    QToolTip::setPalette(pal);

    QToolTip::showText(rect().adjusted(width()/2,0,-1,-1).center(),tr("%1 号摄像机复位码已生成, 请点击 [重发] 按钮!").arg(_d->cameraNum),this,rect(),2500);

    QByteArray ba = QByteArray::fromHex("810104A010FF");
    ba[0] = 0x80 | _d->cameraNum;
    _d->viscaCmdLe->setText(QString(ba.toHex()).toUpper());
    _d->viscaCmdLe->setFocus();

    emit _d->viscaCmdLe->textChanged(_d->viscaCmdLe->text());
}

void TMainWnd::camCbChged(int v)
{
    _d->cameraPreset = v;
     cameraGetReadySent();
}

void TMainWnd::camSleepClick(bool isD)
{
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    if(!btn) return;

    QByteArray ba = QByteArray::fromHex("8101040002FF");
    ba[0] = 0x80 | _d->cameraNum;

    if(isD){
        btn->setText(tr("唤醒"));
        ba[4] = 0x03;

    }else{
         btn->setText(tr("休眠"));
    }


    _d->viscaCmdLe->setText(QString(ba.toHex()).toUpper());
    _d->viscaCmdLe->setFocus();

    emit _d->viscaCmdLe->textChanged(_d->viscaCmdLe->text());
    QTimer::singleShot(0,this, SLOT(doSendNow()));
}

void TMainWnd::cameraGetReadySent()
{
    QString json =  QString("{\"device\":\"camera\", \"number\":%1, \"step\":%2,\"color\":\"white\", \"delay\":0,\"timestamp\":%3}")
            .arg(_d->cameraNum)
            .arg(_d->cameraPreset)
            .arg(fetchTs() )
            ;


    QByteArray ba = QByteArray::fromHex("8101043F0200FF");
    ba[0] = 0x80 | _d->cameraNum;
    ba[5] = _d->cameraPreset;

    _d->resultStrLe->setText(json);
    _d->viscaCmdLe->setText(QString(ba.toHex()).toUpper());
     QTimer::singleShot(0,this, SLOT(doSendNow()));
}

void TMainWnd::viscaLeTxtChged(const QString &s)
{
    QByteArray ba = QByteArray::fromHex(s.toLocal8Bit());

    if(ba.isEmpty()) return;

    QString json =  QString("{\"device\":\"camera\", \"number\":%1, \"command\":\"%2\", \"delay\":0 }")
                                  .arg(_d->cameraNum)
            .arg(QString(ba.toHex()));


    if(_d->viscaCmdLe->hasFocus())
       _d->resultStrLe->setText(json);
}

void TMainWnd::viscaLeReturnPressed()
{
    //qDebug() << __func__;
    QTimer::singleShot(0,this, SLOT(doSendNow()));
}

void TMainWnd::mp3CbChged(const QString &m)
{

  //  QStringList nameLs = m.split("-");
 //   if(nameLs.size() < 2) return;



    QString json =  QString("{\"device\":\"voice\", \"number\":%1,\"step\":%2,\"color\":\"white\",\"delay\":0,\"sounds\":\"%3.mp3\",\"timestamp\":%4}")
                                .arg(_d->mp3RepeatLe->text())
                                .arg(_d->audioVol)
                                .arg(m)
                                .arg(fetchTs())
            ;

    _d->resultStrLe->setText(json);
     QTimer::singleShot(0,this, SLOT(doSendNow()));
}

void TMainWnd::mp3StopCbChged(const QString &m)
{
    QString mm = m;
    if(mm == QString("(allstop)"))
        mm = QString("*");



    QString json =  QString("{\"device\":\"voice\", \"number\":0,\"step\":0,\"color\":\"white\",\"delay\":0,\"sounds\":\"%1.mp3\",\"timestamp\":%2}")
                                .arg(mm)
                                .arg(fetchTs())
            ;



    _d->resultStrLe->setText(json);
     QTimer::singleShot(0,this, SLOT(doSendNow()));
}

void TMainWnd::mp3VolumeChged(const QString &v)
{
    bool isOK;
    int vol = v.toInt(&isOK);

    if(!isOK){
       return;
    }

    _d->audioVol = vol;

//    QString json =  QString("{\"device\":\"player\", \"operate\":\"volume\", \"volume\":%1, \"delay\":0 }")
//                                  .arg(vol) ;

//    _d->resultStrLe->setText(json);
//     QTimer::singleShot(0,this, SLOT(doSendNow()));

}

void TMainWnd::switchHpSkpBtnClick(bool isD)
{
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    if(!btn) return;

    QString json =  QString("{\"device\":\"player\", \"operate\":\"outdev\", \"outdev\":\"%1\", \"delay\":0 }") ;



    if(isD){
        btn->setText(tr("喇叭输出"));
       json = json.arg("hp");

    }else{
         btn->setText(tr("耳机输出"));
        json = json.arg("spk");
    }

    _d->resultStrLe->setText(json);
     QTimer::singleShot(0,this, SLOT(doSendNow()));

}

void TMainWnd::showPlaylistWnd()
{
    TPlaylistWnd wnd(_d->mp3NameStrLs);
    wnd.setWindowModality(Qt::ApplicationModal);
    connect(&wnd, &TPlaylistWnd::resultStrLs, this, &TMainWnd::playlistStrLsArrived);
    connect(&wnd, &TPlaylistWnd::stopCurrPlaylist, this, &TMainWnd::stopCurrPlayingList);
    wnd.show();

    QEventLoop evtloop;
    connect(&wnd, &TPlaylistWnd::meClosed, &evtloop, &QEventLoop::quit);

    evtloop.exec();

}

void TMainWnd::playlistStrLsArrived(const QStringList &strLs)
{
  //  qDebug() << strLs;
    QString mp3Nums;
    for(int i = 0 ; i < strLs.size() ; i ++){
      //  QStringList tmpLs = strLs.at(i).split("-");
      //  if(tmpLs.size() > 1){
       //     bool isOk;
       //     if(tmpLs.at(0).toInt(&isOk)){
                 mp3Nums.append(strLs.at(i)).append(".mp3,");
       //     }
      //  }
    }

    if(mp3Nums.length() < 2 ) return;

    if(mp3Nums.endsWith(","))
        mp3Nums.chop(1);


    QString json =  QString("{\"device\":\"voice\", \"number\":%1,\"step\":%2,\"color\":\"white\",\"delay\":0,\"sounds\":\"%3\",\"timestamp\":%4}")
                                .arg(0)
                                .arg(_d->audioVol)
                                .arg(mp3Nums)
                                .arg(fetchTs())
            ;


    _d->resultStrLe->setText(json);
     QTimer::singleShot(0,this, SLOT(doSendNow()));

}

void TMainWnd::stopCurrPlayingList()
{
    QString json =  QString("{\"device\":\"player\", \"file\":\"(none)\", \"operate\":\"stoplist\", \"delay\":0 }")
                                   ;

    _d->resultStrLe->setText(json);
     QTimer::singleShot(0,this, SLOT(doSendNow()));
}

void TMainWnd::miscCmdToBoard()
{
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    if(!btn) return;


    QString json ;

    bool isOk;
    int boardNum = _d->boardNumLe->text().toUInt(&isOk);

    if( !isOk){
        QMessageBox::warning(this,tr("错误!"), tr("请正确填写目标板卡号...."));
        return;
    }

    if(btn->objectName() == "rebootboard"){
        json =  QString("{\"device\":\"ctrlcmd\",\"boardno\":%1,\"cmd\":\"reboot\",\"delay\":0 }").arg(boardNum);

    }else if(btn->objectName() == "setwifipara"){

        QString wifissid = _d->wifiSsidLe->text().trimmed();
        QString wifipwd = _d->wifiPasswdLe->text();


        if(wifissid.isEmpty() || wifipwd.length() < 8 ){
            QMessageBox::warning(this,tr("错误!"), tr("请正确填写WIFI信息...."));
            return;
        }


        if(QMessageBox::No ==
                QMessageBox::question(this,tr("确认!"),tr("确定将板卡号: %1 设置 WIFI 参数吗?").arg(boardNum), QMessageBox::Yes | QMessageBox::No)
                )
            return;


        json =  QString("{\"device\":\"wifi\", \"operate\":\"setting\",\"boardno\":%1,\"ssid\":\"%2\",\"passwd\":\"%3\",\"delay\":0 }")
                .arg(boardNum)
                .arg(_d->wifiSsidLe->text().trimmed())
                .arg(_d->wifiPasswdLe->text())
                ;

    }



    _d->resultStrLe->setText(json);
      QTimer::singleShot(0,this, SLOT(doSendNow()));




}


void TMainWnd::resetartBtnClick()
{
    QString json =  QString("{\"ct\":\"game\", \"ac\":\"game_start\", \"delay\":0,\"timestamp\":%1}").arg(fetchTs());

    _d->resultStrLe->setText(json);
    QTimer::singleShot(0,this, SLOT(doSendNow()));

    emit uncheckSomeBtns(false);

    _d->isDiscardBtnEvt = true;
    emit checkUnCheckAllHeaderlamp(false);
    emit checkUnCheckAllDesklamp(false);
    emit checkUnCheckAllAmbientlamp(false);
    _d->isDiscardBtnEvt = false;
}

void TMainWnd::allLampCtlBtnClick(bool isD)
{
    QPushButton *btn = qobject_cast<QPushButton *>(sender());

    if(!btn) return;

    QString jsonStr = QString("{\"device\":\"%1\", \"number\":0, \"color\":\"white\", \"step\":%2, \"delay\":%3,\"timestamp\":%4}");


    QString jsonStr2 = QString("{\"device\":\"%1\", \"number\":\"1,2,3,4,5,6,7,8,9,10,11,12\", \"color\":\"white\", \"step\":%2, \"delay\":%3,\"timestamp\":%4}");


    _d->isDiscardBtnEvt = true;
    if(btn->objectName() == QString("allHeaderlamp")){
        emit checkUnCheckAllHeaderlamp(isD);
        jsonStr  =  jsonStr2.arg("headlamp") .arg(isD?100:0).arg(_d->delayCb->currentText()).arg(fetchTs()) ;
    }else if(btn->objectName() == QString("allDesklamp")){
        emit checkUnCheckAllDesklamp(isD);
        jsonStr  =  jsonStr2.arg("desklamp") .arg(isD?100:0).arg(_d->delayCb->currentText()).arg(fetchTs()) ;
    }else if(btn->objectName() == QString("allAmbientlamp")){
        emit checkUnCheckAllAmbientlamp(isD);
        jsonStr =  jsonStr.arg("ambient") .arg(isD?100:0).arg(_d->delayCb->currentText()).arg(fetchTs()) ;
    }

    _d->resultStrLe->setText(jsonStr);
     QTimer::singleShot(0,this, SLOT(doSendNow()));

    _d->isDiscardBtnEvt = false;
  //  qDebug() << btn->objectName() << " isD : " << isD;
}

void TMainWnd::onMqttTcpConnected()
{
    _d->mqttTcpPublisher->subscribed(_d->mqttTopicLe->text() , 2);

    qDebug() << __func__ << " ........ ";

    emit logThiz(" >>>>>>>>>>>>>>>>>> Tcp Mqtt Connnected.........ip: " + _d->mqttTcpPublisher->host().toString());
}

void TMainWnd::onMqttTcpDisconnected()
{
    qDebug() << __func__ << " ........ ";

    emit logThiz(" >>>>>>>>>>>>>>>>>> Tcp Mqtt Disconnected.........");
}

void TMainWnd::onMqttTcpError(QMQTT::ClientError err)
{
    qDebug() << __func__ << " ........ err=" << err;

    emit logThiz(QString(" >>>>>>>>>>>>>>>>>> Tcp Mqtt Error = %1").arg(err));
}

///////////////////////////////////////////////////////////////////////////////////////////////

void TMainWnd::onMqttTlsConnected()
{
    _d->mqttTlsPublisher->subscribed(_d->mqttTopicLe->text() , 2);

    qDebug() << __func__ << " ........ ";

    emit logThiz(" >>>>>>>>>>>>>>>>>> Tls Mqtt Connnected.........ip: " + _d->mqttTlsPublisher->host().toString());
}

void TMainWnd::onMqttTlsDisconnected()
{
    qDebug() << __func__ << " ........ ";

    emit logThiz(" >>>>>>>>>>>>>>>>>> Tls Mqtt Disconnected.........");
}

void TMainWnd::onMqttTlsError(QMQTT::ClientError err)
{
    qDebug() << __func__ << " ........ err=" << err;

    emit logThiz(QString(" >>>>>>>>>>>>>>>>>> Tls Mqtt Error = %1").arg(err));
}

///////////////////////////////////////////////////////////////////////////////////////////////

void TMainWnd::onMqttWsConnected()
{
    _d->mqttWsPublisher->subscribed(_d->mqttTopicLe->text() , 2);

    qDebug() << __func__ << " ........ ";

    emit logThiz(" >>>>>>>>>>>>>>>>>> Ws Mqtt Connnected.........ip: " + _d->mqttWsPublisher->host().toString());
}

void TMainWnd::onMqttWsDisconnected()
{
    qDebug() << __func__ << " ........ ";

    emit logThiz(" >>>>>>>>>>>>>>>>>> Ws Mqtt Disconnected.........");
}

void TMainWnd::onMqttWsError(QMQTT::ClientError err)
{
    qDebug() << __func__ << " ........ err=" << err;

    emit logThiz(QString(" >>>>>>>>>>>>>>>>>> Ws Mqtt Error = %1").arg(err));
}
///////////////////////////////////////////////////////////////////////////////////////////////
void TMainWnd::onMqttWssConnected()
{
    _d->mqttWssPublisher->subscribed(_d->mqttTopicLe->text() , 2);

    qDebug() << __func__ << " ........ ";

    emit logThiz(" >>>>>>>>>>>>>>>>>> Wss Mqtt Connnected.........ip: " + _d->mqttWssPublisher->host().toString());
}

void TMainWnd::onMqttWssDisconnected()
{
    qDebug() << __func__ << " ........ ";

    emit logThiz(" >>>>>>>>>>>>>>>>>> Wss Mqtt Disconnected.........");
}

void TMainWnd::onMqttWssError(QMQTT::ClientError err)
{
    qDebug() << __func__ << " ........ err=" << err;

    emit logThiz(QString(" >>>>>>>>>>>>>>>>>> Wss Mqtt Error = %1").arg(err));
}



const QString TMainWnd::getCliId()
{
    static int cid_idx = 1;

    bool isBigBoard = true;

    QString dt = QString(TOOTBUILDDATE).replace("-","").replace("T","-") .left(14)  ;

    QString cid = QString("Langrensha-%1-%2-%3")
            .arg(isBigBoard ? "b" : "s")
            .arg(dt)
            .arg(QDateTime::currentDateTime().toSecsSinceEpoch() % 1000000 + cid_idx++) ;

    return  cid;
}


///////////////////////////////////////////////////////////////////////////////////////////////



static quint16  _number = 0;
void TMainWnd::doSendNow()
{
    QString rtnStr = _d->resultStrLe->text().trimmed();
    if(rtnStr.isEmpty()) return;

        QMQTT::Message message(_number++ , _d->mqttTopicLe->text(), rtnStr .toUtf8());
        message.setQos(2);

        switch (_d->tabWid->currentIndex()) {
        case 0:
            if(_d->mqttTcpPublisher)
                _d->mqttTcpPublisher->publish(message);
            break;
        case 1:
            if(_d->mqttTlsPublisher)
                _d->mqttTlsPublisher->publish(message);
            break;
        case 2:
            if(_d->mqttWsPublisher)
                    _d->mqttWsPublisher->publish(message);
            break;
        case 3:
            if(_d->mqttWssPublisher)
                _d->mqttWssPublisher->publish(message);
            break;

        default:
            break;
        }



        emit logThiz(QString("Sent: %1").arg(rtnStr));

}


void TMainWnd::testQuickSend()
{

    _d->resultStrLe->setText("{\"device\":\"desklamp\",\"number\":\"7\",\"step\":100,\"color\":\"green\",\"delay\":0,\"sounds\":\"\",\"timestamp\":15936779}");
    doSendNow();
    _d->resultStrLe->setText("{\"device\":\"desklamp\",\"number\":\"8\",\"step\":100,\"color\":\"blue\",\"delay\":0,\"sounds\":\"\",\"timestamp\":159367799}");
    doSendNow();
}



void TMainWnd::showFeedbackWnd()
{

    TMqttFeedbackWnd *fbWnd = new TMqttFeedbackWnd(
                _d->mqttTcpSvrLe->text(),
                _d->mqttTcpPortLe->text().toInt(),
                _d->mqttUsernameLe->text(),
                _d->mqttPasswdLe->text(),
                _d->mqttTopicLe->text()
                );
    fbWnd->show();

}


void TMainWnd::teAppendLog(const QString &l)
{
    _d->remoteMsgTe->append(tr("%1: %2")
                            .arg(QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss"))
                            .arg(l)
                            );
}
