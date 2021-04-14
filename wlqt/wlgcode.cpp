#include <QFile>
#include <QTextStream>
#include "wl3dpoint.h"

#include "wlgcode.h"

WLGCode::WLGCode()
{
reset();

setGCode(98);
setGCode(90);
setGCode(80);
setGCode(17);
setGCode(02);
setGCode(01);
setGCode(54);
setGCode(61);
}

WLGCode::WLGCode(WLGCodeData _data):WLGCode()
{
setData(_data);
}

WLGCode::~WLGCode()
{

}

int WLGCode::getPlaneCirc()
{
int plane;  

if(isGCode(19)) plane=19;
else 
if(isGCode(18)) plane=18;
else plane=17;

return plane;
}

QString WLGCode::getActivGCodeString()
{
QString ret;

for(int i=0;i<GCodeSize;i++)    
   if(m_data.GCode[i])
       {
       switch(i)
       {
       case 64: ret+="G64(P"+QString::number(getG64P())
                        +"Q"+QString::number(getG64Q())
                        +") ";
                break;

       case 61: ret+=isStopMode() ? "G61.1 " : "G61 ";

                break;

       default: ret+="G"+QString::number(i)+" ";
       }
       }

if(m_data.G51Scale.x!=1.0
 ||m_data.G51Scale.y!=1.0
 ||m_data.G51Scale.z!=1.0) ret+="\nG51(X"+QString::number(m_data.G51Scale.x)
                                    +" Y"+QString::number(m_data.G51Scale.y)
                                    +" Z"+QString::number(m_data.G51Scale.z)+")";

ret+="\nF"+QString::number(m_data.gF.value);
ret+=" S" +QString::number(m_data.gS.value);
ret+=" T" +QString::number(m_data.gT.value);
ret+=" H" +QString::number(m_data.gH.value);



return ret;
}


void WLGCode::setDataTool(int number,WLGTool tool,bool send)
{
if(number<sizeTools
 &&number>=0)
    {
    m_data.Tools[number]=tool;
    if(send)
      {
      emit changedTool();
      }
    }
}


double WLGCode::getHofst()
{
double ret=0;

quint16 H=(quint16)getValue('H');

if(H!=0)
{
 if(isGCode(43)) ret=getDataTool(H).h;
   else if(isGCode(44)) ret=-getDataTool(H).h;
}
return ret;
}

void WLGCode::verifyG51()
{
if(isGCode(51)) //Scale
  {
  if(isValid('X')) m_data.G51Scale.x=getValue('X');
  if(isValid('Y')) m_data.G51Scale.y=getValue('Y');
  if(isValid('Z')) m_data.G51Scale.z=getValue('Z');

  resetGValue();
  resetGCode(51);
}
}

void WLGCode::verifyG43()
{
if((isGCode(43)||isGCode(44))
  &&getValue('H')==0) setGCode("49");
}

void WLGCode::setData(const WLGCodeData &data)
{
m_data = data;
}

WLGCodeData WLGCode::getData() const
{
    return m_data;
}

void WLGCode::setHTool(int i, float h)
{
WLGTool Tool=getDataTool(i);

Tool.h=h;

qDebug()<<"setHTool"<<i<<h<<Tool.h;

setDataTool(i,Tool);
}

double WLGCode::getValue(QString name)
{
double ret=0;


if(!name.isEmpty())
{
const char *str=name.toStdString().c_str();

ret=getValue(*str);
}

return ret;
}

double WLGCode::getHTool(int index)
{
if(index<0) index=getValue('H');

return getDataTool(index).h;
}

double WLGCode::getDTool(int index)
{
    return index<0 ? getDataTool(getT()).d : getDataTool(index).d;
}

void WLGCode::writeXMLData(QXmlStreamWriter &stream)
{
stream.writeAttribute("ofstBackLongDrill",QString::number(getOffsetBackLongDrill()));
stream.writeAttribute("strBeforeProgram",getStrBeforeProgram());
stream.writeAttribute("strAfterProgram",getStrAfterProgram());
}

