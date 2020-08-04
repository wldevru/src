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
setType(typeDevice);

m_HA.clear();

m_nameDevice.clear();


status=DEVICE_empty;

m_version=0;

QTimer *timer=new QTimer;

connect(timer,SIGNAL(timeout()),SLOT(sendData()));
timer->start(1);

connect(this,SIGNAL(sendCommand(QByteArray)),this,SLOT(startSend(QByteArray)),Qt::DirectConnection);

connect(&m_serialPort,&QSerialPort::readyRead,this,&WLDevice::readSlot);
connect(&m_serialPort,SIGNAL(error(QSerialPort::SerialPortError)),this,SLOT(onErrorSerialPort(QSerialPort::SerialPortError)));

connect(&m_udpSocket,&QUdpSocket::readyRead,this,&WLDevice::readSlot);

m_timerEth = new QTimer;
m_timerEth->setSingleShot(true);

connect(m_timerEth,&QTimer::timeout,this,&WLDevice::sendEthData);

m_countTxPacket=0;
m_countRxPacket=255;
}
 
WLDevice::~WLDevice()
{
closeConnect();

blockSignals(true);

removeModules();
}

void WLDevice::callPropModules()
{
quint16 sizeOutBuf;

for(int i=0;i<m_modules.size();i++)
    m_modules[i]->callProp();
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

void WLDevice::sendEthData()
{
m_udpSocket.writeDatagram(m_bufEth,m_HA,2020);
/*
for(int i=0;i<m_bufEth.size();i++)
    qDebug()<<(quint8)m_bufEth[i];
*/
 //qDebug()<<"sendEth"<<m_bufEth.size();
if(status==DEVICE_connect)
  {
  Flags.set(fl_waitack);
   m_timerEth->start(100);
  }
}

void WLDevice::removeModules()
{
while(!m_modules.isEmpty())
  delete (m_modules.takeLast());

emit changedModules(m_modules.size());
emit changedReady(Flags.reset(fl_ready));
}

void WLDevice::reconnectSerialPort()
{    
//qDebug()<<"if reconnect"<<getStatus();
QMutexLocker locker(&connectMutex);

if(isOpenConnect()
 &&!m_serialPort.portName().isEmpty()
 //&&getStatus()==DEVICE_connect)
  )
 {
 qDebug()<<"reconnect serial port"<<m_serialPort.portName();
 if(m_serialPort.isOpen())
   {
   m_serialPort.close();
   }

 if(!m_serialPort.open(QIODevice::ReadWrite))
       {
       QTimer::singleShot(50,this,SLOT(reconnectSerialPort()));
       emit reconnected();
       }
   else
      {
       qDebug()<<"reconnect serial port true";
       if(getModuleConnect())
           {
           getModuleConnect()->restartHeart();
           getModuleConnect()->sendHeart();
           }
      }
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

QList<WLDeviceInfo> WLDevice::availableDevices()
{
QList<WLDeviceInfo>  retDevicesInfo;
QList<QSerialPortInfo> portList=QSerialPortInfo::availablePorts();

foreach(QSerialPortInfo portInfo,portList)
 {
 WLDevice  Device;

 Device.initSerialPort(portInfo.portName());
 Device.openConnect();
 Device.closeConnect();

 if(!Device.getUID96().isEmpty())  retDevicesInfo+=Device.getInfo();
 }

QUdpSocket udpSocket;
QHostAddress HA;
quint16 port;
int n;
char buf[]={0,3,0,5};
char dataBuf[512];
QList <QHostAddress> HADList;
QByteArray BA(buf,4);

udpSocket.bind(2021);
udpSocket.writeDatagram(BA,QHostAddress::Broadcast,2020);
QThread::msleep (250);
udpSocket.waitForReadyRead(500);

n=udpSocket.readDatagram(dataBuf,512,&HA,&port);

while(n>0)
{
if(port==2020)
   {
   if(HADList.indexOf(HA)==-1)    HADList+=HA;
    }
n=udpSocket.readDatagram(buf,4,&HA,&port);
}

udpSocket.close();

foreach(QHostAddress HAD,HADList)
 {
 WLDevice  DeviceEth;

 DeviceEth.initUdpSocket(HAD);
 DeviceEth.openConnect();
 DeviceEth.closeConnect();

 if(!DeviceEth.getUID96().isEmpty())  retDevicesInfo+=DeviceEth.getInfo();
 }


return retDevicesInfo;
}

void WLDevice::reboot(uint8_t type)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<static_cast<quint8>(comDev_reboot)<<type;

setCommand(data);

QTimer::singleShot(100,this,SLOT(closeConnect()));
}

void WLDevice::setInfo(WLDeviceInfo info)
{
setNameDevice(info.name);

initSerialPort(info.comPort);
initUdpSocket(info.HA);

setUID96(info.UID96);
setVersion(info.version);
}

WLDeviceInfo WLDevice::getInfo()
{
WLDeviceInfo info;

info.name =getNameDevice();
info.comPort=getPortName();
info.HA=getHA();
info.UID96  =getUID96();
info.version=getVersion();

return info;
}

void WLDevice::setUID96(QString _UID96)
{
m_UID96=_UID96;
emit changedUID96(m_UID96);
}

void WLDevice::setStatus(enum statusDevice _status)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<static_cast<quint8>(comDev_setStatus)<<static_cast<quint8>(_status);

setCommand(data);

qDebug()<<"setStatus Device"<<_status;
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
if(m_serialPort.isOpen())
 {
 reset();
 //wait send
 while(!outBuf.isEmpty()); //ждём отправки
 }
}

QList<WLModule *> WLDevice::getModules() const
{
    return m_modules;
}

void WLDevice::startSend(QByteArray data)
{
    QMutexLocker locker(&OutDataMutex);

if(!data.isEmpty())
    {
    outBuf+=data.size()+1;
    outBuf+=data;
    }
}


void WLDevice::sendData()
{
QMutexLocker locker0(&SendOutMutex);
QMutexLocker locker1(&OutDataMutex);

int n;


if(!outBuf.isEmpty())
{
 if(m_serialPort.isOpen())
    {    
    m_serialPort.write(outBuf);
    outBuf.clear();
    }

 else
   {              
  // qDebug()<<"isOpen"<<m_udpSocket.isOpen()<<Flags.get(DEVF_ethwaitack);
   if(m_udpSocket.isOpen()
   &&!Flags.get(fl_waitack))
       {
       m_bufEth.clear();
       m_bufEth+=(++m_countTxPacket);

        if(outBuf.size()>256)
         {
          n=outBuf[0];

          while((n+outBuf[n])<256)  //only full packets
           {
           n+=outBuf[n];
           }

         m_bufEth+=outBuf.mid(0,n);

         //m_udpSocket.writeDatagram(m_outData.mid(0,n),m_HA,2020);
         outBuf=outBuf.mid(n);
         }
        else
         {
         m_bufEth+=outBuf;
         //m_udpSocket.writeDatagram(outData,m_HA,2020);
         outBuf.clear();
         }
        sendEthData();
        }
    //  else
       // qDebug()<<"Busy Eth"<<m_udpSocket.isOpen()<<Flags.get(DEVF_ethwaitack);;
    }

}


};

bool WLDevice::initSerialPort(QString portName)
{
closeConnect();
m_serialPort.setPortName(portName);

qDebug()<<"Init Serial port:"<<portName;
return true;
}

bool WLDevice::initUdpSocket(QHostAddress HA)
{
closeConnect();

m_HA=HA;

qDebug()<<"initUdpSocket"<<HA.toString();
return true;
}

bool WLDevice::openConnect()
{
QMutexLocker locker(&connectMutex);

Flags.reset(fl_waitack);

if(!m_serialPort.portName().isEmpty())
{
m_serialPort.close();

  if(!m_serialPort.open(QIODevice::ReadWrite))
      {
      qDebug()<<"no init serial Port WLDevice"<<m_serialPort.portName();
      sendMessage("WLDevice:","no device ("+m_serialPort.portName()+")",0);
      return false;
      }
 qDebug()<<"Open QSerialPort"<<thread();
}
else
{
if(!m_HA.isNull())
  {
  if(!m_udpSocket.open(QIODevice::ReadWrite)
   ||!m_udpSocket.bind(2021))
   {
   qDebug()<<"no init udp WLDevice";
   return false;
   }
  m_bufEth.clear();
  }
}

Flags.set(fl_openconnect);

callStatus();
callProp();
callVersion();
callUID();

callModules();

sendData();

m_serialPort.flush();
QThread::msleep (50);

if(!m_serialPort.portName().isEmpty())
 {
 if(m_serialPort.waitForReadyRead(100))
                          readSlot();
 }
else
if(!m_HA.isNull())
 {
 if(m_udpSocket.waitForReadyRead(100))
                          readSlot();
 }

reset();

return true;
}

void WLDevice::closeConnect()
{
if(isOpenConnect())
{

if(getModuleConnect())
  {
  getModuleConnect()->setEnableHeart(false);
  }

 setStatus(DEVICE_init);
 sendData();

 Flags.reset(fl_openconnect);

 connectMutex.lock();

 if(m_serialPort.isOpen())
  {
  qDebug()<<"Close Serial Port";
  m_serialPort.flush();
  QThread::msleep (50);
  m_serialPort.close();
  }
  else if(m_udpSocket.isOpen())
         {
         sendEthData();
         m_udpSocket.flush();
         QThread::msleep(150);
         m_timerEth->stop();

         m_udpSocket.close();
         m_bufEth.clear();
         Flags.reset(fl_waitack);
         }

 connectMutex.unlock();

 emit changedConnect(Flags.reset(fl_connect));
 emit changedReady(false);
}
}


void WLDevice::addModule(WLModule *module) 
{
if(module!=nullptr)
 {
 for(int i=0;i<m_modules.size();i++)
     if(module->getType()==m_modules[i]->getType()) return;

 m_modules+=module;
 connect(module,SIGNAL(sendCommand(QByteArray)),SLOT(startSend(QByteArray)),Qt::DirectConnection);
 connect(module,SIGNAL(sendMessage(QString,QString,int)),SIGNAL(sendMessage(QString,QString,int)));

 module->callProp();

 emit changedModules(m_modules.size());
 }
}


WLModule* WLDevice::getModule(typeModule type)
{
WLModule *ret=nullptr;

for(int i=0;i<m_modules.size();i++)
    if(m_modules[i]->getType()==type)
	    {
        ret=m_modules[i];
		break;
	    }

return ret;
}


void WLDevice::readSlot()
{
QMutexLocker locker(&InputDataMutex);

if(m_serialPort.isOpen())
 {
 inBuf+=m_serialPort.readAll();
 decodeInputData();
 }
else
 {
 //if(m_udpSocket.isOpen())
   {
   QHostAddress HA;
   quint16 port;
   char bufData[512];

   int n = m_udpSocket.readDatagram(bufData,sizeof(bufData),&HA,&port);

   if(HA==m_HA&&port==2020)
     {
     QByteArray byteArray(bufData,n);

     if(byteArray.size()==1)
     {
     //qDebug()<<"Ack"<<(quint8)byteArray[0]<<m_countTxPacket;
     if(Flags.get(fl_waitack)
      &&m_countTxPacket==(quint8)byteArray[0])
         {
         Flags.reset(fl_waitack);
         m_timerEth->stop();
         //qDebug()<<"Ack ok";
         }
     }
     else
        {
        m_udpSocket.writeDatagram(byteArray.data(),1,m_HA,2020);

        if(m_countRxPacket!=(quint8)byteArray[0])
          {
          m_countRxPacket=(quint8)byteArray[0];

          inBuf+=byteArray.mid(1);          
          }
        }
     decodeInputData();
     }
   }
 }
}

void WLDevice::decodeInputData()
{

quint8 ui1,ui2,ui3;
//quint16 ui16[10];

quint8 index;

QChar buf[256];
QString bufStr;

quint8 ui8;
QString uid;

int curi=0;
quint8 size;

QByteArray Data;

while(!inBuf.isEmpty())
{
size=(quint8)inBuf[0];

if(inBuf.size()<size) break;
if(size==0) {inBuf.clear(); break;}

curi++;

Data=inBuf.mid(1,size-1);
inBuf=inBuf.mid(size);

emit readDataDevice();


if(!Data.isEmpty())
{
QDataStream Stream(&Data,QIODevice::ReadOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream>>ui1;

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
                                        for(int i=0;i<m_modules.size();i++)
                                           if(m_modules[i]->getType()==index)
										     {
                                             Q_ASSERT(m_modules[i]->getType()==index);
                                             delete (m_modules.takeAt(i));
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
                                       m_prop=bufStr;

                                       setNameDevice(m_prop.split(".").first());

                                       emit changedProp(m_prop);
                                       emit changedConnect(Flags.set(fl_connect));

                                       setStatus(DEVICE_connect);

                                       //if(getModuleConnect())
                                       //           getModuleConnect()->setEnableHeart(true); //on/off user
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
									  
                                      emit changedProp(m_prop);
                                      emit changedReady(true);
                    			      break;

                   case sendDev_UID: for(quint8 i=0;i<(96/8);i++)
                                       {                                       
                                       Stream>>ui8;
                                       uid+=QString::number(ui8>>4,16);
                                       uid+=QString::number(ui8&0xF,16);
                                       }
                                      setUID96(uid);
                    			      break;

                  case sendDev_version:Stream>>ui1;
                                       Stream>>ui2;
                                       Stream>>ui3;
                                       setVersion(ui1*10000+ui2*100+ui3);
                                       break;

                  case sendDev_status: Stream>>ui1;
                                       if(ui1!=status)//забивает статус
                                          emit changedStatus(status=static_cast<statusDevice>(ui1));
                                       break;

                    case typeMFW:  if(getModule((typeModule)ui1)==nullptr) //oldFW
									     {
									     createModule((typeModule)ui1);										 
									     };

                                    emit changedProp(m_prop);
                                    emit changedReady(Flags.set(fl_ready));

						            break;
				   }
				   break;
 default: for(int i=0;i<m_modules.size();i++)
               if(m_modules[i]->getType()==ui1)
			     {
                 m_modules[i]->readCommand(Data.mid(1));
				 break;
			     }
			  break;

  }
}

if(inBuf.isEmpty()) break;
}
}

void WLDevice::onErrorSerialPort(QSerialPort::SerialPortError serialPortError)
{
qDebug()<<"onErrorSerialPort"<<serialPortError;

//QMutexLocker locker(&connectMutex);

switch(serialPortError)
{
case QSerialPort::DeviceNotFoundError:// reconnectSerialPort();
                                       break;


default: break;
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
  connect(this,&WLDevice::readDataDevice,MConnect,&WLModuleConnect::restartHeart);

  connect(MConnect,&WLModuleConnect::timeoutHeart,this,&WLDevice::reconnectSerialPort,Qt::DirectConnection);
  connect(MConnect,&WLModuleConnect::backupConnect,this,&WLDevice::updateModules);

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
  connect(this,&WLDevice::readDataDevice,MConnect,&WLModuleConnect::restartHeart);

  connect(MConnect,&WLModuleConnect::timeoutHeart,this,&WLDevice::reconnectSerialPort,Qt::DirectConnection);
  connect(MConnect,&WLModuleConnect::backupConnect,this,&WLDevice::updateModules);

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

if(!stream.attributes().value("IP").isEmpty())
         initUdpSocket(QHostAddress(stream.attributes().value("IP").toString()));

if(!stream.attributes().value("UID96").isEmpty())
         setUID96(stream.attributes().value("UID96").toString());
/*
if(!stream.attributes().value("UID").isEmpty())
         setUID(stream.attributes().value("UID").toLong());
*/
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
		
        for(i=0;i<m_modules.size();i++)
            if(stream.name()==m_modules[i]->metaObject()->className())
			    {
                m_modules[i]->readXMLData(stream);
				break;
			    }

        Module=nullptr;

        if(i==m_modules.size()&&add)
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

if(!m_serialPort.portName().isEmpty())  {
  stream.writeAttribute("VCP",m_serialPort.portName());
 }
else
  if(!m_HA.isNull())  stream.writeAttribute("IP",m_HA.toString());

stream.writeAttribute("UID96",getUID96());

stream.writeStartElement("Modules");
for(int i=0;i<m_modules.size();i++)
 {
 stream.writeStartElement(m_modules[i]->metaObject()->className());
   m_modules[i]->writeXMLData(stream);
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

