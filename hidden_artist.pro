QT       += core gui
QT += qml quick widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET   = HiddenArtist
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

include(FramelessHelper/FramelessHelper.pri)

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    themecfgform.cpp \
    uiTheme.cpp

HEADERS += \
    mainwindow.h \
    themecfgform.h \
    uiTheme.h

FORMS += \
    mainwindow.ui \
    themecfgform.ui

TRANSLATIONS += \
    hidden_artist_zh_CN.ts

RESOURCES += \
    FramelessHelper.qrc

RC_ICONS =HuZhenZhen.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    FramelessHelper/FramelessHelper.pri
