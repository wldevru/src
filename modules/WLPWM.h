#ifndef WLPWM_H
#define WLPWM_H

#include <QObject>
#include <QDataStream>
#include <QTimer>
#include <QDebug>

#include "WLModule.h"

#define comPWM_setOut        1 //set percent outPWM
#define comPWM_setEnableOut  2 //enable outPWM
#define comPWM_setKOut       3 //set K outPWM
#define comPWM_setPmaxOut    4 //set max percent outPWM
#define comPWM_setInvOut     5 //set inverse outPWM
#define comPWM_setFOut       6 //set frequency outPWM
#define comPWM_setUnlockOut  7 //unlock outPWM

#define comPWM_getDataOut  100 //call data outPWM

#define sendPWM_dataOut 200 //send data ooutPWM

#define PWMF_enable 1<<0
#define PWMF_inv    1<<2
#define PWMF_unlock 1<<3

const QString errorPWM("0,no error");

class WLPWM : public WLElement
{
	Q_OBJECT

public:
	
 WLPWM(QObject *parent=0);
~WLPWM();

private:
WLFlags Flags;
 quint8 indexPWM;

 float Power;
 float Freq;

 quint8 error;

 quint8 flag;

public:
	void setData(quint8 _flag,float P,float F) {flag=_flag;Power=P;Freq=F;};

	void setIndex(quint8 _index) {indexPWM=_index;};
  quint8 getIndex() {return indexPWM;};

  float getFreq() {return Freq;}

   void setError(quint8 err)  {emit ChangedError(error=err);}
   bool isInv() {return flag&PWMF_inv;}
signals:
 
 void ChangedError(quint8);
 void ChangedFreq(float);

public:

	bool setOut(float P);
    bool setInv(bool inv);
	bool setEnable(bool enable);
	bool setPmax(float Pmax);
	bool sendGetData();
	bool setKOut(float k);
    bool setFreq(float f);

public:

virtual void writeXMLData(QXmlStreamWriter &stream);
virtual void  readXMLData(QXmlStreamReader &stream);

public:
static WLPWM outPWM;
};



#endif // WLPWM_H
