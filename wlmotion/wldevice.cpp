#include "wldevice.h"
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
m_versionProtocol=0;

m_timerSend=new QTimer;

connect(m_timerSend,SIGNAL(timeout()),SLOT(sendData()));

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
qDebug()<<"~WLDevice()";
closeConnect();

blockSignals(true);

delete  m_timerSend;
delete  m_timerEth;

removeModules();
qDebug()<<"~WLDevice()+";
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
QMutexLocker locker(&InputDataMutex);

if(m_udpSocket.write(m_bufEth))
 {
 if(status==DEVICE_connect)
   {
   Flags.set(fl_waitack);
   m_timerEth->start(20);
   }
}
}

void WLDevice::updateReady()
{
foreach(WLModule *module,m_modules)
 {
 if(!module->isReady())
    {
    if(isReady()) setReady(false);

    qDebug()<<"WLDevice::updateReady() false size"<<m_modules.size()<<module->type();
    return;
    }
 }
qDebug()<<"WLDevice::updateReady() true size"<<m_modules.size();
setReady(true);

update();
}

void WLDevice::removeModules()
{
while(!m_modules.isEmpty())
  delete (m_modules.takeLast());

emit changedModules(m_modules.size());

setReady(false);
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
QElapsedTimer Timer;
QList<WLDeviceInfo>  retDevicesInfo;
QList<QSerialPortInfo> portList=QSerialPortInfo::availablePorts();
QList<WLDevice*> Devices;

foreach(QSerialPortInfo portInfo,portList)
 {
 WLDevice *Device=new WLDevice;

 Device->initSerialPort(portInfo.portName());

 if(Device->openConnect())
      Devices+=Device;
   else
      delete Device;
 }

QList <QHostAddress> adrList = QNetworkInterface::allAddresses();
QList <QNetworkInterface> ifaces = QNetworkInterface :: allInterfaces ();
QUdpSocket udpSocket;
QHostAddress HA;
quint16 port;
int n;
char buf[]={0,3,0,5};
char dataBuf[512];
QList <QHostAddress> HADList;
QByteArray BA(buf,4);

udpSocket.bind();
// Interfaces iteration

for (int i = 0; i < ifaces.size(); i++)
{
    // Now get all IP addresses for the current interface
    QList<QNetworkAddressEntry> addrs = ifaces[i].addressEntries();

    // And for any IP address, if it is IPv4 and the interface is active, send the packet
    for (int j = 0; j < addrs.size(); j++)
        if ((addrs[j].ip().protocol() == QAbstractSocket::IPv4Protocol) && (addrs[j].broadcast().toString() != ""))
            udpSocket.writeDatagram(BA,addrs[j].broadcast(),UDPPORT);
}


Timer.start();

while(Timer.elapsed()<500)
{
QCoreApplication::processEvents();

n=udpSocket.readDatagram(dataBuf,512,&HA,&port);

bool add=false;

if(port==UDPPORT&&n!=0)
   {

   if(HADList.indexOf(HA)==-1)
     {
     add=true;
     /*
     foreach(QHostAddress address, adrList)
      {
      if(address.toIPv4Address()==HA.toIPv4Address()) {add=false; continue;}
      }
    */
    if(add) HADList+=HA;
    }

   }
}

udpSocket.close();

foreach(QHostAddress HAD,HADList)
 {
 WLDevice  *Device = new WLDevice;

 Device->initUdpSocket(HAD);
 Device->openConnect();

 Devices+=Device;
 }

Timer.start();
while(Timer.elapsed()<500)
{
QCoreApplication::processEvents();
}

while(!Devices.isEmpty())
 {
 WLDevice  *Device=Devices.takeFirst();

 if(!Device->getUID96().isEmpty())  retDevicesInfo+=Device->getInfo();

 delete Device;
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

if(!isOpenConnect())
 {
 initSerialPort(info.comPort);
 initUdpSocket(info.HA);
 }

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

status=_status;

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
qDebug()<<"comDev_getModule";
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

void WLDevice::callVersionProtocol()
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<static_cast<quint8>(comDev_getVersionProtocol);

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

static bool send=false;

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
   m_serialPort.flush();

   outBuf.clear();
   }
 else
   {              
   if(m_udpSocket.isOpen()
   &&(!Flags.get(fl_waitack)))
       {
       m_bufEth.clear();

       InputDataMutex.lock();
       m_bufEth+=(++m_countTxPacket);
       InputDataMutex.unlock();

        if(outBuf.size()>64)
         {
          n=outBuf[0];

          while((n+outBuf[n])<64)  //only full packets
           {
           n+=outBuf[n];
           }

         m_bufEth+=outBuf.mid(0,n);

         outBuf=outBuf.mid(n);
         }
        else
         {
         m_bufEth+=outBuf;
         outBuf.clear();
         } 

        sendEthData();
        }
    }
}

}


