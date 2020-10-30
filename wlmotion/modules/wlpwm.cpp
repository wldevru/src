#include "wlpwm.h"

WLPWM::WLPWM(QObject *parent)
	: WLElement(parent)
{
setTypeElement(typeEOutPWM);
m_Power=0;
m_Freq=0;
error=0;

connect(this,SIGNAL(changedPower(float)),SIGNAL(changed()));
connect(this,SIGNAL(changedK(float)),SIGNAL(changed()));
connect(this,SIGNAL(changedFreq(float)),SIGNAL(changed()));
//connect(this,SIGNAL(changedEnable(bool)),SIGNAL(changed()));
}

WLPWM::~WLPWM()
{

}

void WLPWM::setData(quint8 _flag, float P, float F)
{
const auto last=Flags.m_Data;

Flags.m_Data=_flag;

if(last!=Flags.m_Data)
  {
  emit changed();
  }

if(m_Power!=P)
  {
  emit changedPower(m_Power=P);
  }

m_Freq=F;
}


bool WLPWM::setOut(float P)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

qDebug()<<data.size();

Stream<<(quint8)comPWM_setOut<<getIndex()<<P;

qDebug()<<"send setOutPWM"<<data.size();

emit sendCommand(data);
return true;
}

bool WLPWM::setInv(bool inv)
{
Flags.set(PWMF_inv,inv);

QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comPWM_setInvOut<<getIndex()<<(quint8)inv;

emit sendCommand(data);

//sendGetData();
return true;
}

bool WLPWM::setEnable(bool enable)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

qDebug()<<data.size();

Stream<<(quint8)comPWM_setEnableOut<<getIndex()<<enable;

emit sendCommand(data);
return true;
}

bool WLPWM::setPmax(float Pmax)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comPWM_setPmaxOut<<getIndex()<<Pmax;

emit sendCommand(data);
return true;
}

bool WLPWM::sendGetData()
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comPWM_getDataOut<<getIndex();

emit sendCommand(data);

return true;
}	

bool WLPWM::setKOut(float k)
{
if(k<0.0) return false;

m_Kout=k;

QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

qDebug()<<data.size();

Stream<<(quint8)comPWM_setKOut<<getIndex()<<k;

emit sendCommand(data);
return true;
}

bool WLPWM::setFreq(float F)
{
if(F<=0) return false;

m_Freq=F;

QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comPWM_setFOut<<getIndex()<<m_Freq;

emit sendCommand(data);
return true;
}

void WLPWM::setData(QDataStream &Stream)
{
quint8 ui1;

Stream>>ui1;

switch(ui1)
{
case dataPWM_Kpwm: Stream>>m_Kout; emit changedK(m_Kout); break;
case dataPWM_Fpwm: Stream>>m_Freq; emit changedFreq(m_Freq); break;
default: break;
}

}

void WLPWM::writeXMLData(QXmlStreamWriter &stream)
{
stream.writeAttribute("Freq",QString::number(freq()));
stream.writeAttribute("inv", QString::number(isInv()));

}

void WLPWM::readXMLData(QXmlStreamReader &stream)
{
if(!stream.attributes().value("Freq").isEmpty())	setFreq(stream.attributes().value("Freq").toString().toFloat());
if(!stream.attributes().value("inv").isEmpty())	    setInv(stream.attributes().value("inv").toString().toInt());
}
