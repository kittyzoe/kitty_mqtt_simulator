

TARGET = lrssimulator_v120



QT += core widgets network websockets


win7:{
INCLUDEPATH += E:/workprj/qmqtt/src/mqtt

LIBS += Qt5Qmqtt.dll
}

INCLUDEPATH += /home/zoe/workprj/misc/qmqtt/src/mqtt

LIBS += -L/home/zoe/workprj/misc/qmqtt/pc64qt5142lib \
        -lQt5Qmqtt

LIBS += -L/home/zoe/workprj/misc/openssl/toot_build_out \
        -lcrypto -lssl


QMAKE_LFLAGS += -s

QMAKE_CXXFLAGS += "-std=c++11"


message($$system(date -I))

TOOTBDATE = '\\"$$system(date -I\'minute\')\\"'
DEFINES += TOOTBUILDDATE=\"$${TOOTBDATE}\"


QMAKE_POST_LINK =


SOURCES += \
    main.cpp \
    tmainwnd.cpp \
    tlampbasicwid.cpp \
    tmqttfeedbackwnd.cpp \
    tplaylistwnd.cpp \
    twebapifetcher.cpp \
    twsaudio.cpp \
    twsconn.cpp

HEADERS += \
    tmainwnd.h \
    tlampbasicwid.h \
    tmqttfeedbackwnd.h \
    tplaylistwnd.h \
    twebapifetcher.h \
    twsaudio.h \
    twsconn.h









