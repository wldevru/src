#include "wlelementtraj.h"
#include <math.h>
#include <QDebug>

//#define M_PI       3.14159265358979323846

WLElementTraj::WLElementTraj()
{
reset();
}

WLElementTraj::~WLElementTraj()
{

}

void WLElementTraj::addM(int iM)
{
if(MList.indexOf(iM)==-1) MList+=iM;
}

void WLElementTraj::reset(bool all)
{ 
blsh=false;
//ipos=0;
plane=0;
index=0;
speedF=0;
speedS=0;
movDistanceIJ=movDistanceK=movDistance=0;
str.clear();
setChild(false);
Type=nomov;
if(all)
	{	
	flags.reset();
    iTool=0;
    }
MList.clear();
//GLElemnt=0;
}


void WLElementTraj::setRotM(QMatrix4x4 M)
{
Q_UNUSED(M)
    /*
WLFrame Fr;

Fr.fromM(M*startPoint.toM());
startPoint=Fr.to6D();

Fr.fromM(M*endPoint.toM());
endPoint=Fr.to6D();

if(Type==circ)
{
WL6DPoint cP=centerPoint;
Fr.fromM(M*cP.toM());
centerPoint=Fr.to3D();
}
*/
/*

if(!Points.isEmpty())
{
for(int i=0;i<Points.size();i++)
 {
 Fr.fromM(M*Points[i].toM());
 Points[i]=Fr.to6D();
 }
}
*/

}

bool WLElementTraj::setULineXYZ(WLGPoint _startPoint,WLGPoint _midPoint,WLGPoint _endPoint)
{
 startPoint=_startPoint;
   endPoint=_endPoint;  

   midPoint=_midPoint;

 if(startPoint==midPoint||endPoint==midPoint) Type=nomov;  else Type=uline;

 if(qAbs(qAbs((startPoint.to3D()-midPoint.to3D()).r())
        -qAbs((endPoint.to3D()-midPoint.to3D()).r()))>1)
                                           return false;


return true;//startPoint!=endPoint;
}


bool WLElementTraj::setLineXYZ(WLGPoint _startPoint,WLGPoint _endPoint)
{
 startPoint=_startPoint;
   endPoint=_endPoint;  

if(startPoint==endPoint) Type=nomov;   else	 Type=line;

return true;//startPoint!=endPoint;
}

QList <WL6DPoint> WLElementTraj::calcLinePoints(bool *ok,WLGModel *GModel,double delta)
{
QList <WL6DPoint> Points;

if(!isLine()||startPoint==endPoint) 	
	{
	if(ok!=NULL) *ok=false;
    }

movDistance=(GModel->getFrame(endPoint).to3D()
            -GModel->getFrame(startPoint).to3D()).r();

Points.clear();

if(delta==0.0f)
 {
 Points+=GModel->getFrame(startPoint).to6D();
 Points+=GModel->getFrame(endPoint).to6D();
 }
else {
 int n=movDistance/delta+1;

 WLGPoint deltaG=(endPoint-startPoint)/(double)n;
 //WLGPoint cur;

 for(int i=0;i<=n;i++)
    {
    //cur=startPoint+deltaG*(double)i;
    Points+=GModel->getFrame(startPoint+deltaG*(double)i).to6D();
    }

}
//Points+=startPoint.to3D();
//Points+=endPoint.to3D();

//midPoint=(endPoint.to3D()+startPoint.to3D())/2;
//movDistance=(endPoint-startPoint).to3D().r();

startV=endV=(endPoint-startPoint).normalize();

if(ok!=NULL) *ok=true;

return Points;
}

