#ifndef WLMILLMACHINE_H
#define WLMILLMACHINE_H

#include <QDebug>

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QTextCodec>

#include "wlflags.h"
#include "wlelementtraj.h"
#include "wlmilldrive.h"
#include "wlmotion.h"
#include "wlevscript.h"
#include "wl3dpoint.h"
#include "wl6dpoint.h"
#include "wlenternum.h"
#include "wlgprogram.h"
#include "wlgcode.h"
#include "wlgmodel.h"
#include "wlmachine.h"

//#define XDrive 0
//#define YDrive 1
//#define ZDrive 2
//#define ADrive 3
//#define M_PI_4 M_PI/4

#define configMMDir  QCoreApplication::applicationDirPath()+"//wlmillconfig//"
#define configMMFile QCoreApplication::applicationDirPath()+"//wlmillconfig//mmconfig.xml"
#define configMKFile QCoreApplication::applicationDirPath()+"//wlmillconfig//mkconfig.xml"
#define      pamFile QCoreApplication::applicationDirPath()+"//wlmillconfig//pam.dat"
#define  mScriptFile QCoreApplication::applicationDirPath()+"//wlmillconfig//mscript.js"

/*
#define in_RDY     1
#define in_SDstop  2
#define in_Dir0    3 
#define in_Dir1    4 
#define in_Dir2    5 
#define in_ORG0    6
#define in_PEL0    7
#define in_MEL0    8
#define in_ALM0    9
#define in_ORG1    10
#define in_PEL1    11
#define in_MEL1    12
#define in_ALM1    13
#define in_ORG2    14
#define in_PEL2    15
#define in_MEL2    16
#define in_ALM2    17
*/
#define out_spindleCW  0
//#define out_spindleCCW 1
#define out_coolS      1
#define out_coolM      2

#define sizeDrive 4
/*
struct WLGTool
{
double H;
double D;
QString comment;
};
*/


struct SHProbeData
{
double hTablet;
double zPos;
};


struct SCorrectSOut
{
float Sadj;
float Scor;

void reset()
{Sadj=Scor=0;}
};

struct SMapHeight
{
QList <QList <WL3DPointf>> points;

float getHeight(WL3DPointf pos)
{
WL3DPointf P00=points[0][0];
WL3DPointf P10=points[0].last();
WL3DPointf P01=points.last()[0];
WL3DPointf P11=points.last().last();

float h0;
float h1;
float hz;

int i,j;

if(pos.x<=P00.x)
    {
    P10=P00;
    }
    else
    {
    if(pos.x>P10.x)
        P00=P10;
    }

if(pos.y<=P00.y)
    {
    P01=P00;
    }
    else{
    if(pos.y>P01.y)
        P00=P01;
    }

for(i=1;i<(points.first().size()-1);i++)
 {
 if((pos.x<=points.first()[i].x)||(P00.x==P10.x))
    {
    for(j=1;j<(points[i].size()-1);j++)
      {
      if((pos.y<=points[j].first().y)||(P00.y==P01.y)) break;
      }

     P11=points[j][i];

     P01=points[j][i!=0?i-1:i];
     P10=points[j!=0?j-1:j][i];

     if(i!=0) i--;
     if(j!=0) j--;

     P00=points[j][i];

     break;
    }
 }

h0=(pos.y-P00.y)/(P01.y-P00.y)*P00.z+(P01.y-pos.y)/(P01.y-P00.y)*P01.z;
h1=(pos.y-P10.y)/(P11.y-P10.y)*P10.z+(P11.y-pos.y)/(P11.y-P10.y)*P11.z;

hz=(P10.x-pos.x)/(P11.x-P10.x)*h0+(pos.x-P11.x)/(P11.x-P10.x)*h1;

qDebug()<<pos.to3D().toString()<<i<<j<<h0<<h1<<hz;

return hz;
}

};

