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


#include <QtCore>
#include <QtWidgets>


#include "tlampbasicwid.h"

TLampBasicWid::TLampBasicWid(quint8 n, QWidget *parent) : QWidget(parent)
  ,thizNum(n),mBrightness(100)
{

    setFixedSize(QSize(80,70));


    initdata();
    setupUI();

}

void TLampBasicWid::initdata()
{

    crBits = 0;

    mCrLs << Qt::black
          << Qt::red << Qt::green << Qt::yellow
          << Qt::blue << Qt::magenta << Qt::cyan
          << Qt::white
            ;


}

void TLampBasicWid::paintEvent(QPaintEvent *evt)
{
    QWidget::paintEvent(evt);

    QPainter p(this);

    QColor cr = mCrLs.at(crBits);

    if(mBrightness == 0)
        cr = Qt::black;

    p.fillRect(rect().adjusted(2,2,-3,-3),cr );

    p.setPen(Qt::gray);
    QFont fn = p.font();
    fn.setPixelSize(26);
    p.setFont(fn);
    p.drawText(rect().adjusted(4,8,0,0),Qt::AlignBottom | Qt::AlignLeft , QString::number(thizNum));

}


void TLampBasicWid::setupUI()
{
    QPalette pal = palette();
    pal.setColor(QPalette::Foreground , Qt::gray);
    setPalette(pal);


   QVBoxLayout * mainLO = new QVBoxLayout;
    mainLO->setMargin(1);
    mainLO->setSpacing(0);

    //
    QHBoxLayout *btnsLO = new QHBoxLayout;
    btnsLO->setMargin(1);
    btnsLO->setSpacing(0);

    QStringList crStrLs;
    crStrLs << tr("R")<< tr("G")<< tr("B") ;

    btnsGp = new QButtonGroup;
    btnsGp->setExclusive(false);
    for(int i = 0 ; i < crStrLs.size(); i ++){
        TColorBtn *btn = new TColorBtn(crStrLs.at(i));
        btn->setCheckable(true);
        btnsLO->addWidget(btn);
        btnsGp->addButton(btn,i);
        connect(this,&TLampBasicWid::allBtnCkhOrNot, btn, &TColorBtn::setChecked);
    }

    connect(btnsGp,SIGNAL(buttonToggled(int,bool)) , SLOT(crBtnClick(int,bool)));

    mainLO->addLayout( btnsLO, 50 );


    QHBoxLayout *hLO = new QHBoxLayout;
    hLO->setSpacing(1);
    hLO->setMargin(2);


    hLO->addWidget(new QLabel(tr("亮度:")));


    QComboBox *brnCb = new QComboBox();
    brnCb->setMinimumWidth(42);
    QStringList valStrLs;
    for(int i = 0 ; i <= 100; i ++)
        valStrLs << QString::number(i);
    brnCb->addItems(valStrLs);
    brnCb->setCurrentIndex(100);
    connect(brnCb,SIGNAL(activated(int)), SLOT(crCbChged(int)));

    hLO->addWidget(brnCb);

    mainLO->addLayout(hLO);
    mainLO->addStretch(200);

    setLayout(mainLO);

}

void TLampBasicWid::crBtnClick(int idx, bool isD)
{
    if(isD)
    crBits |= (1 << idx);
    else
        crBits ^= (1 << idx);




    update();

    emit lampChged();
}


void TLampBasicWid::crCbChged(int v)
{
    mBrightness = v;
    if(crBits   > 0)
       emit lampChged();

    if(mBrightness == 0){
        foreach (QAbstractButton *b, btnsGp->buttons()) {
            b->setChecked(false);
            b->updateGeometry();
        }
    }

    update();
}



///////////////////////////////////////////////////////////////////

TDeskLampWid::TDeskLampWid(quint8 n,QWidget *parent) : TLampBasicWid(n,parent)
{
    connect(this, SIGNAL(lampChged()), SLOT(handleLampChged()));
}

void TDeskLampWid::handleLampChged()
{
    emit deskLampChged(thizNum, crBits , mBrightness);
}


void TDeskLampWid::chkUnchkAllDesklamp( bool isD)
{
    emit allBtnCkhOrNot(isD);

}


///////////////////////////////////////////////////////////////////

TAmbientLampWid::TAmbientLampWid(quint8 n, QWidget *parent) : TLampBasicWid(n,parent)
{

    connect(this, SIGNAL(lampChged()), SLOT(handleLampChged()));
}

void TAmbientLampWid::handleLampChged()
{
    emit ambientLampChged(thizNum, crBits , mBrightness);
}

void TAmbientLampWid::chkUnchkAllAmbientlamp( bool isD)
{

    emit allBtnCkhOrNot(isD);
}


///////////////////////////////////////////////////////////////////////////////////////

void TColorBtn::paintEvent(QPaintEvent *evt)
{
    QPushButton::paintEvent(evt);

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    QRect crRc = rect().adjusted(3,3,-4,-4);

    QColor cr ;
    if(text() == QString("R"))
        cr = QColor(255,0,0);
    else if(text() == QString("G"))
        cr = QColor(0,255,0);
    if(text() == QString("B"))
           cr = QColor(0,0,255);

    p.setPen(QPen(QBrush(cr),3));

    if(isChecked()){
        p.setBrush(cr);
    }else{
        p.setBrush(Qt::NoBrush);
    }

    p.drawEllipse(crRc);

}








