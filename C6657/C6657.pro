QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES += _WIN32_WINNT=0x0601
SOURCES += \
    c6657serialport.cpp \
    c6657udp.cpp \
    iioreceiver.cpp \
    ioworker.cpp \
    main.cpp \
    serialincomingprocessor.cpp \
    udpincomingprocessor.cpp \
    wmain.cpp

HEADERS += \
    IncomingProcessor.h \
    c6657serialport.h \
    c6657udp.h \
    iioreceiver.h \
    ioworker.h \
    serialincomingprocessor.h \
    udpincomingprocessor.h \
    wmain.h

FORMS += \
    main.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
