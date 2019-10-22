#include "WLDCan.h"

WLDCan::WLDCan(QObject *parent)
	: WLElement(parent)
{
setTypeElement(typeEDCan);
adrCan=0;
}

WLDCan::~WLDCan()
{

}

bool WLDCan::setAdrCan(quint16 _adrCan) 
{
if(_adrCan==0) return false;

adrCan=_adrCan;

QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comDCan_setAddress<<(quint8)getIndex()<<adrCan;

emit sendCommand(data);
return true;
}

bool WLDCan::addRemoteElement(WLRemElement remElement)
{
if(remElement.typeE==typeEEmpty) return false;

remEList+=remElement;

QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comDCan_addRemElement<<(quint8)getIndex()
	  <<(quint8)remElement.typeE
	  <<(quint8)remElement.indexLocal
	  <<(quint8)remElement.indexRemote
	  <<(quint8)remElement.master;

emit sendCommand(data);
return true;
}

bool WLDCan::clearAllRemoteElement()
{
remEList.clear();

QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comDCan_clearAllRemElement<<(quint8)getIndex();

emit sendCommand(data);
return true;
}

bool WLDCan::setEnable(bool enable)
{
remEList.clear();

QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comDCan_setEnable<<(quint8)getIndex()<<(quint8)enable;

emit sendCommand(data);
return true;
}

void WLDCan::writeXMLData(QXmlStreamWriter &stream)
{
stream.writeAttribute("adrCan", QString::number(getAdrCan(),16).toUpper());

stream.writeStartElement("remoteElements");

for(int i=0;i<remEList.size();i++)
  	 remEList[i].writeXMLData(stream);

 stream.writeEndElement();

}

void WLDCan::readXMLData(QXmlStreamReader &stream)
{
bool ok;
if(!stream.attributes().value("adrCan").isEmpty())	setAdrCan(stream.attributes().value("adrCan").toString().toInt(&ok,16));

setEnable(getAdrCan()!=0);

clearAllRemoteElement();

while(!stream.atEnd())
{
qDebug()<<stream.name();
stream.readNextStartElement();
    qDebug()<<stream.name();
if(stream.name()=="DCan") break;
if(stream.tokenType()!=QXmlStreamReader::StartElement) continue;

if(stream.name()=="remoteElements")
   {
   while(!stream.atEnd())
   {
    qDebug()<<stream.name();
    stream.readNextStartElement();
    qDebug()<<stream.name();
    if(stream.name()=="remoteElements") break;
    if(stream.tokenType()!=QXmlStreamReader::StartElement) continue;

	WLRemElement remElement;
	remElement.readXMLData(stream);	   

	addRemoteElement(remElement);
   }
   }
}
}

