QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets serialport network

CONFIG += c++11

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
           ../../../WLMotion\
           ../../../WLMotion/modules
SOURCES += \
    ../../../WLMotion/WLDevice.cpp \
    ../../../WLMotion/WLFlags.cpp \
    ../../../WLMotion/WLMotion.cpp \
    ../../../WLMotion/modules/WLAIOPut.cpp \
    ../../../WLMotion/modules/WLAxis.cpp \
    ../../../WLMotion/modules/WLDCan.cpp \
    ../../../WLMotion/modules/WLElement.cpp \
    ../../../WLMotion/modules/WLEncoder.cpp \
    ../../../WLMotion/modules/WLFreq.cpp \
    ../../../WLMotion/modules/WLIOPut.cpp \
    ../../../WLMotion/modules/WLModule.cpp \
    ../../../WLMotion/modules/WLModuleAIOPut.cpp \
    ../../../WLMotion/modules/WLModuleAxis.cpp \
    ../../../WLMotion/modules/WLModuleConnect.cpp \
    ../../../WLMotion/modules/WLModuleDCan.cpp \
    ../../../WLMotion/modules/WLModuleEncoder.cpp \
    ../../../WLMotion/modules/WLModuleFW.cpp \
    ../../../WLMotion/modules/WLModuleFreq.cpp \
    ../../../WLMotion/modules/WLModuleIOPut.cpp \
    ../../../WLMotion/modules/WLModulePWM.cpp \
    ../../../WLMotion/modules/WLModulePlanner.cpp \
    ../../../WLMotion/modules/WLModuleWhell.cpp \
    ../../../WLMotion/modules/WLPWM.cpp \
    ../../../WLMotion/modules/WLWhell.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    ../../../WLMotion/WLDevice.h \
    ../../../WLMotion/WLFlags.h \
    ../../../WLMotion/WLMotion.h \
    ../../../WLMotion/modules/WLAIOPut.h \
    ../../../WLMotion/modules/WLAxis.h \
    ../../../WLMotion/modules/WLDCan.h \
    ../../../WLMotion/modules/WLElement.h \
    ../../../WLMotion/modules/WLEncoder.h \
    ../../../WLMotion/modules/WLFreq.h \
    ../../../WLMotion/modules/WLIOPut.h \
    ../../../WLMotion/modules/WLModule.h \
    ../../../WLMotion/modules/WLModuleAIOPut.h \
    ../../../WLMotion/modules/WLModuleAxis.h \
    ../../../WLMotion/modules/WLModuleConnect.h \
    ../../../WLMotion/modules/WLModuleDCan.h \
    ../../../WLMotion/modules/WLModuleEncoder.h \
    ../../../WLMotion/modules/WLModuleFW.h \
    ../../../WLMotion/modules/WLModuleFreq.h \
    ../../../WLMotion/modules/WLModuleIOPut.h \
    ../../../WLMotion/modules/WLModulePWM.h \
    ../../../WLMotion/modules/WLModulePlanner.h \
    ../../../WLMotion/modules/WLModuleWhell.h \
    ../../../WLMotion/modules/WLPWM.h \
    ../../../WLMotion/modules/WLWhell.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
