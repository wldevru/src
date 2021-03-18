#ifndef WLDRIVE_H
#define WLDRIVE_H

#include <QThread>
#include <QTimer>
#include <QString>
#include <QThread>
#include <QMutex>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <qmath.h>

#include "wlmoduleaxis.h"
#include "wlpad.h"
#include "wlflags.h"

#define err_noerr  1 
#define err_nomov  0
#define err_diap  -2
#define err_nopam -3

#define MOTION 0x01


struct WLDriveDim
{
enum typeDim{stepPerSize,oneStepSize,ratio};

double A;
double B;
double value;

double valueReal;

float kGear;

typeDim type;

WLDriveDim() {value=valueReal=A=B=1; kGear=1; type=typeDim::oneStepSize;}

bool setKGear(float k)
{
if(k>0.0f)
 {
 kGear=k;
 value=valueReal*static_cast<double>(kGear)/(1<<xPD);
 return true;
 }

return false;
}

bool set(typeDim _type,double _A,double _B=1)
{
switch(_type)
  {
  case stepPerSize: A=_A;B=1;  type=_type; valueReal=1/A; setKGear(kGear); return true;
  case oneStepSize: A=_A;B=1;  type=_type; valueReal=A;   setKGear(kGear); return true;
  case ratio:       A=_A;B=_B; type=_type; valueReal=A/B; setKGear(kGear); return true;
  }
  return false;
}

QString toString()
{
return QString(QString::number(type)+","+QString::number(A,'g',16)+","+QString::number(B,'g',16));
}


bool fromString(QString str)
{
QStringList list=str.split(",");
if(list.size()==3)
 {
 type=static_cast<typeDim>(list[0].toInt());
 A=list[1].toDouble();
 B=list[2].toDouble();
 return true;
 }
return false;
}

};


struct WLDrivePosition
{
qint64 step;
double offset;

WLDrivePosition() {step=0;offset=0;}

qint32 getStepI32L() {return (qint32)(step&0x00000000FFFFFFFF);}

double get(WLDriveDim dim) {return (dim.value*step+offset);}
  void set(double val,WLDriveDim dim)   {step=qRound64(val/dim.value);
                                       offset=val-step*dim.value;}
};

#define MAXSLAVEAXIS 4
class WLDrive : public QObject
{
 Q_OBJECT

 Q_PROPERTY(QString name   READ getName WRITE setName NOTIFY changedName)
 Q_PROPERTY(double  nowPos READ position WRITE setPosition NOTIFY changedPosition)
 Q_PROPERTY(double  minPos READ minPosition WRITE setMinPosition NOTIFY changedMinPosition)
 Q_PROPERTY(double  maxPos READ maxPosition WRITE setMaxPosition NOTIFY changedMaxPosition)
 Q_PROPERTY(double  vnow   READ getVnow NOTIFY changedVnow)
 Q_PROPERTY(bool    truPos READ isTruPosition NOTIFY changedTruPosition)

public:
    enum typeDrive {Linear,Rotary};

private:
    enum autoDrive {
	               autoNo=0,
	               autoFind,
		           autoTeach,
                   autoVerify
                   };
	enum FlagDrive
	           {
		       fl_activ=      1<<0 , //активен - ожидает разрешения
               fl_velmode=  1<<1 , //vellocity mode
              // fl_latch2=     1<<2 ,
               //fl_latch3=     1<<3 ,
               fl_lastrot=    1<<4 ,
			   fl_rot=        1<<5 , //направление + 1 / - 0
			   fl_auto=       1<<6 ,//автоматический режим
               fl_interp=     1<<7 ,//интерполяция
			   fl_slave=      1<<8 ,
			   fl_wait=       1<<9 , //ожидание 
			   fl_verpos=     1<<10,//проверять правильность позиции
            //   fl_usefb =     1<<11,
			   fl_manual=     1<<12,//движение в ручном режиме
               fl_pause=      1<<15,//пауза в движении
              // fl_almen=      1<<16,//разрешение исплоьз входа ошибки
			   fl_setpos=     1<<17,//установка положения
               fl_truPos=     1<<18,//привод юстирован
               fl_infinity=   1<<19 //бесконечная
 			   };

