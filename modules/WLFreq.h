#ifndef WLFREQ_H
#define WLFREQ_H

#include <QObject>
#include <QDataStream>
#include <QTimer>
#include <QDebug>

#include "WLModule.h"


#define PWMF_enable 1<<0 
#define PWMF_lock   1<<1
#define PWMF_inv    1<<2

//Freq connect
#define comFreq_setOut       1
#define comFreq_setEnableOut 2
#define comFreq_setKOut      3
#define comFreq_setFmaxOut   4

#define comFreq_getDataOut 100

#define sendFreq_dataOut 200

const QString errorFreq("0,no error");

class WLFreq : public WLElement
{
	Q_OBJECT

public:
	
 WLFreq(QObject *parent=0);
~WLFreq();

private:

 float Freq;

 quint8 error;

 quint8 flag;

public:
	void setData(float F) {Freq=F;};

  float getFreq() {return Freq;}

   void setError(quint8 err)  {emit ChangedError(error=err);}

signals:
 
 void ChangedError(quint8);
 void ChangedFreq(float);

public:

	bool setOut(float F);
    bool setEnable(bool enable);
    bool setK(float k);
	bool setFmax(float Fmax);

	bool sendGetData();


public:

//virtual void writeXMLData(QXmlStreamWriter &stream);
//virtual void  readXMLData(QXmlStreamReader &stream);
};



#endif // WLFREQ_H
