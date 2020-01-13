#include "WLModuleIOPut.h"

WLModuleIOPut::WLModuleIOPut(QObject *parent)
	:WLModule(parent)
{ 
setTypeModule(typeMIOPut);

Init(2,1);
}

WLModuleIOPut::~WLModuleIOPut()
{
//if(inputs!=NULL)  delete []inputs;
    //if(outputs!=NULL) delete []outputs;
}

bool WLModuleIOPut::Init(int _sizeInputs, int _sizeOutputs)
{
if(InitInputs(_sizeInputs)&&InitOutputs(_sizeOutputs))
{
update();
return true;
}
return false;
}

bool WLModuleIOPut::InitInputs(int sizeInputs)
{
if(sizeInputs<2||Inputs.size()==sizeInputs) return false;

WLIOPut *input;

if(Inputs.size()<sizeInputs)
 for(int i=Inputs.size();i<sizeInputs;i++) 
	  {
	  input = new WLIOPut("",true);
	  input->setIndex(i);	  
	  connect(input,SIGNAL(sendCommand(QByteArray)),SLOT(setCommand(QByteArray)));
	  Inputs+=input;  
      }
else
	while(Inputs.size()!=sizeInputs) 
	  {	
	  input = Inputs.takeLast();
	  disconnect(input,SIGNAL(sendCommand(QByteArray)),this,SLOT(setCommand(QByteArray)));
	  delete Inputs.takeLast();  
      }

Inputs[0]->setNow(0);
Inputs[0]->setNow(0);

Inputs[1]->setNow(1);
Inputs[1]->setNow(1);

Inputs[0]->setComment("inLock0");
Inputs[1]->setComment("inLock1");

return true;
}

bool WLModuleIOPut::InitOutputs(int sizeOutputs)
{
if(sizeOutputs<1||Outputs.size()==sizeOutputs) return false;

WLIOPut *output;

if(Outputs.size()<sizeOutputs)
 for(int i=Outputs.size();i<sizeOutputs;i++)  
  {
  output = new WLIOPut;
  output->setIndex(i);  
  Outputs+=output;
  connect(output,SIGNAL(sendCommand(QByteArray)),this,SLOT(setCommand(QByteArray)));
  }
else
  while(Outputs.size()!=sizeOutputs) 
	 {	  	 
     output = Outputs.takeLast();
	 disconnect(output,SIGNAL(sendCommand(QByteArray)),this,SLOT(setCommand(QByteArray)));
	 delete output;
     }

//QTimer *timer=new QTimer;
//connect(timer,SIGNAL(timeout()),SLOT(sendDataOutput()));
//timer->start(3);

return true;
}

void WLModuleIOPut::readCommand(QByteArray Data)
{
quint8 index,ui1,ui2;
quint16 ui16;
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
 case sendIOPut_inputBData:
                       Stream>>ui1;		
					   while(!Stream.atEnd())
					   {
                       Stream>>ui2;					   
                        for(int i=0;i<8;i++)
                          getInputV(i+(ui1)*8)->setNow((ui2>>i)&0x1);   

					   ui1++;
					   }
                       break;

case sendIOPut_ioputData: 
	                  //qDebug()<<"start sendIData";                  
                       Stream>>index;		
					   Stream>>ui1;

					   if(ui1&IOPF_input)
					     {
					     getInputV(index)->setData(ui1);
					     }
					   else
						 {
					     getOutputV(index)->setData(ui1);
					     }
                       break;

case  sendModule_prop: Stream>>ui1;
					   Stream>>ui2;       

					   Init(ui1,ui2);
                       break;

case sendModule_error: Stream>>ui1;  //Error                				                  				 
	                   Stream>>index;
                	  
                       emit sendMessage(metaObject()->className()+getErrorStr(errorIOPut,ui1),QString::number(index),-(int)(ui1));
					   break;
 }


}



void WLModuleIOPut::setInputInvStr(QString data)
{
QStringList List=data.split(",");

for(int i=0;i<List.size();i++)
  if(List[i].toInt()<Inputs.size()&&List[i].toInt()>1) getInputV(List[i].toInt())->setInv();
}

QString WLModuleIOPut::getInputInvStr()
{
QString ret;

for(int i=2;i<Inputs.size();i++)
  {
  if(Inputs[i]->isInv())
    {
	if(!ret.isEmpty())  ret+=",";
	ret+=QString::number(i);
    }
  }

return  ret;
}