void WLGCode::readXMLData(QXmlStreamReader &stream)
{
setOffsetBackLongDrill(stream.attributes().value("ofstBackLongDrill").toDouble());
setStrBeforeProgram(stream.attributes().value("strBeforeProgram").toString());
setStrAfterProgram(stream.attributes().value("strAfterProgram").toString());
}



void WLGCode::resetGValue()
{
m_data.gX.activ=0;
m_data.gY.activ=0;
m_data.gZ.activ=0;

m_data.gI.activ=0;
m_data.gJ.activ=0;
m_data.gK.activ=0;

m_data.gA.activ=0;
m_data.gB.activ=0;
m_data.gC.activ=0;

m_data.gF.activ=0;

m_data.gR.activ=0;
m_data.gP.activ=0;
m_data.gQ.activ=0;

m_data.gS.activ=0;
m_data.gT.activ=0;

m_data.initDrillPlane=false;
}

void WLGCode::resetGCode(int iG)
{
if(iG==-1)
{
for(int i=0;i<GCodeSize;i++)
        m_data.GCode[i]=false;

setGCode(80); //���� 
}
else
{
m_data.GCode[iG]=false;
}
}

void WLGCode::resetMCode(int iM)
{
if(iM==-1)
{
for(int i=0;i<MCodeSize;i++)
        m_data.MCode[i]=false;
}
else
    m_data.MCode[iM]=false;
}


