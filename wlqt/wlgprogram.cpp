#include "wlgprogram.h"
#include <math.h>
#include <QTextStream>
#include <QRegExp>

const QString StartProg="start_program";
const QString EndProg  ="end_program";

#define M_PI 3.14159265358979323846

WLGProgram::WLGProgram(QObject *parent)
    : QObject(parent)
{
m_colorF=WL3DPointf(1,0,0);
m_colorG=WL3DPointf(0,0,1);
m_colorBl=WL3DPointf(0,1,0);

m_buildShow=0;
m_build=0;

m_maxShowPoints=DEF_maxShowPoints;

iActivElement=0;
iLastMovElement=0;

threadProg = new QThread;
threadProg->start(QThread::IdlePriority);
moveToThread(threadProg);	

m_buildElement=0;

time=0;
activ=0;

m_showGCode=nullptr;

m_totalKadr=0;
}

WLGProgram::~WLGProgram()
{
qDebug()<<"~WLGProgram()";

stopBuildShow();

QFile::remove(QCoreApplication::applicationDirPath()+"//prog.bkp");

threadProg->quit();
threadProg->wait();
}


void WLGProgram::setTextProgram(QString txt)
{
QFile nFile(FileName);

nFile.open(QIODevice::WriteOnly);
nFile.write(QTextCodec::codecForName("Windows-1251")->fromUnicode(txt));;
nFile.close();

reloadFile(true);
}


bool WLGProgram::loadFile(QString file,bool build)
{
bool ret=false;

stopBuildShow();

QMutexLocker loker(&MutexShowBuild);

char buf;

WLElementGProgram EP;

EP.offsetInFile=0;
EP.offsetPoint=0;

Mutex.lock();

FileName=file;

indexData.clear();
qDebug()<<"start read File";

if(File.isOpen()) File.close();

QFile::remove(QCoreApplication::applicationDirPath()+"//prog.bkp");
QFile srcFile(FileName);

File.setFileName(QCoreApplication::applicationDirPath()+"//prog.bkp");

if(srcFile.open(QIODevice::ReadOnly)
    &&File.open(QIODevice::WriteOnly)){
while(!srcFile.atEnd())
    {
    srcFile.getChar(&buf);

    if(buf=='\r') continue;

    File.putChar(buf);

    if(buf=='\n')
       {
       EP.offsetInFile=File.pos();
       indexData+=EP;
       }
    }

File.close();
}
/*
QFile::copy(FileName,QCoreApplication::applicationDirPath()+"//prog.bkp");


File.setFileName(QCoreApplication::applicationDirPath()+"//prog.bkp");
*/
if(File.open(QIODevice::ReadOnly))
 {
 ret=true;
 }
/*
  while(!File.atEnd()) 
      {
	  File.getChar(&buf);

      if(buf=='\n')
	     {
         EP.offsetInFile=File.pos();
	     indexData+=EP;	
	     }
      }
 }

*/

Mutex.unlock();

if(build) QTimer::singleShot(0,this,SLOT(updateShowTraj()));

emit ChangedProgram();
emit ChangedTrajSize(getElementCount());

return ret;
}


void WLGProgram::saveFile(QString file)
{ 
File.copy(file);
}


void WLGProgram::calcTime()
{
emit ChangedTime(++time);
}

long WLGProgram::getNKadr(QString data)
{
if(data.isNull()) return 0;

QTextStream str(&data,QIODevice::ReadOnly);

QString buf;

str>>buf;

return buf.remove("N").toLong();
}


