#ifndef WLPWM_H
#define WLPWM_H

#include <QObject>
#include <QDataStream>
#include <QTimer>
#include <QDebug>

#include "wlmodule.h"

//OutPWM
#define comPWM_setOut        1 //set outPWM
#define comPWM_setEnableOut  2 //enable outPWM
#define comPWM_setInvOut     5 //set inverse outPWM
#define comPWM_setFOut       6 //set frequency outPWM
#define comPWM_setUnlockOut  7 //unlock outPWM

#define comPWM_setData 128
#define comPWM_getData 129

enum typeDataPWM{
     dataPWM_value
    ,dataPWM_Fpwm
    ,dataPWM_enable
    ,dataPWM_inv
    ,dataPWM_flag
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

public:
	
 WLPWM(QObject *parent=nullptr);
~WLPWM();

private:

WLFlags Flags;

float m_value;
float m_Freq;

 quint8 error;

public:
  float getFreq() {return m_Freq;}

   void setError(quint8 err)  {emit changedError(error=err);}
   bool isInv()               {return Flags.get(PWMF_inv);}
   bool isEnable()            {return Flags.get(PWMF_enable);}
   bool isInvalid()           {return Flags.get(PWMF_invalid);}
   bool isUnlock()            {return Flags.get(PWMF_unlock);}

   float getValue() {return m_value;}

signals:
 
 void changedError(quint8);
 void changedFreq(float);
 void changedValue(float);
 void changed(int);

public:

    bool setOut(float getValue);
    bool togInv() {return setInv(!isInv());}
    bool setInv(bool inv);
	bool setEnable(bool enable);
    bool sendGetData(typeDataPWM type);
    bool sendGetData();
    bool setFreq(float f);

    void setData(QDataStream&);

public slots:
virtual void update();
virtual void backup();

public:

virtual void writeXMLData(QXmlStreamWriter &stream);
virtual void  readXMLData(QXmlStreamReader &stream);
};



#endif // WLPWM_H