int WLGCode::setGCode(QString val)
{
QStringList List=val.split(".");

int code;

if(List.isEmpty()) return -1;

code=List.first().toInt();

switch(code)
   {
   ///**00   
   case 28: m_data.GCode[28]=1;//"Position Zero point";
           break;
   ///**01
   case 0: m_data.GCode[0]=1; //"Position Fast";
           m_data.GCode[1]=0;
		   return setGCode(80);
           break;
   case 1: m_data.GCode[1]=1;//"Line Interpol";
           m_data.GCode[0]=0;
		   return setGCode(80);
           break;
   case 2: m_data.GCode[2]=1;//"CW";
           m_data.GCode[3]=0;
           m_data.GCode[0]=0;
		   break;
   case 3: m_data.GCode[3]=1;//"CCW";
           m_data.GCode[2]=0;
           m_data.GCode[0]=0;
		   break;
  case 102:
  case 103:m_data.GCode[2]=0;
           m_data.GCode[3]=0;
           break;

   //**03
   case 17:m_data.GCode[17]=1;//"Plos XY";
           m_data.GCode[18]=0;
           m_data.GCode[19]=0;
           m_data.GCode[20]=0;
           break;
   case 18:m_data.GCode[17]=0;//"Plos ZX";
           m_data.GCode[18]=1;
           m_data.GCode[19]=0;
           m_data.GCode[20]=0;
         //  cout<<" no Use";
           break;
   case 19:m_data.GCode[17]=0;//"Plos YZ";
           m_data.GCode[18]=0;
           m_data.GCode[19]=1;
           m_data.GCode[20]=0;
         //  cout<<" no Use";
           break;
   case 20:m_data.GCode[17]=1;//"Plos proizvol";
           m_data.GCode[18]=0;
           m_data.GCode[19]=0;
           m_data.GCode[20]=1;
       //    cout<<" no Use";
           break;
   //**04
   case 21:m_data.GCode[21]=1;//"Razresh kor rab podachi";
           m_data.GCode[22]=0;
           break;
   case 22:m_data.GCode[22]=1;//"Zapret kor rab podachi";
           m_data.GCode[21]=0;
           break;
   //**07
   case 43:m_data.GCode[43]=1;//"Corect Tool H +";
           m_data.GCode[44]=0;
           break;
   case 44:m_data.GCode[44]=1;//"Corect Tool H-";
           m_data.GCode[43]=0;
           break;
   case 49:m_data.GCode[44]=0;//"Corect Tool Off";
           m_data.GCode[43]=0;
           break;
  //**10
   case 51:m_data.GCode[51]=1;
           break;
   //**10
   case 53:m_data.GCode[53]=1;
           break;
   case 54:
   case 55:
   case 56:
   case 57:
   case 58:
   case 59:
           m_data.GCode[28]=0;
           m_data.GCode[53]=0;

           m_data.GCode[54]=0;
           m_data.GCode[55]=0;
           m_data.GCode[56]=0;
           m_data.GCode[57]=0;
           m_data.GCode[58]=0;
           m_data.GCode[59]=0;
           m_data.GCode[code]=1;

           if(m_data.iSC!=code-53)
            {
            m_data.iSC=code-53;//"Check SK";
            }
           break;
   //--smooth
   case 61: m_data.GCode[61]=1; //"Increm SK";
            m_data.GCode[64]=0;

            if((List.size()>1)&&(List.at(1).toInt()==1))
                m_data.stopMode=true;
            else
                m_data.stopMode=false;
           break;

   case 64:m_data.GCode[61]=0; //"Increm SK";
           m_data.GCode[64]=1;
           m_data.stopMode=false;
           break;
   //**13
   case 80:m_data.GCode[80]=1;
           m_data.GCode[81]=0; //"Off Drill";
           m_data.GCode[83]=0;
		   break;

   case 81:if((m_data.GCode[83]==0)
            &&(m_data.GCode[81]==0)) m_data.initDrillPlane=true;

           m_data.GCode[81]=1; //"Drill";
           m_data.GCode[83]=0;
           m_data.GCode[80]=0;
           break;

   case 83:if((m_data.GCode[83]==0)
            &&(m_data.GCode[81]==0)) m_data.initDrillPlane=true;

           m_data.GCode[83]=1; //"Long drill";
           m_data.GCode[81]=0;
           m_data.GCode[80]=0;    
           break;
   //**14
   case 90:if(List.size()==1)		    
	        {
            m_data.GCode[90]=1; //"Absolut SK";
            m_data.GCode[91]=0;
		    }
		   else
		    {
            if(List[1].toInt()==1) m_data.absIJK=true;
		    }
           break;

   case 91:if(List.size()==1)
		    {
            m_data.GCode[91]=1; //"Increm SK";
            m_data.GCode[90]=0;
		    }
		   else
		    {
            if(List.at(1).toInt()==1) m_data.absIJK=false;
		    }
           break;
   //**17
   case 98:m_data.GCode[98]=1;//"To Z 80";
           m_data.GCode[99]=0;
           break;
   case 99:m_data.GCode[99]=1;//"To R 80";
           m_data.GCode[98]=0;
           break;
  default: return -1;


   }
return 1;
}

int WLGCode::setMCode(int code)
{
 switch(code)
   {
   case 3: m_data.MCode[3]=1;
           m_data.MCode[4]=0;
           m_data.MCode[5]=0; break; //�������� ������

   case 4: m_data.MCode[3]=0;
           m_data.MCode[4]=1;
           m_data.MCode[5]=0; break; //�������� �����

   case 5: m_data.MCode[3]=0;
           m_data.MCode[4]=0;
           m_data.MCode[5]=1; break; //���������� ��������

  case 7: m_data.MCode[7]=1;
          m_data.MCode[8]=0;
          m_data.MCode[9]=0;break; //�������������� ����������

  case 8: m_data.MCode[8]=1;
          m_data.MCode[7]=0;
          m_data.MCode[9]=0;break; //�������� ����������

  case 9: m_data.MCode[7]=0;
          m_data.MCode[8]=0;
          m_data.MCode[10]=0;break; //��������� ����������

  case 13: setMCode(3);
           setMCode(8);break;//�������� + ��� ���
  case 14: setMCode(4);
           setMCode(8);break;//�������� + ��� ���
   
  case 30: setMCode(5);
           setMCode(9);break;//����� ���������, �� ������� ��������� �������

  default: return -1;


   }
return 1;
}