	enum TypeLogiFind
	           {
			   noFind,
			   onlyORG,
			   onlyPEL,
			   onlyMEL,
			   onlyORGHome,
			   onlyPELHome,
			   onlyMELHome
 			   };

  WLFlags Flag;
  TypeLogiFind logicFindPos;

  QString m_name;
  int autoTypeDrive;

  double m_startPosition=0;

  double m_maxPosition=100;
  double m_minPosition=0;
  double m_homePosition=0;

  double m_orgSize=2;

  double m_ofstSlaveAxis[MAXSLAVEAXIS];

  WLDrivePosition m_nowPosition;  //current pos
  WLDrivePosition m_nextPosition; //next pos

  double m_orgPosition;
  double m_posCount;

  double m_Vmov;  //заданная скорость
  double m_feedVFind;
  double m_Vnow;  //текущая скорость

  QTimer *updateTimer;

  qint32 m_posLast;

  enum typeDrive m_type;

protected:

  WLDriveDim dim;

public:
    QList <WLIOData> resolutMovIOData;//разрешение двигаться

public:

    bool isPause() {return Flag.get(fl_pause);}

    void addInResolutionMov(WLIOPut *_inEnableMov,bool _state);
    void removeInResolutionMov(WLIOPut *_inEnableMov);

    void setLogicFindPos(quint8 logic) {if(!isAuto()) logicFindPos=static_cast<TypeLogiFind>(logic);}
 quint8 getLogicFindPos() {return logicFindPos;}

   void setFeedVFind(double Vfind) {if(Vfind>0) m_feedVFind=Vfind;}
 double feedVFind() {return m_feedVFind;}

 double getOffsetAxis(quint8 index) {return index<MAXSLAVEAXIS ? m_ofstSlaveAxis[index]:0;}
   void setOffsetAxis(quint8 index,double value) {if(index<MAXSLAVEAXIS)  {m_ofstSlaveAxis[index]=value;qDebug()<<value;}}

void setType(enum typeDrive _type=Linear) {m_type=_type; setTruPosition(false);}
enum typeDrive getType() {return m_type;}

 static double calcRotaryInfEndPosition(double startPos,double endPos);

void setInfinity(bool set=true) {Flag.set(fl_infinity,set);}
bool isInfinity() {return Flag.get(fl_infinity);}

protected slots: 

//  virtual void updateInStop();
//	virtual void updateInEMGStop();
//	virtual void updateInEnableMov();

    virtual void updateInResolutionMov();
	virtual void updateInALM();

public:
	void updateInputs();  

    WLPad m_Pad;

protected:
   // WLThreadStop *ThreadStop;
   int autoOperation;

   QMutex MutexStatus;
   QMutex MutexCallData;
   QMutex MutexDrive;
   QMutex MutexSetTask;

   dataPad  interPad;
   float curKSpeed;

