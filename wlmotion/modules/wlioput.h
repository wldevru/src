#ifndef WLIOPut_H
#define WLIOPut_H

#include <QObject>
#include <QMutex>
#include <QTimer>
#include <QDebug>
#include <qstringlist.h>
#include "wlmodule.h"
#include "wlflags.h"

#define bit0 1<<0
#define bit1 1<<1
#define bit2 1<<2
#define bit3 1<<3
#define bit4 1<<4
#define bit5 1<<5
#define bit6 1<<6
#define bit7 1<<7
//IOPut connect
//IOPut
#define comIOPut_setInputInv   1 //set invers input
#define comIOPut_setOutputInv  2 //set invers output

#define comIOPut_setOutputByte 3 //set group output (index,index+1....)
#define comIOPut_setOutputTo   4 //set output

#define comIOPut_setInputByte  5 //set group input
#define comIOPut_setInput      6 //set input
#define comIOPut_getInput      7 //get input

#define comIOPut_setOutputPulse  8 //set pulse output

#define comIOPut_getAllInputData  100 //call all inputs data
#define comIOPut_getAllOutputData 101 //call all outputs data

#define comIOPut_getInputData 102  //get input data
#define comIOPut_getOutputData 103 //get output data


#define sendIOPut_inputBData  200  //send group input
#define sendIOPut_outputBData  201 //send group output

#define sendIOPut_ioputData 202 //send input or output data


#define errorIOPut_addcb       1 //error add call back
#define errorIOPut_addOutPulse 2 //error add task pulse

#define IOPF_old       1<<0
#define IOPF_now       1<<1
#define IOPF_inv       1<<2
#define IOPF_enable    1<<3
#define IOPF_input     1<<4
#define IOPF_asend     1<<5
#define IOPF_pulse     1<<6
#define IOPF_invalid   1<<7


const QString errorIOPut("0,no error\
,1,add connect ioput\
,1,add pulse output");

class WLIOPut: public WLElement
{        
Q_OBJECT

public:

Q_PROPERTY(bool inv READ isInv() WRITE setInv() NOTIFY changedInv)
Q_PROPERTY(bool now READ getNow() NOTIFY changed)
Q_PROPERTY(bool out READ getNow() WRITE setOut())

private:
         WLFlags Flags;
		 
public:
    WLIOPut (QString _comment="",bool input=false);
void setInv(bool _inv=true);
void togInv()  {setInv(!Flags.get(IOPF_inv));}

inline int  getCond(){return Flags.get(IOPF_now)!=Flags.get(IOPF_old) ? (Flags.get(IOPF_now) ? 2:3): Flags.get(IOPF_now);}
inline bool getNow() {return Flags.get(IOPF_now);}
inline bool getOld() {return Flags.get(IOPF_old);}

bool isInv(void)      {return Flags.get(IOPF_inv);}
bool isEnable()       {return Flags.get(IOPF_enable);}
bool isInvalid(void)  {return Flags.get(IOPF_invalid);}
bool isInput(void)    {return Flags.get(IOPF_input);}
bool isOutput(void)   {return !isInput();}

void setBasicOutputInv() {if(isOutput()) setInv(Flags.get(IOPF_old));}
void setData(quint8 _flags);

QString toString() {
                    QString ret=QString::number(getIndex());

					return ret;
                   }
void fromString(QString data) 
                    {
	                QStringList List=data.split(",");
					if(List.size()==1||List.size()==3)
					{
					setIndex(List[0].toInt());					
					}					
                    }


private slots:

  void setOutTogg() {setOut(!getNow());}
  //void resetBusy()  {busy=false; if(getCond()>1); sendChanged();}

public slots:

void setNow(bool _now)     {
                           if(isEnable())
                             {
                             Flags.set(IOPF_old,getNow());
                             Flags.set(IOPF_now,_now);

                             if(getCond()>1) emit changed();
                             }
                           }

void setOut(bool now);
void setOutPulse(bool _now,quint32 time_ms);

void setTogPulse(quint32 time_ms) {setOutPulse(!getNow(),time_ms);}
void setTog()  {setOut(!getNow());}

signals:

  void changed();

  void changedInv(bool);

public:
static WLIOPut In0;
static WLIOPut In1;
static WLIOPut Out;
};

void setIOPutInvStr(QString data,WLIOPut *ioputs,int size);
QString getIOPutInvStr(WLIOPut *ioputs,int size);

struct WLIOData
{
WLIOPut *IOput;
   bool  state;

public:
   WLIOData(WLIOPut *_IOput,bool _state=0) {IOput=_IOput;state=_state;}
   WLIOData() {IOput=&(WLIOPut::In0); state=0;}
   QString toString()   {return QString::number(IOput->getIndex())+","+QString::number(state);}
   bool  isTry() {return IOput==NULL ? true : IOput->getNow()==state;}
};




unsigned char getByteFrom(WLIOPut *B0
	                       ,WLIOPut *B1
                           ,WLIOPut *B2=nullptr
                           ,WLIOPut *B3=nullptr
                           ,WLIOPut *B4=nullptr
                           ,WLIOPut *B5=nullptr
                           ,WLIOPut *B6=nullptr
                           ,WLIOPut *B7=nullptr);

void setByteTo(unsigned char byte
	              ,WLIOPut *B0
	              ,WLIOPut *B1
                  ,WLIOPut *B2=nullptr
                  ,WLIOPut *B3=nullptr
                  ,WLIOPut *B4=nullptr
                  ,WLIOPut *B5=nullptr
                  ,WLIOPut *B6=nullptr
                  ,WLIOPut *B7=nullptr);


#endif //WLIOPut_H
