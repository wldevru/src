#ifndef WLFRAME_H
#define WLFRAME_H

#include <qmath.h>
#include <QMatrix4x4>
#include "wlcalc.h"
#include "wl6dpoint.h"
#include "wlflags.h"

enum FRAME_TYPE_ABC{TYPE_ABC,TYPE_CBA};

struct WLFrame
{
double x;
double y;
double z;
double a;
double b;
double c;

void reset()
{
x=y=z=a=b=c=0;
}

WLFrame(double _x,double _y,double _z,double _a,double _b,double _c) 
{
x=_x;
y=_y;
z=_z;
a=_a;
b=_b;
c=_c;
}

WLFrame (WL3DPoint P)
{
x=P.x;
y=P.y;
z=P.z;
a=0;
b=0;
c=0;
}

WLFrame (WL6DPoint P)
{
x=P.x;
y=P.y;
z=P.z;
a=P.a;
b=P.b;
c=P.c;
}

WLFrame (QMatrix4x4 M)
{
this->fromM(M);
}


WLFrame() 
{
reset();
}


QString toString() {

return
        "X "+QString::number(x)
      +",Y "+QString::number(y)
      +",Z "+QString::number(z)
      +",A "+QString::number(a)
      +",B "+QString::number(b)
      +",C "+QString::number(c);
}

bool fromString(QString str) 
{
str.remove(QRegExp("[XYZABC]"));
str.remove(QRegExp("[xyzabc]"));
str.remove(QRegExp("[E][\\d]"));      //удаляем E1---6

QStringList List=str.split(",");

if(List.size()==6)
{
this->x=List[0].toDouble();
this->y=List[1].toDouble();
this->z=List[2].toDouble();
this->a=List[3].toDouble();
this->b=List[4].toDouble();
this->c=List[5].toDouble();
return true;
}
else
  if(List.size()==3)
    {
    this->x=List[0].toDouble();
    this->y=List[1].toDouble();
    this->z=List[2].toDouble();    
	return true;
    }

return false;
}

bool operator==(WLFrame A)
{
return x==A.x
	 &&y==A.y
	 &&z==A.z
	 &&a==A.a
	 &&b==A.b
	 &&c==A.c;
}

bool operator!=(WLFrame A)
{
return qRound(x)!=qRound(A.x)
	 ||qRound(y)!=qRound(A.y)
	 ||qRound(z)!=qRound(A.z)
	 ||qRound(a)!=qRound(A.a)
	 ||qRound(b)!=qRound(A.b)
	 ||qRound(c)!=qRound(A.c);
}

WLFrame operator-(WLFrame A)
{
WLFrame ret;

ret.x=x-A.x;
ret.y=y-A.y;
ret.z=z-A.z;
ret.a=a-A.a;
ret.b=b-A.b;
ret.c=c-A.c;

return ret;
}

WLFrame operator+(WLFrame A)
{
WLFrame ret;

ret.x=x+A.x;
ret.y=y+A.y;
ret.z=z+A.z;
ret.a=a+A.a;
ret.b=b+A.b;
ret.c=c+A.c;

return ret;
}

WLFrame operator*(double A)
{
WLFrame ret;

ret.x=x*A;
ret.y=y*A;
ret.z=z*A;
ret.a=a*A;
ret.b=b*A;
ret.c=c*A;

return ret;
}

void set(WL6DPoint P) 
{
x=P.x;
y=P.y;
z=P.z;
a=P.a;
b=P.b;
c=P.c;
};

inline QVector3D toV3D()
{
return QVector3D(this->x,this->y,this->z);
}

inline QVector4D toV4D(double w=0)
{
return QVector4D(this->x,this->y,this->z,w);
}

inline WL3DPoint to3D()
{
return WL3DPoint(this->x,this->y,this->z);
}

inline WL3DPointf to3Df()
{
return WL3DPointf(this->x,this->y,this->z);
}

inline WL6DPoint to6D()
{
return WL6DPoint(x,y,z,a,b,c);
}

QMatrix4x4 toM(FRAME_TYPE_ABC type=TYPE_ABC)
{
QMatrix4x4 retM;

switch(type)
{
case TYPE_ABC: retM=getRotMatrix(0,0,a)
				   *getRotMatrix(0,b,0)
				   *getRotMatrix(c,0,0);
	           break;				   

case TYPE_CBA: retM=getRotMatrix(c,0,0)
				   *getRotMatrix(0,b,0)
				   *getRotMatrix(0,0,a);
	           break;
}
//mM=mC*mB*mA*mM;//для норм конвертации
//mM=mA*mB*mC*mM;

retM.setColumn(3,QVector4D(x,y,z,1));

return retM;
};


double fRound(double D,int n=3)
{
for(int i=0;i<n;i++) D*=10;

D=qRound(D);

for(int i=0;i<n;i++) D/=10;

return D;  
};

bool verRotM4x4(QMatrix4x4 A,QMatrix4x4 B)
{
//qDebug()<<"startVerify";
for(int i=0;i<3;i++)
	for(int j=0;j<3;j++)
	         {
			// qDebug()<<fRound(A(i,j))<<fRound(B(i,j));
			 if(fRound(A(i,j))!=fRound(B(i,j))) return false;
	         }
return true;
}

bool fromM(QMatrix4x4 M)
{
//double last;
x=M(0,3);
y=M(1,3);
z=M(2,3);

//M.setColumn(3,QVector4D(0,0,0,1));

a=b=c=0;

b=atan2(-M(2,0),sqrt(M(0,0)*M(0,0)+M(1,0)*M(1,0)))*180/M_PI;

if(qAbs(b)==90)
    {
	a=0;
	c=b/qAbs(b)*atan2(M(0,1),M(1,1))*180/M_PI;;
    }
else
    {
	a=atan2(M(1,0),M(0,0))*180/M_PI;
	c=atan2(M(2,1),M(2,2))*180/M_PI;
    }


return true;

};

};