 QList <WLAxis*>  m_AxisList;
 WLModuleAxis  *m_ModuleAxis;

protected:
 static QList<WLDrive*> m_driveList;

public:

static void resetDrives();
static void accelDrives();
static void pauseDrives();

static bool isActivDrives();
static bool isMotionDrives();

static WLDrive *getDrive(QString name);
static QList <WLDrive *> getDriveList();

static void  startStopDrives(bool reset=false);
static void  setMainPadDrives();

protected:
void setVerifyPosition(bool enable=true) {Flag.set(fl_verpos,enable);}
bool isVerifyPosition() {return Flag.get(fl_verpos);}   

int Mov(double d);
int Mot(double p);
int Vel(bool dir);

public:

double distanceMoved() {return position()-m_startPosition;}


public:
     WLDrive(QString name);
	~WLDrive();

bool Init();

bool isTruPosition() {return Flag.get(fl_truPos);}

QString getFullName() {return metaObject()->className()+getName();}
QString getName() {return m_name;}

void setName(QString _name) {m_name=_name; emit changedName(m_name);}
void setModuleAxis(WLModuleAxis *_ModuleAxis) {m_ModuleAxis=_ModuleAxis; m_AxisList.clear();}
void setIndexModuleAxisStr(QString str);
QString getIndexModuleAxisStr();

//WLModuleAxis *getModuleAxis() {return ModuleAxis;}


WLAxis* getAxis(quint8 i=0) {return i<m_AxisList.size()? m_AxisList.at(i):nullptr;}

QList <WLAxis*> getAxisList() {return m_AxisList;}
QList <WLAxis*> getSubAxisList() {return getAxisList().mid(1);}

void addSyhData(double pos);

//void inicial();
bool setVmov(double V=0);
bool setScurve(double Scur=0);


WLPad* pad()    {return &m_Pad;}

bool setKGear(float k);
float kGear() {return dim.kGear;}

void setWait(bool wait=true) {Flag.set(fl_wait,wait);}
bool isWait() {return Flag.get(fl_wait);}

void setInterp(bool set=true);
bool isInterp()  {return isActiv()&&Flag.get(fl_interp); }

virtual int setMovTeach();  
virtual int setMovFind();
virtual int setMovVerify();
virtual int setMov(double d) {QMutexLocker locker(&MutexDrive); return Mov(d);}
virtual int setMot(double p) {QMutexLocker locker(&MutexDrive); return Mot(p);}
virtual int setVel(bool dir) {QMutexLocker locker(&MutexDrive); return Vel(dir);}
virtual int setCorMov(double c);
virtual int addMov(double l);

virtual bool isOff() {return positionDrive().step==getAxis()->getHomePos();}
virtual void reset(); //сброс

//inline int setMotMaxPosition() {return WLDrive::setMot(getMaxPosition()); }  //движение в +
//inline int setMotMinPosition() {return WLDrive::setMot(getMinPosition());}  //движение в -

bool setMinMaxPosition(double minPos,double maxPos);
bool setMinPosition(double minPos) {return setMinMaxPosition(minPos,maxPosition());}
bool setMaxPosition(double maxPos) {return setMinMaxPosition(minPosition(),maxPos);}

inline double maxPosition() {return m_maxPosition;}
inline double minPosition() {return m_minPosition;}

inline double distance()    {return  nextPosition()-position();}
//inline double getDistanceL() {return  getNextPositionL()-getPositionL();}

//quint8 indexMAxis(){return getAxis()->getIndex();}

inline double position()     {return positionDrive().get(dim);}
inline double nextPosition() {return nextPositionDrive().get(dim);}

inline WLDrivePosition positionDrive()     {return m_nowPosition;}
inline WLDrivePosition nextPositionDrive() {return m_nextPosition;}

inline void   setOrgPosition(double pos) {m_orgPosition=pos;}
inline double getOrgPosition()           {return m_orgPosition;}
inline int    corPosition(double pos)    {return setPosition(position()-(pos-getOrgPosition()));}

inline double getORGSize()            {return m_orgSize;}
inline void   setORGSize(double size) {if(size>0) m_orgSize=size;}

inline double getOffset() {return positionDrive().offset;}

//inline long getNextPositionL() {return getNextPosition().step;}

inline double getStartPosition() {return m_startPosition;}

inline bool isLatch2();
inline bool isLatch3();

inline double getLatch2Pos(quint8 i=0) {return getLatch2PosL(i)*dimension();}
inline double getLatch3Pos(quint8 i=0) {return getLatch3PosL(i)*dimension();}

 inline long getLatch2PosL(quint8 i=0) {return i<m_AxisList.size() ? m_AxisList[i]->getLatch2() : 0;}
 inline long getLatch3PosL(quint8 i=0) {return i<m_AxisList.size() ? m_AxisList[i]->getLatch3() : 0;}