bool WLGCode::setValue(char name,double data) 
{
switch(name)
{
  case 'X': m_data.gX.set(data); break;
  case 'Y': m_data.gY.set(data); break;
  case 'Z': m_data.gZ.set(data); break;

  case 'I': m_data.gI.set(data); break;
  case 'J': m_data.gJ.set(data); break;
  case 'K': m_data.gK.set(data); break;

  case 'A': m_data.gA.set(data); break;
  case 'B': m_data.gB.set(data); break;
  case 'C': m_data.gC.set(data); break;
  
  case 'P': m_data.gP.set(data); break;
  case 'Q': m_data.gQ.set(data); break;
  case 'R': m_data.gR.set(data); break;
	  	  
  case 'F': m_data.gF.set(data); break;

  case 'S': m_data.gS.set(data); break;
  case 'T': m_data.gT.set(ceil(fabs(data))); break;

  case 'H': if(data>=0
               &&data<sizeTools)   {                
                m_data.gH.set(ceil(fabs(data)));
                }
           else {              
                return false;
                }

            break;

  default : return false;
}
return true;
}

WLGPoint WLGCode::convertPlane(WLGPoint Point,int plane,bool front)
{
WLGPoint ret=Point;
if(front)
switch(plane)
{
case 18: ret.x=Point.z;
	     ret.y=Point.x;
	     ret.z=Point.y;
		 break;

case 19: ret.x=Point.y;
	     ret.y=Point.z;
	     ret.z=Point.x;
		 break;
}
else
switch(plane)
{
case 18: ret.z=Point.x;
	     ret.x=Point.y;
	     ret.y=Point.z;
		 break;

case 19: ret.y=Point.x;
	     ret.z=Point.y;
	     ret.x=Point.z;
		 break;
}

return ret;
}

int WLGCode::getActivSC(WLGPoint *P)
{
 if(P!=nullptr)
    *P=isGCode(53) ? WLGPoint():getSC(m_data.iSC);

return isGCode(53) ? 0 : m_data.iSC;
}

double WLGCode::getValue(char name)
{
  switch(name)
  {
  case 'X': return m_data.gX.value;
  case 'Y': return m_data.gY.value;
  case 'Z': return m_data.gZ.value;

  case 'I': return m_data.gI.value;
  case 'J': return m_data.gJ.value;
  case 'K': return m_data.gK.value;

  case 'A': return m_data.gA.value;
  case 'B': return m_data.gB.value;
  case 'C': return m_data.gC.value;
  
  case 'P': return m_data.gP.value;
  case 'Q': return m_data.gQ.value;
  case 'R': return m_data.gR.value;
  
  case 'F': return m_data.gF.value;

  case 'S': return m_data.gS.value;

  case 'T': return m_data.gT.value;
  case 'H': return m_data.gH.value;

  default : return 0;
 }
/*
switch(name)
 {
  case 'X': gX.activ=false; return gX.value;
  case 'Y': gY.activ=false; return gY.value;
  case 'Z': gZ.activ=false; return gZ.value;

  case 'I': gI.activ=false; return gI.value;
  case 'J': gJ.activ=false; return gJ.value;

  case 'A': gA.activ=false; return gA.value;
  case 'B': gB.activ=false; return gB.value;
  case 'C': gC.activ=false; return gC.value;
  
  case 'Q': gQ.activ=false; return gQ.value;
  case 'R': gR.activ=false; return gR.value;
  
  case 'F': gF.activ=false; return gF.value;
  default : return 0;
 }
 */
}
 