void WLGProgram::buildShowTraj(WLGCodeData GCodeData)
{
if(!m_buildShow) return;

QMutexLocker locker(&MutexShowBuild);
WLGPoint lastGPoint;
WLGCode GCode(GCodeData);

lastGPoint.x=qInf();
lastGPoint.y=qInf();
lastGPoint.z=qInf();

QList <WLElementTraj> curListTraj;
QList <WL6DPoint> Points;

WLShowPointProgram Point;

WL3DPointf color;

int istart=-1;

bool fast=false;
bool ok=true;

bool ch_delta=true;
int iLast=0;

QString txt;
//GCode.reset();

MutexShowPoint.lock();
showPoints.clear();
MutexShowPoint.unlock();

showPoints.reserve(m_maxShowPoints+1000);

minShowPoint=maxShowPoint=WL3DPointf();


emit startedBuildShow();
emit ChangedShowProgress(0);

for(qint32 index=0;(index<indexData.size())
                 &&(showPoints.size()<m_maxShowPoints)
                 &&(m_buildShow&&ok);index++)
  {    

  txt=getTextElement(index);

  if(!translate(txt,curListTraj,lastGPoint,&GCode,index))
      {
      sendMessage(getName(),"error G code: "+txt,-1);
      break;
      }

  indexData[index].offsetPoint=showPoints.size();

  Point.scolor=index;

  if(index%10000==0) emit ChangedShowProgress(50+((float)index*50)/indexData.size());

  MutexShowPoint.lock();

  if(showPoints.isEmpty()
	&&!curListTraj.isEmpty()) fast=curListTraj.first().isFast();

  for(int i=0,j=0;i<curListTraj.size();i++)
    {
    m_GModel.setOffsetFrame(GCode.getSC(GCode.getActivSC()).to3D());

    if(istart!=-1)
      Points=curListTraj[i].calcPoints(&ok,&m_GModel,1);
    else
      Points.clear();

    Point.color= curListTraj[i].isFast()? m_colorF : m_colorG;

    ch_delta=!ch_delta;

     if((fast!=curListTraj[i].isFast())
      ||Points.isEmpty())
           {
           if(!showPoints.isEmpty())
		     {
             Point.pos=showPoints.last().pos;
             showPoints+=Point;
		     }
               fast=curListTraj[i].isFast();
           }

     for(;j<Points.size()
       &&(showPoints.size()<m_maxShowPoints);j++)
        {
        Point.pos=Points[j].to3Df();
        showPoints+=Point;
        }
     j=1;
    }

    if(istart==-1)
	   {
       if(lastGPoint.isValid())
                  {
                  istart=0;//showPoints.size()-1;
                  for(int j=0;j<istart;j++)
                          showPoints[j].pos=showPoints[istart].pos;
                  }
	   }
    else
    if(!showPoints.isEmpty())
    {
    if(iLast==0) maxShowPoint=minShowPoint=showPoints[iLast++].pos;

    for (;iLast<showPoints.size();iLast++)
     {
     if(maxShowPoint.x<showPoints[iLast].pos.x)
         maxShowPoint.x=showPoints[iLast].pos.x;
     else
         if (minShowPoint.x>showPoints[iLast].pos.x)
             minShowPoint.x=showPoints[iLast].pos.x;

     if(maxShowPoint.y<showPoints[iLast].pos.y)
         maxShowPoint.y=showPoints[iLast].pos.y;
     else
         if (minShowPoint.y>showPoints[iLast].pos.y)
             minShowPoint.y=showPoints[iLast].pos.y;

     if(maxShowPoint.z<showPoints[iLast].pos.z)
         maxShowPoint.z=showPoints[iLast].pos.z;
     else
         if (minShowPoint.z>showPoints[iLast].pos.z)
             minShowPoint.z=showPoints[iLast].pos.z;
     }

    }
    MutexShowPoint.unlock();
  }


qDebug()<<maxShowPoint.to3D().toString();
qDebug()<<minShowPoint.to3D().toString();

emit ChangedShowTraj();
emit ChangedShowProgress(100);

qDebug()<<"end buildShowTraj"<<showPoints.size()<<m_maxShowPoints;

}

QString WLGProgram::getTextProgram()
{
QMutexLocker locker(&Mutex);
File.seek(0);
return QTextCodec::codecForName("Windows-1251")->toUnicode(File.readAll());
}

QString  WLGProgram::getTextElement(qint32 index)
{
QString ret="";

QMutexLocker locker(&Mutex);

if(index<indexData.size())
 {
 if(index==0)
     {
     File.seek(0);
     ret=QTextCodec::codecForName("Windows-1251")->toUnicode(File.read(indexData[index].offsetInFile));
     }
   else
     {
     File.seek(indexData[index-1].offsetInFile);
     ret=QTextCodec::codecForName("Windows-1251")->toUnicode(File.read(indexData[index].offsetInFile-indexData[index-1].offsetInFile));
     }
  }

return ret;
}

