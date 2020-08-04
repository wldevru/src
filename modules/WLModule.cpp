#include "WLModule.h"

WLModule::WLModule(QObject *parent)
	:WLElement(parent)
{
m_type=typeDevice;
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
data.prepend(m_type);

emit sendCommand(data); 
}

void WLModule::callProp()
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comModule_getProp;

setCommand(data);
}


void WLModule::reset()
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comModule_reset;

setCommand(data);
}