void WLModuleIOPut::setOutputInvStr(QString data)
{
QStringList List=data.split(",");

for(int i=0;i<List.size();i++)
  if(List[i].toInt()<Outputs.size()&&List[i].toInt()>0) getOutputV(List[i].toInt())->setInv();
}

QString WLModuleIOPut::getOutputInvStr()
{
QString ret;

for(int i=2;i<Outputs.size();i++)
  {
  if(Outputs[i]->isInv())
    {
	if(!ret.isEmpty())  ret+=",";
	ret+=QString::number(i);
    }
  }

return  ret;
}


void WLModuleIOPut::sendGetAllInputData()
{
for(int i=2;i<getSizeInputs();i++)
 {
 Inputs[i]->setInv(Inputs[i]->isInv());
 callInputData(i);
 }

}

void WLModuleIOPut::sendGetAllOutputData()
{
for(int i=1;i<getSizeOutputs();i++)
 {
 Outputs[i]->setInv(Outputs[i]->isInv());
 callOutputData(i);
 }
}

void WLModuleIOPut::callInputData(int index)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMIOPut<<(quint8)comIOPut_getInputData<<(quint8)index;

//qDebug()<<"Call getIData";

emit sendCommand(data);
}

void WLModuleIOPut::callOutputData(int index)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMIOPut<<(quint8)comIOPut_getOutputData<<(quint8)index;

emit sendCommand(data);
}

void WLModuleIOPut::sendSetOData(bool all)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

quint8 b;
quint8 out,mask;
int index;

for(int i=0;i<Outputs.size();i++)
  {
  if(Outputs[i]->getOld()!=Outputs[i]->getNow()||all)
    {  
    i/=8;
	out=0;
	mask=0;
    
    for(quint8 j=0,b=1;j<8;j++,b<<=1)
	     {
	     index=i*8+j;
		// qDebug()<<index<<output[index];
		 mask |= (Outputs[index]->getOld()!=Outputs[index]->getNow()||all )? b:0;
	     out  |= (Outputs[index]->getNow()!=0)? b:0;

		 //outputLast[index]=outputNow[index];
	     }
	//qDebug()<<"setOutput"<<i<<out<<mask<<"BA";
	Stream<<(quint8)typeMIOPut<<(quint8)comIOPut_setOutputByte<<(quint8)i<<out<<mask;
	emit sendCommand(data);

	Stream.device()->reset();
	data.clear();

	i=(i+1)*8; 
    }
}
}

void WLModuleIOPut::update()
{
sendGetAllInputData();
sendGetAllOutputData();
}

void WLModuleIOPut::readXMLData(QXmlStreamReader &stream)
{
int  size=16;
//if(!stream.attributes().value("invOutput").isEmpty()) setOutputInvStr(stream.attributes().value("invOutput").toString());

while(!stream.atEnd())
{
stream.readNextStartElement();

if(stream.name()==metaObject()->className()) break;
if(stream.tokenType()!=QXmlStreamReader::StartElement) continue;

if(stream.name()=="inputs")
   {
   size=16;

   if(!stream.attributes().value("size").isEmpty())    size=stream.attributes().value("size").toString().toInt();

   InitInputs(size);

   if(!stream.attributes().value("inv").isEmpty())   setInputInvStr(stream.attributes().value("inv").toString());

   while(!stream.atEnd())
    {
    stream.readNextStartElement();
    
    if(stream.name()=="inputs") break;
    if(stream.tokenType()!=QXmlStreamReader::StartElement) continue;

    }

   }

if(stream.name()=="outputs")
   {
   size=16;

   if(!stream.attributes().value("size").isEmpty())    size=stream.attributes().value("size").toString().toInt();

   InitOutputs(size);

   if(!stream.attributes().value("inv").isEmpty())   setOutputInvStr(stream.attributes().value("inv").toString());

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

void WLModuleIOPut::writeXMLData(QXmlStreamWriter &stream)
{
stream.writeStartElement("inputs");
 stream.writeAttribute("size", QString::number(getSizeInputs()));	
 stream.writeAttribute("inv",getInputInvStr());

stream.writeEndElement();

stream.writeStartElement("outputs");
 stream.writeAttribute("size", QString::number(getSizeOutputs()));	
 stream.writeAttribute("inv",getOutputInvStr());

stream.writeEndElement();
}
