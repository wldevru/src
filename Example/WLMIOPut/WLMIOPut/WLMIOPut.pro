#-------------------------------------------------
#
# Project created by QtCreator 2019-10-22T07:51:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets serialport

TARGET = WLMIOPut
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += C:/QT/WLMotion/
CONFIG += c++11

SOURCES += \
        ../../../WLMotion/WLDevice.cpp \
        ../../../WLMotion/WLMotion.cpp \
        ../../../WLMotion/modules/WLAXIS.cpp \
        ../../../WLMotion/modules/WLDCan.cpp \
        ../../../WLMotion/modules/WLElement.cpp \
        ../../../WLMotion/modules/WLEncoder.cpp \
        ../../../WLMotion/modules/WLFreq.cpp \
        ../../../WLMotion/modules/WLIOPut.cpp \
        ../../../WLMotion/modules/WLModule.cpp \
        ../../../WLMotion/modules/WLModuleAXIS.cpp \
        ../../../WLMotion/modules/WLModuleConnect.cpp \
        ../../../WLMotion/modules/WLModuleDCAN.cpp \
        ../../../WLMotion/modules/WLModuleEncoder.cpp \
        ../../../WLMotion/modules/WLModuleFW.cpp \
        ../../../WLMotion/modules/WLModuleFreq.cpp \
        ../../../WLMotion/modules/WLModuleIOPUT.cpp \
        ../../../WLMotion/modules/WLModulePWM.cpp \
        ../../../WLMotion/modules/WLModulePlanner.cpp \
        ../../../WLMotion/modules/WLModuleWhell.cpp \
        ../../../WLMotion/modules/WLPWM.cpp \
        ../../../WLMotion/modules/WLWhell.cpp \
        ../../../WLMotion/wlflags.cpp \
        main.cpp \
        widget.cpp

HEADERS += \
        ../../../WLMotion/WLDevice.h \
        ../../../WLMotion/WLMotion.h \
        ../../../WLMotion/modules/WLAXIS.h \
        ../../../WLMotion/modules/WLDCan.h \
        ../../../WLMotion/modules/WLElement.h \
        ../../../WLMotion/modules/WLEncoder.h \
        ../../../WLMotion/modules/WLFreq.h \
        ../../../WLMotion/modules/WLIOPut.h \
        ../../../WLMotion/modules/WLModule.h \
        ../../../WLMotion/modules/WLModuleAxis.h \
        ../../../WLMotion/modules/WLModuleConnect.h \
        ../../../WLMotion/modules/WLModuleDCAN.h \
        ../../../WLMotion/modules/WLModuleEncoder.h \
        ../../../WLMotion/modules/WLModuleFW.h \
        ../../../WLMotion/modules/WLModuleFreq.h \
        ../../../WLMotion/modules/WLModuleIOPUT.h \
        ../../../WLMotion/modules/WLModulePWM.h \
        ../../../WLMotion/modules/WLModulePlanner.h \
        ../../../WLMotion/modules/WLModuleWhell.h \
        ../../../WLMotion/modules/WLPWM.h \
        ../../../WLMotion/modules/WLWhell.h \ \
    ../../../WLMotion/wlflags.h \
    widget.h

        widget.h

FORMS += \
        widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
