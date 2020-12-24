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



#ifndef TWEBAPIFETCHER_H
#define TWEBAPIFETCHER_H

#include <QObject>

#include <QNetworkReply>




//QT_FORWARD_DECLARE_CLASS(QNetworkReply)


class TWebApiFetcher : public QObject
{
    Q_OBJECT
public:
    explicit TWebApiFetcher(QObject *parent = nullptr);

signals:




private slots:
    void webReqFinised(QNetworkReply*);


    void checkSoundListFiles();
    //
    void dlError(QNetworkReply::NetworkError err);
    void updateDlProgress(qint64 read,qint64 total);
    void dlFinished();
    //
    void dlUpdateZipFiles();

private:


    bool checkOneSoundPackage(const QString &md5, const QString &path);
    void downloadUnpackSounds(const QString &url, const QString &p, const QString &m);

    void cleanupDlStuff();


    //void dlZipFile(const QString &url, const QString &n , const QString &md5);
    void dlZipFile(QStringList strls);



private: // disable copying


       ////////////////////////////////////////
       class PrivateData;
       PrivateData *_d;
       TWebApiFetcher::PrivateData *fetchPrivateData() const;



};

#endif // TWEBAPIFETCHER_H
