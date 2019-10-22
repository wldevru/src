#ifndef WLModuleCONNECT_H
#define WLModuleCONNECT_H

#include <QObject>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QStringList>
#include <QMutex>
#include "WLModule.h"
/*
const QString errorPlanner("0,no error\
,1,emg stop\
,2,buf is full\
,3,wrong set data");

const QString errorElementPlanner("0,no error\
,1,wrong ULine position\
,2,wrong ULine mov distance\
,3,wrong Circ position\
,4,wrong Circ radius\
,5,error Line calc\
,6,wrong Line count");
*/

#define sigMCon_heart 100 //heart connect

class WLModuleConnect : public WLModule
{
	Q_OBJECT

public:
	WLModuleConnect(QObject *parent=0);
	~WLModuleConnect();

private:

bool conOk;

quint16 sizeInBuf;
quint16 sizeOutBuf;

QTimer *timerHeart;
public:
	bool isConnect() {return conOk;}
public slots:	
	void sendHeart();
	void restartHeart();

private slots:
	void setTimeoutConnect();

signals:
	void timeoutConnect();	

public:
virtual void writeXMLData(QXmlStreamWriter &stream);
virtual void  readXMLData(QXmlStreamReader &stream);
virtual void readCommand(QByteArray data); 
};

#endif // WLModulePLANNER_H

