#include "WLEncoder.h"

WLEncoder::WLEncoder(QObject *parent)
	: WLElement(parent)
{
setTypeElement(typeEEncoder);
posNow=0;
flag=0;
error=0;
}

WLEncoder::~WLEncoder()
{

}

bool WLEncoder::setPos(long pos)
{
posNow=pos;

QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comEnc_setPos<<(quint8)getIndex()<<(qint32)posNow;

emit sendCommand(data);
return true;
}

bool WLEncoder::sendGetData()
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comEnc_getData<<(quint8)getIndex();

//qDebug()<<"sendGetPWMData"<< i;
emit sendCommand(data);
return true;
}	

bool WLEncoder::setScale(quint16 _scale)	
{
if(_scale>0)
{
scale=_scale;
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comEnc_setScale<<(quint8)getIndex()<<(quint16)scale;

emit sendCommand(data);
return true;
}
else
 return false;
}

bool WLEncoder::setEnable(bool enable)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comEnc_setEnable<<(quint8)getIndex()<<(quint8)enable;

emit sendCommand(data);
return true;
}