bool WLDevice::initSerialPort(QString portName)
{
closeConnect();
m_serialPort.setPortName(portName);

qDebug()<<getNameDevice()<<"Init Serial port:"<<portName;
return true;
}

bool WLDevice::initUdpSocket(QHostAddress HA)
{
closeConnect();

m_HA=HA;

qDebug()<<getNameDevice()<<"initUdpSocket"<<HA.toString();
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
  else
      {
      m_timerSend->start(DEFINE_TIMERWAITUSB);
      qDebug()<<"Open QSerialPort"<<m_serialPort.isOpen()<<thread();
      }
}
else
{
if(!m_HA.isNull())
  {
  if(!m_udpSocket.open(QIODevice::ReadWrite))
   {
   qDebug()<<"no init udp WLDevice"<<m_udpSocket.open(QIODevice::ReadWrite)<<m_udpSocket.bind(UDPPORT);
   return false;
   }
  else
   {
   m_timerSend->start(DEFINE_TIMERWAITETH);
   m_udpSocket.connectToHost(m_HA,UDPPORT);
   }

  m_bufEth.clear();
  }
}

Flags.set(fl_openconnect);

callVersionProtocol();

callStatus();
callProp();
callVersion();
callUID();

callModules();

reset();

return true;
}

bool WLDevice::waitForReady(int timeout)
{
QElapsedTimer Timer;

Timer.start();

while((Timer.elapsed()<timeout)&&(!isReady()))
 {
 QCoreApplication::processEvents();
 }

return isReady();
}

void WLDevice::closeConnect()
{
if(isOpenConnect())
{
if(getModuleConnect())
  {
  getModuleConnect()->setEnableHeart(false);
  }

if(SendOutMutex.tryLock(250))
 {
 SendOutMutex.unlock();
 }
else
 {
 qDebug()<<"error close connect";
 }

 setStatus(DEVICE_init);

 Flags.reset(fl_waitack);

 QElapsedTimer Timer;

 Timer.start();

 while(Timer.elapsed()<500)
 {
 QCoreApplication::processEvents();
 }

 Flags.reset(fl_openconnect);

 connectMutex.lock();


 if(m_serialPort.isOpen())
  {
  qDebug()<<"Close Serial Port";
  m_serialPort.close();
  }
  else if(m_udpSocket.isOpen())     
         {
         qDebug()<<"Close UDP Socket";
         m_udpSocket.close();
         m_bufEth.clear();         
         }

 m_timerSend->stop();
 m_timerEth->stop();

 connectMutex.unlock();

 emit changedConnect(Flags.reset(fl_connect));
 emit changedReady(false);
}
}

void WLDevice::update()
{
callStatus();

foreach(WLModule *Module,m_modules)
 {
  qDebug()<<Module->metaObject()->className()<<"update";
  Module->update();
}
}

void WLDevice::backup()
{
callStatus();
setStatus(getStatus());

foreach(WLModule *Module,m_modules)
 {
  qDebug()<<Module->metaObject()->className()<<"backup";
  Module->backup();
}

}


void WLDevice::addModule(WLModule *module) 
{
    if(module!=nullptr)
    {
        module->setParent(this);

        for(int i=0;i<m_modules.size();i++)
            if(module->type()==m_modules[i]->type()) return;

        m_modules+=module;

        connect(module,SIGNAL(sendCommand(QByteArray)),SLOT(startSend(QByteArray)),Qt::DirectConnection);
        connect(module,SIGNAL(sendMessage(QString,QString,int)),SIGNAL(sendMessage(QString,QString,int)));
        connect(module,SIGNAL(changedReady(bool)),SLOT(updateReady()));

 module->callProp();

 emit changedModules(m_modules.size());
 }
}


WLModule* WLDevice::getModule(typeModule type)
{
WLModule *ret=nullptr;

for(int i=0;i<m_modules.size();i++)
    if(m_modules[i]->type()==type)
	    {
        ret=m_modules[i];
		break;
	    }

return ret;
}


