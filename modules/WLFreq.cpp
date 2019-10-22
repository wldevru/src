#include "WLFreq.h"

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

bool WLFreq::setFmax(float Fmax)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comFreq_setFmaxOut<<getIndex()<<Fmax;

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

bool WLFreq::setK(float K)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comFreq_setKOut<<getIndex()<<K;

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