struct WLPosition
{
double pos;
bool   act;

WLPosition () {reset();}

void set(double _pos) {pos=_pos; act=true;}
double get(double cur)  {return act ? pos: cur;}

void reset() {act=false;pos=0;}

double operator-(WLPosition B) {return pos-B.pos;}
double operator+(WLPosition B) {return pos+B.pos;}
};


#define sizeArmAxis 6
#define sizeExtAxis 6

#define stateKukaBitA1   1<<0
#define stateKukaBitA2   1<<1
#define stateKukaBitA4   1<<2


struct WL6EPos
{
WLFrame  fr;
WLPosition e[sizeExtAxis];

int s,t;

WLFlags Flag;

WL6EPos()
{
s=2;//(b010)
t=0;
for(int i=0;i<sizeExtAxis;i++)	e[i].reset();
}


bool operator==(WL6EPos A)
{
if(fr==A.fr)
{
for(int i=0;i<sizeExtAxis;i++)
     if(e[i].pos!=A.e[i].pos)  return  false;

return true;
}

return false;
}

WL6EPos operator-(WL6EPos B)
{
WL6EPos ret;

ret.fr=fr-B.fr;

for(int i=0;i<sizeExtAxis;i++)
	ret.e[i].pos=(e[i]-B.e[i]);

ret.s=B.s;
ret.t=B.t;

return ret;
}

void copyExtAxis(WLPosition *A)
{
for(int i=0;i<sizeExtAxis;i++)
	this->e[i].pos=A[i].pos;
}

void setStateBit(int b,bool state)
{
if(state)  s|=b; else  s&=~b;
}

inline void togStateBit(int b)
{
setStateBit(b,!(s&b));
}


bool fromString(QString str)
{
str.remove(QRegExp("[XYZABCST]"));
str.remove(QRegExp("[xyzabcst]"));
//str.remove(QRegExp("[E][\\d]"));      //удаляем E1---6

QStringList List=str.split(",");
QStringList ListE;
//qDebug()<<"List.size()"<<List.size();
this->reset();

if(List.size()>=(sizeArmAxis+2)) //xyz abc st
{
this->fr.x=List.takeFirst().toDouble();
this->fr.y=List.takeFirst().toDouble();
this->fr.z=List.takeFirst().toDouble();
this->fr.a=List.takeFirst().toDouble();
this->fr.b=List.takeFirst().toDouble();
this->fr.c=List.takeFirst().toDouble();

this->s=List.takeFirst().toInt();
this->t=List.takeFirst().toInt();
   
for(int ie=0;(ie<sizeExtAxis)&&(!List.isEmpty());ie++)
    {
	ListE = List.takeFirst().split(" ");
	if(ListE.size()==2)  this->e[ListE.first().remove(QRegExp("[E]")).toInt()-1].set(ListE.last().toDouble());	  
    }
return true;
}
else
{
return false;
}	   	  
}

QString toString(int an=10,int en=10,bool all=false)
{
QString ret;

ret=
	 "X "+QString::number(fr.x,'f',an)
   +",Y "+QString::number(fr.y,'f',an)
   +",Z "+QString::number(fr.z,'f',an)
   +",A "+QString::number(fr.a,'f',an)
   +",B "+QString::number(fr.b,'f',an)
   +",C "+QString::number(fr.c,'f',an)
   +",S "+QString::number(s)
   +",T "+QString::number(t);

for(int i=0;i<sizeExtAxis;i++)
	 {     
	 if(e[i].act||all)  ret+=",E"+QString::number(i+1)+" "+QString::number(e[i].pos,'f',en);
     }

return ret;
}

WL6DPoint to6D()
{
return WL6DPoint(fr.x,fr.y,fr.z,fr.a,fr.b,fr.c);
}

WL3DPoint to3D()
{
return WL3DPoint(fr.x,fr.y,fr.z);
}

void reset()
{
fr.reset();
for(int i=0;i<sizeExtAxis;i++)
e[i].reset();
}



};

