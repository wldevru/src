#ifndef WLDevice_H
#define WLDevice_H

#include <QObject>
#include <QTimer>
#include <QMutex>
#include <QString>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>
#include <QThread>
#include <QTimer>
#include <QFile>
#include <QTextCodec>
#include "modules\WLModule.h"
#include "modules\WLModuleConnect.h"
#include "WLFlags.h"

#define comDev_reset       1 //reset device
#define comDev_getVer      2 //call version
#define comDev_getProp     3 //call property
#define comDev_getModule   4 //call modules
#define comDev_getUID      5 //call unique id
#define comDev_getStatus   6 //call status

#define comDev_setReady    10 //set status Ready

#define sendDev_Prop     100 //send prop
#define sendDev_Module   101 //send modules
#define sendDev_UID      102 //send uid
#define sendDev_status   103 //send status
#define sendDev_error    sendModule_error

#define errorDevice_nomodule 20

const QString errorDevice("0,no error\
,20,no module");

#define errorDevice_nomodule 20


class WLDevice: public WLModule
{
	Q_OBJECT

public:
	enum flag{fl_connect = 1<<0
	         ,fl_ready   = 1<<1};

	 WLDevice();
	~WLDevice();

	 void off();

QList <WLModule*> Modules;

quint32 UID96[3];
public:

bool initSerialPort(QString portName);


WLModule* getModule(typeModule type);
     void addModule(WLModule *module);

WLModuleConnect* getModuleConnect() {return static_cast<WLModuleConnect*>(getModule(typeMConnect));}

void setNameDevice(QString _name) {nameDevice=_name;}
QString getNameDevice() {return nameDevice;}

bool readFromFile(QString nameFile,bool add=true);
bool writeToFile(QString nameFile);
bool writeToDir(QString dir) {return writeToFile(dir+"\\"+getNameDevice()+".xml");}

bool isReady()   {return Flags.get(fl_ready);}
bool isConnect() {return Flags.get(fl_connect);}

private:	
	QMutex InputDataMutex;
	QMutex OutDataMutex;
	QMutex SendOutMutex;

	
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

public:

private slots:	

virtual	void readSlot();

   void sendData();
   void startSend(QByteArray data);

public slots:
	void removeModules();
	void callModules();
	void reconnectSerialPort();

signals:
    void readDataDevice();

	void sendMessage(QString,QString,int); 

	void ChangedErrorCut(quint8 index,quint8 error);

	void ChangedConnect(bool);
	void ChangedModules(int);
	void ChangedReady(bool);
	void ChangedProp(QString);
	void ChangedUID96(quint32 *);


public:
    QString	getPortName()  {QString ret; if(serialPort) ret+=serialPort->portName(); return ret;}
inline	QString  getProp()  {return prop;}
void 	getUID96(quint32 *uid) {memcpy(uid,UID96,12);}

private slots:

    void callProp();
	void callUID();

public:

virtual void writeXMLData(QXmlStreamWriter &stream);
virtual  void readXMLData(QXmlStreamReader &stream);

};

#endif //WLDEVICE_H
