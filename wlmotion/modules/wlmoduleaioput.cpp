#include "wlmoduleaioput.h"

WLModuleAIOPut::WLModuleAIOPut(QObject *parent)
	: WLModule(parent)
{
setType(typeMAIOPut);
Init(1,1);
}

WLModuleAIOPut::~WLModuleAIOPut()
{
while(Inputs.isEmpty())
    delete Inputs.takeLast();
}

bool WLModuleAIOPut::Init(int _sizeInputs, int _sizeOutputs)
{
return InitInputs(_sizeInputs)&&InitOutputs(_sizeOutputs);
}

bool WLModuleAIOPut::InitInputs(int sizeInputs)
{
if(sizeInputs<2) sizeInputs=2;

if((Inputs.size()== sizeInputs)) return false;

WLAIOPut *ainput;

if(sizeInputs>Inputs.size())
 for(int i=Inputs.size();i<sizeInputs;i++ )
  {
  ainput = new WLAIOPut("",true);
  ainput->setIndex(i);
  ainput->setParent(this);
  connect(ainput,SIGNAL(sendCommand(QByteArray)),SLOT(setCommand(QByteArray)));
  connect(ainput,SIGNAL(changed(int)),SIGNAL(changedInput(int)));
  Inputs+=ainput;
  }
else
    while(Inputs.size()!= sizeInputs)
	  {	  
      ainput=Inputs.takeLast();
      disconnect(ainput,SIGNAL(sendCommand(QByteArray)),this,SLOT(setCommand(QByteArray)));
      disconnect(ainput,SIGNAL(changed()),this,SIGNAL(changedInput(int)));
      delete ainput;
      }

return true;
}

bool WLModuleAIOPut::InitOutputs(int sizeOutputs)
{
if(sizeOutputs<1) sizeOutputs=1;

if(Outputs.size()== sizeOutputs
 ||isReady()) return false;

WLAIOPut *aoutput;

if(sizeOutputs>Outputs.size())
 for(int i=Outputs.size();i<sizeOutputs;i++ )
  {
  aoutput = new WLAIOPut;
  aoutput->setIndex(i);
  aoutput->setParent(this);
  connect(aoutput,SIGNAL(sendCommand(QByteArray)),SLOT(setCommand(QByteArray)));
  connect(aoutput,SIGNAL(changed(int)),this,SIGNAL(changedOutput(int)));
  Outputs+=aoutput;
  }
else
    while(Outputs.size()!= sizeOutputs)
      {
      aoutput=Outputs.takeLast();
      disconnect(aoutput,SIGNAL(sendCommand(QByteArray)),this,SLOT(setCommand(QByteArray)));
      disconnect(aoutput,SIGNAL(changed(int)),this,SIGNAL(changedOutput(int)));
      delete aoutput;
      }

return true;
}

WLAIOPut *WLModuleAIOPut::getInput(int index)
{
Q_ASSERT((index<getSizeInputs())&&(index<255));

return index<getSizeInputs() ? Inputs[index]:nullptr;
}

WLAIOPut *WLModuleAIOPut::getOutput(int index)
{
Q_ASSERT((index<getSizeOutputs())&&(index<255));

return index<getSizeOutputs() ? Outputs[index]:nullptr;
}

void WLModuleAIOPut::update()
{
foreach(WLAIOPut *aioput,Inputs)
       {
       aioput->sendGetData();
       }

foreach(WLAIOPut *aioput,Outputs)
       {
       aioput->sendGetData();
       }
}

void WLModuleAIOPut::backup()
{

}

void  WLModuleAIOPut::readCommand(QByteArray Data)
{
quint8 index,ui1,ui2;
qint32 i32;

QDataStream Stream(&Data,QIODevice::ReadOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream>>ui1;

switch(ui1)
{
case  comAIOPut_setDataInput:  Stream>>index;//index8
                               if(index<getSizeInputs())
                                  Inputs[index]->setData(Stream);
                               break;

case  comAIOPut_setDataOutput: Stream>>index;//index8
                               if(index<getSizeOutputs())
                                  Outputs[index]->setData(Stream);
                               break;

case  sendModule_prop: Stream>>ui1>>ui2;
                       Init(ui1,ui2);
                       setReady(true);

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
stream.writeStartElement("inputs");
 stream.writeAttribute("size", QString::number(getSizeInputs()));
stream.writeEndElement();

stream.writeStartElement("outputs");
 stream.writeAttribute("size", QString::number(getSizeOutputs()));
stream.writeEndElement();
}


void WLModuleAIOPut::readXMLData(QXmlStreamReader &stream)
{
int size;

while(!stream.atEnd())
{
stream.readNextStartElement();

if(stream.name()==metaObject()->className()) break;
if(stream.tokenType()!=QXmlStreamReader::StartElement) continue;

if(stream.name()=="inputs")
 {
 size=2;

 if(!stream.attributes().value("size").isEmpty()) size=stream.attributes().value("size").toString().toInt();

 InitInputs(size);

 while(!stream.atEnd())
  {
  stream.readNextStartElement();
  if(stream.name()=="inputs") break;
  if(stream.tokenType()!=QXmlStreamReader::StartElement) continue;
  }
 }

if(stream.name()=="outputs")
   {
   size=2;

   if(!stream.attributes().value("size").isEmpty())    size=stream.attributes().value("size").toString().toInt();

   InitOutputs(size);

   while(!stream.atEnd())
    {
    stream.readNextStartElement();

    if(stream.name()=="outputs") break;
    if(stream.tokenType()!=QXmlStreamReader::StartElement) continue;

    }
   }
}
update();
}