struct WL6APos
{
double a[sizeArmAxis];
WLPosition e[sizeExtAxis];

WL6APos()
{
reset();
}

void reset()
{
for(int i=0;i<sizeArmAxis;i++)  a[i]=0;
for(int i=0;i<sizeExtAxis;i++)	e[i].reset();
}

void getPosExtAxis(double *buf)
{
for(int i=0;i<sizeExtAxis;i++) buf[i]=e[i].pos;
}

QString toString()
{
QString ret;

for(int i=0;i<sizeArmAxis;i++)
	 {
     if(i>0) ret+=",";
	 
	 ret+="A"+QString::number(i+1)+" "+QString::number(a[i]);	 
     }

for(int i=0;i<sizeExtAxis;i++)
     {
     ret+=",E"+QString::number(i+1);
	 if(e[i].act) ret+=" "+QString::number(e[i].pos);	 
     }

return ret;
}

bool fromString(QString str)
{
str.remove(QRegExp("[A][\\d]"));      //удаляем A1---6
//str.remove(QRegExp("[E][\\d]"));      //удаляем E1---6
	
QStringList List=str.split(",");
QStringList ListE;
//qDebug()<<"List.size()"<<List.size();
this->reset();

if(List.size()>=sizeArmAxis)
{
for(int ia=0;ia<sizeArmAxis;ia++)
	this->a[ia]=List.takeFirst().toDouble();

for(int ie=0;(ie<sizeExtAxis)&&(!List.isEmpty());ie++)
    {
	ListE = List.takeFirst().split(" ");

	if(ListE.size()==2)  this->e[ListE.first().remove(QRegExp("[E]")).toInt()-1].set(ListE.last().toDouble());	  
    }

return true;
}
else
{
return false;
}	   	  
}

void copyExtAxis(WLPosition *A)
{
for(int i=0;i<sizeExtAxis;i++)
	this->e[i].pos=A[i].pos;
}

WL6APos operator-(WL6APos B)
{
WL6APos ret;

for(int i=0;i<sizeArmAxis;i++)
	ret.a[i]=(a[i]-B.a[i]);

for(int i=0;i<sizeExtAxis;i++)
	ret.e[i].pos=(e[i]-B.e[i]);

return ret;
}

WL6APos operator+(WL6APos B)
{
WL6APos ret;

for(int i=0;i<sizeArmAxis;i++)
	ret.a[i]=a[i]+B.a[i];

for(int i=0;i<sizeExtAxis;i++)
	ret.e[i].pos=e[i]+B.e[i];

return ret;
}

WL6APos operator*(double B)
{
WL6APos ret;
for(int i=0;i<sizeArmAxis;i++)
	ret.a[i]=a[i]*B;

for(int i=0;i<sizeExtAxis;i++)
	ret.e[i].pos=e[i].pos*B;

return ret;
}
};

enum typeElementKuka {KUKA_PTP=0,KUKA_LIN=1,KUKA_CIRC=2};

#define EKTF_singular  0x01
#define EKTF_noreach   0x02
#define EKTF_outlimits 0x04
#define EKTF_update    0x08

struct WLElementKukaTraj
{
WL6EPos   ePoint;//конечная точка
WL3DPoint mPoint;//средняя точка круга

WLPosition rotA;
WLFlags Flag;

double distance;
double F;

QList <WL6EPos>   viewPoints;
QList <WL6EPos>   calcEPos;

typeElementKuka type;

WLElementKukaTraj()
{
distance=0;
F=0;
}

void update() 
{
viewPoints.clear();
Flag.set(EKTF_update,1);
}

bool isFast() {return F<0;}
};

struct WLFramen: public WLFrame
{
QString name;

WLFramen ()
{
}

WLFramen (QString _name)
{
name=_name;
reset();
}

WLFramen operator=(WLFrame A)
{
x=A.x;
y=A.y;
z=A.z;

a=A.a;
b=A.b;
c=A.c;

return *this;
}

};
#endif
