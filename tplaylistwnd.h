/**************************************************************************
**   Copyright @ 2014 TOOTzoe.com
**   Special keywords: Administrator 2020/5/27 星期三 2020
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



#ifndef TPLAYLISTWND_H
#define TPLAYLISTWND_H

#include <QWidget>

QT_FORWARD_DECLARE_CLASS(QListWidget)
QT_FORWARD_DECLARE_CLASS(QListWidgetItem)
QT_FORWARD_DECLARE_CLASS(QTextEdit)

class TPlaylistWnd : public QWidget
{
    Q_OBJECT
public:
    explicit TPlaylistWnd( QStringList currStrLs, QWidget *parent = nullptr);

signals:

    void meClosed();

    void stopCurrPlaylist();
    void resultStrLs(const QStringList &);


protected:
    void closeEvent(QCloseEvent *event) override;


private slots:


    void okBtnClick();
    void listItChged(QListWidgetItem *item);


private:


    QListWidget *existFilenamesLsWid;
    QTextEdit *resultTe;


};

#endif // TPLAYLISTWND_H