void WLDevice::readSlot()
{
QMutexLocker locker(&InputDataMutex);

//qDebug()<<"readSlot";

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

   if(HA==m_HA&&port==UDPPORT)
     {
     QByteArray byteArray(bufData,n);
     //qDebug()<<"n"<<n;
     if(n==1)
     {
    // qDebug()<<"Ack"<<(quint8)byteArray[0]<<m_countTxPacket;
     if(Flags.get(fl_waitack))
      {
      if(m_countTxPacket==(quint8)byteArray[0])
         {
         Flags.reset(fl_waitack);
         m_timerEth->stop();

        // QTimer::singleShot(0,this,SLOT(sendData()));
         }
         else
           qDebug()<<"error m_countTxPacket==(quint8)byteArray[0]"<<(m_countTxPacket==(quint8)byteArray[0]);
      }
     }
     else if(n>1)
        {
        // qDebug()<<"no Ack";
        //m_udpSocket.writeDatagram(byteArray.data(),1,m_HA,UDPPORT);
         m_udpSocket.write(byteArray.data(),1);
        if(m_countRxPacket!=(quint8)byteArray[0])
          {
          m_countRxPacket=(quint8)byteArray[0];

          byteArray=byteArray.mid(1);

          quint16 i=0;

          while(1)
          {
          if((i>byteArray.size())||((quint8)byteArray[i]==0))
            {
            qDebug()<<"error pack";
            break;
            }

          i+=(quint8)byteArray[i];

          if(i==byteArray.size())
            {
            inBuf+=byteArray;
            decodeInputData();

            //qDebug()<<"decodeInputData";
            break;
            }
          }


          }
        }

     }
   }
 }
}

void WLDevice::decodeInputData()
{

quint8 ui1,ui2,ui3;
quint16 ui16;

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

if(inBuf.size()<size)
{
break;
}

//qDebug()<<"size"<<size<<getPortName();

if(size==0)
{
qDebug()<<"size==0 !!!";
inBuf.clear();
break;
}

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
                                           if(m_modules[i]->type()==index)
										     {
                                             Q_ASSERT(m_modules[i]->type()==index);
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

                                       QStringList List=m_prop.split(".");

                                       setNameDevice(List.takeFirst());
                                       m_typeFW=List.takeFirst();

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


                                       if(!Stream.atEnd()){
                                           Stream>>ui16;
                                           setVersionProtocol(ui16);
                                           }else {
                                           setVersionProtocol(0);
                                           }
                                       break;

                  case sendDev_status: Stream>>ui1;

                                       if(status==DEVICE_connect
                                           &&ui1!=DEVICE_connect)   emit sendMessage(getNameDevice(),"detect reset controller!!!",-1);

                                       if(ui1!=status)//забивает статус
                                          emit changedStatus(status=static_cast<statusDevice>(ui1));

                                       break;

                   case typeMFW:  if(getModule((typeModule)ui1)==nullptr) //oldFW
									     {
									     createModule((typeModule)ui1);										 
									     };

                                    emit changedProp(m_prop);

                                    setReady(true);

						            break;
				   }
				   break;
 default: for(int i=0;i<m_modules.size();i++)
               if(m_modules[i]->type()==ui1)
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
case QSerialPort::DeviceNotFoundError:if(getModuleConnect())
                                         {
                                         if(!getModuleConnect()->isEnableHeart())
                                            {
                                            sendMessage(getNameDevice(),"QSerialPort::DeviceNotFoundError",0);
                                            closeConnect();
                                            }
                                         }
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
  connect(MConnect,&WLModuleConnect::backupConnect,this,&WLDevice::backup);

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
  connect(MConnect,&WLModuleConnect::backupConnect,this,&WLDevice::update);

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
bool add=getUID96().isEmpty();
		
qDebug()<<"readXMLData Device";

if(getNameDevice()==stream.name()
 ||getNameDevice().isEmpty())	
{
setNameDevice(stream.name().toString());
/*
if(!stream.attributes().value("VCP").isEmpty())
         initSerialPort(stream.attributes().value("VCP").toString());

if(!stream.attributes().value("IP").isEmpty())
         initUdpSocket(QHostAddress(stream.attributes().value("IP").toString()));
*/
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

void WLDevice::setVersionProtocol(quint16 _ver)
{
m_versionProtocol=_ver;

if(!isValidProtocol()) sendMessage(getNameDevice(),tr("no valid protol (update firmware)"),-1);

emit changedVersionProtocol(m_versionProtocol);
}


void WLDevice::clearBuf()
{
QMutexLocker locker0(&OutDataMutex);
QMutexLocker locker1(&InputDataMutex);

outBuf.clear();
inBuf.clear();
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

