#include "WLDevice.h"
//#include "wldefine.h"
#include <QDebug>

#define initStream \
\QMutexLocker locker(&BufMutex);\
\QByteArray data;\
\QDataStream Stream(&data,QIODevice::WriteOnly);\
\
\Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);\
\Stream.setByteOrder(QDataStream::LittleEndian);

WLDevice::WLDevice()
{
nameDevice.clear();
serialPort=NULL;

UID96[0]=UID96[1]=UID96[2]=0;

QTimer *timer=new QTimer;
connect(timer,SIGNAL(timeout()),SLOT(sendData()));
timer->start(1);	
}
 
WLDevice::~WLDevice()
{
removeModules();

if(serialPort!=NULL)
 {
 serialPort->close();
 delete serialPort;
 }
}

void WLDevice::callPropModules()
{
for(int i=0;i<Modules.size();i++) 	
	Modules[i]->callProp();
}

void WLDevice::removeModules()
{
while(!Modules.isEmpty())
  delete (Modules.takeLast());

emit ChangedModules(Modules.size());
emit ChangedReady(Flags.reset(fl_ready));
}

void WLDevice::reconnectSerialPort()
{
if(serialPort!=NULL)
 {
 serialPort->close();
 if(!serialPort->open(QIODevice::ReadWrite)) QTimer::singleShot(100,this,SLOT(reconnectSerialPort()));
 }
}

void WLDevice::callModules()
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeDevice<<(quint8)comDev_getModule;

qDebug()<<"Call getModule dev";

startSend(data);
}

void WLDevice::off()
{
if(serialPort!=NULL)
{
if(serialPort->isOpen())
 {
 reset();
 //wait send
 while(!outData.isEmpty()); //ждём отправки
 }
}
}

void WLDevice::startSend(QByteArray data)
{
QMutexLocker locker(&OutDataMutex); 
//data.prepend(data.size()+1);
//write(data);
outData+=data.prepend(data.size()+1);

//QTimer::singleShot(0,this,SLOT(sendData()));
}


void WLDevice::sendData()
{
QMutexLocker locker0(&SendOutMutex);

QMutexLocker locker1(&OutDataMutex); 
if(serialPort&&!outData.isEmpty())
 {
  serialPort->write(outData);;
 }


outData.clear();	 
};

bool WLDevice::initSerialPort(QString portName)
{
emit ChangedConnect(Flags.reset(fl_connect));

QList<QSerialPortInfo> portList=QSerialPortInfo::availablePorts(); 	 

if(serialPort!=NULL) 
 {
 serialPort->close();
 disconnect(serialPort,SIGNAL(readyRead()),this,SLOT(readSlot()));
 delete serialPort;

 serialPort=NULL;
 if(portName.isEmpty()) return false;
 }

if(portList.size()==1) portName=portList.first().portName();

serialPort = new QSerialPort(portName);

connect(serialPort,SIGNAL(readyRead()),SLOT(readSlot()));

qDebug()<<"init serial Port WLDevice"<<portName;

prop.clear();

#ifndef enableDemo
if(!serialPort->open(QIODevice::ReadWrite)) 
	{
	sendMessage("WLDevice:","no device ("+portName+")",0); 
	return false;    
    }
else
    {
	callProp();
    callUID();
	callModules();
    }
#endif

reset();



return true;
}

void WLDevice::addModule(WLModule *module) 
{
if(module!=NULL)
 {
 for(int i=0;i<Modules.size();i++)
	 if(module->getTypeModule()==Modules[i]->getTypeModule()) return;

 Modules+=module;
 connect(module,SIGNAL(sendCommand(QByteArray)),SLOT(startSend(QByteArray)));
 connect(module,SIGNAL(sendMessage(QString,QString,int)),SIGNAL(sendMessage(QString,QString,int)));
 module->callProp();

 emit ChangedModules(Modules.size());
 }
}


