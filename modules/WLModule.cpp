#include "WLModule.h"

WLModule::WLModule(QObject *parent)
	:WLElement(parent)
{
typeM=typeDevice;
}


WLModule::~WLModule()
{

}

QString WLModule::getErrorStr(QString str,int ierr)
{
QString ret;
QStringList list=str.split(",");

for(int i=0;i<list.size();i+=2)
	if(list[i].toInt()==ierr)
	  {
      ret="("+list[i+1]+")";
	  break;
	  }
return ret;
}

void WLModule::setCommand(QByteArray data)
{
if(typeM!=0) data.prepend(typeM);
emit sendCommand(data); 
}

void WLModule::callProp()
{
if(typeM!=0)
 {
 QByteArray data;
 QDataStream Stream(&data,QIODevice::WriteOnly);
 
 Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
 Stream.setByteOrder(QDataStream::LittleEndian);
 
 Stream<<(quint8)typeM<<(quint8)comModule_getProp;
 
 emit sendCommand(data); 
 }
}

void WLModule::reset()
{
if(typeM!=0)
 {
 QByteArray data;
 QDataStream Stream(&data,QIODevice::WriteOnly);
 
 Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
 Stream.setByteOrder(QDataStream::LittleEndian);
 
 Stream<<(quint8)typeM<<(quint8)comModule_reset;
 
 emit sendCommand(data); 
 }
}