bool WLGCode::isValid(char name)
{
switch(name)
 {
  case 'X': return m_data.gX.activ;
  case 'Y': return m_data.gY.activ;
  case 'Z': return m_data.gZ.activ;

  case 'I': return m_data.gI.activ;
  case 'J': return m_data.gJ.activ;
  case 'K': return m_data.gK.activ;

  case 'A': return m_data.gA.activ;
  case 'B': return m_data.gB.activ;
  case 'C': return m_data.gC.activ;

  case 'P': return m_data.gP.activ;
  case 'Q': return m_data.gQ.activ;
  case 'R': return m_data.gR.activ;

  case 'F': return m_data.gF.activ;
  
  case 'S': return m_data.gS.activ;
  case 'T': return m_data.gT.activ;

  case 'H': return m_data.gH.activ;

  default : return false;
 }
}   



WLGPoint WLGCode::getPointGCode(WLGPoint lastPoint,bool scale)
{ 
WLGPoint newPoint=lastPoint;

if(isGCode(91))
	{
    if(isValid('X')) newPoint.x+=getValue('X')*(scale ? m_data.G51Scale.x:1.0);
    if(isValid('Y')) newPoint.y+=getValue('Y')*(scale ? m_data.G51Scale.y:1.0);
    if(isValid('Z')) newPoint.z+=getValue('Z')*(scale ? m_data.G51Scale.z:1.0);

	if(isValid('A')) newPoint.a+=getValue('A');   
	if(isValid('B')) newPoint.b+=getValue('B');   
	if(isValid('C')) newPoint.c+=getValue('C');
    }
else
    {
    if(isValid('X')) newPoint.x=getValue('X')*(scale ? m_data.G51Scale.x:1.0);
    if(isValid('Y')) newPoint.y=getValue('Y')*(scale ? m_data.G51Scale.y:1.0);

    if(isValid('Z'))
     {
     newPoint.z=getValue('Z')*(scale ? m_data.G51Scale.z:1.0);
     newPoint.z+=getHofst();
     }

	if(isValid('A')) newPoint.a=getValue('A'); 
	if(isValid('B')) newPoint.b=getValue('B'); 
	if(isValid('C')) newPoint.c=getValue('C'); 
    }

return newPoint;
}


WLGPoint WLGCode::getPointSC(int iSC,WLGPoint GPoint,bool back)
{
WLGPoint SC=getSC(iSC);


if(getRefPoint0SC(iSC).a!=0)
{
WLFrame Fr;
WLFrame frP0(getRefPoint0SC(iSC).to3D());

if(back) GPoint=GPoint-SC;

Fr.x=GPoint.x;
Fr.y=GPoint.y;
Fr.z=GPoint.z;

if(back)
 {
 Fr.fromM(frP0.toM()*getRotMatrix(0,0,-getRefPoint0SC(iSC).a)*frP0.toM().inverted()*Fr.toM()); }
else
 {
 Fr.fromM(frP0.toM()*getRotMatrix(0,0,getRefPoint0SC(iSC).a)*frP0.toM().inverted()*Fr.toM());
 }

GPoint.x=Fr.x;
GPoint.y=Fr.y;
GPoint.z=Fr.z;

if(!back) GPoint=GPoint+SC;

return GPoint;
}
else
 return back? GPoint-SC:GPoint+SC;

}


WLGPoint WLGCode::getPointActivSC(WLGPoint GPoint,bool back)
{
return getPointSC(getActivSC(),GPoint,back);
}

WLGPoint WLGCode::movPointToActivSC(int iLastSC, WLGPoint &lastGPoint)
{      
if(iLastSC!=m_data.iSC)
 {
 lastGPoint=getPointSC(iLastSC,lastGPoint);
 lastGPoint=getPointActivSC(lastGPoint,true);
 }

return lastGPoint;
}


