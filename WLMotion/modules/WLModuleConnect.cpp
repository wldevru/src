#include "wlmoduleconnect.h"

WLModuleConnect::WLModuleConnect(QObject *parent)
	: WLModule(parent)
{
setType(typeMConnect);

timeoutConnect_ms=5000;
timeHeart_ms=0;

conOk=false;

timerHeart = new QTimer;
timerHeart->setSingleShot(true);
connect(timerHeart,SIGNAL(timeout()),this,SLOT(setTimeoutHeart()));

timerConnect = new QTimer;
timerConnect->setSingleShot(true);
connect(timerConnect,SIGNAL(timeout()),this,SLOT(setTimeoutConnect()));
}

WLModuleConnect::~WLModuleConnect()
{
//setEnableHeart(false);
timerHeart->stop();
timerConnect->stop();

delete timerHeart;
delete timerConnect;
}

bool WLModuleConnect::setTimersConnect(quint16 timeout_ms, quint16 heart_ms)
{
timeout_ms = timeout_ms<10000 ? 10000: (timeout_ms>30000? 30000: timeout_ms);
heart_ms= (heart_ms>5000? 5000: heart_ms);

if(timeout_ms<heart_ms) return false;

timeoutConnect_ms=timeout_ms;
timeHeart_ms=heart_ms;

QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMConnect<<(quint8)comMCon_setTimers<<timeoutConnect_ms<<timeHeart_ms;

qDebug()<<"setTimersConnect"<<timeout_ms<<heart_ms;

emit sendCommand(data);
return true;
}


bool WLModuleConnect::setEnableHeart(bool enable)
{
if(timeHeart_ms==0) enable=false;

QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMConnect<<(quint8)comMCon_setEnableHeart<<(quint8)enable;

qDebug()<<"setEnableHeart"<<enable;

Flags.set(MCF_enbheart,enable);

if(!enable)
{
timerHeart->stop();
}

emit sendCommand(data);
return true;
}


void WLModuleConnect::setTimeoutConnect()
{
emit sendMessage("WLModuleConnect","timeout connect "+QString::number(timeoutConnect_ms),0);
emit timeoutConnect();

conOk=false;
}

void WLModuleConnect::setTimeoutHeart()
{
emit sendMessage("WLModuleConnect","timeout heart "+QString::number(timeHeart_ms),1);
emit timeoutHeart();

conOk=false;
}

void WLModuleConnect::restartHeart()
{
if(Flags.get(MCF_enbheart))
 {
 timerHeart->start(timeHeart_ms+250);
 
 if(!conOk)
   {
   emit sendMessage("WLModuleConnect","backup connect",1);
   emit backupConnect();
   }
 }

timerConnect->start(timeoutConnect_ms);

conOk=true;
}

void WLModuleConnect::sendHeart()
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMConnect<<(quint8)sigMCon_heart;

conOk=true;

emit sendCommand(data);
}

void WLModuleConnect::writeXMLData(QXmlStreamWriter &stream)
{
stream.writeAttribute("timeoutConnect_ms",QString::number(getTimeoutConnectVal()));
stream.writeAttribute("timeHeart_ms",QString::number(getTimeHeartVal()));
}

void WLModuleConnect::readXMLData(QXmlStreamReader &stream)
{
if(!stream.attributes().value("timeoutConnect_ms").isEmpty()
 &&!stream.attributes().value("timeHeart_ms").isEmpty())
     setTimersConnect(stream.attributes().value("timeoutConnect_ms").toString().toLong()
                     ,stream.attributes().value("timeHeart_ms").toString().toLong());

}


void  WLModuleConnect::readCommand(QByteArray Data)
{
quint8 ui1;

QDataStream Stream(&Data,QIODevice::ReadOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream>>ui1;

switch(ui1)
  {
  case sigMCon_heart:   sendHeart(); break;      
								
  case sendModule_prop: Stream>>sizeInBuf; 
	                    Stream>>sizeOutBuf; 	                     
                        break;
  case sendModule_error:  /* 
				                  Stream>>ui1;  //Error
								  Stream>>index;

								  if(ui1>errorModule_start)
								   {
								   emit sendMessage("WLModulePlanner "+getErrorStr(errorModule,ui1),"",-(int)(ui1));				     
								   }
								  else								   
                                   switch(ui1)
								   {
								    case errorPlanner_waxis:    emit sendMessage("WLMotionPlanner+Axis ","",-(int)(ui1));break;
									case errorPlanner_welement: emit sendMessage("WLMotionPlanner+Elementis"+getErrorStr(errorElementPlanner,index),"",-(int)(ui1));break;
									default:                    emit sendMessage("WLMotionPlanner"+getErrorStr(errorPlanner,index),"",-(int)(ui1));break;                   				       
								   }

                   				  emit ChangedReset();    */              
                   			      break;
								  
 }
				  


}
