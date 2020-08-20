#ifndef WL6DPOINT_H
#define WL6DPOINT_H

#include <math.h>
#include <QString>
#include <QVector4D>
#include <QMatrix4x4>

#include "wl3dpoint.h"
#include "wlcalc.h"

#ifndef M_PI
  #define M_PI 3.14159265358979323846
#endif

struct WL6DPoint
{
double x;
double y;
double z;

double a;
double b;
double c;

WL6DPoint () {x=y=z=a=b=c=0;}
WL6DPoint (WL3DPoint a) {set(a.x,a.y,a.z);}

WL6DPoint (double _x,double _y,double _z,double _a=0,double _b=0,double _c=0)
{
x=_x;
y=_y;
z=_z;
a=_a;
b=_b;
c=_c;
}

void set(double _x=0,double _y=0,double _z=0,double _a=0,double _b=0,double _c=0)
{
this->x=_x;
this->y=_y;
this->z=_z;
this->a=_a;
this->b=_b;
this->c=_c;
}

inline WL3DPoint to3D()
{

return WL3DPoint(this->x,this->y,this->z);
}

inline  WL3DPointf to3Df()
{
return WL3DPointf(this->x,this->y,this->z);
}

inline QVector4D toV()
{ 
return QVector4D(x,y,z,0);
}

inline void fromV(QVector4D V)
{ 
x=V.x();
y=V.y();
z=V.z();
}

WL6DPoint operator+(WL6DPoint a)
{
WL6DPoint ret;

ret.x=this->x+a.x;
ret.y=this->y+a.y;
ret.z=this->z+a.z;
/*
ret.a=this->x+a.a;
ret.b=this->y+a.b;
ret.c=this->z+a.c;
*/

return ret;
}

WL6DPoint operator+(WL3DPoint a)
{
WL6DPoint ret;

ret.x=this->x+a.x;
ret.y=this->y+a.y;
ret.z=this->z+a.z;
/*
ret.a=this->x+a.a;
ret.b=this->y+a.b;
ret.c=this->z+a.c;
*/

return ret;
}

void operator+=(WL6DPoint a)
{
this->x+=a.x;
this->y+=a.y;
this->z+=a.z;
/*
this->a+=a.a;
this->b+=a.b;
this->c+=a.c;
*/
}

WL6DPoint operator-(WL6DPoint a)
{
WL6DPoint ret;

ret.x=this->x-a.x;
ret.y=this->y-a.y;
ret.z=this->z-a.z;
/*
ret.a=this->a-a.a;
ret.b=this->b-a.b;
ret.c=this->c-a.c;
*/

return ret;
}

void operator-=(WL6DPoint a)
{
this->x-=a.x;
this->y-=a.y;
this->z-=a.z;
/*
this->a-=a.a;
this->b-=a.b;
this->c-=a.c;
*/
}

WL3DPoint operator=(WL3DPoint a)
{
this->x=a.x;
this->y=a.y;
this->z=a.z;

this->a=0;
this->b=0;
this->c=0;

return a;
}

void operator*=(double zoom)
{
this->x*=zoom;
this->y*=zoom;
this->z*=zoom;
}

bool operator!=(WL6DPoint p)
{
if(this->x!=p.x
 ||this->y!=p.y
 ||this->z!=p.z
 ||this->a!=p.a
 ||this->b!=p.b
 ||this->c!=p.c)

  return true;
else
  return false;
}

bool operator==(WL6DPoint p)
{
if(this->x==p.x
 &&this->y==p.y
 &&this->z==p.z
 &&this->a==p.a
 &&this->b==p.b
 &&this->c==p.c)
  return true;
else
  return false;
}


double getAxy(WL6DPoint cP)
{
double x=this->x-cP.x;
double y=this->y-cP.y;

if(x==0)
  {
  if(y>0) return M_PI/2;
  if(y<0) return 3*M_PI/2;
  }
if(y==0)
  {
  if(x>0) return 0;
  if(x<0) return M_PI;

  }
if(x>0)
  {
  if(y>0) return atan(y/x);
  if(y<0) return (2*M_PI-atan(-y/x));
  }
  else
  {
  if(y>0) return (M_PI-atan(y/-x));
  if(y<0) return (M_PI+atan(y/x));
  }
return 0;
}

double getR(WL6DPoint cP)
{
double x=this->x-cP.x;
double y=this->y-cP.y;

return sqrt(x*x+y*y);
}


QMatrix4x4 toM(int Ar=3,int Br=2,int Cr=1) //тип СК
{
QMatrix4x4 M;

M.setToIdentity();

switch(Ar)  //поворот по значению A
{
case  1: M*=getRotMatrix( a,0,0); break;
case -1: M*=getRotMatrix(-a,0,0); break;
case  2: M*=getRotMatrix(0, a,0); break;
case -2: M*=getRotMatrix(0,-a,0); break;
case  3: M*=getRotMatrix(0,0, a); break;
case -3: M*=getRotMatrix(0,0,-a); break;
default: break;
}

switch(Br)  //поворот по значению B
{
case  1: M*=getRotMatrix( b,0,0); break;
case -1: M*=getRotMatrix(-b,0,0); break;
case  2: M*=getRotMatrix(0, b,0); break;
case -2: M*=getRotMatrix(0,-b,0); break;
case  3: M*=getRotMatrix(0,0, b); break;
case -3: M*=getRotMatrix(0,0,-b); break;
default: break;
}

switch(Cr)  //поворот по значению B
{
case  1: M*=getRotMatrix( c,0,0); break;
case -1: M*=getRotMatrix(-c,0,0); break;
case  2: M*=getRotMatrix(0, c,0); break;
case -2: M*=getRotMatrix(0,-c,0); break;
case  3: M*=getRotMatrix(0,0, c); break;
case -3: M*=getRotMatrix(0,0,-c); break;
default: break;
}

M.setColumn(3,QVector4D(x,y,z,1)); 

return M;
}

bool fromString(QString str)
{
str.remove(QRegExp("[XYZABC]"));
str.remove(QRegExp("[xyzabc]"));

QStringList List=str.split(",");

//qDebug()<<"List.size()"<<List.size();

if(List.size()==(6))
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
 return false;

}	

QString toString(bool full=true)
{
return full?  ("X "+QString::number(this->x)
             +",Y "+QString::number(this->y)
             +",Z "+QString::number(this->z)
	         +",A "+QString::number(this->a)
             +",B "+QString::number(this->b)
             +",C "+QString::number(this->c))
			 :
              ("X "+QString::number(this->x)
             +",Y "+QString::number(this->y)
             +",Z "+QString::number(this->z));

}
};


struct WL6DPointString
{
WL6DPoint Point;

QString x;
QString y;
QString z;

QString a;
QString b;
QString c;

WL6DPointString ()
{};

void setPoint(WL6DPoint P, int n=3) 
 {
 Point=P;

 x=QString::number(P.x,'f',n);
 y=QString::number(P.y,'f',n);
 z=QString::number(P.z,'f',n);

 a=QString::number(P.a,'f',n);
 b=QString::number(P.b,'f',n);
 c=QString::number(P.c,'f',n);
 }

bool operator!=(WL6DPointString p)
{
if(this->x!=p.x
 ||this->y!=p.y
 ||this->z!=p.z
 ||this->a!=p.a
 ||this->b!=p.b
 ||this->c!=p.c)

  return true;
else
  return false;
}

bool operator==(WL6DPointString p)
{
if(this->x==p.x
 &&this->y==p.y
 &&this->z==p.z
 &&this->a==p.a
 &&this->b==p.b
 &&this->c==p.c)
  return true;
else
  return false;
}

};
#endif // WL6DPOINT_H
