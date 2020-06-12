#ifndef WLDevice_H
#define WLDevice_H

#include <QObject>
#include <QTimer>
#include <QMutex>
#include <QString>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QUdpSocket>
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
struct WLDeviceInfo
{
QString  name;
QString  comPort;
QHostAddress  HA;
QString UID96;
quint32 version;
};

class WLDevice: public WLModule
{
	Q_OBJECT

public:

   enum statusDevice{DEVICE_empty,DEVICE_init,DEVICE_connect};

    enum flag{fl_openconnect = 1<<0
             ,fl_connect = 1<<1
             ,fl_ready   = 1<<2};

	 WLDevice();
	~WLDevice();

	 void off();

QList <WLModule*> Modules;

private:

    WLDeviceInfo deviceInfo;
    QString  UID96;
    quint32 version;

    QMutex InputDataMutex;
    QMutex OutDataMutex;
    QMutex SendOutMutex;
    QMutex connectMutex;

    enum statusDevice status;

    QByteArray outData;

    QByteArray inBuf;

    QString m_nameDevice;

    QSerialPort m_serialPort;

    QHostAddress   m_HA;
    QUdpSocket   m_udpSocket;

    WLFlags Flags;

    QString prop;

    quint32 error;

public:

bool initSerialPort(QString portName="");
bool initUdpSocket(QHostAddress HA);

bool  openConnect();

WLModule* getModule(typeModule type);
     void addModule(WLModule *module);

WLModuleConnect* getModuleConnect() {return static_cast<WLModuleConnect*>(getModule(typeMConnect));}

void setNameDevice(QString _name) {if(m_nameDevice.isEmpty()||!_name.isEmpty()) m_nameDevice=_name;}
QString getNameDevice() {return m_nameDevice;}

bool initFromFile(QString nameFile);                              

bool writeToFile(QString nameFile);
bool writeToDir(QString dir) {return writeToFile(dir+"\\"+getNameDevice()+".xml");}

bool isReady()   {return Flags.get(fl_ready);}
bool isOpenConnect() {return Flags.get(fl_openconnect);}
bool isConnect() {return Flags.get(fl_connect);}

statusDevice getStatus() {return status;}

quint32 getVersion() {return version;}
void    setVersion(quint32 _ver) {version=_ver; emit changedVersion(version);}

protected:
virtual WLModule *createModule(QString name);
virtual WLModule *createModule(typeModule type);

public:
virtual void callPropModules();
virtual void callProp();
virtual void reset();

public:

private slots:	
void updateModules() {qDebug()<<"updaet Modules";foreach(WLModule *Module,Modules)     Module->update();}
//void setStandby() {if(status!=DEVICE_empty) emit ChangedStatus(status=DEVICE_empty);}

virtual	void readSlot();

void onErrorSerialPort(QSerialPort::SerialPortError serialPortError);

   void sendData();
   void startSend(QByteArray data);

public slots:
	void removeModules();
	void callModules();  
    void callVersion();
	void reconnectSerialPort();

    void closeConnect();

public slots:
 virtual void callStatus();

signals:
    void readDataDevice();
    void createdModules();

    void reconnected();

    void changedConnect(bool);
    void changedModules(int);
    void changedReady(bool);
    void changedProp(QString);
    void changedStatus(statusDevice);
    void changedUID96(QString);
    void changedVersion(quint32);

private:

void init(QXmlStreamReader &stream);

public:

static QList<WLDeviceInfo> availableDevices();

WLDeviceInfo getInfo();
void setInfo(WLDeviceInfo info);

QHostAddress getHA() {return m_HA;}

QString getPortName()  {return m_serialPort.portName();}
QString getProp()  {return prop;}
QString getUID96() {return UID96;}
   void setUID96(QString);
void 	setStatus(enum statusDevice);

private slots:

	void callUID();

public:

virtual void writeXMLData(QXmlStreamWriter &stream);
virtual  void readXMLData(QXmlStreamReader &stream);

};

#endif //WLDEVICE_H
