#include "WLElement.h"

WLElement::WLElement(QObject *parent)
	:QObject(parent)
{
typeE=typeEEmpty;
index=0;
}


WLElement::~WLElement()
{

}
/*
void WLElement::callStatus()
{
if(typeE!=0)
 {
 QByteArray data;
 QDataStream Stream(&data,QIODevice::WriteOnly);
 
 Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
 Stream.setByteOrder(QDataStream::LittleEndian);
 
 emit sendCommand(data); 
 }
}
*/