class WLMillMachine : public WLMachine
{
	Q_OBJECT
	
private:
    enum StateMMachine{noInit,Init,Ready};
    enum TypeAutoMMachine{AUTO_no
                         ,AUTO_ProbeEMG
                         ,AUTO_ProbeSD
                         ,AUTO_HProbeEMG
                         ,AUTO_HProbeSD
                         ,AUTO_FindDrivePos
                         ,AUTO_HToolEMG
                         ,AUTO_HToolSD};
	enum FlagMMachine 
	          {
               ma_busy=      1<<0,     //�����
               ma_runlist=   1<<1,     //��������� �������� �� ������
               ma_go=        1<<2,     //����
			   ma_manual=    1<<3,     //������ ����� 1
               //ma_auto=      1<<4,     //���� �����
			   ma_pause=     1<<5,     //�����
               //ma_smooth=    1<<6,     //�����������
			   ma_activ=     1<<7,     //������ ��������
			   ma_blcomp=    1<<8,     //���������� �����
               //ma_ready=     1<<9,     //������
			   ma_blnextmov=  1<<10,     //���������� ������������� �����
			   ma_continuemov=1<<11,    //����������� ��������
			   ma_spindle    =1<<12,
			   ma_detplasma  =1<<13,    //�������� ��������� ������
               ma_useGModel  =1<<14,
			   ma_on         =1<<15,
			   ma_runprogram =1<<16,    //������ �� ���������
			   ma_autostart  =1<<17,     //���������	
               ma_useMPG     =1<<18,
			   ma_useCorrectSOut =1<<19,   
			   ma_readyRunList   =1<<20,
			   ma_runscript      =1<<21, 
               ma_useHMap        =1<<22,               
               ma_useHPause      =1<<23,
               ma_continue       =1<<24,
               ma_stop           =1<<25,
			   };    

    WLGPoint m_nowBL;
    WLGModel m_GModel;
    WLGPoint lastMillGPoint;
	WLFlags Flag;

    SMapHeight m_mapHeight;

    QVector <WLMillDrive*> millDrives;

public:
    WLMillMachine(WLGProgram *_Program,WLEVScript *_EVMScript,QObject *parent=nullptr);
	~WLMillMachine();

 	      QMutex Mutex;

QList<WLElementTraj>      MillTraj;
QList<WLElementTraj>      baseTraj;
QList<WLElementTraj>  showMillTraj;   

 QMutex MutexTraj;//listMutex;
 QMutex MutexAuto;
 QMutex MutexMillTraj;
 QMutex MutexShowTraj;

Q_INVOKABLE bool runGCode(QString gtxt); 
            bool runGProgram(int istart=0);


bool isCompleteProgram() {return m_iProgram==m_Program->getElementCount();}
bool isRunProgram() {return Flag.get(ma_runprogram);}
bool isRunList() {return Flag.get(ma_runlist);}
bool isReadyRunList() {return Flag.get(ma_readyRunList);}
bool isPossiblyManual();

 int getMillTrajSize() {return MillTraj.size();}

 quint32 getIProgram() {return m_iProgram;}

QList<WLElementTraj> getTraj() {QMutexLocker locker(&MutexMillTraj); return MillTraj;}
long getTrajIProgramSize();

WLGModel *getGModel() {return &m_GModel;}
private:

void addHeightMap(QList<WLElementTraj> &Traj,double dist=0.5f);
void addBacklash(QList<WLElementTraj> &Traj);
void addCalcGModel(QList<WLElementTraj> &addTraj);
void addSmooth(QList<WLElementTraj> &addTraj);
void enableBacklash(bool enable);

QList<WLElementTraj>  addCirclePoints(WLElementTraj  ETraj);

private:
 QTime m_programTime;
  long m_elementsTime;
//HANDLE mx;

SHProbeData hProbeData;

float m_percentManual;
//float m_smoothDist;
//float m_simpliDist;
float m_percentSpeed;
float m_percentSOut;
//float percentDriveActiv;
/*
private: //for find position

QString m_strFindDrivePos="Z,X,Y";
QList<QString> m_listFindDrivePos;
*/

private: 	

WLGCode   m_GCode;

QList <SCorrectSOut> m_correctSList;

  double m_FG1;
  double m_Fbacklash;
  double m_Fprobe;

 double m_backProbePosition;

WLGPoint lastGPoint;

    float m_minS;
    float m_maxS;
    float m_minSOut;
    float m_maxSOut;

    float tarSOut;
	float curSOut;

	float m_smoothAng;
    long m_iElementProgram;

	WL3DPoint bufNowBL;

    double m_mainDim; 
	int m_curTool;

    WLGProgram *m_Program;
    QString m_MScriptCode;

	QTimer *timeLoopPLC;

	double m_baseOffsetTool;

public:
    QList <SCorrectSOut> correctSList() {return m_correctSList;}
    void setCorrectSList(QList <SCorrectSOut> list) {m_correctSList=list;sortCorrectSList();}

