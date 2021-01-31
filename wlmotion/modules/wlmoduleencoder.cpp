#include "wlmoduleencoder.h"

WLModuleEncoder::WLModuleEncoder(QObject *parent)
	: WLModule(parent)
{
setType(typeMEncoder);
Init(1);

//QTimer *updateTimer = new QTimer;
//connect(updateTimer,SIGNAL(timeout()),SLOT(update()));
//updateTimer->start(200);
}

WLModuleEncoder::~WLModuleEncoder()
{
while(Encoder.isEmpty())
       delete Encoder.takeLast();
}

bool WLModuleEncoder::Init(int sizeEncoder)
{
if((sizeEncoder<1)||(Encoder.size()== sizeEncoder)) return false;

WLEncoder *enc;

if(sizeEncoder>Encoder.size())
 for(int i=Encoder.size();i<sizeEncoder;i++ )
  {
  enc = new WLEncoder;
  enc->setIndex(i);
  enc->setParent(this);
  connect(enc,SIGNAL(sendCommand(QByteArray)),SLOT(setCommand(QByteArray)));
  connect(enc,SIGNAL(changed(int)),this,SIGNAL(changedEncoder(int)));
  Encoder+=enc;
  }
else
	while(Encoder.size()!= sizeEncoder) 
	  {	  
	  enc=Encoder.takeLast();
	  disconnect( enc,SIGNAL(sendCommand(QByteArray)),this,SLOT(setCommand(QByteArray)));
      connect(enc,SIGNAL(changed(int)),this,SIGNAL(changedEncoder(int)));
	  delete  enc;  
      }

return true;
}

WLEncoder *WLModuleEncoder::getEncoder(int index)
{
Q_ASSERT((index<getSizeEncoder())&&(index<255));

return index<getSizeEncoder() ? Encoder[index]:nullptr;
}

void WLModuleEncoder::update()
{
foreach(WLEncoder *encoder,Encoder)
        encoder->sendGetData();
}

void  WLModuleEncoder::readCommand(QByteArray Data)
{
quint8 index,ui1;
qint32 i32;

QDataStream Stream(&Data,QIODevice::ReadOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream>>ui1;

switch(ui1)
{
case   comEnc_setData  : Stream>>index;//index8
                         if(index<getSizeEncoder()) Encoder[index]->setData(Stream);
                        break;

case  sendModule_prop: Stream>>ui1;					                      
					   Init(ui1);
                       break;

case  sendModule_error:Stream>>ui1;  //Error
					   Stream>>index;  //Error
                    			
					   if(ui1>200)
                        emit sendMessage("WLModuleEncoder "+getErrorStr(errorModule,ui1),QString::number(index),(int)(ui1));	
					   else
						 if(index<getSizeEncoder())  
						     {
							 Encoder[index]->setError(ui1);       									  
							 emit sendMessage("WLEncoder "+getErrorStr(errorEncoder,ui1),QString::number(index),(int)(ui1));	
            			     }
                       break;
}

}


void WLModuleEncoder::updateEncoder()
{
WLEncoder *Encoder=static_cast<WLEncoder*>(sender());

emit changedEncoder(Encoder->getIndex());
}


void WLModuleEncoder::writeXMLData(QXmlStreamWriter &stream)
{
stream.writeAttribute("size",QString::number(getSizeEncoder()));

for(int i=0;i<getSizeEncoder();i++)
 {
 stream.writeStartElement("Encoder");
 stream.writeAttribute("index",QString::number(i));
   Encoder[i]->writeXMLData(stream);
 stream.writeEndElement();
 }
}


void WLModuleEncoder::readXMLData(QXmlStreamReader &stream)
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
	   if(index<getSizeEncoder())	
		   Encoder[index]->readXMLData(stream);		    	    	   
      }
}
}
