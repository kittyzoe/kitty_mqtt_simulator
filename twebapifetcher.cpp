/**************************************************************************
**   Copyright @ 2014 TOOTzoe.com
**   Special keywords: zoe 8/7/2020 2020
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
#include <QtNetwork>

#include <QDebug>

#include "twebapifetcher.h"



class TWebApiFetcher::PrivateData{
public:

    QNetworkAccessManager *nam;

    QNetworkAccessManager *dlNam;
    QNetworkReply *dlRpl;
    QFile *dlFile;


     QList < QStringList > soundListStrLs;

     //

     QList<QStringList>   dlInfoItemStrLsLs;

};



TWebApiFetcher::TWebApiFetcher(QObject *parent) : QObject(parent)
    ,_d(new PrivateData)
{


#if 0

    QSslSocket *socket = new QSslSocket();

    QObject::connect(socket, &QSslSocket::encrypted,
                     [=](){qDebug() << socket->peerCertificate() << " cert.....................";}
    );

    socket->connectToHostEncrypted("stackoverflow.com", 443);

#endif






    _d->nam = new QNetworkAccessManager(this);


    QUrlQuery postData;

    quint64 ts = (QDateTime::currentDateTime().toSecsSinceEpoch() % 10000000000);

    postData.addQueryItem("appid","2007312053466994422");
    postData.addQueryItem("timestamp",QString::number(ts));
    postData.addQueryItem("key","8358b47d91d69559ac16ff4073f0f252");

    QByteArray baa = postData.toString(QUrl::FullyEncoded).toUtf8();

   QCryptographicHash hash(QCryptographicHash::Md5);
   hash.addData(baa);
    QByteArray fmd5 =    hash.result().toHex().toUpper();


    postData.removeQueryItem("key");           // Don't send key as ASCII
    postData.addQueryItem("sign",  fmd5 );

     baa = postData.toString(QUrl::FullyEncoded).toUtf8();

     qDebug() << "post data: " << baa;


   // QNetworkRequest req(QUrl("http://api1.langrensha.game/?ac=check_device_version"));
    QNetworkRequest req(QUrl("https://testapi.langrensha.game/?ac=check_device_version"));


   // QNetworkRequest req  (QUrl("https://testapi.langrensha.game/?ac=down_sound_list"));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    #if 1
    QSslConfiguration config = QSslConfiguration::defaultConfiguration();
        config.setProtocol(QSsl::AnyProtocol);
        req.setSslConfiguration(config);
       // req.setUrl(QUrl("https://testapi.langrensha.game/?ac=down_sound_list"));
       // addSSl(&request);
       // request.setHeader(QNetworkRequest::ServerHeader, "application/json");


      //  qDebug() << QSslSocket::sslLibraryBuildVersionString();
      //  qDebug() << QSslSocket::sslLibraryVersionString();



    #endif



    connect(_d->nam, &QNetworkAccessManager::finished , this, &TWebApiFetcher::webReqFinised);

    _d->nam ->post(req ,baa );


   //     _d->nam ->get(req);



}


QJsonValue findKey(const QString& key, const QJsonValue& value) {
    if (value.isObject()) {
        const QJsonObject obj = value.toObject();
        if (obj.contains(key))
            return obj.value(key);           // return 'early' if object contains key

        for (const auto& val  : obj) {
            QJsonValue recurse = findKey(key, val );  // call itself, forwarding a value
            if (!recurse.isNull())
                return recurse;              // value found, return 'early'
        }
    } else if (value.isArray()) {
        for (const auto& val  : value.toArray()) {
            QJsonValue recurse = findKey(key, val );
            if (!recurse.isNull())
                return recurse;
        }
    }

    return QJsonValue();          // base case: a null value
}

static QByteArray fileChecksum(const QString &fileName, QCryptographicHash::Algorithm hashAlgorithm)
{
    QFile f(fileName);
    if (f.open(QFile::ReadOnly)) {
        QCryptographicHash hash(hashAlgorithm);
        if (hash.addData(&f)) {
            return hash.result();
        }
    }
    return QByteArray();
}

void TWebApiFetcher::webReqFinised(QNetworkReply* rpl)
{
#if 0
    qDebug() << "Default SSL configuration isNull: "
                 << QSslConfiguration::defaultConfiguration().isNull();

        qDebug() << "SSL configuration used by QNAM isNull: "
                 << rpl->sslConfiguration().isNull();


        qDebug() << " -----------------------------------------------------------";
        qDebug() << rpl->errorString() << QSslSocket::supportsSsl() << QSslSocket::sslLibraryBuildVersionString() << QSslSocket::sslLibraryVersionString();
#endif


    QJsonDocument jdoc = QJsonDocument::fromJson(rpl->readAll());
    QJsonObject msgJObj = jdoc.object();
    rpl->deleteLater();

      qDebug() << msgJObj;


//     device_conf":["
//                "{"filelink":"http://uploads1.langrensha.game/motherboard/7430d8b95bb3d681f5459eaf583f53ff.zip",
//                  "md5":"7430d8b95bb3d681f5459eaf583f53ff",
//                  "name":"lrshelper.zip",
//                  "remark":"安安静静"
//                },

//                {"filelink":"http://uploads1.langrensha.game/motherboard/5dbb84e5cb0b7f68467116c915011438.zip",
//                 "md5":"5dbb84e5cb0b7f68467116c915011438",
//                 "name":"lrsgame.zip",
//                 "remark":"时时是"
//                }
//                ]

     QJsonArray jarr = findKey("device_conf", msgJObj).toArray() ;
     for(int i = 0  ; i < jarr.size() ; i ++){

         QJsonObject obj = jarr.at(i).toObject();


         _d->dlInfoItemStrLsLs  << (QStringList() << obj.value("filelink").toString()
                            << obj.value("name").toString()
                            << obj.value("md5").toString()
                            );




     }

    // qDebug() << " obj : =====+++++++++++++++++++++++++++++++++++++++++++++++" ;
    // qDebug() << dlInfoItemStrLsLs ;
     QTimer::singleShot(0,this,SLOT(dlUpdateZipFiles()));


     return;

  // QJsonValue jval = msgJObj.find("files", );

  // qDebug() <<  msgJObj.find("files") ;

   // QString ctCmd = msgJObj.value("ct").toString();
   // QString acType = msgJObj.value("ac").toString();


    QJsonValue myVal = findKey("files", msgJObj) ;

    if( myVal.isArray()){
       QJsonArray myArr = myVal.toArray();

       for(int i = 0 ; i < myArr.size() ; i ++)
       {
           QJsonValue v = myArr.at(i);
           QJsonObject obj = v.toObject();

           QString md5 =  obj.value("file_md5").toString();

           if(md5.size() == 32){
               _d->soundListStrLs << (QStringList() << md5 << obj.value("filepath").toString());
           }
       }

    }

  //  qDebug() << "value:" << findKey("files", msgJObj) ;

    QTimer::singleShot(0,this,SLOT(checkSoundListFiles()));

}


void TWebApiFetcher::dlUpdateZipFiles()
{

    foreach (QStringList strLs, _d->dlInfoItemStrLsLs) {
        if(strLs.size() != 3 ) continue;

            dlZipFile(strLs);
    }

}

void TWebApiFetcher::dlZipFile(QStringList strls)
{

    QNetworkRequest req  (QUrl( strls.at(0).toLocal8Bit()));

    QSslConfiguration config = QSslConfiguration::defaultConfiguration();
    config.setProtocol(QSsl::AnyProtocol);
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    req.setSslConfiguration(config);

    QString fn = strls.at(1);

    _d->dlFile = new QFile(QString(fn) );
    if(!_d->dlFile->open(QIODevice::WriteOnly)){
        qDebug() << " Create download file error....." << _d->dlFile->errorString();
        _d->dlFile = nullptr;
        return;
    }
    _d->dlFile->reset();


    _d->dlNam = new QNetworkAccessManager(this);
    _d->dlRpl = _d->dlNam ->get(req);


    connect(_d->dlRpl, SIGNAL(error(QNetworkReply::NetworkError)) , this, SLOT(dlError(QNetworkReply::NetworkError)));
    connect(_d->dlRpl, &QNetworkReply::downloadProgress , this, &TWebApiFetcher::updateDlProgress);
    connect(_d->dlRpl, &QNetworkReply::finished , this, &TWebApiFetcher::dlFinished);


    QEventLoop evtloop;
    connect(_d->dlRpl,SIGNAL(finished()) , &evtloop, SLOT(quit()));
    evtloop.exec();




    QString thizFileMd5 = fileChecksum(QString(fn), QCryptographicHash::Md5).toHex().toLower();

    QString m = strls.at(2);

    qDebug() << "ori Md5: " << m;
    qDebug() << "new Md5: " << thizFileMd5;

   if(m.toLower() != thizFileMd5){
       // some error when download files.....so we restart....
       qDebug() << " Md5 checksum Not the same, download failed.....";
       return  ;
   }

   qDebug() << " ******************* Successfully download file: " << fn;

}

void TWebApiFetcher::checkSoundListFiles()
{
    foreach (QStringList strLs, _d->soundListStrLs) {
        if(strLs.size() != 2 ) continue;

        if(strLs.at(1).toLower().endsWith("sounds_def.zip")){ // default sound list.....

                if(!checkOneSoundPackage(strLs.at(0), "sounds_def")){
                    qDebug() << " default sound files need update....";
                    downloadUnpackSounds(strLs.at(1) ,"sounds_def" , strLs.at(0) );
                }
        }else if(strLs.at(1).toLower().endsWith("sounds_girl.zip")){ // default sound list.....

            if(!checkOneSoundPackage(strLs.at(0), "sounds_girl")){
                qDebug() << " girl sound files need update....";
                downloadUnpackSounds(strLs.at(1),"sounds_girl" , strLs.at(0));
            }
    }

    }


}

bool TWebApiFetcher::checkOneSoundPackage(const QString &md5, const QString &path)
{
    QString fn = QString("mp3s/%1/.md5").arg(path);
    QFile md5f (fn);
    if(md5f.open(QIODevice::ReadOnly)){
        QString str = QString(md5f.readAll()).trimmed() ;
        if(str == md5){
            qDebug() << " Md5 is then same , no need update sound files....." << path;
            return true;
        }
    }

    return  false;
}

void TWebApiFetcher::downloadUnpackSounds(const QString &url ,const QString &p ,const QString &m  )
{

    QNetworkRequest req  (QUrl( url.toLocal8Bit()));

    QSslConfiguration config = QSslConfiguration::defaultConfiguration();
    config.setProtocol(QSsl::AnyProtocol);
    req.setSslConfiguration(config);


    _d->dlFile = new QFile(QString("mp3s/.zip") );
    if(!_d->dlFile->open(QIODevice::WriteOnly)){
        qDebug() << " Create download file error....." << _d->dlFile->errorString();
        _d->dlFile = nullptr;
        return;
    }
    _d->dlFile->reset();


    _d->dlNam = new QNetworkAccessManager(this);
    _d->dlRpl = _d->dlNam ->get(req);


    connect(_d->dlRpl, SIGNAL(error(QNetworkReply::NetworkError)) , this, SLOT(dlError(QNetworkReply::NetworkError)));
    connect(_d->dlRpl, &QNetworkReply::downloadProgress , this, &TWebApiFetcher::updateDlProgress);
    connect(_d->dlRpl, &QNetworkReply::finished , this, &TWebApiFetcher::dlFinished);


    QEventLoop evtloop;
    connect(_d->dlRpl,SIGNAL(finished()) , &evtloop, SLOT(quit()));
    evtloop.exec();


    QString cmd = QString("cd %1/mp3s;unzip -oqq .zip;echo \"%2\" > %3/.md5;sync;rm -rf __MACOSX .zip")
            .arg(QCoreApplication::applicationDirPath())
            .arg(m)
            .arg(p)
                  ;
    system(cmd.toLocal8Bit());

   // system(QString("echo \"%1\" > %2/.md5").arg(m).arg(p).toLocal8Bit());

}

void TWebApiFetcher::dlError(QNetworkReply::NetworkError  )
{
    qDebug() << __func__;

    cleanupDlStuff();
}

void TWebApiFetcher::updateDlProgress(qint64 read,qint64 total)
{
    if(_d->dlRpl){
      QByteArray ba =  _d->dlRpl->readAll();
      //QDataStream ds(_d->dlFile);
      //ds << ba;
      _d->dlFile->write(ba);
    }
    qDebug() << " downloaded: " << read  << " total: " << total;
}

void TWebApiFetcher::dlFinished()
{
    qDebug() << " dlFinished......: "  ;

   cleanupDlStuff();
}

void TWebApiFetcher::cleanupDlStuff()
{
    if(_d->dlRpl){
        _d->dlRpl->deleteLater();
        _d->dlRpl = nullptr;
    }

    if(_d->dlNam){
        _d->dlNam->deleteLater();
        _d->dlNam = nullptr;
    }

    if(_d->dlFile ){
        if(_d->dlFile->isOpen())
            _d->dlFile->close();
        _d->dlFile = nullptr;
    }
}

// https://api.langrensha.game/?ac=down_sound_list


// https://testlangrensha.aostatic.com/sounds_def.zip