WLGPoint WLGCode::getPointIJK(WLGPoint lastGPoint)
{ 
WLGPoint newPoint=lastGPoint;

if(m_data.absIJK)
 { 
 switch(getPlaneCirc())
  {
  case 17: if(isValid('I')) newPoint.x=getValue('I')*m_data.G51Scale.x;
           if(isValid('J')) newPoint.y=getValue('J')*m_data.G51Scale.y;
           if(isValid('K')) newPoint.z=getValue('K')*m_data.G51Scale.z;
           break;

  case 18: if(isValid('I')) newPoint.z=getValue('I')*m_data.G51Scale.z;
           if(isValid('J')) newPoint.x=getValue('J')*m_data.G51Scale.x;
           if(isValid('K')) newPoint.y=getValue('K')*m_data.G51Scale.y;
           break;

  case 19: if(isValid('I')) newPoint.y=getValue('I')*m_data.G51Scale.y;
           if(isValid('J')) newPoint.z=getValue('J')*m_data.G51Scale.z;
           if(isValid('K')) newPoint.x=getValue('K')*m_data.G51Scale.x;
           break;
  }

 }
else
 {
 switch(getPlaneCirc())
  {
  case 17: if(isValid('I')) newPoint.x+=getValue('I')*m_data.G51Scale.x;
           if(isValid('J')) newPoint.y+=getValue('J')*m_data.G51Scale.y;
           if(isValid('K')) newPoint.z+=getValue('K')*m_data.G51Scale.z;
           break;

  case 18: if(isValid('I')) newPoint.z+=getValue('I')*m_data.G51Scale.z;
           if(isValid('J')) newPoint.x+=getValue('J')*m_data.G51Scale.x;
           if(isValid('K')) newPoint.y+=getValue('K')*m_data.G51Scale.y;
           break;

  case 19: if(isValid('I')) newPoint.y+=getValue('I')*m_data.G51Scale.y;
           if(isValid('J')) newPoint.z+=getValue('J')*m_data.G51Scale.z;
           if(isValid('K')) newPoint.x+=getValue('K')*m_data.G51Scale.x;
           break;
  }
 }

return newPoint;
}

WLGPoint WLGCode::getPointG28(WLGPoint lastGPoint)
{ 
WLGPoint newPoint=getPointActivSC(lastGPoint);//getPointActivSC(lastPoint,1);

if(isValid('X')) {newPoint.x=m_data.G28Position.x; getValue('X');}
if(isValid('Y')) {newPoint.y=m_data.G28Position.y; getValue('Y');}
if(isValid('Z')) {newPoint.z=m_data.G28Position.z; getValue('Z');}
if(isValid('A')) {newPoint.a=m_data.G28Position.a; getValue('A');}
if(isValid('B')) {newPoint.b=m_data.G28Position.b; getValue('B');}
if(isValid('C')) {newPoint.c=m_data.G28Position.c; getValue('C');}
if(isValid('U')) {newPoint.u=m_data.G28Position.u; getValue('U');}
if(isValid('V')) {newPoint.v=m_data.G28Position.v; getValue('V');}
if(isValid('W')) {newPoint.w=m_data.G28Position.w; getValue('W');}

return getPointActivSC(newPoint,true);
}

WLGPoint WLGCode::getPointG53(WLGPoint lastGPoint)
{
WLGPoint newPoint=getPointActivSC(lastGPoint);

newPoint=getPointGCode(newPoint,false);

if(isGCode(90)
 &&isValid('Z')) newPoint.z-=getHofst();

return getPointActivSC(newPoint,true);
}



void  WLGCode::rotAboutRotPointSC(int i,float a)
{
m_data.refPoint0SC[i].a=a;

emit changedSK(i);
}



WLGPoint  WLGCode::getSC(int i,bool *ok)
{
if(0<=i&&i<sizeSC) 
  {
  if(ok) *ok=true;
  return m_data.offsetSC[i];
  } 
else 
  {
  if(ok) *ok=false;
  return WLGPoint();
  }
}

WLGPoint  WLGCode::getRefPoint0SC(int i,bool *ok)
{
if(0<=i&&i<sizeSC) 
  {
  if(ok) *ok=true;
  return m_data.refPoint0SC[i];
  } 
else 
  {
  if(ok) *ok=false;
  return WLGPoint();
  }
}

