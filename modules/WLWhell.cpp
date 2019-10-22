#include "WLWhell.h"

WLWhell::WLWhell(QObject *parent)
	: WLElement(parent)
{
setTypeElement(typeEWhell);
error=0;
}

WLWhell::~WLWhell()
{

}
bool WLWhell::setEnable(bool enable)
{
Flags.set(WHF_enable,enable);

QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comWhell_setEnable<<(quint8)getIndex()<<(quint8)enable;

emit sendCommand(data);
return true;
}

bool WLWhell::setAxis(int iAxis)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comWhell_setAxis<<(quint8)getIndex()<<(quint8)iAxis;

emit sendCommand(data);
return true;
}

bool WLWhell::setEncoder(quint8 _iEncoder)
{
iEncoder=_iEncoder;

QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comWhell_setEncoder<<(quint8)getIndex()<<(quint8)iEncoder;

emit sendCommand(data);
return true;
}


bool WLWhell::setKTrack(float k)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comWhell_setKTrack<<(quint8)getIndex()<<k;

emit sendCommand(data);
return true;
}


bool WLWhell::setTypeTrack(quint8 type)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comWhell_setTypeTrack<<(quint8)getIndex()<<(quint8)type;

emit sendCommand(data);
return true;
}

void WLWhell::writeXMLData(QXmlStreamWriter &stream)
{
//stream.writeAttribute("Freq",QString::number(getFreq()));
//stream.writeAttribute("inv", QString::number(isInv()));
}

void WLWhell::readXMLData(QXmlStreamReader &stream)
{
//if(!stream.attributes().value("Freq").isEmpty())	setFreq(stream.attributes().value("Freq").toString().toFloat());
//if(!stream.attributes().value("inv").isEmpty())	    setInv(stream.attributes().value("inv").toString().toInt());
}
