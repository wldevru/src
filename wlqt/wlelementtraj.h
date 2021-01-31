#ifndef WLELEMENTTRAJ_H
#define WLELEMENTTRAJ_H

#include <QList>

#include <QtGui>

#include "wl3dpoint.h"
#include "wlgcode.h"
#include "wlgmodel.h"
#include "wlframe.h"
#include "wlflags.h"

struct WLElementTraj 
{
private:
    enum Flag {
               fl_smooth=      1<<4, //сглаживание
               fl_ccw=         1<<5, //круг против часовой
               fl_spiral=      1<<6, //признак спирали
               fl_child=       1<<7, //дочерний элемент
               fl_script=      1<<8  //порожден скриптом
			   };	
 			 
    WLFlags Flags;
public:
	enum TypeElement {nomov,line,circ,uline};

public:
    void setG611(bool stop=false) {Flags.set(fl_smooth,!stop); m_P=0; m_Q=0;}
    void setG64PQ(float P,float Q) {if(P>=0&&Q>=0) {m_P=P; m_Q=Q;Flags.set(fl_smooth); }}

    bool isSmooth() {return Flags.get(fl_smooth);}

    void setScript(bool en) {Flags.set(fl_script,en);}
    bool isScript() {return Flags.get(fl_script);}

    float getG64P() {return m_P;}
    float getG64Q() {return m_Q;}

    bool isCCW() {return Flags.get(fl_ccw);}
	
    void setChild(bool ch) {Flags.set(fl_child,ch);}
    bool isChild()         {return Flags.get(fl_child);}

	bool isNoMov()         {return Type==nomov;}
	bool isEmpty()         {return isNoMov()&&isEmptyM();}

	QString toString(); 

inline bool isEqData(WLElementTraj ET);

public:
	WLElementTraj();
	~WLElementTraj();

bool setLineXYZ(WLGPoint _startPoint,WLGPoint _endPoint);
bool setCircleXY(WLGPoint _startPoint,WLGPoint _centerPoint,WLGPoint endPoint,bool ccw,int plane);
bool setULineXYZ(WLGPoint _startPoint,WLGPoint _midPoint,WLGPoint _endPoint);

inline QList<WL6DPoint> calcPoints(bool *ok,WLGModel *GModel,double delta=0)
	                {
                    QList<WL6DPoint> List;
					switch (Type)
					 {
                     case circ:  List=calcCirclePoints(ok,GModel,delta);break;
                     case line:  List=calcLinePoints(ok,GModel,delta);  break;
                     case uline: List=calcULinePoints(ok,GModel,delta); break;
                     default: break;
                     }
					return List; 
                    }

QList <WLElementTraj> calcModelPoints(bool *ok,WLGModel *GModel,double delta);

TypeElement getType() {return Type;}

inline void setFast(bool _fast=true)     {speedF= _fast ? -1: 0;}
inline void setBckl(bool _blsh=true)     {blsh=_blsh;}
inline bool isBacklash()     {return blsh;}

void setRotM(QMatrix4x4 M);

inline void setF(float f) {speedF=f;}
inline float getF() {return speedF;}

inline void setS(float s) {speedS=s;}
inline float getS() {return speedS;}

 void reset(bool all=true);

inline bool isCirc()  {return Type==circ;}
inline bool isLine()  {return Type==line;}
inline bool isULine() {return Type==uline;}

inline bool isSpiral() {return isCirc()&&Flags.get(fl_spiral);}
inline bool isFast()   {return (speedF==-1.0f);}

void addM(int iM);

inline void clearMList()   {return MList.clear();}
inline bool isEmptyM() {return MList.isEmpty();}
inline int  takeM()    {return MList.takeFirst();}
inline QList <int> getMList()    {return MList;}

inline bool setTool(int iT) {iTool=iT;return true;}

float movDistance;

float movDistanceIJ;
float movDistanceK;

TypeElement Type;

int plane;

WLGPoint  startPoint;
WLGPoint    midPoint; //ULine
WLGPoint    endPoint;

WLGPoint centerPoint;//Circ

WLGPoint startV;
WLGPoint   endV;


float radius;
QString str;

bool blsh;

float speedF;
float speedS;
float hcorr;

float m_P=0;
float m_Q=0;

quint32  index;

int   iTool;

QList <int> MList;

public:

static void addBacklah(QList<WLElementTraj> &Traj,WL3DPoint lastBL,bool nextMov);
static void removeNoMov(QList<WLElementTraj> &Traj);
static  int simpliTrajectory(QList<WLElementTraj> &simpliTraj,QList<WLElementTraj> baseTraj,float simpliDist ,bool oneSimpli=false,float simpliAngle=0,int Ar=0,int Br=0,int Cr=0);
static void updateFS(QList<WLElementTraj> &Traj);

bool calcVector(WL3DPoint &startV,WL3DPoint &endV);


private:

QList <WL6DPoint> calcCirclePoints(bool *ok,WLGModel *GModel,double delta);
QList <WL6DPoint> calcLinePoints(bool *ok,WLGModel *GModel,double delta);
QList <WL6DPoint> calcULinePoints(bool *ok,WLGModel *GModel,double delta);

void update();


};



#endif // WLELEMENTTRAJ_H