WLGPoint  WLGCode::getRefPoint1SC(int i,bool *ok)
{
if(0<=i&&i<sizeSC) 
  {
  if(ok) *ok=true;
  return m_data.refPoint1SC[i];
  } 
else 
  {
  if(ok) *ok=false;
  return WLGPoint();
  }
}

bool WLGCode::setOffsetSC(int i, WLGPoint P,bool send)
{
if(0<i&&i<sizeSC)
   {
   m_data.offsetSC[i]=P;

   if(send) emit changedSK(m_data.iSC);
   return 1;
   }

return 0;
}

WLGPoint  WLGCode::getOffsetSC(int i,bool *ok)
{
 if(0<=i&&i<sizeSC)
  {
  if(ok) *ok=true;
  return m_data.offsetSC[i];
  } 
else 
  {
  if(ok) *ok=false;
  return WLGPoint();
  }
}
 

bool WLGCode::loadData(QString name_file)
{
if(name_file.isNull()) return false;

QFile FileConf(name_file);
if(!FileConf.open(QIODevice::ReadOnly)) return false;

QTextStream DriveData(&FileConf);

QString com;

//WL3DPoint P;
/*

for(;;)
{
if(DriveData.status()!=QTextStream::Ok) {qDebug("end load conf"); return 1;}
DriveData>>com;

if(com==("SC"))
            { 
			DriveData>>i>>P.x>>P.y>>P.z;  
			//if(setOffsetSC(i,P)!=0) qFatal("error load GCode(SK)");
			} 

}*/
return 1;

}

bool WLGCode::saveData(QString name_file)
{
QFile FileConf(name_file);

if(!FileConf.open(QIODevice::WriteOnly)) return false;

QTextStream Data(&FileConf);

FileConf.close();
return true;
}

bool WLGCode::calcCenterPointR(WLGPoint startGPoint,WLGPoint endGPoint)
{
//qDebug()<<"calcIJfromR";
WL3DPoint startPoint;
WL3DPoint   endPoint;
const int plane=getPlaneCirc();

startPoint=WLGCode::convertPlane(startGPoint,plane,true).to3D();
  endPoint=WLGCode::convertPlane(endGPoint,plane,true).to3D();

WL3DPoint O=(endPoint+startPoint)/2;//������� ������� �����
WL3DPoint C=(endPoint-O);          //������� ������ �� ������� ����� � �����
WL3DPoint N,Pr;

if(!isValid('R')) return false;

double R=getValue('R');

if(R==0.0) return false;

if(R<0.0)
    N.set(0,0,1); 
  else 
	N.set(0,0,-1);


double  R1=sqrt(C.x*C.x+C.y*C.y); //������� ���������� �� ������� ����� � �����
qDebug()<<"R1"<<R1;

if(R1<0) return false;


double  Rnq=R*R-R1*R1;//������� ������ ������
qDebug()<<"Rnq"<<Rnq;

if(Rnq<0) return false;

// qDebug()<<"x"<<O.x<<" y"<<O.y<<" Rnq="<<Rnq;

O+=(C*N).normalize()*sqrt(Rnq)-startPoint; //������� ������� �� ������ � ������ ���� �� ��� ���������;//������� ������������� � ���������� � ������� �����

if(m_data.absIJK){
 WLGPoint GO=WLGCode::convertPlane(WLGPoint(O),plane,false);
 GO=GO+startGPoint;
 GO=getPointActivSC(GO,true);
 O=WLGCode::convertPlane(GO,plane,true).to3D();
 }

setValue('I',O.x);//������������� ��������
setValue('J',O.y);

return true;
}

WLGCodeData::WLGCodeData()
{
G51Scale.x=1;
G51Scale.y=1;
G51Scale.z=1;

absIJK=false;

offsetHTool=0;

iCurTool=1;

gF.value=200;
gS.value=0;
gT.value=0;
}
