#ifndef WLMODULEFW_H
#define WLMODULEFW_H

#include <QTimer>
#include <QMutex>
#include <QString>
#include <QStringList>
#include <QtSerialPort/QSerialPort.h>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>
#include <QThread>
#include <QTimer>
#include "modules\WLModule.h"

#define _startReadFW   1
#define _readFW        2
#define _startWriteFW  3
#define _writeFW       4
#define _resetMFW      5
#define _getPropMFW    6

#define _getPSizeFW  10

#define _sendFW  100
#define _sendPropMFW 101

#define _sendSignalMFW 200

 #define _sigEndReadPage    1
 #define _sigEndReadFW      2
 #define _sigEndWritePage   3
 #define _sigEndWriteFW     4
 #define _sigCallNextDataFW 5
 #define _sigChgStatus_u8   6 
 //#define _sigChgSizeFW_ui32 7
 #define _sigErrorFW_u8     8 

class WLModuleFW: public WLModule
{
	Q_OBJECT

public:
	 enum statusMFW{MFW_standby,MFW_read,MFW_write};

	 WLModuleFW();
	~WLModuleFW();



public:

	QByteArray getBufFW() {return FWBuf;};

private:	
	QMutex InputDataMutex;
	QMutex OutDataMutex;
	QMutex SendOutMutex;
	QMutex BufMutex;
	
	QByteArray outData;

	QByteArray inBuf;

    QString  prop;
	
	quint8 sizeBlockFW;
	
	quint32 error;	

    QByteArray FWBuf;
	     int indexBuf;

		quint32 sizeFW;

	statusMFW status;

	int addSpeed;

private:

   bool readFW();   
   bool writeFW();

public slots:


signals:
	void sendMessage(QString,QString,int); 

	void ChangedConnect(bool);
	void ChangedProp(QString);
	void ChangedActiv(bool);
	void ChangedEndReadPage();

	void ChangedEndReadFW();
	void ChangedEndWriteFW();

	void ChangedProgress(int);


public:
inline	QString getProp() {return prop;}
inline  quint32 getSizeFW() {return sizeFW;}

public:

	    bool startReadFW(quint8 mask=0);
		bool startWriteFW(QByteArray BA,quint8 mask=0);
		void reset();	


public:
virtual void callProp();
//virtual void writeXMLData(QXmlStreamWriter &stream);
//virtual void  readXMLData(QXmlStreamReader &stream);
virtual void  readCommand(QByteArray data);  
};

#endif //WLMODULEFW_H
