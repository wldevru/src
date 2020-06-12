#include "WLModulePlanner.h"

WLModulePlanner::WLModulePlanner(QObject *parent)
	: WLModule(parent)
{
setTypeModule(typeMPlanner);

m_sizeBuf=0;
m_free=0;
status=MPLANNER_stop;
Flags.set(PLF_empty);
curIdElementBuf=0;
lastIndexElementBuf=0;

m_smoothAng=0;
}

WLModulePlanner::~WLModulePlanner()
{

}

void WLModulePlanner::setSizeBuf(int value)
{
    m_sizeBuf = value;
}

void WLModulePlanner::sendGetDataBuf()
{
    QByteArray data;
    QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMPlanner<<(quint8)comPlanner_getDataPlanner;

qDebug()<<"getDataBuf";

emit sendCommand(data);
}

void WLModulePlanner::update()
{    
sendGetDataBuf();
}


bool WLModulePlanner::setIAxisSlave(quint8 *indexsAxis,quint8 size)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMPlanner<<(quint8)comPlanner_setISlaveAxis<<size;

for(int i=0;i<size;i++)
  Stream<<indexsAxis[i];

emit sendCommand(data);

return true;
}

bool WLModulePlanner::setHPause(quint8 enable,qint32 hPause)
{
Flags.set(PLF_usehpause,enable);

m_hPause=hPause;

QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMPlanner<<(quint8)comPlanner_setHPause<<enable<<m_hPause;

emit sendCommand(data);

return true;
}

bool WLModulePlanner::setSOutPWMOut(quint8 i)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMPlanner<<(quint8)comPlanner_setSOutPWMOut<<i;

emit sendCommand(data);

return true;
}

bool WLModulePlanner::setSOutFreqOut(quint8 i)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMPlanner<<(quint8)comPlanner_setSOutFreqOut<<i;

emit sendCommand(data);
return true;
}


bool WLModulePlanner::resetSOutPWMOut()
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMPlanner<<(quint8)comPlanner_resetSOutPWMOut;

emit sendCommand(data);

return true;
}

bool WLModulePlanner::resetSOutFreqOut()
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMPlanner<<(quint8)comPlanner_resetSOutFreqOut;

emit sendCommand(data);
return true;
}

bool WLModulePlanner::setParMov(float Aac,float Ade,float Fst,float Fma)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMPlanner<<(quint8)comPlanner_setMPar<<Aac<<Ade<<Fst<<Fma;

qDebug()<<"setMPar"<<" "<<Aac<<Ade<<Fst<<Fma;;

emit sendCommand(data);
return true;
}


bool WLModulePlanner::addULine(quint8 mask,quint8 size,quint8 indexs[],long endPos[],long midPos[],float S,float Fmov,quint32 _id)
{
QMutexLocker locker(&Mutex);
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMPlanner<<(quint8)comPlanner_addULine<<mask<<size;//<<endPos[0]<<endPos[1]<<endPos[2]<<S<<Fmov   ;

for(int i=0;i<size;i++)
   Stream<<indexs[i]<<(qint32)endPos[i]<<(qint32)midPos[i];

Stream<<S
	  <<Fmov
	  <<_id;

qDebug()<<"index"<<lastIndexElementBuf<<m_free;
qDebug()<<"addBufULine en:"<<midPos[0]<<midPos[1]<<midPos[2]<<_id;
qDebug()<<"addBufULine en:"<<endPos[0]<<endPos[1]<<endPos[2]<<"S:"<<S<<"F:"<<Fmov;

m_free--;
//emit ChangedFreeBuf(getFreeBuf());

lastIndexElementBuf++;

Flags.reset(PLF_empty);

emit sendCommand(data);
return true;
}


bool WLModulePlanner:: addLine(quint8 mask,quint8 size,quint8 indexs[],long endPos[],float S,float Fmov,quint32 _id)
{
QMutexLocker locker(&Mutex);
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMPlanner
      <<(quint8)comPlanner_addLine
      <<mask
      <<size;

for(int i=0;i<size;i++)
   Stream<<indexs[i]<<(qint32)endPos[i];

Stream<<S
	  <<Fmov
	  <<_id;

qDebug()<<"index"<<lastIndexElementBuf<<m_free;
qDebug()<<"addBufLine3D en:"<<endPos[0]<<endPos[1]<<endPos[2]<<"i:"<<_id<<"S:"<<S<<"F:"<<Fmov;

m_free--;
//emit ChangedFreeBuf(getFreeBuf());

lastIndexElementBuf++;

Flags.reset(PLF_empty);

emit sendCommand(data);
return true;
}

bool WLModulePlanner::addCirc(quint8 mask,quint8 size,quint8 indexs[],long endPos[],long cenPosIJ[],float S,float Fmov,quint32 _id)

{
QMutexLocker locker(&Mutex);
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);


Stream<<(quint8)typeMPlanner
      <<(quint8)comPlanner_addCirc
	  <<mask
      <<size;

