#ifndef WLModuleCONNECT_H
#define WLModuleCONNECT_H

#include <QObject>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QStringList>
#include <QMutex>
#include "wlmodule.h"


#define comMCon_setTimers 1
#define comMCon_setEnableHeart 2

#define sigMCon_heart 100 //heart connect

#define MCF_timeout    1<<0
#define MCF_outBufFull 1<<1
#define MCF_enbheart   1<<2



class WLModuleConnect : public WLModule
{
	Q_OBJECT

public:
    WLModuleConnect(QObject *parent=nullptr);
	~WLModuleConnect();

private:

WLFlags Flags;
bool conOk;

quint16 sizeInBuf;
quint16 sizeOutBuf;

quint16 timeoutConnect_ms;
quint16 timeHeart_ms;

QTimer *timerHeart;
QTimer *timerConnect;
public:
	bool isConnect() {return conOk;}

    bool setTimersConnect(quint16 timeout_ms,quint16 heart_ms);

    quint16 getTimeoutConnectVal() {return timeoutConnect_ms;}
    quint16 getTimeHeartVal() {return timeHeart_ms;}

    bool setEnableHeart(bool enable);

    bool isEnableHeart();

public slots:	
	void sendHeart();
	void restartHeart();

private slots:
    void setTimeoutHeart();
    void setTimeoutConnect();

signals:
    void timeoutHeart();
    void timeoutConnect();
    void backupConnect();

    void changedConnect(bool);

public:
virtual void writeXMLData(QXmlStreamWriter &stream);
virtual void  readXMLData(QXmlStreamReader &stream);
virtual void readCommand(QByteArray data); 
};

#endif // WLModulePLANNER_H

