#include "WLFWDevice.h"
//#include "wldefine.h"
#include <QDebug>


#include <QtGui/QApplication>

WLFWDevice::WLFWDevice()
{
//connect(this,SIGNAL(startSend(QByteArray)),SLOT(sendData(QByteArray)),Qt::QueuedConnection);
status=MFW_standby;
sizeFW=0;
prop.clear();

connect(this,SIGNAL(readyRead()),SLOT(readSlot()));
}
 
WLFWDevice::~WLFWDevice()
{
close();
}


void WLFWDevice::startSend(QByteArray data)
{
QMutexLocker locker(&OutDataMutex); 
outData+=data.prepend(data.size()+1);

QTimer::singleShot(0,this,SLOT(sendData()));
}


void WLFWDevice::sendData()
{
QMutexLocker locker0(&SendOutMutex);
QMutexLocker locker1(&OutDataMutex); 
while(!outData.isEmpty())
{
//qDebug()<<"sendData";
if(outData.size()>64)
  {
  if(write(outData.mid(0,64))==64)	  
      outData=outData.remove(0,64);
  else
      {
	  qDebug()<<"no sendData";	  
	  outData.clear();
      }
  }
else
  {
  if(write(outData)==outData.size())
	  outData.clear();
  else
      {
      qDebug()<<"no sendData";	  
	  outData.clear();
      }
  }
}

};

bool WLFWDevice::Init(QString portName)
{
if(isOpen()) close();

emit ChangedConnect(false);

setPortName(portName);
prop.clear();
qDebug()<<"Init WLFWDevice "<<portName;

#ifndef enableDemo
if(!open(QIODevice::ReadWrite)) 
	{
	sendMessage("WLFWDevice:","no device ("+portName+")",0); 
	return false;    
    }
else
    {	
	getProp();	
	getPropMFW();	
	qDebug()<<"Ok";
    }
#endif

return true;
}

void WLFWDevice::readSlot()
{
QMutexLocker locker(&InputDataMutex);
//QMutexLocker locker1(&BufMutex);

inBuf+=readAll();

quint32 ui32;
qint32 *posProbe;
quint8 com,ui1,ui2,ui3,ui4;
quint16 ui16;
qint32 l1;
quint8 index;
float f1;
QChar buf[256];

//if(inBuf.size()>64) 
//	qDebug()<<"size Data > 64 ="<<inBuf.size();;	

//qDebug()<<"size Data ="<<inBuf.size();;
/*
outBuf[j++]=            (i<<4)|sendA; //1
outBuf[j++]=(Axis[i].error<<4)|Axis[i].status;
outBuf[j++]= Axis[i].flags;	
memcpy(outBuf+j,&(Axis[i].posNow),4);	j+=4;//		
memcpy(outBuf+j,&(Axis[i].Vnow),4);	  j+=4;//		
*/

int curi=0;
quint8 size;

QByteArray Data;
/*
for(int i=0;i<inBuf.size();i++)
qDebug()<<"stack"<<i<<((quint8)inBuf[i]);
*/
//qDebug()<<"readData"<<size;

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

switch(ui1)
 {
 case typeMFW:       Stream>>ui1;
	                switch(ui1)
					{
                    case _sendFW:     Stream>>ui1;//status
						              //Stream>>ui16; 
						
									  for(int i=0;i<sizeBlockFW;i++)
									   {
									   Stream>>ui1;   
									   FWBuf+=ui1; 

									   if(FWBuf.size()<=32)  qDebug("%x",ui1);
									   }
								
									  if(status==MFW_read) 
										  {
										  if(sizeFW!=0) emit ChangedProgress(100*FWBuf.size()/sizeFW);

										  readFW();
									      }
                                      break;		

                   case _sendSignalMFW:Stream>>ui1;
						              switch(ui1)
									  {
									  case _sigEndReadFW:    emit ChangedEndReadFW();break;
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
									  //case _sigChgSizeFW_ui32: Stream>>ui32; sizeFW=ui32;
										//                       break;
									  }
						
						              break;
					case _sendPropMFW: Stream>>sizeBlockFW;
						               Stream>>sizeFW;
						               break;
					}
					break;

 case typeMainLoop:Stream>>ui1;
	               switch(ui1)
				    { 
				    case _sendProp:   for(int i=0;i<(size-3);i++) 
									   {
						               Stream>>ui1;//f	
									   buf[i]=ui1;
									   }
									  prop=QString(buf,size-3);
						              
                    	              emit ChangedProp(prop);
									  emit ChangedConnect(true);
                    			      break;
				   }
				   break;

 default: break;

  }

if(inBuf.isEmpty()) break;
}
}

bool  WLFWDevice::startWriteFW(QByteArray BA,quint8 mask)
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
startSend(data);
return true;
}


bool WLFWDevice::startReadFW(quint8 mask)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMFW<<(quint8)_startReadFW<<mask;
//qDebug()<<"Call Pos"<<i;
FWBuf.clear();

emit ChangedProgress(0);
startSend(data);
return true;
}

bool WLFWDevice::getProp()
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMainLoop<<(quint8)_getProp;
//qDebug()<<"Call Pos"<<i;

startSend(data);
return true;
}

bool WLFWDevice::getPropMFW()
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMFW<<(quint8)_getPropMFW;
//qDebug()<<"Call Pos"<<i;

startSend(data);
return true;
}

bool WLFWDevice::readFW()
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMFW<<(quint8)_readFW;
//qDebug()<<"Call Pos"<<i;

startSend(data);
return true;
}

bool WLFWDevice::writeFW()
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

startSend(data);
return true;
}

bool WLFWDevice::resetFW()
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMFW<<(quint8)_resetMFW;
//qDebug()<<"Call Pos"<<i;

startSend(data);
return true;
}




void WLFWDevice::readXMLData(QXmlStreamReader &stream)
{
QString port;
int iSize=0,oSize=0;
if(!stream.attributes().value("VCP").isEmpty()) 
		 port=stream.attributes().value("VCP").toString();
	 else
		 port="Com5";

setPortName(port);

//if(!stream.attributes().value("enableinvInput").isEmpty())  setInputInvStr(stream.attributes().value("invInput").toString());

//if(!stream.attributes().value("invInput").isEmpty())  setInputInvStr(stream.attributes().value("invInput").toString());
//if(!stream.attributes().value("invOutput").isEmpty()) setOutputInvStr(stream.attributes().value("invOutput").toString());

}

void WLFWDevice::writeXMLData(QXmlStreamWriter &stream)
{
stream.writeAttribute("VCP",portName());

//stream.writeAttribute("invInput",getInputInvStr());
//stream.writeAttribute("invOutput",getOutputInvStr());
}