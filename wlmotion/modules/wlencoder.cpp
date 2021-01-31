#include "wlencoder.h"

WLEncoder::WLEncoder(QObject *parent)
	: WLElement(parent)
{
setTypeElement(typeEEncoder);
m_count=0;
flag=0;
error=0;

connect(this,&WLEncoder::changedCount,this,[=](){emit changed(getIndex());});
}

WLEncoder::~WLEncoder()
{

}


long WLEncoder::count() {return m_count;}

void WLEncoder::setData(QDataStream &data)
{
quint8 ui1,type;
qint32 l;

data>>type;

switch((typeDataEncoder)type)
 {
 case dataEncoder_count: data>>l;

                        if(m_count!=l)
                         {
                         m_count=l;

                         emit changedCount(m_count);
                         }
                        break;

case dataEncoder_flag:  data>>flag;
                        qDebug()<<"setFlagEncoder"<<flag;
                        emit changed(getIndex());
                        break;
/*
 case dataAxis_F:      data>>Freq;
                       emit changedFreq(Freq);
                       break;

 case dataAxis_latch2: data>>m_latchPos2;
                       m_validLatch2=true;
                       emit changedLatch2(m_latchPos2);
                       break;

 case dataAxis_latch3: data>>m_latchPos3;
                       m_validLatch3=true;
                       emit changedLatch3(m_latchPos3);
                       break;
                       */
}
}

bool WLEncoder::setCount(qint32 cnt)
{
m_count=cnt;

QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comEnc_setData<<(quint8)getIndex()<<(quint8)dataEncoder_count<<(qint32)m_count;

emit sendCommand(data);
return true;
}

bool WLEncoder::sendGetData()
{
sendGetData(typeDataEncoder::dataEncoder_count);
sendGetData(typeDataEncoder::dataEncoder_flag);
return true;
}

bool WLEncoder::sendGetData(typeDataEncoder type)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comEnc_getData<<(quint8)getIndex()<<(quint8)type;

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
