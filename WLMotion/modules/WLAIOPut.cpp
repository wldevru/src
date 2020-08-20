#include "wlaioput.h"

WLAIOPut::WLAIOPut(QString _comment, bool input)
{
    m_value=0.0;
    m_histValue=0.0;
    setTypeElement(input ? typeEInput : typeEOutput);
    setComment(_comment);
    Flags.reset();
    Flags.set(AIOPF_input,input);
    setObjectName("AIO");
}

void WLAIOPut::setData(QDataStream &Stream)
{
    quint8 ui1;
    float F;

    Stream>>ui1;

    switch(ui1)
    {
    case dataAIOPut_value:  Stream>>F;
        setValue(F);

        break;
    default: break;
    }

    return;
}

/*
void WLAIOPut::setInv(bool _inv)
{
//if((Flags.get(IOPF_inv))^_inv)
 {
 Flags.set(IOPF_inv,_inv);

 QByteArray data;
 QDataStream Stream(&data,QIODevice::WriteOnly);
 
 Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
 Stream.setByteOrder(QDataStream::LittleEndian);
 
 if(Flags.get(IOPF_input))
  Stream<<(quint8)comIOPut_setInputInv<<getIndex()<<(quint8)_inv;
 else
  Stream<<(quint8)comIOPut_setOutputInv<<getIndex()<<(quint8)_inv;

 emit sendCommand(data);
 emit invChanged(_inv);
 }
}

void WLAIOPut::setOut(bool now)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comIOPut_setOutputTo<<getIndex()<<(quint8)now;

emit sendCommand(data);
}

void WLAIOPut::setOutPulse(bool _now,quint32 time_ms)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comIOPut_setOutputPulse<<getIndex()<<(quint8)_now<<time_ms;

emit sendCommand(data);
}*/

void WLAIOPut::writeXMLData(QXmlStreamWriter &stream)
{
stream.writeAttribute("hist",QString::number(getHist()));

}

void WLAIOPut::readXMLData(QXmlStreamReader &stream)
{
if(!stream.attributes().value("hist").isEmpty()) setHist(stream.attributes().value("Hist").toString().toFloat());
}