QList <WL6DPoint> WLElementTraj::calcULinePoints(bool *ok,WLGModel *GModel,double delta)
{
Q_UNUSED(GModel)
Q_UNUSED(delta)
QList <WL6DPoint> Points;

if(!isULine()||startPoint==endPoint) 	
	{
    if(ok!=nullptr) *ok=false;
    }

float ax[3],ay[3],az[3];
float dt;
WL3DPoint P;

QMatrix3x3 T;
T(0,0)= 1; T(0,1)= 0; T(0,2)= 0;
T(1,0)=-3; T(1,1)= 4; T(1,2)=-1;
T(2,0)= 2; T(2,1)=-4; T(2,2)= 2;

 
ax[0]=startPoint.x*T(0,0)+midPoint.x*T(0,1)+endPoint.x*T(0,2);
ax[1]=startPoint.x*T(1,0)+midPoint.x*T(1,1)+endPoint.x*T(1,2);
ax[2]=startPoint.x*T(2,0)+midPoint.x*T(2,1)+endPoint.x*T(2,2);

ay[0]=startPoint.y*T(0,0)+midPoint.y*T(0,1)+endPoint.y*T(0,2);
ay[1]=startPoint.y*T(1,0)+midPoint.y*T(1,1)+endPoint.y*T(1,2);
ay[2]=startPoint.y*T(2,0)+midPoint.y*T(2,1)+endPoint.y*T(2,2);

az[0]=startPoint.z*T(0,0)+midPoint.z*T(0,1)+endPoint.z*T(0,2);
az[1]=startPoint.z*T(1,0)+midPoint.z*T(1,1)+endPoint.z*T(1,2);
az[2]=startPoint.z*T(2,0)+midPoint.z*T(2,1)+endPoint.z*T(2,2);  
   
dt=1.0f/20;

Points+=startPoint.to3D();

for(float d=dt;d<1;d+=dt)
 {
 P.x=ax[0]+ax[1]*d+ax[2]*d*d;
 P.y=ay[0]+ay[1]*d+ay[2]*d*d;
 P.z=az[0]+az[1]*d+az[2]*d*d;

 Points+=P; 
 }

Points+=endPoint.to3D();

movDistance=0;

for(int i=1;i<Points.size();i++)
 {
 movDistance+=(Points[i]-Points[i-1]).to3D().r();
 }

startV.x=ax[1];
startV.y=ay[1];	
startV.z=az[1];	
startV=startV.normalize();

endV.x=2*ax[2]+ax[1];
endV.y=2*ay[2]+ay[1];	
endV.z=2*az[2]+az[1];	
endV=endV.normalize();


if(ok) *ok=true;

return Points;
}
/*
void WLElementTraj::calcGLElement()
{
if(GLElemnt==0) GLElemnt=glGenLists(1);

if(GLElemnt!=0)
{
glNewList(GLElemnt,GL_COMPILE);

glBegin(GL_LINE_STRIP);

for(int i=0;i<Points.size();i++)
   {
   glVertex3f(Points[i].x
	         ,Points[i].y
			 ,Points[i].z);
   }
glEnd();
}

glEndList();
}
*/
bool WLElementTraj::setCircleXY(WLGPoint _startPoint,WLGPoint _centerPoint,WLGPoint _endPoint,bool CCW,int _plane)
{
Type=circ;

flags.set(fl_ccw,CCW);

 startPoint=_startPoint;
   endPoint=_endPoint;
centerPoint=_centerPoint;
      plane=_plane;

/*
qDebug()<<"SP:"<<startPoint.toString();
qDebug()<<"CP:"<<centerPoint.toString();
qDebug()<<"EP:"<<endPoint.toString();
*/
return true;
}