    QString correctSOut();
	void setStringCorrectSOut(QString str);

    WLGCode   *getGCode() {return &m_GCode;}
 public:
    WLEVScript *m_EVMScript;
    WLEVScript *m_EVLScript;


private:
  void setEVMScript();
  void setEVLScript();

  void sortCorrectSList();

  float calcCorrectSOut(float);


   WLMotion *motDevice;
public:
   WLMotion* getMotionDevice() {return motDevice;}

 public:

  WLMPG *getMPG();
public:

  double getTimeElement() const {double ret=m_programTime.elapsed(); return m_iProgram==m_elementsTime ? 0 : ret/(m_iProgram-m_elementsTime);}

    void addCurrentSCor();
    void clearSCorList();

    bool isUseGModel() {return Flag.get(ma_useGModel);}
    void setEnableGModel(bool enable) {Flag.set(ma_useGModel,enable);}

    bool isUseHPause() {return Flag.get(ma_useHPause);}
    void setEnableHPause(bool enable) {Flag.set(ma_useHPause,enable);}

    bool isUseCorrectSOut()                     {return Flag.get(ma_useCorrectSOut);}
    void setEnableUseCorrectSOut(bool enable)   {Flag.set(ma_useCorrectSOut,enable);/*setSOut(getCurSOut());*/}

    bool isUseMPG()           {return  Flag.get(ma_useMPG);}
    void setUseMPG(bool en)   {Flag.set(ma_useMPG,en);}

SHProbeData getHProbeData(){return hProbeData;}
void setHProbeData(SHProbeData hPData) {hProbeData=hPData;}

double getBaseOffsetTool() {return m_baseOffsetTool;}
void setBaseOffsetTool(double offset) {m_baseOffsetTool=offset;}

float getVMax() {WLModuleAxis *ModuleAxis=motDevice->getModuleAxis();
                 if(ModuleAxis)
					 return ModuleAxis->getFmax()*m_mainDim;
				 else
					 return 50000;
                }

 void setFeedVBacklash(float _VBacklash) {if(_VBacklash>=0) m_Fbacklash=_VBacklash;}
float VBacklash() {return m_Fbacklash;}

 void setFeedVProbe(float _VProbe) {if(_VProbe>0) m_Fprobe=_VProbe;}
float VProbe() {return m_Fprobe;}

float maxSOut() {return m_maxSOut;}
float minSOut() {return m_minSOut;}

bool setRangeSOut(float min,float max) {if(min<max&&min>=0&&max>0) {m_maxSOut=max;m_minSOut=min; return true;} else return false;}
bool setRangeS(float min,float max) {if(min<max&&min>=0&&max>0) {m_maxS=max;m_minS=min; return true;} else return false;}

float Smax() {return m_maxS;}
float Smin() {return m_minS;}

float getSTar() {return tarSOut;}
float calcSOut(float S);

bool isBLNextMov()      {return Flag.get(ma_blnextmov);}
bool isContinueMov()    {return Flag.get(ma_continuemov);}

WLGPoint getAxisPosition();
WLGPoint getCurrentPosition(bool real=0);
WLGPoint getCurrentPositionActivSC();

virtual void   setAuto();
virtual void resetAuto();



virtual void  updateAuto();

void updateMillMachineAuto();

bool updateProbe();
bool updateHProbe();
bool updateProgram();
bool updateHToolProbe();

void updateMainDimXYZ();

private:
   int  iOperation;
quint32 m_iProgram;
WLDrive *driveProbe;
   bool iDriveDir;

   float m_hPause;
   TypeAutoMMachine m_typeAutoMMachine;

QVector <double> lastEndPos;

QList <int> m_MList;

public:
  //void initDevice();

private:
  int updateMovList();
  int updateMovBuf();
  int updateMovProgram();

virtual  bool verifyReadyAutoMotion();
virtual  bool verifyReadyManualMotion();

private slots:
  void init();

public:
   void setHPause(float _hPause) {m_hPause=_hPause;}
   float HPause() {return m_hPause;}

  void setActiv(bool en=true) {
	                           bool last=Flag.get(ma_activ); 
                                         Flag.set(ma_activ,en);
                                    if(last!=en)
                                         emit changedActiv(en);
                              }

  bool isEmptyMotion();

  bool isActivScript() {return   m_EVMScript->isBusy();}
  bool isRunScript()   {return   Flag.get(ma_runscript);}

