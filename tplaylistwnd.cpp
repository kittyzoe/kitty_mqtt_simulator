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

#include <QtWidgets>

#include "tplaylistwnd.h"

TPlaylistWnd::TPlaylistWnd(QStringList currStrLs, QWidget *parent) : QWidget(parent)
{

    setWindowTitle(tr("选择连播文件"));
    resize(600,600);


    QVBoxLayout *mainLO = new QVBoxLayout;

    QPushButton *clearBtn = new QPushButton(tr("清空所选"));
    clearBtn->setMaximumWidth(width() / 3);

    mainLO->addWidget(clearBtn);


    existFilenamesLsWid = new QListWidget();
    existFilenamesLsWid->setSelectionMode(QListWidget::MultiSelection);
    existFilenamesLsWid->addItems(currStrLs);

    connect(existFilenamesLsWid, &QListWidget::itemClicked, this, &TPlaylistWnd::listItChged);


    connect(clearBtn, &QPushButton::clicked, existFilenamesLsWid, &QListWidget::clearSelection);


    mainLO->addWidget(existFilenamesLsWid, 60);

    resultTe = new QTextEdit;
    connect(clearBtn, &QPushButton::clicked, resultTe, &QTextEdit::clear);


    mainLO->addWidget(resultTe,30);

    QHBoxLayout *btnLO = new QHBoxLayout;
    QPushButton *cancelBtn = new QPushButton(tr("取  消"));
    QPushButton *stopBtn = new QPushButton(tr("终止当前连播"));
    QPushButton *okBtn = new QPushButton(tr("开始连播"));


    connect(cancelBtn, &QPushButton::clicked, this, &TPlaylistWnd::close);
    connect(stopBtn, &QPushButton::clicked, this, &TPlaylistWnd::stopCurrPlaylist);
    connect(stopBtn, &QPushButton::clicked, this, &TPlaylistWnd::close);
    connect(okBtn, &QPushButton::clicked, this, &TPlaylistWnd::okBtnClick);

    btnLO->addWidget(cancelBtn);
    btnLO->addWidget(stopBtn);
    btnLO->addWidget(okBtn);

    mainLO->addLayout(btnLO);

    setLayout(mainLO);
}


void TPlaylistWnd::closeEvent(QCloseEvent * )
{
    emit meClosed();
}

void TPlaylistWnd::listItChged(QListWidgetItem * )
{

    QList<QListWidgetItem *>itemls = existFilenamesLsWid->selectedItems();

    resultTe->clear();

    for(int i = 0 ; i < itemls.size() ; i ++){
         QString txt = itemls.at(i)->data(Qt::DisplayRole).toString();
            resultTe->append(txt) ;
    }

}

void TPlaylistWnd::okBtnClick()
{

    QList<QListWidgetItem *>itemls = existFilenamesLsWid->selectedItems();

    QStringList strLs;

    for(int i = 0 ; i < itemls.size() ; i ++){
         strLs << itemls.at(i)->data(Qt::DisplayRole).toString();
    }

    emit resultStrLs(strLs);

    close();
}