QList <WL6DPoint> WLElementTraj::calcCirclePoints(bool *ok,WLGModel *GModel,double delta)
{
QList <WL6DPoint> Points;

if(!isCirc()) 
	{
	if(ok!=NULL) *ok=false;
	return Points;
    }

double dl= delta < 1 ? 1: delta;
double R,R1;
double A_st;
double A_en;
double A_now;
double Ioffset;
double Joffset;

//qDebug()<<" StartP x:"<<startPoint.x<<" y:"<<startPoint.y<<" z:"<<startPoint.z;
//qDebug()<<"   EndP x:"<<endPoint.x<<" y:"<<endPoint.y<<" z:"<<endPoint.z;
//qDebug()<<"Centert x:"<<centerPoint.x<<" y:"<<centerPoint.y<<" z:"<<centerPoint.z;

//centerPoint.z=startPoint.z;???
startPoint=WLGCode::convertPlane(startPoint,plane,true);
centerPoint=WLGCode::convertPlane(centerPoint,plane,true);
endPoint=WLGCode::convertPlane(endPoint,plane,true);

Ioffset=startPoint.x-centerPoint.x;
Joffset=startPoint.y-centerPoint.y;

R =hypot(Ioffset,Joffset);

Ioffset=endPoint.x-centerPoint.x;
Joffset=endPoint.y-centerPoint.y;

R1=hypot(Ioffset,Joffset);
/*
double dR;

if(R1!=0&&R!=0)
  {
  if(R>R1) dR=R/R1; else dR=R1/R;
  }
else
  dR=2;
  */
if(R==0.0||R1==0.0)
{
//qDebug()<<"error radius"<<R<<R1;
if(ok!=NULL) *ok=false;
return Points;
}

radius=(R+R1)/2;

A_st=startPoint.to3D().getAxy(centerPoint.to3D());
A_en=endPoint.to3D().getAxy(centerPoint.to3D());

if((flags.get(fl_ccw))&&(A_en<=A_st))  A_en+=2*M_PI;
if((!flags.get(fl_ccw))&&(A_en>=A_st)) A_en-=2*M_PI;

movDistanceIJ=qAbs((A_en-A_st)*R);
movDistanceK  =qAbs(endPoint.z-startPoint.z);
movDistance   =hypot(movDistanceIJ,movDistanceK);

int n=1;

if(R<10) dl=R/10;

n=qAbs(A_en-A_st)*R/dl+1;

const double da=qAbs(A_en-A_st)/n;
const double dz=(endPoint.z-startPoint.z)/n;

flags.set(fl_spiral,dz!=0);

WL6DPoint Point;

Point=startPoint.to3D();

Points.clear();

//qDebug("A_st=%f A_e=%f dA=%f n=%d R=%f dl=%f",A_st,A_en,da,n,R,dl);

//qDebug("Start Point  %f:%f:%f",Point.x,Point.y,Point.z);

midPoint=centerPoint;
midPoint.x+=R*cos(A_st+(A_en-A_st)/2);
midPoint.y+=R*sin(A_st+(A_en-A_st)/2);
midPoint.z=(endPoint.z+startPoint.z)/2;

A_now=A_st;

int i;
for(i=0;;i++)
 {
 Point=centerPoint.to3D();
 Point.x+=R*cos(A_now);
 Point.y+=R*sin(A_now);
 Point.z+=dz*i;

 Points+=Point;
 
//qDebug("Point  %f:%f:%f",Point.x,Point.y,Point.z);
 if(flags.get(fl_ccw))
   { 
   A_now+=da;
   if(A_now>=A_en) break;
   }
 else
   {
   A_now-=da;
   if(A_now<=A_en) break;
  }
 //qDebug("A_now %f",A_now);
 }


//qDebug("i=%d",i);

//qDebug("endPoint  %f:%f:%f",endPoint.x,endPoint.y,endPoint.z);
Points+=endPoint.to3D();

 WL3DPoint N(0,0,flags.get(fl_ccw)?-1:1);

 WL3DPoint sV=(startPoint.to3D()-centerPoint.to3D());
 WL3DPoint eV=(endPoint.to3D()  -centerPoint.to3D());

 sV.z=0;
 sV=sV.normalize();
 sV=sV*N;

 eV.z=0;
 eV=eV.normalize();
 eV=eV*N;

 if(flags.get(fl_spiral))
  {
  float k=movDistanceIJ/movDistance;

  sV.x*=k;
  sV.y*=k;
  sV.z =(endPoint.to3D().z-startPoint.to3D().z)/movDistance;

  eV.x*=k;
  eV.y*=k;
  eV.z = startV.z;
  }

 startV.x=sV.x;
 startV.y=sV.y;
 startV.z=sV.z;

 endV.x=eV.x;
 endV.y=eV.y;
 endV.z=eV.z;

 startV=startV.normalize();
 endV=endV.normalize();

//qDebug("End Point  %f:%f:%f",endPoint.x,endPoint.y,endPoint.z);

startPoint=WLGCode::convertPlane(startPoint,plane,false);
centerPoint=WLGCode::convertPlane(centerPoint,plane,false);
endPoint=WLGCode::convertPlane(endPoint,plane,false);

startV=WLGCode::convertPlane(startV,plane,false);
  endV=WLGCode::convertPlane( endV,plane,false);

for(int i=0;i<Points.size();i++)
{
WLGPoint GP;

GP.x=Points[i].x;
GP.y=Points[i].y;
GP.z=Points[i].z;

GP=WLGCode::convertPlane(GP,plane,false);

Points[i].x=GP.x;
Points[i].y=GP.y;
Points[i].z=GP.z;
}
  
if(ok!=NULL) *ok=true;
return Points;  
}