QList <WLElementTraj> WLGProgram::buildListTraj(WLGCodeData GData)
{	
QMutexLocker locker(&MutexBuild);
QList <WLElementTraj> ListTraj;
QList <WLElementTraj> curListTraj;
WLGCode GCode;
QString com,str1;

bool ok;
WLFrame Fr;

int i;

GCode.setData(GData);

emit ChangedTrajSize(0);

ListTraj.clear();

WLGPoint lastGPoint;

ok=true;

GCode.reset();
QByteArray BA;

ok=true;
i=0;
qDebug()<<"start";
m_build=1;
QString line;


for(qint32 i=0;i<indexData.size();i++)
  {
  line=getTextElement(i);

  ok=translate(line,curListTraj,lastGPoint,&GCode,i);

  if(ok) 
      {
	  ListTraj+=curListTraj;	  
      }

   }


if(!ok) 	
  {
  qDebug()<<"Error in the frame"<<i<<ListTraj.size();
  sendMessage("Program",tr("Error in the frame: ")+BA,(-1));
  }

WLElementTraj::updateFS(ListTraj);

if(!ListTraj.isEmpty())  
  {
  setTotalKadr(m_totalKadr);
  ListTraj.first().startPoint=ListTraj.first().endPoint;
  updateNoMovPoints(ListTraj);
  }


return ListTraj;
}

void updateNoMovPoints(QList<WLElementTraj> &Traj)
{
int i,j;

  for(i=0;i<Traj.size();i++)
    {
    for(j=i;j<Traj.size();j++)
	   if(Traj[j].getType()!=WLElementTraj::nomov) 	  
		   {
		   for(;i<j;i++) //копируем
		     {
             Traj[i].startPoint=Traj[i].endPoint=Traj[j].startPoint;
		     }
		   break;
	       }	
    }

  if(Traj.last().getType()==WLElementTraj::nomov) 	  
    {
    for(i=Traj.size()-2;i>=0;i--)
		 if(Traj[i].getType()!=WLElementTraj::nomov) 
		 {		 

		 for(j=i+1;j<Traj.size();j++) //копируем
		     {
		     Traj[j].startPoint=Traj[j].endPoint=Traj[i].endPoint; 

		     }
		 break;
		 }
    }

}