for(quint8 i=0;i<size;i++)
   Stream<<indexs[i]<<(qint32)endPos[i];

Stream<<(qint32)cenPosIJ[0]<<(qint32)cenPosIJ[1];

Stream<<S
	  <<Fmov
	  <<_id;


qDebug()<<"addBufCirc3D"<<mask<<"S:"<<S<<"F:"<<Fmov<<indexs[0]<<indexs[1]<<indexs[2];
qDebug()<<"ePos"<<endPos[0]<<endPos[1]<<endPos[2];
qDebug()<<"cPos"<<cenPosIJ[0]<<cenPosIJ[1];

m_free--;
//emit ChangedFreeBuf(getFreeBuf());

lastIndexElementBuf++;

Flags.reset(PLF_empty);

emit sendCommand(data);
return true;
}


bool WLModulePlanner::startMov()
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMPlanner<<(quint8)comPlanner_start;

emit sendCommand(data);
return true;
}

bool WLModulePlanner::stopMov()
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMPlanner<<(quint8)comPlanner_stop;

lastIndexElementBuf=0;

emit sendCommand(data);
return true;
}

bool WLModulePlanner::pauseMov()
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMPlanner<<(quint8)comPlanner_pause;

qDebug()<<"pauseMov0";
emit sendCommand(data);
qDebug()<<"pauseMov1";
return true;
}

bool WLModulePlanner::setKF(float _KF)
{
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMPlanner<<(quint8)comPlanner_setKF<<_KF;

emit sendCommand(data);
return true;
}
}

bool WLModulePlanner::setSmoothAng(float ang_gr)
{
if(0<=ang_gr&&ang_gr<=30)  
{
m_smoothAng=ang_gr;

QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMPlanner<<(quint8)comPlanner_setSmoothAng<<ang_gr;

emit sendCommand(data);
return true;
}
else
return false;
}

bool WLModulePlanner::setSOut(float s)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

qDebug()<<"setSOutBuf"<<s;

Stream<<(quint8)typeMPlanner<<(quint8)comPlanner_setSOut<<s;

emit sendCommand(data);
return true;
}

bool WLModulePlanner::setKSOut(float k)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

qDebug()<<"setKSOutBuf"<<k;

Stream<<(quint8)typeMPlanner<<(quint8)comPlanner_setKSOut<<k;

emit sendCommand(data);
return true;
}

bool WLModulePlanner::setEnableSOut(quint8 enable)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMPlanner<<(quint8)comPlanner_enableSOut<<enable;

emit sendCommand(data);
return true;
}


void WLModulePlanner::writeXMLData(QXmlStreamWriter &stream)
{
stream.writeAttribute("SmoothAngGr",QString::number(getSmoothAng()));
}

void WLModulePlanner::readXMLData(QXmlStreamReader &stream)
{
if(!stream.attributes().value("SmoothAngGr").isEmpty()) 
	 setSmoothAng(stream.attributes().value("SmoothAngGr").toString().toFloat());
}

void  WLModulePlanner::readCommand(QByteArray Data)
{
quint8 index,ui1,ui2,ui3,ui4;
quint32 ui32;
float f1;

QDataStream Stream(&Data,QIODevice::ReadOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Mutex.lock();

 qDebug()<<"readCommand MPlanner"<<Data.size();

Stream>>ui1;

switch(ui1)
  {
   case sendPlanner_data:
		                 Stream>>ui1;//size
                         Stream>>ui2;//lastIndex
                         Stream>>ui3;//status
 					     Stream>>ui4;//flags
						 Stream>>ui32;									
						 Stream>>f1;//Sout
						//Stream>>f2;//Ftar

                         qDebug()<<"sendMBSize"<<lastIndexElementBuf<<ui32<<ui1<<ui2;
			                  
						//if(flagsBuf&MBF_reset) emit ChangedResetBuf();
                        emit changedSOut(f1);

                        if(lastIndexElementBuf==ui2)
                             {
                             curIdElementBuf=ui32;

                             Flags.m_Data=ui4;
                             qDebug()<<"sendMBSize0";
                             if(status!=(statusPlanner)(ui3))
                                 {
                                 qDebug()<<"sendMBSize1";
                                 emit changedStatus(status=(statusPlanner)(ui3));
                                 }
                            //if(freeBuf!=ui1)
                             emit changedFree(m_free=ui1);
                             qDebug()<<"sendMBSize2";
                             }
                           break;
								
	case  sendModule_prop: Stream>>ui1; 
                           m_sizeBuf=ui1;
                           update();
                           break;
	case sendModule_error:   
				                  Stream>>ui1;  //Error
								  Stream>>index;

                                  if(ui1>startIndexErrorModule)
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

                                  emit reset();
                   			      break;
								  
    case sendPlanner_signal:    Stream>>ui1;
				                  /*
					              switch(ui1)
								  {
								  case _sigChangedSOut_f32: Stream>>f1; emit  ChangedSOut(f1); break;								  								  
								  }
								  */
					
					              break;
			   }
				  
Mutex.unlock();

}
