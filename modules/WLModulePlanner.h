#ifndef WLModulePLANNER_H
#define WLModulePLANNER_H

#include <QObject>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QStringList>
#include <QMutex.h>
#include "WLModule.h"

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
#define comPlanner_setMPar         11
#define comPlanner_setMaxNView     12
#define comPlanner_setSOutPWMOut   13
#define comPlanner_setSOutFreqOut  14
#define comPlanner_setKSOut        15 
#define comPlanner_addULine        16
#define comPlanner_setISlaveAxis   17
#define comPlanner_enableSOut      18
#define comPlanner_resetSOutPWMOut   19
#define comPlanner_resetSOutFreqOut  20

#define comPlanner_getData    101
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

#define MASK_abs       1<<1 //���������� ����������
//#define MASK_nomov     1<<2 //��� ��������
#define MASK_ccw       1<<3 //������ ������� �������
#define MASK_fline     1<<4 //������� �����
#define MASK_ensmooth  1<<5 //����������� ���.

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

#define PLF_enable   1<<0
#define PLF_empty    1<<2
#define PLF_moving   1<<3
#define PLF_chgdata  1<<4 

class WLModulePlanner : public WLModule
{
	Q_OBJECT

public:
enum statusPlanner{stop
                  ,run
                  ,pause
                  ,paused
                  ,stopped}; //����������,��������,���������������


public:
	WLModulePlanner(QObject *parent=0);
	~WLModulePlanner();


private:

QMutex Mutex;

statusPlanner status;
      int flags;
      int sizeBuf;
      int free;

quint8  lastIndexElementBuf;
quint32 curIdElementBuf;

float smoothAng;

public:

	 float getSmoothAng() {return smoothAng;} 

quint32 getCurIdElement() {return curIdElementBuf;}

    bool setIAxisSlave(quint8 *indexsAxis,quint8 size);
	//void sendGetDataBuf();
	
	bool setSOutPWMOut(quint8 i);
    bool setSOutFreqOut(quint8 i);

	bool resetSOutPWMOut();
    bool resetSOutFreqOut();

	bool setParMov(float Aac,float Ade,float Fst,float Fma);

	bool addULine(quint8 mask,quint8 size,quint8 indexs[],long endPos[],long midPos[],float S,float Fmov,quint32 _id);
	bool addLine(quint8 mask,quint8 size,quint8 indexs[],long endPos[],float S,float Fmov,quint32 _id);
	bool addCirc(quint8 mask,quint8 iI,quint8 iJ,quint8 iK,long endPos[],long cenPos[],float S,float Fmov,quint32 _id);

	bool startMov();
	bool stopMov();
	bool pauseMov();

	bool setKF(float _KF);

	bool setSmoothAng(float ang_gr);

	bool setSOut(float s);
	bool setKSOut(float k);

	bool setEnableSOut(quint8 enable);
		
    int getFree()   {return free;};
statusPlanner getStatus() {return status;}
   bool isEmpty()  {return flags&PLF_empty;}
   bool isMoving() {return flags&PLF_moving;}

public slots:
	void sendGetDataBuf();

signals:
	void ChangedFree(int);
	void ChangedStatus(int);
	void ChangedReset();
	void ChangedSOut(float);

public:
virtual void getProp() {};	
virtual void writeXMLData(QXmlStreamWriter &stream);
virtual void  readXMLData(QXmlStreamReader &stream);
virtual void readCommand(QByteArray data); 
};

#endif // WLModulePLANNER_H

