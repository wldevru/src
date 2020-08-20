#include "wlmoduleaioput.h"

WLModuleAIOPut::WLModuleAIOPut(QObject *parent)
	: WLModule(parent)
{
setType(typeMAIOPut);
Init(1);
}

WLModuleAIOPut::~WLModuleAIOPut()
{
while(Inputs.isEmpty())
       delete Inputs.takeLast();
}

bool WLModuleAIOPut::Init(int sizeInputs)
{
if((sizeInputs<1)||(Inputs.size()== sizeInputs)) return false;

WLAIOPut *ainput;

if(sizeInputs>Inputs.size())
 for(int i=Inputs.size();i<sizeInputs;i++ )
  {
  ainput = new WLAIOPut;
  ainput->setIndex(i);
  ainput->setParent(this);
  connect(ainput,SIGNAL(sendCommand(QByteArray)),SLOT(setCommand(QByteArray)));
  Inputs+=ainput;
  }
else
    while(Inputs.size()!= sizeInputs)
	  {	  
      ainput=Inputs.takeLast();
      disconnect(ainput,SIGNAL(sendCommand(QByteArray)),this,SLOT(setCommand(QByteArray)));
      delete ainput;
      }

return true;
}

WLAIOPut *WLModuleAIOPut::getInput(int index)
{
Q_ASSERT((index<getSizeInputs())&&(index<255));

return index<getSizeInputs() ? Inputs[index]:nullptr;
}

void WLModuleAIOPut::update()
{
foreach(WLAIOPut *aioput,Inputs)
       {
       // aioput->sendGetData();
       }
}

void  WLModuleAIOPut::readCommand(QByteArray Data)
{
quint8 index,ui1;
qint32 i32;

QDataStream Stream(&Data,QIODevice::ReadOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream>>ui1;

switch(ui1)
{
case   comAIOPut_setValue:   Stream>>index;//index8
                              if(index<getSizeInputs())
                                  Inputs[index]->setData(Stream);
                               break;

case  sendModule_prop: Stream>>ui1;					                      
					   Init(ui1);
                       break;

case  sendModule_error:Stream>>ui1;  //Error
					   Stream>>index;  //Error
                    			
					   if(ui1>200)
                        emit sendMessage("WLModuleAIOPut "+getErrorStr(errorModule,ui1),QString::number(index),(int)(ui1));
					   else
                         if(index<getSizeInputs())
						     {
                             //Inputs[index]->setError(ui1);
                             emit sendMessage("WLEncoder "+getErrorStr(errorAIOPut,ui1),QString::number(index),(int)(ui1));
            			     }
                       break;
}

}

void WLModuleAIOPut::writeXMLData(QXmlStreamWriter &stream)
{
stream.writeAttribute("size",QString::number(getSizeInputs()));

for(int i=0;i<getSizeInputs();i++)
 {
 stream.writeStartElement("Inputs");
 stream.writeAttribute("index",QString::number(i));
   Inputs[i]->writeXMLData(stream);
 stream.writeEndElement();
 }
}


void WLModuleAIOPut::readXMLData(QXmlStreamReader &stream)
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

if(stream.name()=="Encoder")
	   {
	   index=stream.attributes().value("index").toString().toInt();
       if(index<getSizeInputs())
           Inputs[index]->readXMLData(stream);
      }
}
}