  float getCurSpeed() {return sqrt(pow(getDrive("X")->getVnow(),2)
                                  +pow(getDrive("Y")->getVnow(),2)
                                  +pow(getDrive("Z")->getVnow(),2));}

  float getCurSOut() {return curSOut;}


public:

            //float getSmoothDist()    {return m_smoothDist;}
            //float getSimpliDist()    {return m_simpliDist;}

Q_INVOKABLE bool getInProbe()   {return motDevice->getModuleAxis()->getInput(MAXIS_inProbe)->getNow();}
Q_INVOKABLE bool getInSDStop()  {return motDevice->getModuleAxis()->getInput(MAXIS_inSDStop)->getNow();}
Q_INVOKABLE bool getInEMGStop() {return motDevice->getModuleAxis()->getInput(MAXIS_inEMGStop)->getNow();}
Q_INVOKABLE bool getIn(int index)  {return motDevice->getModuleIOPut()->getInput(index)->getNow();}
Q_INVOKABLE bool getOut(int index) {return motDevice->getModuleIOPut()->getOutput(index)->getNow();}
Q_INVOKABLE void setOutput(int index,bool set)            {setOut(index,set);} //old command
Q_INVOKABLE void setOut(int index,bool set)               {motDevice->getModuleIOPut()->getOutput(index)->setOut(set);}
Q_INVOKABLE void setOutPulse(int index,bool set,int time) {motDevice->getModuleIOPut()->getOutput(index)->setOutPulse(set,time);}
Q_INVOKABLE void setOutTog(int index)                     {motDevice->getModuleIOPut()->getOutput(index)->setTog();}

Q_INVOKABLE	  int getCurTool()       {return m_curTool;}
Q_INVOKABLE  void setSOut(float S);
Q_INVOKABLE  void enableSOut(bool enable) {
                                          setSOut(m_GCode.getValue('S'));
                                          motDevice->getModulePlanner()->setEnableSOut(enable);
                                          } 

	        bool isDetPlasmaOn()    {return Flag.get(ma_detplasma);}

Q_INVOKABLE bool isTryProbe(bool dir);
Q_INVOKABLE double getProbePosition(QString nameDrive,bool dir);

Q_INVOKABLE void rotAboutRotPointSC(int i,float a);
Q_INVOKABLE void setCurPositionSC(QString nameCoord,double pos);

Q_INVOKABLE bool isActiv() {
                           WLModulePlanner *ModulePlanner=motDevice->getModulePlanner();

                           qDebug()<<!MillTraj.isEmpty()
                                   <<!ModulePlanner->isEmpty()
                                   <<ModulePlanner->isMoving()
                                   <<isAuto()
                                   <<isPause();

                           return   !MillTraj.isEmpty()
                                  ||!ModulePlanner->isEmpty()
                                  ||ModulePlanner->isMoving()
                                  ||isAuto()
                                  ||isPause();
                           }

Q_INVOKABLE double getCurPosition(QString name);
Q_INVOKABLE QString getCurPosition();
Q_INVOKABLE double getCurPositionSC(QString name);

Q_INVOKABLE bool isManual()         {return  Flag.get(ma_manual);}
Q_INVOKABLE	bool isActivDrive(QString name);

Q_INVOKABLE	double getFProbe() {return m_Fprobe;}
public:
	   
  void goOn();
  void goOff();

   void resetALM(QString name) {WLDrive::getDrive(name)->resetAlarm();}

   void addElementTraj(QList<WLElementTraj>  ListTraj);

   bool loadConfig();


   bool isOn() {return Flag.get(ma_on);}

   float percentSOut() {return m_percentSOut;}

 private:	   

    void sendPause(QString msg,int code=-1) {setMessage(metaObject()->className(),msg,code);}
public:
    bool runMScript(int iM);
    bool runScript(QString txt);

    void addDrive(WLMillDrive *millDrive);
    void removeDrive(WLMillDrive *millDrive);
    
private slots:

    void setCompleteScript(QString);
    void setFinished();

   void updateInput();

   void setDataSOut(float val);

 public slots: 

	void saveConfig();
	void setMessage(QString name,QString data,int code) {qDebug()<<"setMessageMM"<<code;
	                                                     if(code<0)
														  {
                                                          emit error();
                                                          reset();
														  } 
														  else
                                                            if(code==0) Pause(1);
                                                          emit sendMessage(name,data,code);
                                                          }