bool WLGProgram::translate(QString dataStr,QList <WLElementTraj> &curListTraj,WLGPoint &lastGPoint,WLGCode *GCode,qint32 _index,bool GCodeOnly)
{
Q_UNUSED(GCodeOnly)
if(dataStr.isNull()) return  true;

WLElementTraj ElementTraj;

QString com,data,buf;
data=dataStr.toUpper();

double d1;
int i1;
bool ok;
char a;

int pos = 0;

WLGPoint curGPoint;

curListTraj.clear();

int iLastSC=GCode->getActivSC();

GCode->resetGValue();

data.remove(QRegExp("[(].*[)]"));
data.remove(QRegExp("(\\/).*"));
data.remove(QRegExp("(\\;).*"));

ok=true;

QRegExp RegExp("[A-Z]{1}[\\s]*[-]?(?:([\\d]+[.]?[\\d]*)|([\\d]?[.]?[\\d]+))");

RegExp.indexIn(data);

QTextStream str(&data,QIODevice::ReadOnly);

while ((pos = RegExp.indexIn(data, pos)) != -1)
{
QString bufStr=data.mid(pos,RegExp.matchedLength());

pos += RegExp.matchedLength();

QTextStream str(&bufStr,QIODevice::ReadOnly);

str>>a;

switch(a)
{
 case 'G': str>>buf;
           GCode->setGCode(buf);
           break;

 case 'X':
 case 'Y':
 case 'Z':

 case 'I':
 case 'J':
 case 'K':

//#ifdef DEF_5D
 case 'A':
 case 'B':
 case 'C':
//#endif

 case 'R':
 case 'P':
 case 'Q':
 case 'H':

 case 'F':
 case 'S':
 case 'T': str>>d1;
           GCode->setValue(a,d1);
           break;

 //case 'N':  str>>kadr; //qDebug()<<"N="<<kadr<<a<<f1;
//	        break;
 case 'M': str>>(i1);
           ElementTraj.addM(i1);
           GCode->setMCode(i1);
           break;
}

}

GCode->verifyG51();
GCode->verifyG43();

if(GCode->isGCode(53))
{
GCode->resetGCode(53);
curGPoint=GCode->getPointG53(lastGPoint);
}
else
 {
 GCode->movPointToActivSC(iLastSC,lastGPoint);
 curGPoint=GCode->getPointGCode(lastGPoint);
 }

ElementTraj.index=_index;
ElementTraj.str+=dataStr;

if(GCode->isValid('T')) ElementTraj.iTool=GCode->getValue('T'); 

ElementTraj.setF(GCode->getValue('F'));
ElementTraj.setS(GCode->getValue('S'));

ElementTraj.hcorr=GCode->getHofst();

if(GCode->isGCode(64)
&&(GCode->isValid('P')||GCode->isValid('Q')))
 {
 GCode->setG64PQ(GCode->isValid('P') ? GCode->getValue('P'):0
                ,GCode->isValid('Q') ? GCode->getValue('Q'):0);
 }

if(GCode->isGCode(64))
   {
   ElementTraj.setG64PQ(GCode->getG64P(),GCode->getG64Q());
   }
else
   {
   ElementTraj.setG611(GCode->isStopMode());
   }


if(GCode->isValid('R') //Если R для круга то перещитываем в I и J
 &&GCode->isGCode(80)){                      
                      ok=GCode->calcCenterPointR(GCode->getPointActivSC(lastGPoint)
                                                ,GCode->getPointActivSC(curGPoint));
                      }
if(!ok) return ok;

if(GCode->isGCode(28))
{
curGPoint=GCode->getPointG28(lastGPoint);
ElementTraj.setLineXYZ(GCode->getPointActivSC(lastGPoint)
	                  ,GCode->getPointActivSC(curGPoint));

GCode->resetGCode(28);

ElementTraj.speedF=-1; 

if(ok) curListTraj+=ElementTraj;

}
else
{
if(((GCode->isGCode(81)
   ||GCode->isGCode(83))
   &&
     (GCode->isValid('X')
    ||GCode->isValid('Y')
    ||GCode->isValid('Z')

    ||GCode->isValid('A')
    ||GCode->isValid('B')
    ||GCode->isValid('C'))))
  {
  ok=calcDrill(ElementTraj,curListTraj,lastGPoint,GCode);
  curGPoint=lastGPoint;//т.к. меняет last в конце
  }
else
{
if(GCode->isValid('I')
 ||GCode->isValid('J')
 ||GCode->isValid('K'))
  {
  if(lastGPoint.x==qInf()
   ||lastGPoint.y==qInf()
   ||lastGPoint.z==qInf())
  {
  ok=false;
  }
  else
  ok=ElementTraj.setCircleXY(GCode->getPointActivSC(lastGPoint)
                            ,GCode->getPointActivSC(GCode->getPointIJK(lastGPoint))
						    ,GCode->getPointActivSC(curGPoint)
						    ,GCode->isGCode(3)
							,GCode->getPlaneCirc());

  if(ok) curListTraj+=ElementTraj; 
 }
 else
 if(GCode->isValid('X')
  ||GCode->isValid('Y')
  ||GCode->isValid('Z')

  ||GCode->isValid('A')
  ||GCode->isValid('B')
  ||GCode->isValid('C'))
    {
    ok=ElementTraj.setLineXYZ(GCode->getPointActivSC(lastGPoint)
		                     ,GCode->getPointActivSC(curGPoint));

    if(GCode->isGCode(0)) ElementTraj.speedF=-1; 

	if(ok) curListTraj+=ElementTraj;
    }
    else
	{
	 ElementTraj.Type=WLElementTraj::nomov;
     ElementTraj.endPoint=
     ElementTraj.startPoint=GCode->getPointActivSC(lastGPoint);
     curListTraj+=ElementTraj;	   
	 
    }

}
}

lastGPoint=curGPoint;

return ok;
}


