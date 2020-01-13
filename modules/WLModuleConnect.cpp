#include "WLModuleConnect.h"

WLModuleConnect::WLModuleConnect(QObject *parent)
	: WLModule(parent)
{
setTypeModule(typeMConnect);

timeoutConnect_ms=1000;
timeHeart_ms=250;

conOk=0;

timerHeart = new QTimer;
timerHeart->setSingleShot(true);
connect(timerHeart,SIGNAL(timeout()),this,SLOT(setTimeoutConnect()));

}

WLModuleConnect::~WLModuleConnect()
{
    delete timerHeart;
}

bool WLModuleConnect::setTimersConnect(quint16 timeout_ms, quint16 heart_ms)
{
timeout_ms = timeout_ms<500 ? 500: (timeout_ms>10000? 10000: timeout_ms);
heart_ms = heart_ms<50 ? 50: (heart_ms>1000? 1000: heart_ms);

if(timeout_ms<=heart_ms) return false;

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
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMConnect<<(quint8)comMCon_setEnableHeart<<(quint8)enable;

qDebug()<<"setEnableHeart"<<enable;

emit sendCommand(data);
return true;
}




void WLModuleConnect::setTimeoutConnect()
{
emit sendMessage("WLModuleConnect","timeout "+QString::number(timeoutConnect_ms),0);
emit timeoutConnect();

conOk=false;
}

void WLModuleConnect::restartHeart()
{
timerHeart->start(timeoutConnect_ms);

if(!conOk) emit backupConnect();

sendHeart();
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
quint8 index,ui1,ui2,ui3,ui4;
quint16 ui16;
quint32 ui32;
float f1;

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
