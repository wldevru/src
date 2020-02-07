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
setTypeModule(typeDevice);

nameDevice.clear();
serialPort=nullptr;

status=DEVICE_empty;

UID96[0]=UID96[1]=UID96[2]=0;
version=0;

QTimer *timer=new QTimer;
connect(timer,SIGNAL(timeout()),SLOT(sendData()));
timer->start(1);

connect(this,SIGNAL(sendCommand(QByteArray)),this,SLOT(startSend(QByteArray)));
}
 
WLDevice::~WLDevice()
{
setStatus(DEVICE_init);

removeModules();

sendData();

if(serialPort!=nullptr)
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

void WLDevice::callProp()
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<static_cast<quint8>(comDev_getProp);

setCommand(data);
}

void WLDevice::reset()
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<static_cast<quint8>(comDev_resetAll);

setCommand(data);
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
if(serialPort!=nullptr)
 {
 qDebug()<<"reconnect serial port";
 serialPort->close();
 if(!serialPort->open(QIODevice::ReadWrite)) QTimer::singleShot(100,this,SLOT(reconnectSerialPort()));
 }
}

void WLDevice::callStatus()
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<static_cast<quint8>(comDev_getStatus);

setCommand(data);
}

void WLDevice::setStatus(enum statusDevice _status)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<static_cast<quint8>(comDev_setStatus)<<static_cast<quint8>(_status);

setCommand(data);

callStatus();
}

void WLDevice::callModules()
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<static_cast<quint8>(comDev_getModule);

setCommand(data);
}

void WLDevice::callVersion()
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<static_cast<quint8>(comDev_getVersion);

setCommand(data);
}

void WLDevice::off()
{
if(serialPort!=nullptr)
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
if(serialPort
 &&serialPort->isOpen()
 &&!outData.isEmpty())
 {
 serialPort->write(outData);
 }


outData.clear();	 
};

bool WLDevice::initSerialPort(QString portName)
{
    //return true;
emit ChangedConnect(Flags.reset(fl_connect));

QList<QSerialPortInfo> portList=QSerialPortInfo::availablePorts();

if(serialPort)
 {
 serialPort->close();
 disconnect(serialPort,SIGNAL(readyRead()),this,SLOT(readSlot()));
 delete serialPort;

 serialPort=nullptr;
 if(portName.isEmpty()) return false;
 }

//if(portList.size()==1
//&&!portName.isEmpty()) portName=portList.first().portName();

serialPort = new QSerialPort(portName);

connect(serialPort,SIGNAL(readyRead()),SLOT(readSlot()));

prop.clear();

if(!serialPort->open(QIODevice::ReadWrite))
    {
    qDebug()<<"no init serial Port WLDevice"<<portName;
    sendMessage("WLDevice:","no device ("+portName+")",0);
    return false;
    }
else
    {
    qDebug()<<"init serial Port WLDevice"<<portName;
    callStatus();
    callProp();
    callVersion();
    callUID();
    }


reset();
return true;
}

bool WLDevice::initFromSerialPort(QString portName)
{
removeModules();

if(initSerialPort(portName))
 {
 callModules();
 reset();
 return true;
 }

return false;
}

