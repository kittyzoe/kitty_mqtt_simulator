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


#include <QApplication>
#include <QFile>
#include "tmainwnd.h"
//#include "twsconn.h"
#include "twebapifetcher.h"
#include "twsaudio.h"

int main(int argc, char** argv)
{

    QApplication app(argc, argv);


    TMainWnd wnd;
    wnd.show();



  //  TWsAudio wsaudio;


    return app.exec();
}

// find *.mp3 -exec lame -b 48 --resample 44.1 {} \; && find *.mp3.mp3 -exec rename -f 's/.mp3//' {} \;





