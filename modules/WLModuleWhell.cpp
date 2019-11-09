#include "WLModuleWhell.h"

WLModuleWhell::WLModuleWhell(QObject *parent)
	: WLModule(parent)
{
setTypeModule(typeMWhell);
Init(1);
}

WLModuleWhell::~WLModuleWhell()
{
//if(Whell!=NULL) delete []Whell;
}

bool WLModuleWhell::Init(int sizeWhell)
{
if(sizeWhell<1||Whell.size()== sizeWhell) return false;

WLWhell *whell;

if(sizeWhell>Whell.size())
 for(int i=Whell.size();i<sizeWhell;i++ )
  {
  whell = new WLWhell;
  whell->setIndex(i);
  connect(whell,SIGNAL(sendCommand(QByteArray)),SLOT(setCommand(QByteArray)));
  Whell+=whell;
  }
else
	while(Whell.size()!= sizeWhell) 
	  {	  
	  whell=Whell.takeLast();
	  disconnect(whell,SIGNAL(sendCommand(QByteArray)),this,SLOT(setCommand(QByteArray)));
	  delete whell;  
      }


return true;
}

void WLModuleWhell::update()
{
foreach(WLWhell *whell,Whell)
        whell->sendGetData();
}

/*
bool WLModuleWhell::setAxisTrackWhell(int iWhell,int iAxis)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMWhell<<(quint8)comWhell_setAxis<<(quint8)iWhell<<(quint8)iAxis;

qDebug()<<"_setAxisWHL"<<iWhell<<iAxis;

emit sendCommand(data);

return true;
}

bool WLModuleWhell::setKTrackWhell(int iWhell,float k)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMWhell<<(quint8)comWhell_setKTrack<<(quint8)iWhell<<k;

qDebug()<<"_setKTrackWHL"<<iWhell<<k;

emit sendCommand(data);

return true;
}

bool WLModuleWhell::setEnableTrackWhell(int iWhell,quint8 enable)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMWhell<<(quint8)comWhell_setEnable<<(quint8)iWhell<<enable;

qDebug()<<"_setEnableWHL"<<(quint8)iWhell<<enable;

emit sendCommand(data);

return true;
}

bool WLModuleWhell::setTypeTrackWhell(int iWhell,quint8 type)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMWhell<<(quint8)comWhell_setTypeTrack<<(quint8)iWhell<<(quint8)type;

qDebug()<<"setTypeTrackWHL";

emit sendCommand(data);

return true;
}

bool WLModuleWhell::setIInAxisTrackWHL(int iWhell,int index8[])
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMWhell<<(quint8)comWhell_setIInAxisTrack<<(quint8)iWhell;

for(int i=0;i<8;i++)
	Stream<<(quint8)index8[i];

qDebug()<<"setIInAxisTrackWHL";

emit sendCommand(data);

return true;
}
    
bool WLModuleWhell::setIInKTrackWHL(int iWhell,int index8[])
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMWhell<<(quint8)comWhell_setIInKTrack<<(quint8)iWhell;

for(int i=0;i<8;i++)
	Stream<<(quint8)index8[i];

qDebug()<<"setIInKTrackWHL";

emit sendCommand(data);

return true;
}

bool WLModuleWhell::setIInTypeTrackWHL(int iWhell,int index)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMWhell<<(quint8)comWhell_setIInTypeTrack<<(quint8)iWhell<<(quint8)index;
qDebug()<<"setIInTypeTrackWHL";

emit sendCommand(data);

return true;
}

bool WLModuleWhell::setUseInputWHL(int iWhell,bool enable)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMWhell<<(quint8)comWhell_setKTrackData<<(quint8)iWhell<<(quint8)enable;
qDebug()<<"setKTrackDataWHL";

emit sendCommand(data);

return true;
}

bool WLModuleWhell::setKTrackDataWHL(int iWhell,float K8[],double mainDim)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMWhell<<(quint8)comWhell_setKTrackData<<(quint8)iWhell;

for(int i=0;i<8;i++)
	Stream<<K8[i];

qDebug()<<"setKTrackDataWHL";

emit sendCommand(data);

return true;
}
*/
void WLModuleWhell::readCommand(QByteArray Data)
{
quint8 index,ui1,ui2;
qint32 l1;
qint32 *posProbe;
int size=Data.size();
float f1;

QDataStream Stream(&Data,QIODevice::ReadOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream>>ui1;

switch(ui1)
{
case  sendModule_prop: Stream>>ui1;
					                      
					   Init(ui1);
                       break;

case  sendModule_error:Stream>>ui1;
                       Stream>>index;  

                       if(ui1>startIndexErrorModule)
					    {
						emit sendMessage("WLModuleWhell "+getErrorStr(errorModule,ui1),QString::number(index),(int)(ui1));	
					    }
					    else
							if(index<getSizeWhell())   
								{
								Whell[index]->setError(ui1);       									  
								emit sendMessage("WLWhell "+getErrorStr(errorWhell,ui1),QString::number(index),(int)(ui1));	
							    }
                       break;
}

}


void WLModuleWhell::writeXMLData(QXmlStreamWriter &stream)
{

stream.writeAttribute("size",QString::number(getSizeWhell()));

for(int i=0;i<getSizeWhell();i++)
 {
 stream.writeStartElement("Whell");
 stream.writeAttribute("index",QString::number(i));
   Whell[i]->writeXMLData(stream);
 stream.writeEndElement();
 }
}


void WLModuleWhell::readXMLData(QXmlStreamReader &stream)
{
quint8 index;
int size=4;

if(!stream.attributes().value("size").isEmpty()) size=stream.attributes().value("size").toString().toInt();    

Init(size);
/*
if(!stream.attributes().value("inEMGStop").isEmpty()) setInEMGStop(stream.attributes().value("inEMGStop").toString().toInt());    
if(!stream.attributes().value("inSDStop").isEmpty())  setInSDStop(stream.attributes().value("inSDStop").toString().toInt());
if(!stream.attributes().value("inProbe").isEmpty())   setInProbe( stream.attributes().value("inProbe").toString().toInt());	
*/
while(!stream.atEnd())
{
stream.readNextStartElement();

if(stream.name()==metaObject()->className()) break;
if(stream.tokenType()!=QXmlStreamReader::StartElement) continue;

if(stream.name()=="Whell")
	   {
	   index=stream.attributes().value("index").toString().toInt();
	   if(index<getSizeWhell())	
		   Whell[index]->readXMLData(stream);		    	    	   
      }
}
}
