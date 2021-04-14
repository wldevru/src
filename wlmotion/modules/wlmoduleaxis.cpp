#include "wlmoduleaxis.h"

WLModuleAxis::WLModuleAxis(WLModuleIOPut *_ModuleIOPut,QObject *parent)
	:WLModule(parent)
{
setType(typeMAxis);
ModuleIOPut=_ModuleIOPut;

Fmax=0;

inEMGStop=&WLIOPut::In0;
inSDStop=&WLIOPut::In0;
inProbe=&WLIOPut::In0;

updateTimer= new QTimer;
connect(updateTimer,SIGNAL(timeout()),SLOT(callPosAxis()));
updateTimer->start(100);

Init(1);
}

WLModuleAxis::~WLModuleAxis()
{
while(Axis.isEmpty())
    delete Axis.takeLast();
}



bool WLModuleAxis::Init(int sizeAxis)
{
if(sizeAxis<1
 ||Axis.size()== sizeAxis
 ||isReady()) return false;

WLAxis *axis;
long l=0;

if(sizeAxis>Axis.size())
 for(int i=Axis.size();i<sizeAxis;i++ )
  { 
  axis = new WLAxis;
  axis->init(ModuleIOPut,i);
  axis->setParent(this);

  connect(axis,SIGNAL(sendCommand(QByteArray)),SLOT(setCommand(QByteArray)));
  Axis+=axis;

  posLatchProbe2+=l;
  posLatchProbe3+=l;
  }
else
 while(sizeAxis!=Axis.size())
  {
  axis=Axis.takeLast();
  disconnect(axis,SIGNAL(sendCommand(QByteArray)),this,SLOT(setCommand(QByteArray)));
  delete axis;

  posLatchProbe2.takeLast();
  posLatchProbe3.takeLast();
  }
update();
return true;
}

WLAxis *WLModuleAxis::getAxis(int index)
{
Q_ASSERT(index<getSizeAxis());

return index<getSizeAxis() ? Axis[index]:nullptr;
}

void WLModuleAxis::setLatchProbe2(qint32 *Pos,quint8 n)
{
    qDebug()<<"setLatchProbe2";
    for(int i=0;i<n&&i<getSizeAxis();i++)
    {
	posLatchProbe2[i]=Pos[i];
	qDebug()<<Pos[i];
    }

Flags.set(MAF_latchProbe2);
}

void WLModuleAxis::setLatchProbe3(qint32 *Pos,quint8 n)
{
qDebug()<<"setLatchProbe3";
for(int i=0;i<n&&i<getSizeAxis();i++)
    {
	posLatchProbe3[i]=Pos[i];
	qDebug()<<Pos[i];
    }

Flags.set(MAF_latchProbe3);
}

void WLModuleAxis::callDataAxis()
{
for(int i=0;i<getSizeAxis();i++) Axis[i]->sendGetDataAxis();
}

void WLModuleAxis::callPosAxis()
{
for(int i=0;i<getSizeAxis();i++)
  {
  Axis[i]->getData(typeDataAxis::dataAxis_pos);
  Axis[i]->getData(typeDataAxis::dataAxis_F);
  }

}

void WLModuleAxis::update()
{
foreach(WLAxis *axis,Axis)
    axis->update();
}

void WLModuleAxis::backup()
{
foreach(WLAxis *axis,Axis)
     axis->backup();

setInProbe(getInput(MAXIS_inProbe)->getIndex());
setInSDStop(getInput(MAXIS_inSDStop)->getIndex());
setInEMGStop(getInput(MAXIS_inEMGStop)->getIndex());
}

void WLModuleAxis::readCommand(QByteArray Data)
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
 case comAxis_setData:  Stream>>index;//index8

                       if(index<getSizeAxis()) Axis[index]->setData(Stream);
                       break;

 case sendAxis_data:   Stream>>index;//index8
 	                   Stream>>ui1;  //Status4|Mode4
 				       Stream>>ui2;  //Flag8
 			           Stream>>l1;   //Pos32
 				       Stream>>f1;   //Freq32
                        
					   if(index<getSizeAxis())
					    { 				   		
                        Axis[index]->setDataAxis(ui1,ui2,l1,qAbs(f1));
					    }
					    else
                       qDebug()<<"Error indexAxis";
 			           break;

 case sendAxis_rInProbe: posProbe=new qint32 [(size-1)/4];
                       for(ui1=0;ui1<(size-1)/4;ui1++)
						Stream>>posProbe[ui1];
					   qDebug()<<"sendRProbeAXIS";

					   setLatchProbe2(posProbe,(size-2)/4);

					   delete posProbe;
					   break;

case sendAxis_fInProbe: posProbe=new qint32 [(size-1)/4];
					  for(ui1=0;ui1<(size-1)/4;ui1++)
						 Stream>>posProbe[ui1];
					  qDebug()<<"sendFProbeAXIS";

					  setLatchProbe3(posProbe,(size-2)/4);

					  delete posProbe;
					  break;

