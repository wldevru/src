#ifndef WLAXIS_H
#define WLAXIS_H

#include <QObject>
#include <QDataStream>
#include <QTimer>
#include "WLFlags.h"
#include "WLModule.h"
#include "WLModuleIOPut.h"

#define xPD 4

#define errorAxis_setdata    1
#define errorAxis_setinput   2
#define errorAxis_dataSCurve 3
#define errorAxis_emg 4
#define errorAxis_sd  5
#define errorAxis_alm 6
#define errorAxis_pel 7
#define errorAxis_mel 8
#define errorAxis_limit 9
#define errorAxis_nomov 10 
#define errorAxis_modestatus 11
#define errorAxis_fma   12
#define errorAxis_fcalc  13
#define errorAxis_poscalc 14
#define errorAxis_bufactiv 15
#define errorAxis_aad 16
#define errorAxis_fst 17
#define errorAxis_dma 35

const QString errorAxis("0,no error\
,1,set data\
,2,set input\
,3,set S curve\
,4,wrong state inEMGStop 1\
,5,wrong state inSDStop\
,6,wrong state inALM\
,7,wrong state inPEL\
,8,wrong state inMEL\
,9,out limit position\
,10,no mov\
,11,wrong mode or status\
,12,wrong Fmax\
,13,error calc F\
,14,error calc Position\
,15,error servo period\
,16,wrong accel/decel\
,17,wrong Fstart\
,18,wrong Fmov\
,19,wrong type par mov\
,35,error DMA");

//Axis coonect
#define MASK_abs       1<<1 //absolute coordinate
#define MASK_ccw       1<<3 //counter clock wise
#define MASK_fline     1<<4 //fast line
#define MASK_ensmooth  1<<5 //enable smooth
#define MASK_dir       1<<6 //dir vel mode

//Axis
#define comAxis_movPos      1 //mov position mode Axis
#define comAxis_sdStop      2 //slow down stop
#define comAxis_emgStop     3 //emergency stop
#define comAxis_addSyhData  4 //set syh position
#define comAxis_setKSTCurve 5 //old s curve
#define comAxis_reset       6 //reset
#define comAxis_acc         7 //start acceleration to Fmov
#define comAxis_newF        8 //set new Fmov
#define comAxis_setKF       9 //set K(sclae (0...1]) Fmov
#define comAxis_setFlim     10 //set Flimit
#define comAxis_setInput    11 //set inputs Axis(inPEL..,inORG...)
#define comAxis_dec         12 //start decel Axis
#define comAxis_setKGear    13 //set program Gear Axis
#define comAxis_setParMov   16 //set parametr moving
#define comAxis_setActIn    17 //set action on input

#define comAxis_setMinMaxPos 18 //set limit position
#define comAxis_setTypePulse 19 //set type output pulse
#define comAxis_setInputM    20 //set input moduleAxis (inEMG,inSD)
#define comAxis_setPos           21 //set position Axis

#define comAxis_setActInProbe    22 //set action on inProbe

#define comAxis_setDisableLimit  23 //disable limit Axis
#define comAxis_setLatchSrc      24 //set latch source Axis

#define comAxis_setOutput     25//set output Axis (outEN,outRALM...)
#define comAxis_setEnable     26//enable Axis

#define comAxis_setDelaySCurve     27//set inertion time (S curve)
#define comAxis_movVel      28 //mov vellocity mode Axis

#define comAxis_getData   100 //call data Axis

#define sendAxis_signal 200
/*enum signalsAxis
  {

    }
*/
#define sendAxis_data          202 //send data Axis
#define sendAxis_rInProbe      203 //send position inProbe (rise / front)
#define sendAxis_fInProbe      204 //send position inProbe (fall \ front)

#define errorAxis_setdata    1
#define errorAxis_setinput   2
#define errorAxis_dataSCurve 3
#define errorAxis_emg 4
#define errorAxis_sd  5
#define errorAxis_alm 6
#define errorAxis_pel 7
#define errorAxis_mel 8
#define errorAxis_limit 9
#define errorAxis_nomov 10 
#define errorAxis_modestatus 11
#define errorAxis_fma   12
#define errorAxis_fcalc  13
#define errorAxis_poscalc 14
#define errorAxis_bufactiv 15
#define errorAxis_aad 16
#define errorAxis_fst 17
#define errorAxis_fmov 18
#define errorAxis_typeMPar 19
#define errorAxis_dma 35

//Axis flags
#define AF_dir           1<<0  //direction
#define AF_latch2        1<<1  //latch rise
#define AF_latch3        1<<2  //latch false
#define AF_update        1<<3  //update state
#define AF_enable        1<<4  //enable
#define AF_sdstop        1<<5  //stop when F=Fst
#define AF_typePulseABxx 1<<6  //type out AB_ (AB,ABx2,ABx4)
#define AF_disableLimit  1<<7  //no use limit


#define MAF_invStep  1<<1
#define MAF_invDir   1<<0

enum typeIOPutAXIS{IO_inEMGStop,IO_inSDStop,IO_inProbe};

enum typeActIOPutAxis{AXIS_actNo,AXIS_actSdStop,AXIS_actEmgStop};
enum typeInputAxis{AXIS_inORG,AXIS_inALM,AXIS_inPEL,AXIS_inMEL};//_inEMG
enum typeOutputAxis{AXIS_outENB,AXIS_outRALM};//