  double homePosition()         {return m_homePosition;}
 int  setHomePosition(double pos);

inline bool isActiv()                  {return Flag.get(fl_activ)||isAuto();}
inline bool isMotion()                 {return getAxis()? getAxis()->isMotion(): false;}// {return Flag.get(fl_motion);}
       bool isMotionSubAxis();
/*
inline void setMotion(bool mot=true) {bool last=Flag.get(fl_motion); 
                                      Flag.set(fl_motion,mot); 
                                     if(last!=mot) emit changedMotion(mot);}
*/

inline bool isManual() {return Flag.get(fl_manual);}

inline bool isAuto()  {return Flag.get(fl_auto);}
inline bool isAutoDrive()  {return isAuto()&&(autoTypeDrive!=autoNo);}
//inline bool isUseFB() {return Flag.get(fl_usefb);}


inline bool isAlarm()    {if(getAxis()) return getAxis()->getInput(typeInputAxis::AXIS_inALM)->getNow(); else return false;}

inline bool isDone()   {return positionDrive().step==nextPositionDrive().step;}
inline void setDone()  {m_nextPosition=m_nowPosition;}

inline bool   rot()  {return Flag.get(fl_rot);}
inline double getVnow() {return m_Vnow;}
inline double getVmov() {return m_Vmov;}

inline double dimensionGear() {if(getAxis()) return dim.value/getAxis()->getKGear(); else return dim.value;}
inline double dimension()     {return dim.value;}

inline WLDriveDim getDriveDim()     {return dim;}
inline WLDriveDim getDriveDimGear()  {WLDriveDim ret=getDriveDim(); ret.A/=getAxis()->getKGear(); return dim;}
inline bool setDriveDim(WLDriveDim dd)     {return setDimension(dd.type,dd.A,dd.B);}

bool setDimension(WLDriveDim::typeDim _type,double A, double B=1);

bool setPad(dataPad pad,typeMParAxis m_type=typeMParAxis::AXIS_MParAll);
bool setCurPad() {return setPad(pad()->getData());}

public:
virtual bool setReady() {return true;}
virtual bool setMainPad();

protected:
inline void setActiv(bool enable=true) {Flag.set(fl_activ,enable);}

protected:

virtual int waitForStartMotion()      {return 0;}
virtual int waitAfterStartMotion()    {return 0;}
virtual int waitAfterMotion()         {return 0;}
virtual int waitAfterUpdatePosition() {emit changedPosition(m_nowPosition.get(dim)); return 0;}

virtual void updatePosition();

public:
virtual int setTruPosition(bool tru=true) { int ret;

                                           if(Flag.get(fl_truPos)&&!tru) ret=-1; else ret=0;

                                            Flag.set(fl_truPos,tru);

                                            if(getAxis())
                                               getAxis()->setDisableLimit((!tru)||isInfinity());

                                            emit changedTruPosition(tru);
                                            return ret;}
public:
virtual int calcForStartMotion() {return 0;}

public:
virtual int On() {return 0;}
virtual int Off(){return 0;}

virtual void writeXMLData(QXmlStreamWriter &stream);
virtual void  readXMLData(QXmlStreamReader &stream);

protected: 

virtual	void resetAuto() {
                          qDebug()<<getName()<<"resetAuto";

                          Flag.set(fl_auto,0);
                          autoTypeDrive=autoNo;
                          if(getAxis()) getAxis()->setDisableManual(false);
                         }

        bool setAuto()   {qDebug()<<getName()<<"setAuto";

                          if(Flag.get(fl_auto))
                              return false;
                           else
                              {
                              Flag.set(fl_auto,1);
                              if(getAxis()) getAxis()->setDisableManual(true);
                              return true;
                              }
                         }


private :

public:

int setMovHome() {return setMot(homePosition());}

public:
    bool getInput(typeInputAxis type);

    bool getInputPEL() {return getInput(AXIS_inPEL);}
    bool getInputMEL() {return getInput(AXIS_inMEL);}
    bool getInputORG() {return getInput(AXIS_inORG);}
    bool getInputALM() {return getInput(AXIS_inALM);}

    int setPosition(double pos);//задание текущего значения/положения
    //int setPositionL(long pos,double offset=0);//задание текущего значения/положения

virtual	QString getStatus(){QString status;
	                   QTextStream str(&status,QIODevice::WriteOnly);
					   str<<" Activ-"<<isActiv()
						  <<" Motion-"<<isMotion()
						  <<" Wait-"<<isWait()
                          <<" ModeA-"<<getAxis()->getMode()
                          <<" StatusA-"<<getAxis()->getStatus()<<getVnow()
                          <<" StartPos="<<getStartPosition()
                          <<" NowPos="<<position()<<"("<<positionDrive().step<<")"
                          <<" NextPos="<<nextPosition()<<"("<<nextPositionDrive().step<<") ";

					   return status;
                       }
private slots: 