case  sendModule_prop: Stream>>ui1;
					   Stream>>l1;

                       Fmax=l1;			

					   Init(ui1);

                       setReady(true);
                       break;

 case sendModule_error:
	                Stream>>ui1; 
                    Stream>>index; 
                    
					
					if(ui1>200)
					{                    
					emit sendMessage("ModuleAxis "+getErrorStr(errorModule,ui1),QString::number(index),(int)(-ui1));	
					}
					else
				    if(index<getSizeAxis())
					    {
						emit sendMessage("Axis "+getErrorStr(errorAxis,ui1),QString::number(index),(int)(-ui1));	

                   	    Axis[index]->setError(ui1);       									  
					    }
                    break;
}			
}
bool WLModuleAxis::setInputMAxis(typeIOPutAXIS type,quint8 num)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMAxis<<(quint8)comAxis_setInputM<<(quint8)type<<num;

emit sendCommand(data);
return true;
}

bool WLModuleAxis::setActInProbe(typeActIOPutAxis typeAct)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

qDebug()<<"setActInProbeAxis"<<typeAct;

Stream<<(quint8)typeMAxis<<(quint8)comAxis_setActInProbe<<(quint8)typeAct;

emit sendCommand(data);
return true;
}

void  WLModuleAxis::setInEMGStop(int index)
{
disconnect(inEMGStop,SIGNAL(changed(int)),this,SIGNAL(changedInEMGStop()));

inEMGStop->removeComment("inEMGStop");

if(index>=ModuleIOPut->getSizeInputs()) index=0;

inEMGStop=ModuleIOPut->getInput(index);;
inEMGStop->addComment("inEMGStop");

connect(inEMGStop,SIGNAL(changed(int)),this,SIGNAL(changedInEMGStop()));

setInputMAxis(IO_inEMGStop,index);
}

void  WLModuleAxis::setInSDStop(int index)
{
disconnect(inSDStop,SIGNAL(changed(int)),this,SIGNAL(changedInSDStop()));

inSDStop->removeComment("inSDStop");

if(index>=ModuleIOPut->getSizeInputs()) index=0;

inSDStop=ModuleIOPut->getInput(index);;
inSDStop->addComment("inSDStop");


connect(inSDStop,SIGNAL(changed(int)),this,SIGNAL(changedInSDStop()));

setInputMAxis(IO_inSDStop,index);
}

void  WLModuleAxis::setInProbe(int index)
{
inProbe->removeComment("inProbe");

if(index>=ModuleIOPut->getSizeInputs()) index=0;

inProbe=ModuleIOPut->getInput(index);;
inProbe->addComment("inProbe");

setInputMAxis(IO_inProbe,index);
}

WLIOPut *WLModuleAxis::getInput(typeInputMAXIS type)
{
WLIOPut *ret=NULL;
switch(type)
{
case MAXIS_inEMGStop: ret=inEMGStop; break;
case MAXIS_inSDStop:  ret=inSDStop;  break;
case MAXIS_inProbe:   ret=inProbe;   break;
}
return ret;
}

void WLModuleAxis::readXMLData(QXmlStreamReader &stream)
{
quint8 index;
int size=4;

if(!stream.attributes().value("size").isEmpty()) size=stream.attributes().value("size").toString().toInt();    

Init(size);

if(!stream.attributes().value("inEMGStop").isEmpty()) setInEMGStop(stream.attributes().value("inEMGStop").toString().toInt());    
if(!stream.attributes().value("inSDStop").isEmpty())  setInSDStop(stream.attributes().value("inSDStop").toString().toInt());
if(!stream.attributes().value("inProbe").isEmpty())   setInProbe( stream.attributes().value("inProbe").toString().toInt());	

while(!stream.atEnd())
{
stream.readNextStartElement();

if(stream.name()==metaObject()->className()) break;
if(stream.tokenType()!=QXmlStreamReader::StartElement) continue;

if(stream.name()=="Axis")
	   {
	   index=stream.attributes().value("index").toString().toInt();
	   if(index<getSizeAxis())	
		   Axis[index]->readXMLData(stream);		    	    	   
      }
}
//if(!stream.attributes().value("invLocalInput").isEmpty())  setInputInvStr(stream.attributes().value("invLocalInput").toString());
//if(!stream.attributes().value("invLocalOutput").isEmpty()) setOutputInvStr(stream.attributes().value("invLocalOutput").toString());
}

void WLModuleAxis::writeXMLData(QXmlStreamWriter &stream)
{
stream.writeAttribute("size",QString::number(getSizeAxis()));

stream.writeAttribute("inEMGStop",QString::number(inEMGStop->getIndex()));
stream.writeAttribute("inSDStop",QString::number(inSDStop->getIndex()));
stream.writeAttribute("inProbe",QString::number(inProbe->getIndex()));
stream.writeAttribute("Fmax",QString::number(Fmax));

for(int i=0;i<getSizeAxis();i++)
 {
 stream.writeStartElement("Axis");
 stream.writeAttribute("index",QString::number(i));
   Axis[i]->writeXMLData(stream);
 stream.writeEndElement();
 }

}
