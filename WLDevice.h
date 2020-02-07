#ifndef WLDevice_H
#define WLDevice_H

#include <QObject>
#include <QTimer>
#include <QMutex>
#include <QString>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>
#include <QThread>
#include <QTimer>
#include <QFile>
#include <QTextCodec>
#include "modules/WLModule.h"
#include "modules/WLModuleConnect.h"
#include "WLFlags.h"

//WLDevice
#define comDev_resetAll    1 //reset all
#define comDev_getVersion  2 //call version
#define comDev_getProp     3 //call prop
#define comDev_getModule   4 //call modules
#define comDev_getUID      5 //call	UID
#define comDev_getStatus   6 //call status

#define comDev_setStatus   10 //set status

#define sendDev_prop     100
#define sendDev_UID      102
#define sendDev_Module   101 //send modules
#define sendDev_UID      102 //send uid
#define sendDev_status   103 //send status
#define sendDev_version  104 //send version


#define errorDevice_nomodule 20

const QString errorDevice("0,no error\
,20,no module");

#define errorDevice_nomodule 20


class WLDevice: public WLModule
{
	Q_OBJECT

public:

   enum statusDevice{DEVICE_empty,DEVICE_init,DEVICE_ready};

	enum flag{fl_connect = 1<<0
	         ,fl_ready   = 1<<1};

	 WLDevice();
	~WLDevice();

	 void off();

QList <WLModule*> Modules;

quint32 UID96[3];
quint32 version;

public:

bool initFromSerialPort(QString portName);
bool initSerialPort(QString portName="");


WLModule* getModule(typeModule type);
     void addModule(WLModule *module);

WLModuleConnect* getModuleConnect() {return static_cast<WLModuleConnect*>(getModule(typeMConnect));}

void setNameDevice(QString _name) {if(nameDevice.isEmpty()||!_name.isEmpty()) nameDevice=_name;}
QString getNameDevice() {return nameDevice;}

bool initFromFile(QString nameFile);                              

bool writeToFile(QString nameFile);
bool writeToDir(QString dir) {return writeToFile(dir+"\\"+getNameDevice()+".xml");}

bool isReady()   {return Flags.get(fl_ready);}
bool isConnect() {return Flags.get(fl_connect);}

statusDevice getStatus() {return status;}

quint32 getVersion() {return version;}

private:	
	QMutex InputDataMutex;
	QMutex OutDataMutex;
	QMutex SendOutMutex;

    enum statusDevice status;

	QByteArray outData;

	QByteArray inBuf;

	QString nameDevice;

    QSerialPort *serialPort;

	WLFlags Flags;

    QString prop;

	quint32 error;	

protected:
virtual WLModule *createModule(QString name);
virtual WLModule *createModule(typeModule type);

public:
virtual void callPropModules();
virtual void callProp();
virtual void reset();

public:

private slots:	
void updateModules() {foreach(WLModule *Module,Modules)     Module->update();}

//void setStandby() {if(status!=DEVICE_empty) emit ChangedStatus(status=DEVICE_empty);}

virtual	void readSlot();

   void sendData();
   void startSend(QByteArray data);

public slots:
	void removeModules();
	void callModules();  
    void callVersion();
	void reconnectSerialPort();



public slots:
 virtual void callStatus();

signals:
    void readDataDevice();
    void createdModules();

	void sendMessage(QString,QString,int); 

	void ChangedErrorCut(quint8 index,quint8 error);

	void ChangedConnect(bool);
	void ChangedModules(int);
	void ChangedReady(bool);
	void ChangedProp(QString);
    void ChangedStatus(statusDevice);
	void ChangedUID96(quint32 *);

private:

void init(QXmlStreamReader &stream);

public:

QString getPortName()  {QString ret=""; if(serialPort) ret=serialPort->portName(); return ret;}
QString getProp()  {return prop;}
void 	getUID96(quint32 *uid) {memcpy(uid,UID96,12);}
void 	setStatus(enum statusDevice);

private slots:

	void callUID();

public:

virtual void writeXMLData(QXmlStreamWriter &stream);
virtual  void readXMLData(QXmlStreamReader &stream);

};

#endif //WLDEVICE_H
