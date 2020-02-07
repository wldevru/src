#include "WLModuleFW.h"
//#include "wldefine.h"
#include <QDebug>
#include <QTime>

WLModuleFW::WLModuleFW()
{
setTypeModule(typeMFW);

status=MFW_standby;
sizeFW=0;
sizeBlockFW=0;
prop.clear();

}
 
WLModuleFW::~WLModuleFW()
{

}


void WLModuleFW::readCommand(QByteArray Data)
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
case _sendFW:     Stream>>ui1;//status
	              //Stream>>ui16; 
	
				  for(int i=0;i<sizeBlockFW;i++)
				   {
				   Stream>>ui1;   
				   FWBuf+=ui1; 

				   //if(FWBuf.size()<=32)  
                   //qDebug("%x",ui1);
				   }
			
				  if(status==MFW_read) 
					  {					  
					  if(sizeFW!=0) emit ChangedProgress(100*FWBuf.size()/sizeFW);			
					  readFW();
				      }
                   break;		

 case _sendSignalMFW:
	              Stream>>ui1;
	              switch(ui1)
				  {
                  case _sigEndReadFW:    emit ChangedEndReadFW(); break;
				  case _sigEndWriteFW:   emit ChangedEndWriteFW();break;
				  case _sigChgStatus_u8: Stream>>ui1;
					                     status=(statusMFW)ui1;
										 emit ChangedActiv(status!=MFW_standby);
										 if(status==MFW_standby) emit ChangedProgress(0);
									     break;

                  case _sigCallNextDataFW: if(status==MFW_write) 
										    {
											writeFW();																
										    }
										   break;
				  }
	
	              break;
case _sendPropMFW: Stream>>sizeBlockFW;
	               Stream>>sizeFW;
	               break;
}

}

bool  WLModuleFW::startWriteFW(QByteArray BA,quint8 mask)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

FWBuf=BA;
indexBuf=0;

Stream<<(quint8)typeMFW<<(quint8)_startWriteFW<<mask;
//qDebug()<<"Call Pos"<<i;
emit ChangedProgress(0);
emit sendCommand(data);

writeFW();

return true;
}


bool WLModuleFW::startReadFW(quint8 mask)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMFW<<(quint8)_startReadFW<<mask;
//qDebug()<<"Call Pos"<<i;
FWBuf.clear();

emit ChangedProgress(0);
emit sendCommand(data);

readFW();

return true;
}


void WLModuleFW::callProp()
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMFW<<(quint8)_getPropMFW;
//qDebug()<<"Call Pos"<<i;

emit sendCommand(data);
}

bool WLModuleFW::readFW()
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMFW<<(quint8)_readFW;

emit sendCommand(data);
return true;
}

bool WLModuleFW::writeFW()
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

if((indexBuf)<FWBuf.size())
{
Stream<<(quint8)typeMFW<<(quint8)_writeFW;

for(int i=0;i<sizeBlockFW;i++)
   Stream<<(quint8)FWBuf[indexBuf+i];
 
indexBuf+=sizeBlockFW;
//qDebug()<<"Call Pos"<<i;
if(sizeFW!=0) emit ChangedProgress(100*(indexBuf+1)/sizeFW);
}
else
	qDebug()<<"outSize";

emit sendCommand(data);
return true;
}

void WLModuleFW::reset()
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMFW<<(quint8)_resetMFW;
//qDebug()<<"Call Pos"<<i;

emit sendCommand(data);
}
