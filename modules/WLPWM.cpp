#include "WLPWM.h"

WLPWM WLPWM::outPWM;

WLPWM::WLPWM(QObject *parent)
	: WLElement(parent)
{
setTypeElement(typeEOutPWM);
Power=0;
Freq=0;
flag=0;
error=0;
indexPWM=0;
}

WLPWM::~WLPWM()
{

}


bool WLPWM::setOut(float P)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

qDebug()<<data.size();

Stream<<(quint8)comPWM_setOut<<(quint8)indexPWM<<P;

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

Stream<<(quint8)comPWM_setInvOut<<(quint8)indexPWM<<(quint8)inv;

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

Stream<<(quint8)comPWM_setEnableOut<<(quint8)indexPWM<<enable;

emit sendCommand(data);
return true;
}

bool WLPWM::setPmax(float Pmax)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comPWM_setPmaxOut<<(quint8)indexPWM<<Pmax;

emit sendCommand(data);
return true;
}

bool WLPWM::sendGetData()
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comPWM_getDataOut<<(quint8)indexPWM;

emit sendCommand(data);

return true;
}	

bool WLPWM::setKOut(float k)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

qDebug()<<data.size();

Stream<<(quint8)comPWM_setKOut<<(quint8)indexPWM<<k;

emit sendCommand(data);
return true;
}

bool WLPWM::setFreq(float F)
{
if(F<=0) return false;

Freq=F;

QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comPWM_setFOut<<(quint8)indexPWM<<Freq;

emit sendCommand(data);
return true;
}

void WLPWM::writeXMLData(QXmlStreamWriter &stream)
{
stream.writeAttribute("Freq",QString::number(getFreq()));
stream.writeAttribute("inv", QString::number(isInv()));

}

void WLPWM::readXMLData(QXmlStreamReader &stream)
{
if(!stream.attributes().value("Freq").isEmpty())	setFreq(stream.attributes().value("Freq").toString().toFloat());
if(!stream.attributes().value("inv").isEmpty())	    setInv(stream.attributes().value("inv").toString().toInt());
}
