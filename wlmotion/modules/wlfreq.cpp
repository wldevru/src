#include "wlfreq.h"

WLFreq::WLFreq(QObject *parent)
	: WLElement(parent)
{
setTypeElement(typeEFreq);

Freq=1000;
flag=0;
error=0;
}

WLFreq::~WLFreq()
{

}

bool WLFreq::setMaxOut(float Fmax)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comFreq_setMaxOut<<getIndex()<<Fmax;

emit sendCommand(data);
return true;
}

bool WLFreq::sendGetData()
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<((quint8)comFreq_getDataOut)<<getIndex();

emit sendCommand(data);
return true;
}	

bool WLFreq::setEnable(bool enable)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comFreq_setEnableOut<<getIndex()<<(quint8)enable;

emit sendCommand(data);
return true;
}
