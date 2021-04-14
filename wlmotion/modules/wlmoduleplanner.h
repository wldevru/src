#ifndef WLModulePLANNER_H
#define WLModulePLANNER_H

#include <QObject>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QStringList>
#include <QMutex>
#include "wlmodule.h"

//Planner connect
#define comPlanner_addCirc       2 //
#define comPlanner_addLine       3 //
#define comPlanner_start         4 //
#define comPlanner_stop          5 //
#define comPlanner_pause         6 //
#define comPlanner_reset         7 //
#define comPlanner_setKF         8 //
#define comPlanner_setSmoothAng  9 //��������� ������� ����������� 
#define comPlanner_setSOut         10 
#define comPlanner_setKFpause       11
#define comPlanner_setMaxNView     12
//#define comPlanner_setSOutPWMOut   13
//#define comPlanner_setSOutFreqOut  14
#define comPlanner_setKSOut        15 
#define comPlanner_addULine        16
#define comPlanner_setISlaveAxis   17
#define comPlanner_enableSOut      18
//#define comPlanner_resetSOutPWMOut   19
//#define comPlanner_resetSOutFreqOut  20
#define comPlanner_setHPause         21 //set offset z detectpause;

#define comPlanner_setOutElementSOut 22 //set selement
#define comPlanner_resetOutElementSOut 23 //reset selement
#define comPlanner_setAccSOut 24 //set acceleration SOut
#define comPlanner_setDecSOut 25 //set deceleration SOut

#define comPlanner_getDataPlanner    101

//#define comPlanner_setData 128
//#define comPlanner_getData 129

#define comPlanner_getProp    102

#define sendPlanner_signal 200
/* 
enum typeSignalBuf{_sigChgEmptyBuf_ui8   
                  ,_sigChgSOut_f32
                  ,_sigChgFreeSizeBuf_ui8}; 
*/ 
#define sendPlanner_data   201
//#define sendPlanner_prop   202 //������ ������ ������

//#define sendPlanner_error  255

#define MASK_abs       1<<1 //absolute coordinate
#define MASK_circxyz   1<<2 //3 axis circ
#define MASK_ccw       1<<3 //counter clock wise
#define MASK_fast      1<<4 //fast
#define MASK_ensmooth  1<<5 //enable smooth

#define errorPlanner_emg       1
#define errorPlanner_buffull   2
#define errorPlanner_setdata   3
#define errorPlanner_waxis     4
#define errorPlanner_welement  5 


#define errorULine_pos   1
#define errorULine_mov   2
#define errorCirc_pos    3
#define errorCirc_radius 4
#define errorLine_df     5
#define errorLine_count  6

const QString errorPlanner("0,no error\
,1,emg stop\
,2,buf is full\
,3,wrong set data");

const QString errorElementPlanner("0,no error\
,1,wrong ULine position\
,2,wrong ULine mov distance\
,3,wrong Circ position\
,4,wrong Circ radius\
,5,error Line calc\
,6,wrong Line count");


#define PLF_enable    (1<<0)
#define PLF_empty     (1<<2)
#define PLF_moving    (1<<3)
#define PLF_chgdata   (1<<4)
#define PLF_usehpause (1<<5)

enum statusPlanner{MPLANNER_stop
                  ,MPLANNER_run
                  ,MPLANNER_pause
                  ,MPLANNER_paused
                  ,MPLANNER_stopped
                  ,MPLANNER_hpause
                  ,MPLANNER_continue};


class WLModulePlanner : public WLModule
{
	Q_OBJECT

public:

public:
    WLModulePlanner(QObject *parent=nullptr);
	~WLModulePlanner();


private:

QMutex Mutex;
statusPlanner m_status;
WLFlags Flags;
int m_sizeBuf;
int m_free;

float m_KFpause=0.25f;

quint8  m_lastIndexElementBuf;
quint32 m_curIdElementBuf;
quint32 m_countAddElement;

float m_accSOut=0;
float m_decSOut=0;

float m_KF=1;
float m_KSOut=1;

float m_smoothAng;

qint32  m_hPause;

typeElement m_typeSOut;
     quint8 m_iSout;
public:
     float getAccSOut() const;
     float getDecSOut() const;

typeElement getTypeSOut() const;
     quint8 getISOut() const;

     int getSizeBuf() {return m_sizeBuf;}
     int getCountBuf() {return m_sizeBuf-m_free;}

     float getKFpause() {return m_KFpause;}
     float getSmoothAng() {return m_smoothAng;}

quint32 getCurIdElement() {return m_curIdElementBuf;}

    bool setIAxisSlave(quint8 *indexsAxis,quint8 size);
    bool setHPause(quint8 enable,qint32 hPause);

    bool setAccSOut(float acc);
    bool setDecSOut(float dec);

    bool setElementSOut(typeElement element,quint8 i);
    bool resetElementSOut();

	bool addULine(quint8 mask,quint8 size,quint8 indexs[],long endPos[],long midPos[],float S,float Fmov,quint32 _id);
	bool addLine(quint8 mask,quint8 size,quint8 indexs[],long endPos[],float S,float Fmov,quint32 _id);
    bool addCirc(quint8 mask,quint8 size,quint8 indexs[],long endPos[],long cenPosIJ[],float S,float Fmov,quint32 _id);

	bool startMov();
	bool stopMov();
	bool pauseMov();

	bool setKF(float _KF);
   float getKF()  {return m_KF;}
    bool setKFpause(float _KF);

	bool setSmoothAng(float ang_gr);

	bool setSOut(float s);
	bool setKSOut(float k);
   float getKSOut(){return m_KSOut;}

	bool setEnableSOut(quint8 enable);
		
     int getFree()   {return m_free;}
    void setSizeBuf(int value);


 quint32 getCountAddElement() const;

statusPlanner getStatus()  const {return m_status;}

   bool isEmpty()  {return Flags.get(PLF_empty);}
   bool isMoving() {return Flags.get(PLF_moving);}
   bool isBusy()  {return !isEmpty()||isMoving();}

public slots:
	void sendGetDataBuf();

public slots:
virtual void update();
virtual void backup();

signals:
    void changedFree(int);
    void changedStatus(int);
    void changedCurIElement(int);

    void changedSOut(float);

    void reset();

public:
virtual void getProp() {}
virtual void writeXMLData(QXmlStreamWriter &stream);
virtual void  readXMLData(QXmlStreamReader &stream);
virtual void readCommand(QByteArray data); 

                           };
#endif // WLModulePLANNER_H

