#ifndef WLFWDEVICE_H
#define WLFWDEVICE_H

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

#include "wlmodule.h"

//#define PAGESIZE 2048

//#define sizeBlockFW 16

class WLFWDevice: public QSerialPort
{
	Q_OBJECT

public:
	 enum statusMFW{MFW_standby,MFW_read,MFW_write};

	 WLFWDevice();
	~WLFWDevice();



public:
	virtual bool Init(QString portName);

	QByteArray getBufFW() {return FWBuf;};
	int getMaxFWSize() {
	                   QStringList List=prop.split(".");
		               return List.size()>2 ? List[1].toInt(): 0;
	                   }
private:	
	QMutex InputDataMutex;
	QMutex OutDataMutex;
	QMutex SendOutMutex;
	QMutex BufMutex;
	
	QByteArray outData;

	QByteArray inBuf;

	QString  prop; //свойствно
	
	quint8 sizeBlockFW;
	
	quint32 error;	

    QByteArray FWBuf;
	     int indexBuf;

		quint32 sizeFW;

	statusMFW status;
public:
	QMutex *ioMutex;	

private slots:	

virtual	void readSlot();
        void sendData(); 

private:
   void startSend(QByteArray data);

   void sendSetOData(bool all);

   bool readFW();   
   bool writeFW();

public slots:
	//void updateData();

signals:
	void sendMessage(QString,QString,int); 

	void ChangedConnect(bool);
	void ChangedProp(QString);
	void ChangedActiv(bool);
	void ChangedEndReadPage();
	void ChangedEndReadFW();

	void ChangedProgress(int);
	/*
	void ChangedDataAxis(quint8 index,quint8 statMode,quint8 flags,qint32 pos,float F);

	//void ChangedErrorDevice(quint8 index,quint8 error);
	void ChangedErrorCut(quint8 index,quint8 error);
	void ChangedErrorAxis(quint8 index,quint8 error);

	void ChangedFreeBuf(int);
	void ChangedStatusBuf(int);
	void ChangedResetBuf();
	void ChangedSOutBuf(float);

	void ChangedLatchProbe2(qint32*,quint8);
	void ChangedLatchProbe3(qint32*,quint8);

	void ChangedLatch2(quint8 index,qint32 pos);
	void ChangedLatch3(quint8 index,qint32 pos);
	void ChangedDataOutPWM(quint8 index,float per);
	void ChangedDataOutFreq(quint8 index,float fnow);
	void ChangedDataCut(quint8 index,quint8 statusFlag
		                            ,quint8 curPower 
		                            ,quint16 time_start
		                            ,quint16 time_acc
									,quint16 time_cut
									,quint16 time_dec
									,quint16 time_stop);
    */

public:
inline	QString getprop() {return prop;};

private slots:
	/*
	void sendGetIData();
	void sendGetDataBuf();
	void sendSetOData() {sendSetOData(true);};
	void sendGetProp();
	void sendGetIOSize();*/

public:
	    bool getProp();
	    bool startReadFW(quint8 mask=0);
		bool startWriteFW(QByteArray BA,quint8 mask=0);
		bool getPropMFW();
		bool resetFW();	

virtual void writeXMLData(QXmlStreamWriter &stream);
virtual void readXMLData(QXmlStreamReader &stream);
};

#endif //WLFWDEVICE_H
