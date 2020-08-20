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
		       fl_spinCW=    1<<0, //шпиндель по часовой
			   fl_spinCCW=   1<<1, //шпиндель против часовой
			   fl_coolM=     1<<2, //охлаждение основное
			   fl_coolS=     1<<3, //охлаждение дополнительное
			   fl_smooth=    1<<4, //склейка
			   fl_ccw=       1<<5, //склейка
			   fl_spiral=    1<<6, //склейка
			   fl_child=     1<<7, //склейка
			   };	
 			 
	WLFlags flags;
public:
	enum TypeElement {nomov,line,circ,uline};
public:

	void setSpindleCW(bool en=true)  {flags.set(fl_spinCW,en); /*if(en) flags.set(fl_spinCCW,false);*/}
	//void setSpindleCCW(bool en=true) {flags.set(fl_spinCCW,en);if(en) flags.set(fl_spinCW,false);}
	
	void setSpindleOff() {/*setSpindleCCW(false);*/}

	bool isSpindleCW()  {return flags.get(fl_spinCW);}
	bool isSpindleCCW() {return flags.get(fl_spinCCW);}

	void setCoolM(bool en=true) {flags.set(fl_coolM,en);}
	void setCoolS(bool en=true) {flags.set(fl_coolS,en);}
    
	bool isCoolM()  {return flags.get(fl_coolM);}
	bool isCoolS()  {return flags.get(fl_coolS);}

//	void setSmooth(bool en=true) {flags.set(fl_smooth,en);}		

	bool isCCW() {return flags.get(fl_ccw);}
	
	void setChild(bool ch) {flags.set(fl_child,ch);}
	bool isChild()         {return flags.get(fl_child);}

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

inline bool isSpiral() {return isCirc()&&flags.get(fl_spiral);}
inline bool isFast()   {return speedF==-1;}

void addM(int iM);

inline void clearM()   {return MList.clear();}
inline bool isEmptyM() {return MList.isEmpty();}
inline int  takeM()    {return MList.takeFirst();}

inline bool setTool(int iT) {iTool=iT;return true;}

float movDistance;

float movDistanceIJ;
float movDistanceK;
//private:
//int SC;

TypeElement Type;

int plane;
//QList <WL6DPoint> Points;

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


quint32  index;
//int   ipos;
int   iTool;
//GLuint  GLElemnt;

QList <int> MList;
private:

/*
WL6DPoint getStartVector();
WL6DPoint getEndVector();
*/
public:
//void calcGLElement();
//WLElementTraj::removeNoMov(ListET);

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