void WLElementTraj::removeNoMov(QList<WLElementTraj> &Traj)
{
for(int i=0;i<Traj.size();i++)
	if(Traj[i].isNoMov()) Traj.removeAt(i--);
}





int WLElementTraj::simpliTrajectory(QList<WLElementTraj> &simpliTraj
	                               ,QList<WLElementTraj> baseTraj
								   ,float simpliDist
								   ,bool oneSimpli,float simpliAngle,int Ar,int Br,int Cr)
{
qDebug()<<"SmoothTraj";

QList <int> indexs;
WL6DPoint A,B,O;

float dist; //рассто€ние

WL3DPoint vZA,vZO;//вектор Z

simpliTraj.clear();
indexs.clear();

int i,j;

if(baseTraj.size()==1)
  {
  simpliTraj=baseTraj;
  return 1;
  }

//if(startSmooth>=0) 	i=startSmooth; else i=0;

for(i=0;i<baseTraj.size();i++)
{
indexs+=i; 

//qDebug()<<"smooth++"<<i<<indexs.size();

if(baseTraj[i].Type!=WLElementTraj::circ)//если теущий элемент лини€
//if(baseTraj[i].isLine())//если теущий элемент лини€
{
//if(Traj[i+1].isLine())     //если последующий элемент лини€//необ€зательно лижбы текущий был линией
if(indexs.size()==1)
  {
  A=baseTraj[indexs.first()].startPoint.to6D();//перва€ точка текущей пачки
  vZA.fromV(A.toM(Ar,Br,Cr).column(2));
  }

if(indexs.size()>=2)
  {
 if(simpliAngle!=0.0f) //по углу
	{
    ////KUKA
    /*
    vZO.fromV(baseTraj[indexs.last()].endPoint.to6D().toM(Ar,Br,Cr).column(2));
	if((calcAngleGrd(vZA,vZO)>simpliAngle)&&(!baseTraj[i].isFast())) goto endpack;
    */
    if(baseTraj[indexs.first()].startPoint.a!=baseTraj[indexs.last()].endPoint.a
     ||baseTraj[indexs.first()].startPoint.b!=baseTraj[indexs.last()].endPoint.b
     ||baseTraj[indexs.first()].startPoint.c!=baseTraj[indexs.last()].endPoint.c) goto endpack;
	}

  if(!baseTraj[indexs.first()].isEqData(baseTraj[indexs.last()])) goto endpack;

  if((calcACos(baseTraj[indexs.last()].endPoint.to3D()-baseTraj[indexs.size()-2].endPoint.to3D(),
             (baseTraj[indexs.size()-2].endPoint.to3D()-baseTraj[indexs.first()].startPoint.to3D()))<(-0.707)))goto endpack;

  B=baseTraj[indexs.last()].endPoint.to6D();//последн€€ точка текущей пачки

  if(baseTraj[i].isLine())
  for(j=0;j<(indexs.size()-1);j++) //по дистанции
     {	
	// qDebug()<<"verify"<<j;
     O=baseTraj[indexs[j]].endPoint.to6D(); //перебор
     dist=fabs((O.to3D()-A.to3D()).r()*calcAngleRad((O.to3D()-A.to3D()),(B.to3D()-A.to3D()))); //находим рассто€ние от общей пр€мой до всех точек
	 
   //qDebug()<<"A:"<<A.x<<A.y<<" O:"<<O.x<<O.y<<" B:"<<B.x<<B.y;
   //qDebug()<<"(O-A).r()="<<(O.to3D()-A.to3D()).r();
   //qDebug()<<"dist"<<dist;

     if(dist>simpliDist) //если нельз€ дальше считать
	     {
		//qDebug()<<"dist"<<"!!!";
		 endpack:
		 indexs.removeLast();
		 i--;
		 goto endspack;
	     }
	 } 
  }
}
else
 {
  endspack:
  //qDebug()<<"endspack:";

  if(!indexs.isEmpty()) //если 2 и больше
  {
  //Traj[indexs.first()].endPoint=Traj[indexs.last()].endPoint; //склеиваем  
  simpliTraj+=baseTraj[indexs.first()];
    
  if(indexs.size()>1)
   {
   simpliTraj+=baseTraj[indexs.last()];	   	
   simpliTraj[simpliTraj.size()-2].endPoint=simpliTraj[simpliTraj.size()-1].startPoint;
   }
  
  indexs.clear(); 
  }

  if(oneSimpli) return i;
//  smoothTraj+=baseTraj[i];
  }
}

 if(!indexs.isEmpty()) 
  {
  simpliTraj+=baseTraj[indexs.first()];

  if(indexs.size()>1)
   {
   simpliTraj+=baseTraj[indexs.last()];	   	
   simpliTraj[simpliTraj.size()-2].endPoint=simpliTraj[simpliTraj.size()-1].startPoint;
   }
  indexs.clear(); 
  }

   qDebug()<<"endsmooth";

/*
if(indexs.size()>=2) //если 2 и больше
 {
  if(smoothTraj.isEmpty())
	  smoothTraj.last().endPoint=baseTraj[indexs.last()].endPoint; //склеиваем
  //Traj[indexs.first()].endPoint=Traj[indexs.last()].endPoint; //склеиваем
  
  //j=1
  for(j=0;j<indexs.size();j++)
	   {
	   smoothTraj+=baseTraj[indexs[j]];
	   //Traj.removeAt(indexs[1]);
	   //i--;
	   } 
 
  indexs.clear(); 
  }
*/
return i;
}
///end smooth---

