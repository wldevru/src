#ifndef WLDevice_H
#define WLDevice_H

#include <QObject>
#include <QCoreApplication>
#include <QTimer>
#include <QElapsedTimer>
#include <QMutex>
#include <QString>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QUdpSocket>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>
#include <QThread>
#include <QTimer>
#include <QFile>
#include <QTextCodec>
#include <QNetworkInterface>
#include "modules/wlmodule.h"
#include "modules/wlmoduleconnect.h"
#include "wlflags.h"

//WLDevice
#define comDev_resetAll    1 //reset all
#define comDev_getVersion  2 //call version
#define comDev_getProp     3 //call prop
#define comDev_getModule   4 //call modules
#define comDev_getUID      5 //call	UID
#define comDev_getStatus   6 //call status
#define comDev_getVersionProtocol  7 //call protocol

#define comDev_setStatus   10 //set status
#define comDev_reboot      11 //rebooting

#define sendDev_prop     100
#define sendDev_UID      102
#define sendDev_Module   101 //send modules
#define sendDev_UID      102 //send uid
#define sendDev_status   103 //send status
#define sendDev_version  104 //send version

#define errorDevice_nomodule 20

#define DEFINE_TIMERWAITUSB  2
#define DEFINE_TIMERWAITETH  1

#ifndef UDPPORT
 #define UDPPORT 2020
#endif

#define WLM_PROTOCOL 0x0001

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

bool isValid(WLDeviceInfo info)
                              {
                               return name==info.name
                                    &&UID96==info.UID96;
                              }
};

class WLDevice: public WLModule
{
	Q_OBJECT

public:

   enum statusDevice{DEVICE_empty,DEVICE_init,DEVICE_connect};

    enum flag{fl_openconnect = 1<<0
             ,fl_connect = 1<<1
            // ,fl_ready   = 1<<2
             ,fl_waitack = 1<<3};

	 WLDevice();
	~WLDevice();

	 void off();


private:
    QList <WLModule*> m_modules;

    WLDeviceInfo m_deviceInfo;

    QString  m_UID96;
    quint32  m_version;
    quint16  m_versionProtocol;

    QMutex InputDataMutex;
    QMutex OutDataMutex;
    QMutex SendOutMutex;
    QMutex connectMutex;

    enum statusDevice status;

    QByteArray outBuf;
    QByteArray inBuf;

    QString m_nameDevice;

    QSerialPort m_serialPort;

    QHostAddress  m_HA;
    QUdpSocket   m_udpSocket;

    WLFlags Flags;

    QString m_prop;

    quint32 error;

    QByteArray m_bufEth;
    QTimer    *m_timerEth;
    quint8    m_countTxPacket;
    quint8    m_countRxPacket;

    QTimer *m_timerSend;

public:

bool isValidProtocol() {return m_versionProtocol==WLM_PROTOCOL;}

bool initSerialPort(QString portName="");
bool initUdpSocket(QHostAddress HA);

bool  openConnect();

WLModule* getModule(typeModule type);
     void addModule(WLModule *module);

QList<WLModule *> getModules() const;

WLModuleConnect* getModuleConnect() {return static_cast<WLModuleConnect*>(getModule(typeMConnect));}

void setNameDevice(QString _name) {if(m_nameDevice.isEmpty()||!_name.isEmpty()) m_nameDevice=_name;}
QString getNameDevice() {return m_nameDevice;}

bool initFromFile(QString nameFile);                              

bool writeToFile(QString nameFile);
bool writeToDir(QString dir) {return writeToFile(dir+"\\"+getNameDevice()+".xml");}

//bool isReady()   {return Flags.get(fl_ready);}
bool isOpenConnect() {return Flags.get(fl_openconnect);}
bool isConnect() {return Flags.get(fl_connect);}

statusDevice getStatus() {return status;}

quint32 getVersion() {return m_version;}

void    setVersion(quint32 _ver) {m_version=_ver; emit changedVersion(m_version);}
void    setVersionProtocol(quint16 _ver);

void clearBuf();

protected:
virtual WLModule *createModule(QString name);
virtual WLModule *createModule(typeModule type);

public:
virtual void callPropModules();
virtual void callProp();
virtual void reset();

public:

private slots:	

void sendEthData();
void updateReady();

virtual	void readSlot();

    void onErrorSerialPort(QSerialPort::SerialPortError serialPortError);

   void sendData();
   void startSend(QByteArray data);

public slots:
	void removeModules();
	void callModules();  
    void callVersion();
    void callVersionProtocol();
	void reconnectSerialPort();

    void closeConnect();

    void update();

public slots:
 virtual void callStatus();

signals:
    void readDataDevice();
    void createdModules();

    void reconnected();

    void changedConnect(bool);
    void changedModules(int);
    void changedProp(QString);
    void changedStatus(statusDevice);
    void changedUID96(QString);
    void changedVersion(quint32);
    void changedVersionProtocol(quint16);

private:

void init(QXmlStreamReader &stream);
void decodeInputData();
public:

static QList<WLDeviceInfo> availableDevices();

void reboot(uint8_t type);

WLDeviceInfo getInfo();

void setInfo(WLDeviceInfo info);

QHostAddress getHA() {return m_HA;}

QString getPortName()  {return m_serialPort.portName();}
QString getProp()  {return m_prop;}
QString getUID96() {return m_UID96;}
   void setUID96(QString);
   void setStatus(enum statusDevice);

private slots:

	void callUID();

public:

virtual void writeXMLData(QXmlStreamWriter &stream);
virtual  void readXMLData(QXmlStreamReader &stream);


    };

#endif //WLDEVICE_H