bool WLGProgram::calcDrill(WLElementTraj ElementTraj,QList <WLElementTraj> &curListTraj,WLGPoint &lastGPoint,WLGCode *GCode)
{	
WLGPoint Point;

float F=ElementTraj.getF();
float R;

Point=GCode->getPointGCode(lastGPoint);

if(GCode->isInitDrillPlane())  GCode->setDrillPlane(lastGPoint.z);

ElementTraj.Type=WLElementTraj::line;
ElementTraj.setFast(true);            //??????
ElementTraj.startPoint=GCode->getPointActivSC(lastGPoint);
ElementTraj.endPoint=GCode->getPointActivSC(GCode->getPointGCode(lastGPoint));

ElementTraj.endPoint.z=ElementTraj.startPoint.z;

qDebug()<<"Z-="<<ElementTraj.endPoint.z;

QString str=ElementTraj.str;
curListTraj+=ElementTraj;

ElementTraj.setChild(true);
ElementTraj.setFast(true);            //Быстро опускаемся
ElementTraj.str=str+"//fast plane R";
ElementTraj.startPoint=ElementTraj.endPoint;

Point=GCode->getPointGCode(lastGPoint);
Point.z=GCode->getValue('R')+GCode->getHofst();

ElementTraj.endPoint.z=GCode->getPointActivSC(Point).z;

curListTraj+=ElementTraj;

if(GCode->isGCode(81))               //??????? ?????????
  {
  ElementTraj.setF(F);            //?????????
  ElementTraj.str=str+"//drill to Z";
  ElementTraj.startPoint=ElementTraj.endPoint;

  Point=GCode->getPointGCode(lastGPoint);
  Point.z=GCode->getValue('Z')+GCode->getHofst();

  ElementTraj.endPoint.z=GCode->getPointActivSC(Point).z;

  curListTraj+=ElementTraj;

  ElementTraj.setFast(true);              //подъём
  ElementTraj.str=str+"//back R";
  ElementTraj.startPoint=ElementTraj.endPoint;

  Point=GCode->getPointGCode(lastGPoint);

  if(GCode->isGCode(99))
     Point.z=GCode->getValue('R')+GCode->getHofst();
    else //98
     Point.z=GCode->getDrillPlane();

  ElementTraj.endPoint.z=GCode->getPointActivSC(Point).z;

  curListTraj+=ElementTraj;

  lastGPoint=GCode->getPointGCode(lastGPoint);
  lastGPoint.z=Point.z;
  return true;
  }
else
if(GCode->isGCode(83))               //с подъёмами
  {
  if(GCode->getValue('Q')==0) {return false;}

  float dist=GCode->getValue('R')-GCode->getValue('Z');
  int   n=dist/GCode->getValue('Q');
  float step=dist/n;

  ElementTraj.setF(F);            //сверлим
  ElementTraj.str=str+"//drill to Z";
  ElementTraj.startPoint=ElementTraj.endPoint;

  Point=GCode->getPointGCode(lastGPoint);
  Point.z=GCode->getValue('R')+GCode->getHofst();

  for(int i=0;i<n;i++)
   {
   if(i!=0){
           ElementTraj.setFast(true);
           ElementTraj.str=str+"//back to drill";
           ElementTraj.startPoint=ElementTraj.endPoint;

           Point=GCode->getPointGCode(lastGPoint);
           Point.z=GCode->getValue('R')+GCode->getHofst();
           Point.z-=step*(i+1-1);

           if(GCode->getOffsetBackLongDrill()>0)
            {
            if((Point.z+GCode->getOffsetBackLongDrill())<=R)
                 {
                 Point.z+=GCode->getOffsetBackLongDrill();
                 ElementTraj.endPoint.z=GCode->getPointActivSC(Point).z;
                 curListTraj+=ElementTraj;
                 }
            }
            else {
                 ElementTraj.endPoint.z=GCode->getPointActivSC(Point).z;
                 curListTraj+=ElementTraj;
                 }
           }

   ElementTraj.setF(F);            //сверлим
   ElementTraj.str=str+"//drill to Z";
   ElementTraj.startPoint=ElementTraj.endPoint;

   Point=GCode->getPointGCode(lastGPoint);
   Point.z=GCode->getValue('R')+GCode->getHofst();

   Point.z-=step*(i+1);

   ElementTraj.endPoint.z=GCode->getPointActivSC(Point).z;
   curListTraj+=ElementTraj;
   
   if((i+1)<n)
   {
   ElementTraj.setFast(true);            //подъём
   ElementTraj.str=str+"//back R";
   ElementTraj.startPoint=ElementTraj.endPoint;

   Point=GCode->getPointGCode(lastGPoint);
   Point.z=GCode->getValue('R')+GCode->getHofst();

   ElementTraj.endPoint.z=GCode->getPointActivSC(Point).z;
   curListTraj+=ElementTraj;
   }
   }

  ElementTraj.setFast(true);              //подъём
  ElementTraj.str=str+"//back R";
  ElementTraj.startPoint=ElementTraj.endPoint;

  Point=GCode->getPointGCode(lastGPoint);

  if(GCode->isGCode(99))
     Point.z=GCode->getValue('R')+GCode->getHofst();
    else //98
     Point.z=GCode->getDrillPlane();

  ElementTraj.endPoint.z=GCode->getPointActivSC(Point).z;

  curListTraj+=ElementTraj;

  lastGPoint=GCode->getPointGCode(lastGPoint);
  lastGPoint.z=Point.z;
  return true;
  }


return false;
}	