void WLElementTraj::updateFS(QList<WLElementTraj> &Traj)
{
float curF=1;
for(int i=0;i<Traj.size();i++)
  {
  if(Traj[i].speedF==0) 
	  Traj[i].speedF=curF;
      else
	    if(Traj[i].speedF>=0)  
			curF=Traj[i].speedF;

 // qDebug()<<"F="<<Traj[i].speedF;
  }

float curS=1;
for(int i=0;i<Traj.size();i++)
  {
  if(Traj[i].speedS==0) 
	  Traj[i].speedS=curS;
      else
	    if(Traj[i].speedS>=0)  
			curF=Traj[i].speedS;

 // qDebug()<<"F="<<Traj[i].speedF;
  }

}

inline bool WLElementTraj::isEqData(WLElementTraj ET)
{
return (((speedF==ET.speedF)
       &&(speedS==ET.speedS)
	   &&(iTool==ET.iTool))||ET.Type==nomov)
	   &&(ET.isEmptyM());
}

QString WLElementTraj::toString() 
{
QString ret;
ret=    "i"+QString::number(index)+
	  " iT"+QString::number(iTool)+
	" type"+QString::number(Type)+
	 " sP:"+startPoint.toString(false)+
	 " eP:"+endPoint.toString(false)+
      " S:"+QString::number(speedS)+
	  " F:"+QString::number(speedF);

for(int i=0;i<MList.size();i++)
 {
 ret+=" M"+QString::number(MList[i]);
 }

return ret;
}