    void Pause() {Pause(true);emit changedPause(true);}//������� ���������

	void reset();

    QString nameClass() {return metaObject()->className();}

	private:
	 void startMovList();

	public slots: 	

    void Start() {startMovList();}
    void Stop();//���������

	void setCurTool(int iT) {
		                     if(iT>256) 
		                     iT=256; 
	                         if(iT<0) iT=0;
							 m_curTool=iT;
							 qDebug()<<"setCurTool"<<m_curTool;
                             emit changedCurTool(m_curTool);
	                        }
	

	void setOn(bool on);
	void setOff(bool off);

	void setAutoStart(bool enable) {Flag.set(ma_autostart,enable);}
    bool isAutoStart() {return Flag.get(ma_autostart);}

//MANUAL

    WLMillDrive *getDrive(QString nameDrive,bool send=false);
    QList <WLMillDrive*> getDrives();

    void setDriveManualWhell(QString name,quint8 X1=1,bool vmode=false);

Q_INVOKABLE void goDriveTouch(QString nameDrive,int dir,float F);
Q_INVOKABLE	void goDriveProbe(QString nameDrive,int dir,float F,int type);
Q_INVOKABLE	void goHProbe(float F,bool sd);
Q_INVOKABLE	void goHToolProbe(float F,bool sd);
	

    bool isPause() {return Flag.get(ma_pause);}
    void Pause(bool en);//������� ���������
	
    void setBLNextMov(bool enable)  {Flag.set(ma_blnextmov,enable);}
    void setContinueMov(bool enable){Flag.set(ma_continuemov,enable);}
	

    //void setSimpli(bool enable) {Flag.set(ma_simpli,enable);}
    //void setSimpliDist(double val)  {m_simpliDist=qBound(0.0f,(float)val,5.0f);}

    //void setSmooth(bool enable)     {Flag.set(ma_smooth,enable);}
    //void setSmoothDist(double val)  {m_smoothDist=val;}

    void setDetPlasmaOn(bool on)   { Flag.set(ma_detplasma,on);}

    void setPercentSpeed(double per) {if(0<=per&&per<=300)   {emit changedPercentSpeed(m_percentSpeed=per);}
                                      motDevice->getModulePlanner()->setKF(m_percentSpeed/100);}

    void setPercentSOut(double per) {if(0.1<=per&&per<=300)   {emit changedPercentSOut(m_percentSOut=per);}
                                     motDevice->getModulePlanner()->setKSOut(m_percentSOut/100); }
	                                    
								      

	void setPercentSpeed50() {setPercentSpeed(50);} 

    void verifyPosibleManual() {emit changedPossibleManual(isPossiblyManual());}

signals:

    void changedPossibleManual(bool);

    void saveLog(QString,QString);

    void changedEMG(bool);
    void changedRDY(bool);

    void changedSValue(int);

    void changedOn(bool);
    void changedActiv(bool);
    void changedReadyRunList(bool);

    void changedCurrentIndex(long);
    void changedSpeedF(float);

    void changedPause(bool);
	
    void changedHomePosition();

    void changedPercentSpeed(double);
    void changedPercentSOut(double);

    void changedCurTool(int);

	void finished();
	
	void noActiv();

    void changedMotion(bool);

	void sendMessage(QString name,QString data,int code);

	void error();

    void changedTrajSize(int);

private slots:
    void runLoopPLC() {qDebug()<<"runLoopPLC"; if(m_EVLScript!=nullptr) m_EVLScript->runFunc("loopPLC()"); }

    void on_changedStatusMPlanner(int status);

public slots:



	void runScriptM(int iM) {qDebug()<<"runMScript"<<iM; runMScript(iM);}

	void runScriptM3(){runScriptM(3);}
	void runScriptM4(){runScriptM(4);}
	void runScriptM5(){runScriptM(5);}
	void runScriptM7(){runScriptM(7);}
	void runScriptM8(){runScriptM(8);}
	void runScriptM9(){runScriptM(9);}

	void runUserFunc1() {runScript("userFunc1()");}
    void runUserFunc2() {runScript("userFunc2()");}
	void runUserFunc3() {runScript("userFunc3()");}
	void runUserFunc4() {runScript("userFunc4()");}
	void runUserFunc5() {runScript("userFunc5()");}
	
friend class WLPositionWidget;

};
#endif // WLMILLMACHINE_H
