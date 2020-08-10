#include "WLPad.h"
#include <QDebug>

WLPad::WLPad()
{

}

WLPad::~WLPad()
{

}

bool WLPad::Load(QString _name)
{
QMutexLocker locker(&Mutex);

if(_name.isEmpty())	return true;
 
for(int i=0;i<Data.size();i++)
{
if(Data[i].name==_name)
    {
    qDebug()<<"LoadPad"<<_name;
	nowPadBase=nowPad=Data[i];
	Vmov=nowPadBase.Vma;
	return true;
    }
}
return false;
}

inline bool WLPad::Reload()
{
return Load(nowPad.name);
}

QList<dataPad> WLPad::getDataList()
{
return Data;
}

void WLPad::setDataList(QList<dataPad> _Data)
{
QMutexLocker locker(&Mutex);

Data=_Data;

for(int i=0;i<Data.size();i++)
 for(int j=i+1;j<Data.size();j++)
     if(Data[i].name==Data[j].name)
             Data.removeAt(j--);

}

bool WLPad::SaveAD(double _Vst,double _Vma,double _Aac,double _Ade,QString n)
{
QMutexLocker locker(&Mutex);
if(!(_Vst>=0&&_Vma>0&&_Aac>0&&_Ade<0&&_Vma>=_Vst)) return 0;

dataPad PadSave;

int i;

PadSave.Aac=_Aac;
PadSave.Ade=_Ade;
PadSave.Vst=_Vst;
PadSave.Vma=_Vma;
PadSave.name=n;

for(i=0;i<Data.size();i++)
   {
   if(Data[i].name==n)   break;
   }

if(Data.size()==0
 ||Data.size()==i)
 Data+=PadSave;
else
 Data[i]=PadSave;

nowPadBase=nowPad=PadSave;

qDebug()<<"Ok"<<PadSave.Aac<<PadSave.Ade<<PadSave.Vst<<PadSave.Vma<<PadSave.name;
return 1;
}

bool WLPad::SaveTT(double Vst, double Vma, double Tac, double Tde, QString name) {return SaveAD(Vst,Vma,(Vma-Vst)/Tac,(Vst-Vma)/Tde,name);}

bool WLPad::Save(dataPad pad)   {return SaveAD(pad.Vst,pad.Vma,pad.Aac,pad.Ade,pad.name);}

QString WLPad::getName()  {return nowPad.name;}

dataPad WLPad::getData()  {return nowPad;}

QList<dataPad> WLPad::getPads() {return Data;}

dataPad WLPad::getData(QString name,bool *ok) {
    for(int i=0;i<Data.size();i++)
        if(Data[i].name==name)
          {
          if(ok) *ok=true;
          return Data[i];
          }

if(ok) *ok=false;
return nowPad;
}

bool WLPad::findData(QString name)
{
foreach(dataPad pad,Data)
 {
 if(pad.name==name) return true;
 }

return false;
}

QString WLPad::toString()
{
QString ret;
foreach(dataPad data,Data)
    {
    if(!ret.isEmpty()) ret+=";";

    ret+=data.toString();
    }

return ret;
}

void WLPad::fromString(QString str)
{
QList <dataPad> dataList;
dataPad data;
QStringList List=str.split(";");

foreach(QString dataStr,List)
    {
    data.fromString(dataStr);
    dataList+=data;
    }

setDataList(dataList);
}


bool WLPad::setSA(dataSA data)
{
return setSpeed(data.speed)+setAcc(data.acc);
}

bool WLPad::setSpePer(float percent)
{
if(percent<=0||percent>100) return false;

float k=percent/100;

nowPad.Vma=k*nowPadBase.Vma;
nowPad.Vst=k*nowPadBase.Vst;

return true;
}

bool WLPad::addSpeK(float k)
{
qDebug()<<"addSpeK"<<k;
if(k<=0||k>1) return false;

qDebug()<<"addSpeK"<<nowPad.Vma;
nowPad.Vma*=k;
nowPad.Vst*=k;
qDebug()<<"addSpeK"<<nowPad.Vma;

return true;
}

bool WLPad::setSpeed(float speed)
{
if((speed<=0)||(speed>nowPadBase.Vma))  return false;

nowPad.Vst=nowPadBase.Vst;
nowPad.Vma=speed;

if(nowPad.Vst>speed) nowPad.Vst=speed;

return true;
}

bool WLPad::setAcc(float acc)
{
if((acc<=0)||(acc>nowPad.Aac))   return false;

float k=acc/nowPad.Aac;

nowPad.Aac=acc;//=k*nowPadBase.Aac;
nowPad.Ade=k*nowPadBase.Ade;

return true;
}



bool WLPad::setAccPer(float percent)
{
if(percent<=0)  return false;

if(percent>100)    percent=100;

float k=percent/100;

nowPad.Aac=k*nowPadBase.Aac;
nowPad.Ade=k*nowPadBase.Ade;

return true;
}

