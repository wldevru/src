QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets serialport network

CONFIG += c++11

QMAKE_LFLAGS = -no-pie

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH +=\
           ../../../wlmotion\
           ../../../wlmotion/modules
SOURCES += \
    ../../../wlmotion/modules/wlaioput.cpp \
    ../../../wlmotion/modules/wlaxis.cpp \
    ../../../wlmotion/modules/wldcan.cpp \
    ../../../wlmotion/modules/wlelement.cpp \
    ../../../wlmotion/modules/wlencoder.cpp \
    ../../../wlmotion/modules/wlfreq.cpp \
    ../../../wlmotion/modules/wlioput.cpp \
    ../../../wlmotion/modules/wlmodule.cpp \
    ../../../wlmotion/modules/wlmoduleaioput.cpp \
    ../../../wlmotion/modules/wlmoduleaxis.cpp \
    ../../../wlmotion/modules/wlmoduleconnect.cpp \
    ../../../wlmotion/modules/wlmoduledcan.cpp \
    ../../../wlmotion/modules/wlmoduleencoder.cpp \
    ../../../wlmotion/modules/wlmodulefreq.cpp \
    ../../../wlmotion/modules/wlmodulefw.cpp \
    ../../../wlmotion/modules/wlmoduleioput.cpp \
    ../../../wlmotion/modules/wlmoduleplanner.cpp \
    ../../../wlmotion/modules/wlmodulepwm.cpp \
    ../../../wlmotion/modules/wlmodulewhell.cpp \
    ../../../wlmotion/modules/wlpwm.cpp \
    ../../../wlmotion/modules/wlwhell.cpp \
    ../../../wlmotion/wldevice.cpp \
    ../../../wlmotion/wlflags.cpp \
    ../../../wlmotion/wlmotion.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    ../../../wlmotion/modules/wlaioput.h \
    ../../../wlmotion/modules/wlaxis.h \
    ../../../wlmotion/modules/wldcan.h \
    ../../../wlmotion/modules/wlelement.h \
    ../../../wlmotion/modules/wlencoder.h \
    ../../../wlmotion/modules/wlfreq.h \
    ../../../wlmotion/modules/wlioput.h \
    ../../../wlmotion/modules/wlmodule.h \
    ../../../wlmotion/modules/wlmoduleaioput.h \
    ../../../wlmotion/modules/wlmoduleaxis.h \
    ../../../wlmotion/modules/wlmoduleconnect.h \
    ../../../wlmotion/modules/wlmoduledcan.h \
    ../../../wlmotion/modules/wlmoduleencoder.h \
    ../../../wlmotion/modules/wlmodulefreq.h \
    ../../../wlmotion/modules/wlmodulefw.h \
    ../../../wlmotion/modules/wlmoduleioput.h \
    ../../../wlmotion/modules/wlmoduleplanner.h \
    ../../../wlmotion/modules/wlmodulepwm.h \
    ../../../wlmotion/modules/wlmodulewhell.h \
    ../../../wlmotion/modules/wlpwm.h \
    ../../../wlmotion/modules/wlwhell.h \
    ../../../wlmotion/wldevice.h \
    ../../../wlmotion/wlflags.h \
    ../../../wlmotion/wlmotion.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