WLModule* WLDevice::getModule(typeModule type)
{
WLModule *ret=NULL;

for(int i=0;i<Modules.size();i++)
	if(Modules[i]->getTypeModule()==type) 
	    {
		ret=Modules[i];
		break;
	    }

return ret;
}


void WLDevice::readSlot()
{
QMutexLocker locker(&InputDataMutex);

if(serialPort!=NULL) inBuf+=serialPort->readAll();

quint32 ui32;
qint32 *posProbe;
quint8 com,ui1,ui2,ui3,ui4;
//quint16 ui16[10];
qint32 l1;
quint8 index;
float f1;
QChar buf[256];

int curi=0;
quint8 size;

QByteArray Data;

while(inBuf.size()>=(quint8)inBuf[0])
{
size=(quint8)inBuf[0];

if(size==0) {inBuf.clear(); break;}


curi++;

Data=inBuf.mid(1,size-1);
inBuf=inBuf.mid(size);

QDataStream Stream(&Data,QIODevice::ReadOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream>>ui1;

emit readDataDevice();

if(!Data.isEmpty())
switch(ui1)
 {
 case typeDevice:Stream>>ui1;
	             switch(ui1)
				    { 
                    case sendDev_error: Stream>>ui1;
                    	               Stream>>index; 
                    				  
                    				   qDebug()<<"WLDevice Detect Error"<<index<<ui1;
                    				  
                    			  	   emit sendMessage("WLDevice "+getErrorStr(errorDevice,ui1),QString::number(index),-(int)(ui1));				     
									  // emit ChangedErrorDevice(index,ui1);
									   
									   if(ui1==errorDevice_nomodule)
									    for(int i=0;i<Modules.size();i++)
										   if(Modules[i]->getTypeModule()==index)  
										     {
											 delete (Modules.takeAt(i));
											 break;
										     }
                    
                    			       break;                    

                    case sendDev_Prop:
						              for(int i=0;i<(size-3);i++) 
									   {
						               Stream>>ui1;//f	
									   buf[i]=ui1;
									   }

									  prop=QString(buf,size-3);

									  
									  setNameDevice(prop.split(".").first());

                    	              emit ChangedProp(prop);
									  emit ChangedConnect(Flags.set(fl_connect));		  
                    			      break;

                   case sendDev_Module:   
					                 for(int i=0;i<(size-3);i++) 
									   {
						               Stream>>ui1;//f	
									   if(getModule((typeModule)ui1)==NULL)
									     {
									     createModule((typeModule)ui1);										 
									     }
									   buf[i]=ui1;
									   }
									  
                    	              emit ChangedProp(prop);
									  emit ChangedReady(true);
                    			      break;

                    case sendDev_UID: Stream>>UID96[0];
						              Stream>>UID96[1];
						              Stream>>UID96[2];
									  emit ChangedUID96(UID96);
                    			      break;

					case typeMFW:  if(getModule((typeModule)ui1)==NULL) //oldFW
									     {
									     createModule((typeModule)ui1);										 
									     };

					            	emit ChangedProp(prop);
									emit ChangedReady(Flags.set(fl_ready));

						            break;
				   }
				   break;
 default: for(int i=0;i<Modules.size();i++)
			   if(Modules[i]->getTypeModule()==ui1)
			     {
				 Modules[i]->readCommand(Data.mid(1));
				 break;
			     }
			  break;

  }

if(inBuf.isEmpty()) break;
}
}

void WLDevice::callProp()
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeDevice<<(quint8)comDev_getProp;

qDebug()<<"Call getProp dev";

startSend(data);
}

void WLDevice::callUID()
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeDevice<<(quint8)comDev_getUID;

qDebug()<<"Call getUID";

startSend(data);
}

WLModule *WLDevice::createModule(typeModule type)
{
WLModule *Module=NULL;

if(Module==NULL)
{
if(type==typeMConnect)
  {
  WLModuleConnect *MConnect = new WLModuleConnect();
  connect(this,SIGNAL(readDataDevice()),MConnect,SLOT(restartHeart()));
  connect(MConnect,SIGNAL(timeoutConnect()),this,SLOT(reconnectSerialPort()));
  Module=MConnect;
  }

addModule(Module);
}

return Module;
}

