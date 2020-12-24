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



#ifndef TLAMPBASICWID_H
#define TLAMPBASICWID_H

#include <QWidget>
#include <QPushButton>





QT_FORWARD_DECLARE_CLASS(QButtonGroup)



class TColorBtn : public QPushButton
{
    Q_OBJECT
public:
    explicit TColorBtn(const QString &str, QWidget *parent = 0):QPushButton(str,parent){;}

signals:

public slots:



protected:
    void paintEvent(QPaintEvent *);



private:


};


class TLampBasicWid : public QWidget
{
    Q_OBJECT
public:
    explicit TLampBasicWid(quint8 n, QWidget *parent = 0);

signals:

    void lampChged();

    void allBtnCkhOrNot(bool);

public slots:




protected:
    void paintEvent(QPaintEvent *);


    quint8 thizNum;
     quint8 crBits;
    quint8 mBrightness;

private slots:
    void crBtnClick(int,bool);



    void crCbChged(int);


private:
    void initdata();

    void setupUI();




    QList<QColor> mCrLs;

    QButtonGroup *btnsGp;



};

///////////////////////////////////////////////////


class TDeskLampWid : public TLampBasicWid
{
    Q_OBJECT
public:
    explicit TDeskLampWid(quint8 n,QWidget *parent = 0);

signals:
      void deskLampChged(quint8 n, quint8 crBit , quint8 brightness);

public slots:


      void chkUnchkAllDesklamp(bool isD);


protected:
    //void paintEvent(QPaintEvent *);



private slots:
      void handleLampChged();


private:




};




///////////////////////////////////////////////////


class TAmbientLampWid : public TLampBasicWid
{
    Q_OBJECT
public:
    explicit TAmbientLampWid(quint8 n,QWidget *parent = 0);

signals:

    void ambientLampChged(quint8 n, quint8 crBit , quint8 brightness);

public slots:

        void chkUnchkAllAmbientlamp(bool isD);


protected:

private slots:
      void handleLampChged();


private:



};






#endif // TLAMPBASICWID_H
