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

#define comPWM_setValue 128
#define comPWM_getValue 129

#define sendPWM_dataOut 200 //send data ooutPWM

enum typeDataPWM{
     dataPWM_Pnow
    ,dataPWM_Ptar
    ,dataPWM_Kpwm
    ,dataPWM_Fpwm
    ,dataPWM_enable
    ,dataPWM_inv
  };

#define PWMF_enable  1<<0
#define PWMF_inv     1<<2
#define PWMF_unlock  1<<3
#define PWMF_invalid 1<<7

const QString errorPWM("0,no error");

class WLPWM : public WLElement
{
	Q_OBJECT

public:
    Q_PROPERTY(float kout WRITE setKOut)

public:
	
 WLPWM(QObject *parent=nullptr);
~WLPWM();

private:
WLFlags Flags;

float m_Power;
float m_Kout;
float m_Freq;

 quint8 error;

public:
    void setData(quint8 _flag,float P,float F);

  float freq() {return m_Freq;}

   void setError(quint8 err)  {emit changedError(error=err);}
   bool isInv()               {return Flags.get(PWMF_inv);}
   bool isEnable()            {return Flags.get(PWMF_enable);}
   bool isInvalid()           {return Flags.get(PWMF_invalid);}
   bool isUnlock()            {return Flags.get(PWMF_unlock);}

   float power() {return m_Power;}
signals:
 
 void changedError(quint8);
 void changedFreq(float);
 void changedPower(float);

public:

	bool setOut(float P);
    bool togInv() {return setInv(!isInv());}
    bool setInv(bool inv);
	bool setEnable(bool enable);
	bool setPmax(float Pmax);
	bool sendGetData();
	bool setKOut(float k);
    bool setFreq(float f);

    float getKOut() {return m_Kout;}

     void setData(QDataStream&);
public:

virtual void writeXMLData(QXmlStreamWriter &stream);
virtual void  readXMLData(QXmlStreamReader &stream);
};



#endif // WLPWM_H