enum statusAxis{AXIS_stop,AXIS_acc,AXIS_fconst,AXIS_dec,AXIS_wait};
enum   modeAxis{AXIS_standby,AXIS_pos,AXIS_slave,AXIS_vel,AXIS_traxis} ;

enum   typeMParAxis{AXIS_MParAll
                   ,AXIS_MParPlus
                   ,AXIS_MParMinus};

enum   typePulseAxis{AXIS_pulse_SD
                    ,AXIS_pulse_CWCCW
                    ,AXIS_pulse_ABx1
                    ,AXIS_pulse_ABx2
                    ,AXIS_pulse_ABx4
                    ,AXIS_pulse_SDx2
                    ,AXIS_pulse_CWCCWx2
                    ,AXIS_pulse_empty};

enum   typeFindAxis{AXIS_findNO
                   ,AXIS_findPEL
                   ,AXIS_findMEL
				   ,AXIS_findORG};

class WLAxis : public WLElement
{
	Q_OBJECT

public:	
 WLAxis(QObject *parent=0);
~WLAxis();

private:
 qint32 nowPosition;
 qint32 maxPosition;
 qint32 minPosition;

statusAxis status;
  modeAxis mode;
   WLFlags Flags;

  float Freq;
 qint32 latchPos2;
 qint32 latchPos3;

 qint32 homePosition;
 qint32 orgSize;

quint8 error;

float kSTCurve;
float delaySCurve;

float kGear;

quint8 typePulse;
quint8 outSDinv;

WLIOPut *inORG;
WLIOPut *inPEL;
WLIOPut *inMEL; 
WLIOPut *inALM;

WLIOPut *outENB;
WLIOPut *outRALM;

WLModuleIOPut *ModuleIOPut;

typeActIOPutAxis actIn[4];


public:

enum modeAxis   getMode()   {return mode;}
enum statusAxis getStatus() {return status;}

 void init(WLModuleIOPut *_ModuleIOPut,quint8 _index);

 bool isEnable() {return Flags.get(AF_enable);}
 //void setIOPut(int index);
 void setInORG(int getIndex);
 void setInPEL(int getIndex);
 void setInMEL(int getIndex);
 void setInALM(int getIndex);
  
 void setOutENB(int m_index);
 void setOutRALM(int m_index);

 void setLatch2(qint32 pos) {emit changedLatch2(latchPos2=pos);}
 void setLatch3(qint32 pos) {emit changedLatch3(latchPos3=pos);}

 long getLatch2() {return latchPos2;}
 long getLatch3() {return latchPos3;}

 void setError(quint8 err)  {emit changedError(error=err);}

 int getTypePulse(){return typePulse;}
 int getOutSDInv() {return outSDinv;}

float getDelaySCurve() {return delaySCurve;}
float getKSTCurve() {return kSTCurve;}

typeActIOPutAxis getActIn(quint8 typeIn) {return actIn[typeIn];}
           float getKGear() {return kGear;}

WLModuleIOPut* getModuleIOPut() {return ModuleIOPut;}

WLIOPut*  getInput(typeInputAxis);
WLIOPut*  getOutput(typeOutputAxis);

qint32 getMaxPos()  {return maxPosition;}
qint32 getMinPos()  {return minPosition;}
qint32 getNowPos()  {return nowPosition;}
qint32 getHomePos() {return homePosition;}
qint32 getORGSize() {return orgSize;}

void setORGSize(qint32 size) {if(size>0) orgSize=size;}
bool setHomePos(qint32 pos) {if(minPosition<=pos&&pos<=maxPosition) {homePosition=pos; return true;} else return false;}
	
	void setData(quint8 statMode,quint8 flags,qint32 pos,float F);

signals:

 void changedLatch2(qint32);
 void changedLatch3(qint32);
 void changedError(quint8);
 void changedPosition(qint32);
 void changedStatus(statusAxis);
 void changedMode(modeAxis);
 void changedFreq(float);
 void changedInALM(bool);

 void finished();
 void started();

private:
    bool setInput(typeInputAxis type,quint8 num);
    bool setOutput(typeOutputAxis type,quint8 num);

public:
	bool sendGetData();
    bool setParMov(float Aac,float Ade,float Fst,float Fma,typeMParAxis type=typeMParAxis::AXIS_MParAll);
    bool movPos(quint8 mask,qint32 Dist,float Fmov);
    bool movVel(quint8 mask,float Fmov);
	bool acc();
	bool dec();
	bool sdStop();
	bool setNewF(float newF);
	bool emgStop();
	bool addSyhData(qint32 pos);
	bool setPos(qint32 pos);
	bool setMinMaxPos(qint32 minpos,qint32 maxpos);
	bool setKF(float _KFA);
	void reset();	
	bool setDisableLimit(bool dis);
    bool setLatchSrc(quint8 In);
	bool setActIn(typeInputAxis type,typeActIOPutAxis typeAct);
	bool setTypePulse(typePulseAxis type,quint8 SDinv);
	bool setKSTCurve(float kSTcurve);
	bool setDelaySCurve(float delayScurve);
	bool setKGear(float kGear);
	bool setEnable(bool enable);

public:
virtual void writeXMLData(QXmlStreamWriter &stream);
virtual void  readXMLData(QXmlStreamReader &stream);
};



#endif // WLAXIS_H
