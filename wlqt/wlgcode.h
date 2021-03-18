#ifndef WLGCODE_H
#define WLGCODE_H

#include <QDebug>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#include "wl3dpoint.h"
#include "wl6dpoint.h"
#include "wlframe.h"

#define GNO_err  1
#define GNO_use  0
#define GErr    -1

#define GCodeSize 100
#define MCodeSize 100
#define sizeSC 7

#define sizeTools 24+1

struct WLGTool
{
float d;
float h;

WLGTool() {d=h=0.0f;}

QString toString()
{
return QString::number(d)+","+QString::number(h);
}

bool fromString(QString str)
{
QStringList List=str.split(",");
if(List.size()==2)
 {
 d=List[0].toFloat();
 h=List[1].toFloat();
 return true;
 }
return false;
}

};

typedef struct par
{
double value;
bool  activ;

par() {value=0;activ=false;}
void set(double _val) {value=_val; activ=true;}

}par;

#define GPointNames "X,Y,Z,A,B,C,U,V,W"

typedef struct WLGPoint
{    
double x;
double y;
double z;
double a;
double b;
double c;
double u;
double v;
double w;

WLGPoint() {x=y=z=a=b=c=u=v=w=0;}
WLGPoint(WL6DPoint point) {u=v=w=0; from6D(point); }

bool isNull()
{
return x==0.0
     &&y==0.0
     &&z==0.0
     &&a==0.0
     &&b==0.0
     &&c==0.0
     &&u==0.0
     &&v==0.0
     &&w==0.0;
}

double get(QString name,bool *ok=nullptr)
{
name=name.toUpper();

if(ok!=nullptr) *ok=true;

if(name=="X") return x;
if(name=="Y") return y;
if(name=="Z") return z;
if(name=="A") return a;
if(name=="B") return b;
if(name=="C") return c;
if(name=="U") return u;
if(name=="V") return v;
if(name=="W") return w;

if(ok!=nullptr) *ok=false;
return 0;
}

void set(QString name,double value)
{
name=name.toUpper();

if(name=="X") x=value;
else
if(name=="Y") y=value;
else
if(name=="Z") z=value;
else
if(name=="A") a=value;
else
if(name=="B") b=value;
else
if(name=="C") c=value;
else
if(name=="U") u=value;
else
if(name=="V") v=value;
else
if(name=="W") w=value;
}

bool isValid()
{
return   !isnan(x)&&!isinf(x)
       &&!isnan(y)&&!isinf(y)
       &&!isnan(z)&&!isinf(z)
       &&!isnan(a)&&!isinf(a)
       &&!isnan(b)&&!isinf(b)
       &&!isnan(c)&&!isinf(c);
}

QString toString()
{
return
   +"X "+QString::number(x)
   +",Y "+QString::number(y)
   +",Z "+QString::number(z)
   +",A "+QString::number(a)
   +",B "+QString::number(b)
   +",C "+QString::number(c);
}

bool fromString(QString str)
{
str.remove(QRegExp("[XYZABCUVW]"));
str.remove(QRegExp("[xyzabcuvw]"));

QStringList List=str.split(",");

switch(List.size())
{
case 9: u=List[6].toDouble();
        v=List[7].toDouble();
        w=List[8].toDouble();

case 6: a=List[3].toDouble();
        b=List[4].toDouble();
        c=List[5].toDouble();

case 3: x=List[0].toDouble();
        y=List[1].toDouble();
        z=List[2].toDouble();
        return true;
}

return false;
}

QString toString(bool all)
{
if(all)
return QString("X "+QString::number(x)+","
              +"Y "+QString::number(y)+","
              +"Z "+QString::number(z)+","
              +"A "+QString::number(a)+","
              +"B "+QString::number(b)+","
              +"C "+QString::number(c)+","
              +"U "+QString::number(u)+","
              +"V "+QString::number(v)+","
              +"W "+QString::number(w));
else {
    return QString("X "+QString::number(x)+","
                  +"Y "+QString::number(y)+","
                  +"Z "+QString::number(z));

}
}
WLGPoint normalize()
{
WLGPoint ret;
const double F=sqrt(x*x+y*y+z*z+a*a+b*b+c*c+u*u+v*v+w*w);

ret.x=x/F;
ret.y=y/F;
ret.z=z/F;
ret.a=a/F;
ret.b=b/F;
ret.c=c/F;
ret.u=u/F;
ret.v=v/F;
ret.w=w/F;

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

void from6D(WL6DPoint A)
{
x=A.x;
y=A.y;
z=A.z;

a=A.a;
b=A.b;
c=A.c;
}

WL6DPoint to6D()
{
WL6DPoint ret;

ret.x=x;
ret.y=y;
ret.z=z;

ret.a=a;
ret.b=b;
ret.c=c;

return ret;
}

bool operator==(WLGPoint A)
{
return x==A.x
     &&y==A.y
     &&z==A.z
     &&a==A.a
     &&b==A.b
     &&c==A.c
     &&u==A.u
     &&v==A.v
     &&w==A.w;
}

WLGPoint operator+(WLGPoint A)
{
WLGPoint ret;

ret.x=x+A.x;
ret.y=y+A.y;
ret.z=z+A.z;
ret.a=a+A.a;
ret.b=b+A.b;
ret.c=c+A.c;
ret.u=u+A.u;
ret.v=v+A.v;
ret.w=w+A.w;

return ret;
}

WLGPoint operator-(WLGPoint A)
{
WLGPoint ret;

ret.x=x-A.x;
ret.y=y-A.y;
ret.z=z-A.z;
ret.a=a-A.a;
ret.b=b-A.b;
ret.c=c-A.c;
ret.u=u-A.u;
ret.v=v-A.v;
ret.w=w-A.w;

return ret;
}

WLGPoint operator*(double A)
{
WLGPoint ret;

ret.x=x*A;
ret.y=y*A;
ret.z=z*A;
ret.a=a*A;
ret.b=b*A;
ret.c=c*A;
ret.u=u*A;
ret.v=v*A;
ret.w=w*A;

return ret;
}


WLGPoint operator/(double A)
{
WLGPoint ret;

ret.x=x/A;
ret.y=y/A;
ret.z=z/A;
ret.a=a/A;
ret.b=b/A;
ret.c=c/A;
ret.u=u/A;
ret.v=v/A;
ret.w=w/A;

return ret;
}


}WLGPoint;

struct WLGCodeData
{

 WLGPoint    offsetSC[sizeSC]; //������� ��������� ��������
 WLGPoint refPoint0SC[sizeSC]; //��������
 WLGPoint refPoint1SC[sizeSC]; //��������

 WLGPoint G43Position;
 WLGPoint G28Position;

 double offsetHTool=0;

 WLGTool Tools[sizeTools];

 WLGPoint G51Scale;

 int iCurTool=0;

 int iSC=0;

 double drillPlane=0;
 double G64P=0;
 double G64Q=0;

 bool GCode[GCodeSize];

 bool absIJK;
 bool stopMode;
 bool initDrillPlane;

 bool MCode[MCodeSize];

 QString strBeforeProgram;
 QString strAfterProgram;
 double backOffsetLonfDrill=1;

 par gX;
 par gY;
 par gZ;

 par gI;
 par gJ;
 par gK;

 par gA;
 par gB;
 par gC;

 par gF;

 par gR;
 par gP;
 par gQ;

 par gS;
 par gT;

 par gH;

 WLGCodeData();
};

class WLGCode: public QObject
{
 Q_OBJECT

public:

	enum Code
	 {
     fast_motion=00,
    
	 line       =01,
     circle_cw  =02,
     circle_ccw =03,

	 wait_motion=04,

     plane_xy   =17,
	 plane_zx   =18,
	 plane_yz   =19,
     
	 drill      =81,
	 drill_long =83,
	 drill_off  =80,

	 absolute   =90,
	 incremental=91,

	 plane_drill =98,
	 plane_drillR =99
     };

public:
    WLGCode();
    WLGCode(WLGCodeData data);

    ~WLGCode();

    bool isStopMode() {return m_data.stopMode;}

    double getG64Q() {return m_data.G64Q;}
    double getG64P() {return m_data.G64P;}

    void setG64PQ(float smooth,float simply) {if(smooth>=0&&simply>=0) {m_data.G64P=smooth;m_data.G64Q=simply;}}

Q_INVOKABLE  bool isGCode(int i) {return m_data.GCode[i];}

    bool isMCode(int i) {return m_data.MCode[i];}

    bool isInitDrillPlane() {return  m_data.initDrillPlane;}
    void setDrillPlane(double pos) {qDebug()<<"setDrillPlane"<<pos; m_data.drillPlane=pos;}
    double getDrillPlane() {return m_data.drillPlane;}

   double getValue(char);
   bool isValid(char);
   bool setValue(char name,double data);

  void resetGValue();

   WLGPoint getPointGCode(WLGPoint lastGPoint,bool scale=true);

   WLGPoint getPointG28(WLGPoint lastGPoint);
   WLGPoint getPointG53(WLGPoint lastGPoint);
   WLGPoint getPointIJK(WLGPoint lastGPoint);
   WLGPoint getPointSC(int iSC,WLGPoint GPoint,bool back=false);
   WLGPoint getPointActivSC(WLGPoint GPoint,bool back=false);

   WLGPoint movPointToActivSC(int iLastSC,WLGPoint &lastGPoint);

   static WLGPoint convertPlane(WLGPoint Point,int plane,bool front);

   int getActivSC(WLGPoint *P=nullptr);
   
   WLGPoint getSC(int i,bool *ok=nullptr);
   WLGPoint getOffsetSC(int i,bool *ok=nullptr);
   WLGPoint getOffsetActivSC(bool *ok=nullptr) {return getOffsetSC(m_data.iSC,ok);}
   WLGPoint getRefPoint0SC(int i,bool *ok=nullptr);
   WLGPoint getRefPoint1SC(int i,bool *ok=nullptr);

   bool setOffsetActivSC(WLGPoint P)    {return setOffsetSC(m_data.iSC,P);}
   bool setOffsetSC(int i,WLGPoint P,bool send=true);
   
   bool setRefPoint0SC(int i,WLGPoint P)  {if(0<i&&i<sizeSC) {m_data.refPoint0SC[i]=P; return 1;} else return 0;}
   bool setRefPoint1SC(int i,WLGPoint P)  {if(0<i&&i<sizeSC) {m_data.refPoint1SC[i]=P; return 1;} else return 0;}

   void rotAboutRotPointSC(int i,float a);

   bool loadData(QString name_file);
   bool saveData(QString name_file);

   void setXSC(double X) {setXSC(X,m_data.iSC);}
   void setYSC(double Y) {setXSC(Y,m_data.iSC);}
   void setZSC(double Z) {setXSC(Z,m_data.iSC);}
  // void setASC(float A) {setXSC(A,iSC);};

   void setXSC(double X,int i)       {m_data.offsetSC[i].x=X;}
   void setYSC(double Y,int i)       {m_data.offsetSC[i].y=Y;}
   void setZSC(double Z,int i)       {m_data.offsetSC[i].z=Z;}
													   					 
   void setOffsetASC(double A,int i) {m_data.offsetSC[i].a=A; }

    bool calcCenterPointR(WLGPoint startPoint,WLGPoint endPoint);
	 
	int setGCode(QString val);
    int setGCode(int val) {return setGCode(QString::number(val));}
	
	void resetGCode(int iG=-1);

	int setMCode(int);
	void resetMCode(int iM=-1);
	     
	void reset(void) {resetGValue();resetGCode();resetMCode();}

    WLGPoint getG28Position()        {return m_data.G28Position;}
    void setG28Position(WLGPoint hp) {m_data.G28Position=hp;}

    WLGPoint getG43Position()        {return m_data.G43Position;}
    void setG43Position(WLGPoint hp) {m_data.G43Position=hp;}

    double getOffsetHTool() {return m_data.offsetHTool; }
    void   setOffsetHTool(double ofst) {m_data.offsetHTool=ofst;}

	int getPlaneCirc();

	QString getActivGCodeString();

       void setDataTool(int index,WLGTool tool,bool send=true);
    WLGTool getDataTool(int index) {return index<sizeTools ? m_data.Tools[index] : WLGTool();}

    double getHofst();

    void verifyG51();
    void verifyG43();

    QString getStrBeforeProgram() {return m_data.strBeforeProgram;}
    QString getStrAfterProgram() {return m_data.strAfterProgram;}

    void setStrBeforeProgram(QString str) {m_data.strBeforeProgram=str;}
    void setStrAfterProgram(QString str) {m_data.strAfterProgram=str;}

    void setOffsetBackLongDrill(double offset=0) {if(offset>=0) m_data.backOffsetLonfDrill=offset;}
    double getOffsetBackLongDrill() {return  m_data.backOffsetLonfDrill;}

    void setData(const WLGCodeData &data);

    WLGCodeData getData() const;
public:

    Q_INVOKABLE void setHTool(int i,float h);
    Q_INVOKABLE  int getT()    {return getValue('T');}
    Q_INVOKABLE double getValue(QString name);
    Q_INVOKABLE double getHTool(int index);
    Q_INVOKABLE double getDTool(int index);

private:
    WLGCodeData m_data;

signals:

void changedSK(int);
void changedF();
void changedTool();

public:

virtual void writeXMLData(QXmlStreamWriter &stream);
virtual void  readXMLData(QXmlStreamReader &stream);
};

#endif // WLGCODE_H
