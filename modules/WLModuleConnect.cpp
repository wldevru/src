#include "WLModuleConnect.h"

WLModuleConnect::WLModuleConnect(QObject *parent)
	: WLModule(parent)
{
setTypeModule(typeMConnect);


conOk=0;

timerHeart = new QTimer;
timerHeart->setSingleShot(true);
connect(timerHeart,SIGNAL(timeout()),this,SLOT(setTimeoutConnect()));

}

WLModuleConnect::~WLModuleConnect()
{
delete timerHeart;
}



void WLModuleConnect::setTimeoutConnect()
{
emit sendMessage("WLModuleConnect","timeout",0);		
emit timeoutConnect();

conOk=false;
}

void WLModuleConnect::restartHeart()
{
timerHeart->start(1000);
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
//stream.writeAttribute("SmoothAngGr",QString::number(getSmoothAng()));
}

void WLModuleConnect::readXMLData(QXmlStreamReader &stream)
{
//if(!stream.attributes().value("SmoothAngGr").isEmpty()) 
//	 setSmoothAng(stream.attributes().value("SmoothAngGr").toString().toFloat());
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
