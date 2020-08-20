#include <math.h>
#include <QDebug>
#include <QStringList>
#include <QVector4D>
#include <QMatrix4x4>

#ifndef WL3DPOINT_H
#define WL3DPOINT_H

#ifndef M_PI
  #define M_PI 3.14159265358979323846
#endif




struct WL3DPoint
{
double x;
double y;
double z;

WL3DPoint (double _x=0,double _y=0,double _z=0)
{
x=_x;
y=_y;
z=_z;
}

QMatrix4x4 toM()
{
QMatrix4x4 ret;

ret.setToIdentity();
ret.setColumn(3,QVector4D(x,y,z,1));

return ret;
}

void fromV(QVector4D V)
{
this->x=V.x();
this->y=V.y();
this->z=V.z();
}

void set(double _x,double _y,double _z)
{
this->x=_x;
this->y=_y;
this->z=_z;
}

WL3DPoint operator+(WL3DPoint a)
{
WL3DPoint ret;

ret.x=this->x+a.x;
ret.y=this->y+a.y;
ret.z=this->z+a.z;

return ret;
}

void operator+=(WL3DPoint a)
{
this->x+=a.x;
this->y+=a.y;
this->z+=a.z;
}

WL3DPoint operator-(WL3DPoint a)
{
WL3DPoint ret;

ret.x=this->x-a.x;
ret.y=this->y-a.y;
ret.z=this->z-a.z;

return ret;
}

WL3DPoint operator/(double n)
{
WL3DPoint ret;

ret.x=this->x/n;
ret.y=this->y/n;
ret.z=this->z/n;

return ret;
}

void operator-=(WL3DPoint a)
{
this->x-=a.x;
this->y-=a.y;
this->z-=a.z;
}

void operator*=(double zoom)
{
this->x*=zoom;
this->y*=zoom;
this->z*=zoom;
}

void operator/=(double zoom)
{
this->x/=zoom;
this->y/=zoom;
this->z/=zoom;
}

bool operator!=(WL3DPoint p)
{
if(this->x!=p.x
 ||this->y!=p.y
 ||this->z!=p.z)
  return true;
else
  return false;
}

bool operator==(WL3DPoint p)
{
if(this->x==p.x
 &&this->y==p.y
 &&this->z==p.z)
  return true;
else
  return false;
}


inline double getAxy(WL3DPoint cP)
{
return atan2(this->y-cP.y,this->x-cP.x);
}

inline double getRxy(WL3DPoint cP)
{
return hypot(this->x-cP.x,this->y-cP.y);
}

double r()
{
return sqrt(this->x*this->x
	       +this->y*this->y
		   +this->z*this->z);
}


WL3DPoint normalize()
{ 
WL3DPoint ret;

double l=sqrt(this->x*this->x
	         +this->y*this->y
	         +this->z*this->z);

if(l==0)
{
ret.x=0;
ret.y=0;
ret.z=0;
}
else
{
ret.x=this->x/l;
ret.y=this->y/l;
ret.z=this->z/l;
}

return ret;
}



WL3DPoint operator*(WL3DPoint A)
{ 
WL3DPoint ret;

ret.x=A.z*this->y-A.y*this->z;
ret.y=A.x*this->z-A.z*this->x;
ret.z=A.y*this->x-A.x*this->y;

return ret;
}

WL3DPoint operator*(double s)
{ 
WL3DPoint ret;

ret.x=this->x*s;
ret.y=this->y*s;;
ret.z=this->z*s;;

return ret;
}

void setScale(double scale)
{
this->x*=scale;
this->y*=scale;
this->z*=scale;
}

WL3DPoint toScale(double scale)
{
WL3DPoint ret;

ret.x=this->x*scale;
ret.y=this->y*scale;
ret.z=this->z*scale;

return ret;
}

inline QVector4D toV4D(double w=0)
{ 
return QVector4D(this->x,this->y,this->z,w);
}


bool fromString(QString str)
{
str.remove(QRegExp("[XYZ]"));
str.remove(QRegExp("[xyz]"));

QStringList List=str.split(",");

if(List.size()==(3))
{
this->x=List[0].toDouble();
this->y=List[1].toDouble();
this->z=List[2].toDouble();

return true;
}
else
 return false; 	
}

QString toString()
{
return ("X "+QString::number(this->x)
      +",Y "+QString::number(this->y)
      +",Z "+QString::number(this->z));

}


/*
double calcAngle(WL3DPoint A,WL3DPoint B)
{ 
return acosf((A.x*B.x+A.y*B.y+A.z*B.z)/(A.r()*B.r()));
}
*/

};

struct WL3DPointf
{
float x;
float y;
float z;

WL3DPointf (float _x=0,float _y=0,float _z=0)
{
x=_x;
y=_y;
z=_z;
}

void set(float _x=0,float _y=0,float _z=0)
{
x=_x;
y=_y;
z=_z;
}

WL3DPointf operator+(WL3DPointf A)
{
WL3DPointf ret;

ret.x=A.x+x;
ret.y=A.y+y;
ret.z=A.z+z;

return ret;
}

WL3DPointf operator/(float n)
{
WL3DPointf ret;

ret.x=x/n;
ret.y=y/n;
ret.z=z/n;

return ret;
}

WL3DPoint to3D()
{
WL3DPoint ret;

ret.x=x;
ret.y=y;
ret.z=z;

return ret;
}

};

double calcAngleRad(WL3DPoint A,WL3DPoint B);
double calcAngleGrd(WL3DPoint A,WL3DPoint B);
double calcACos(WL3DPoint A,WL3DPoint B);
/*
double calcAngleRad(QVector4D A,QVector4D B) {};
double calcAngleGrd(QVector4D A,QVector4D B) {};
double calcACos(QVector4D A,QVector4D B)     {};
  */
#endif // WL3DPOINT_H