void WLDevice::addModule(WLModule *module) 
{
if(module!=nullptr)
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
WLModule *ret=nullptr;

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

if(serialPort!=nullptr) inBuf+=serialPort->readAll();

quint32 ui32;
qint32 *posProbe;
quint8 com,ui1,ui2,ui3,ui4;
//quint16 ui16[10];
qint32 l1;
quint8 index;
float f1;
QChar buf[256];
QString bufStr;

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
                    case sendModule_error: Stream>>ui1;
                                           Stream>>index;
                    				  
                    				   qDebug()<<"WLDevice Detect Error"<<index<<ui1;
                    				  
                    			  	   emit sendMessage("WLDevice "+getErrorStr(errorDevice,ui1),QString::number(index),-(int)(ui1));				     
                                     //emit ChangedErrorDevice(index,ui1);
									   
									   if(ui1==errorDevice_nomodule)
                                        {
									    for(int i=0;i<Modules.size();i++)
										   if(Modules[i]->getTypeModule()==index)  
										     {
											 delete (Modules.takeAt(i));
											 break;
										     }
                                         }
                    			       break;                    

                    case sendDev_prop:
                                      for(int i=0;i<(size-4);i++)
                                       {
                                       Stream>>ui1;
                                       buf[i]=ui1;
                                       }

                                      bufStr=QString(buf,size-4);

                                      if(!bufStr.isEmpty())
                                       {
                                       prop=bufStr;

                                       setNameDevice(prop.split(".").first());

                                       emit ChangedProp(prop);
                                       emit ChangedConnect(Flags.set(fl_connect));

                                       setStatus(DEVICE_ready);

                                       if(getModuleConnect()!=nullptr)   getModuleConnect()->setEnableHeart(true);
                                       }
                    			      break;

                   case sendDev_Module:   
					                 for(int i=0;i<(size-3);i++) 
									   {
						               Stream>>ui1;//f	
                                       if(getModule(static_cast<typeModule>(ui1))==nullptr)
									     {
									     createModule((typeModule)ui1);										 
									     }
									   buf[i]=ui1;
									   }
									  
                    	              emit ChangedProp(prop);
									  emit ChangedReady(true);                                     
                    			      break;

                   case sendDev_UID:  Stream>>UID96[0];
						              Stream>>UID96[1];
						              Stream>>UID96[2];
									  emit ChangedUID96(UID96);
                    			      break;

                  case sendDev_version:Stream>>ui1;
                                       Stream>>ui2;
                                       Stream>>ui3;
                                       version=ui1*10000+ui2*100+ui3;
                                       emit ChangedUID96(UID96);
                                       break;

                  case sendDev_status: Stream>>ui1;
                                       if(ui1!=status)
                                           emit ChangedStatus(status=static_cast<statusDevice>(ui1));
                                      break;

                    case typeMFW:  if(getModule((typeModule)ui1)==nullptr) //oldFW
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



void WLDevice::callUID()
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comDev_getUID;

qDebug()<<"Call getUID";

setCommand(data);
}

WLModule *WLDevice::createModule(typeModule type)
{
WLModule *Module=nullptr;

if(Module==nullptr)
{
if(type==typeMConnect)
  {
  WLModuleConnect *MConnect = new WLModuleConnect();
  connect(this,SIGNAL(readDataDevice()),MConnect,SLOT(restartHeart()));
  connect(MConnect,SIGNAL(timeoutConnect()),this,SLOT(reconnectSerialPort()));
  connect(MConnect,SIGNAL(backupConnect()),this,SLOT(updateModules()));

  connect(MConnect,SIGNAL(timeoutConnect()),this,SLOT(setStatusEmpty()));
  Module=MConnect;
  }

addModule(Module);
}

return Module;
}

WLModule *WLDevice::createModule(QString name)
{
WLModule *Module=nullptr;

if(Module==nullptr)
{
if(name=="WLModuleConnect")
  {
  WLModuleConnect *MConnect = new WLModuleConnect();
  connect(this,SIGNAL(readDataDevice()),MConnect,SLOT(restartHeart()));
  connect(MConnect,SIGNAL(timeoutConnect()),this,SLOT(reconnectSerialPort()));
  connect(MConnect,SIGNAL(backupConnect()),this,SLOT(updateModules()));

  //connect(MConnect,SIGNAL(timeoutConnect()),this,SLOT(setStatusEmpty()));

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

WLModule *Module;
bool add=true;
		
qDebug()<<"readXMLData Device";

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

        Module=nullptr;

        if(i==Modules.size()&&add)
		  {
          Module=createModule(stream.name().toString());

          if(Module)
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

if(serialPort!=nullptr) stream.writeAttribute("VCP",serialPort->portName());

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

bool WLDevice::initFromFile(QString nameFile)
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
     qDebug()<<"stream.name()="<<stream.name();

     if(stream.name()=="WLDevice"
     &&stream.tokenType()==QXmlStreamReader::StartElement)
      {
      stream.readNextStartElement();
      readXMLData(stream);
      }
     }

  FileXML.close();

  if(!getModuleConnect()) createModule(typeMConnect);

  return true;
  }
return false;
}

