#include "wlmodulempg.h"

WLModuleMPG::WLModuleMPG(QObject *parent)
    : WLModule(parent)
{
setType(typeMMPG);
Init(1);
}

WLModuleMPG::~WLModuleMPG()
{
    while(MPG.isEmpty())
        delete MPG.takeLast();
}

bool WLModuleMPG::Init(int sizeWhell)
{
if(sizeWhell<1||MPG.size()== sizeWhell) return false;

WLMPG *whell;

if(sizeWhell>MPG.size())
 for(int i=MPG.size();i<sizeWhell;i++ )
  {
  whell = new WLMPG;
  whell->setIndex(i);
  whell->setParent(this);
  connect(whell,SIGNAL(sendCommand(QByteArray)),SLOT(setCommand(QByteArray)));
  MPG+=whell;
  }
else
    while(MPG.size()!= sizeWhell)
	  {	  
      whell=MPG.takeLast();
	  disconnect(whell,SIGNAL(sendCommand(QByteArray)),this,SLOT(setCommand(QByteArray)));
	  delete whell;  
      }


return true;
}

WLMPG *WLModuleMPG::getMPG(int index)
{
Q_ASSERT((index<getSize())&&(index<255));

return index<getSize() ? MPG[index] : nullptr;
}

void WLModuleMPG::update()
{
    foreach(WLMPG *whell,MPG)
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
void WLModuleMPG::readCommand(QByteArray Data)
{
quint8 index,ui1,ui2,ui3;

QDataStream Stream(&Data,QIODevice::ReadOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream>>ui1;

switch(ui1)
{
case sendMPG_data:    Stream>>index;//index8
                      Stream>>ui1;  //Flag8
                      Stream>>ui2;  //indexA
                      Stream>>ui3;  //Vmode(0x80) indexX(0x7F)

                      MPG.at(index)->setData(ui1,ui2,ui3&0x7F,ui3&0x80);
                      break;

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
                            if(index<getSize())
								{
                                MPG[index]->setError(ui1);
                                emit sendMessage("WLWhell "+getErrorStr(errorMPG,ui1),QString::number(index),(int)(ui1));
							    }
                       break;
}

}


void WLModuleMPG::writeXMLData(QXmlStreamWriter &stream)
{

stream.writeAttribute("size",QString::number(getSize()));

for(int i=0;i<getSize();i++)
 {
 stream.writeStartElement("MPG");
 stream.writeAttribute("index",QString::number(i));
   MPG[i]->writeXMLData(stream);
 stream.writeEndElement();
 }
}


void WLModuleMPG::readXMLData(QXmlStreamReader &stream)
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

if(stream.name()=="Whell" //old style
 ||stream.name()=="MPG")
	   {
	   index=stream.attributes().value("index").toString().toInt();
       if(index<getSize())
           MPG[index]->readXMLData(stream);
      }
}
}