WLModule *WLDevice::createModule(QString name)
{
WLModule *Module=NULL;

if(Module==NULL)
{
if(name=="WLModuleConnect")
  {
  WLModuleConnect *MConnect = new WLModuleConnect();
  connect(this,SIGNAL(readDataDevice()),MConnect,SLOT(restartHeart()));
  connect(MConnect,SIGNAL(timeoutConnect()),this,SLOT(reconnectSerialPort()));
  Module=MConnect;
  }

addModule(Module);
}

return Module;
}


void WLDevice::readXMLData(QXmlStreamReader &stream)
{
QString port;
int i;
int iSize=0,oSize=0;
WLModule *Module;
bool add=true;
		
if(getNameDevice()==stream.name()
 ||getNameDevice().isEmpty())	
{
setNameDevice(stream.name().toString());

if(!stream.attributes().value("VCP").isEmpty()) 
		 initSerialPort(stream.attributes().value("VCP").toString());

while(!stream.atEnd())
{
stream.readNextStartElement();
qDebug()<<stream.name();

if(stream.name()==getNameDevice()) break;
if(stream.tokenType()!=QXmlStreamReader::StartElement) continue;

if(stream.name()=="Modules")
	   {
	   while(!stream.atEnd())
	    {
        stream.readNextStartElement();
		qDebug()<<stream.name()<<stream.tokenType();
		if(stream.name()=="Modules") break;
		if(stream.tokenType()!=QXmlStreamReader::StartElement) continue;
		
		for(i=0;i<Modules.size();i++)
			if(stream.name()==Modules[i]->metaObject()->className()) 
			    {
				Modules[i]->readXMLData(stream);
				break;
			    }

		Module=NULL;

        if(i==Modules.size()&&add)
		  {
		  Module=createModule(stream.name().toString());	  
		  Module->readXMLData(stream);
		  }
	    }
	   }
}
}


}


void WLDevice::writeXMLData(QXmlStreamWriter &stream)
{
stream.writeStartElement(getNameDevice());

if(serialPort!=NULL) stream.writeAttribute("VCP",serialPort->portName());

stream.writeStartElement("Modules");
for(int i=0;i<Modules.size();i++)
 {
 stream.writeStartElement(Modules[i]->metaObject()->className());
   Modules[i]->writeXMLData(stream);  
 stream.writeEndElement();
 }
stream.writeEndElement();

stream.writeEndElement();
//stream.writeAttribute("invInput",getInputInvStr());
//stream.writeAttribute("invOutput",getOutputInvStr());
}


bool WLDevice::writeToFile(QString nameFile)
{
QFile FileXML(nameFile);

QByteArray Data;

QXmlStreamWriter stream(&Data);

stream.setAutoFormatting(true);

stream.setCodec(QTextCodec::codecForName("Windows-1251"));
stream.writeStartDocument("1.0");

  stream.writeStartElement("WLDevice");
   writeXMLData(stream);
 stream.writeEndElement();

stream.writeEndDocument();

if(FileXML.open(QIODevice::WriteOnly))
 {
 FileXML.write(Data.constData());
 FileXML.close();
 return true;
 }
return false;
}

bool WLDevice::readFromFile(QString nameFile,bool add)
{
QFile FileXML(nameFile);
QXmlStreamReader stream;
		
qDebug()<<"load config";

if(FileXML.open(QIODevice::ReadOnly))
  {
  qDebug()<<"open XML";
  stream.setDevice(&FileXML);
  
  while(!stream.atEnd())
	 { 
	 stream.readNextStartElement();
		
	 if(stream.name()=="WLDevice"
	 &&stream.tokenType()==QXmlStreamReader::StartElement)	
	  {	   	 
	  stream.readNextStartElement();	     	
	  readXMLData(stream);
	  }
	                                  
     } 

  FileXML.close();
  return true;
  }
return false;
}