   void setFinished();

   void updatePos(qint32);
   void updateFreq(float);

   void setLatch2(qint32 Pos);
   void setLatch3(qint32 Pos);

   void setError(quint8 error);  


public slots:

virtual void updateAuto();
        void setEnable(bool enable);

virtual void startTask();

public:
   bool startMovPos(double pos,float V) {if(setMot(pos)==1) {startMotion(V); return true;} return false;}
   void startMovVel(float V)            {startMotion(V);}

protected:
   
   bool startAuto() {if(isAuto()) {updateAuto(); return true;} return false;}
   bool startMotion(float _Vmov=-1); //начало движения

private:
	void toStartAccel(); //ускорение
    void toStartPause(); //замедление
	void toStartStop(); //остановка
	void toStartEMGStop(); //остановка
	void toSetKSpeed(float kspeed=1);

public:

	void startAccel(); //ускорение
    void startPause(); //замедление
    void startStop(bool reset=false);  //остановка 
    void startEMGStop();  //быстрая остановка со сбросом
    void setKSpeed(float kspeed);


public slots:

virtual	void startManualInc() {startMovManual(true);}
virtual	void startManualDec() {startMovManual(false);}

virtual void stopManualMov()  {startStop();}

void setManualPercent(float per);

virtual void setPos0() {setPosition(0);}

virtual void resetAlarm();
        

public:
   void startMovManual(bool rot,double dist=0);

private:

	bool startInterp();
   float manualPercent;

public:
   float getManualPercent() {return manualPercent;}


signals:

	void autoFinished();

	void paused();//остановился но незакончил движение
	void finished();//закончил движение

    void changedMotion(bool);
    void changedPosition(double);
    void changedActiv(bool);
     
	void sendMessage(QString,QString,int); 

    void changedMaxPosition(double);
    void changedMinPosition(double);
    void changedVnow(double);
    void changedName(QString);
    void changedTruPosition(bool);
};


class WLDriveContext : public QObject
{
Q_OBJECT

Q_PROPERTY(QString name   READ nameDrive /* WRITE setNameDrive */NOTIFY changedNameDrive)
Q_PROPERTY(double  nowPos READ position /*WRITE setPosition */NOTIFY changedPosition)
//Q_PROPERTY(double  minPos READ minPosition WRITE setMinPosition NOTIFY changedMinPosition)
//Q_PROPERTY(double  maxPos READ maxPosition WRITE setMaxPosition NOTIFY changedMaxPosition)
Q_PROPERTY(double  vnow   READ Vnow NOTIFY changedVnow)
Q_PROPERTY(bool    truPos READ isTruPosition NOTIFY changedTruPosition)

public:

WLDriveContext(WLDrive *_Drive) {
                                 Drive=_Drive;
                                 connect(Drive,&WLDrive::changedName,this,&WLDriveContext::onChangedNameDrive);
                                 connect(Drive,&WLDrive::changedPosition,this,&WLDriveContext::onChangedPosition);
                                 connect(Drive,&WLDrive::changedVnow,this,&WLDriveContext::onChangedVnow);
                                 connect(Drive,&WLDrive::changedTruPosition,this,&WLDriveContext::onChangedTruPosition);
                                 }

QString nameDrive() {return Drive->getName();}
double  position()   {return Drive->position();}
double Vnow() {return Drive->getVnow();}

bool isTruPosition() {return Drive->isTruPosition();}

private:
 WLDrive *Drive;

public slots:

 void onChangedPosition(double pos)         {emit changedPosition(pos);}
 void onChangedNameDrive(QString _name)     {emit changedNameDrive(_name);}
 void onChangedVnow(double vnow)            {emit changedVnow(vnow);}
 void onChangedTruPosition(bool trupos)     {emit changedTruPosition(trupos);}

signals:

void changedNameDrive(QString);
void changedPosition(double);
void changedVnow(double);
void changedTruPosition(bool);
};

#endif // WLDRIVE_H
