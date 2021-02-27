#include "wlmoduleplanner.h"

WLModulePlanner::WLModulePlanner(QObject *parent)
	: WLModule(parent)
{
setType(typeMPlanner);

m_sizeBuf=0;
m_free=0;
m_status=MPLANNER_stop;
Flags.set(PLF_empty);
m_curIdElementBuf=0;
m_lastIndexElementBuf=0;
m_countAddElement=0;
m_smoothAng=0;
}

WLModulePlanner::~WLModulePlanner()
{

}

quint8 WLModulePlanner::getISOut() const
{
    return m_iSout;
}

typeElement WLModulePlanner::getTypeSOut() const
{
    return m_typeSOut;
}

quint32 WLModulePlanner::getCountAddElement() const
{
    return m_countAddElement;
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

bool WLModulePlanner::setElementSOut(typeElement telement,quint8 i)
{
if(telement==typeElement::typeEOutPWM
 ||telement==typeElement::typeEAOutput)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMPlanner<<(quint8)comPlanner_setOutElementSOut<<(quint8)telement<<i;

emit sendCommand(data);

m_typeSOut=telement;
m_iSout=i;

return true;
}

return false;
}

bool WLModulePlanner::resetElementSOut()
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMPlanner<<(quint8)comPlanner_resetOutElementSOut;

emit sendCommand(data);

m_typeSOut=typeEEmpty;
m_iSout=0;

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
/*
qDebug()<<"index"<<m_lastIndexElementBuf<<m_free;
qDebug()<<"addBufULine en:"<<midPos[0]<<midPos[1]<<midPos[2]<<_id;
qDebug()<<"addBufULine en:"<<endPos[0]<<endPos[1]<<endPos[2]<<"S:"<<S<<"F:"<<Fmov;
*/
m_free--;
//emit ChangedFreeBuf(getFreeBuf());

m_lastIndexElementBuf++;

Flags.reset(PLF_empty);

emit sendCommand(data);

m_countAddElement++;
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

//ebug()<<"index"<<m_lastIndexElementBuf<<m_free;
qDebug()<<"addBufLine3D en:"<<endPos[0]<<endPos[1]<<endPos[2]<<endPos[3]<<"i:"<<_id<<"S:"<<S<<"F:"<<Fmov;
m_free--;
//emit ChangedFreeBuf(getFreeBuf());

m_lastIndexElementBuf++;

Flags.reset(PLF_empty);

emit sendCommand(data);

m_countAddElement++;

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

/*
qDebug()<<"addBufCirc3D"<<mask<<"S:"<<S<<"F:"<<Fmov<<indexs[0]<<indexs[1]<<indexs[2];
qDebug()<<"ePos"<<endPos[0]<<endPos[1]<<endPos[2];
qDebug()<<"cPos"<<cenPosIJ[0]<<cenPosIJ[1];
*/
m_free--;
//emit ChangedFreeBuf(getFreeBuf());

m_lastIndexElementBuf++;

Flags.reset(PLF_empty);

emit sendCommand(data);

m_countAddElement++;

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

m_countAddElement=0;

return true;
}

bool WLModulePlanner::stopMov()
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMPlanner<<(quint8)comPlanner_stop;

m_lastIndexElementBuf=0;

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

emit sendCommand(data);

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

bool WLModulePlanner::setKFpause(float _F)
{
if((0.0f<_F)&&(_F<=1.0f))
{
m_KFpause=_F;

QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMPlanner<<(quint8)comPlanner_setKFpause<<m_KFpause;

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
stream.writeAttribute("KFpause",QString::number(getKFpause()));
stream.writeAttribute("SOut",QString::number(getTypeSOut())
                        +","+QString::number(getISOut()));
}

void WLModulePlanner::readXMLData(QXmlStreamReader &stream)
{
if(!stream.attributes().value("SmoothAngGr").isEmpty()) 
	 setSmoothAng(stream.attributes().value("SmoothAngGr").toString().toFloat());

if(!stream.attributes().value("KFpause").isEmpty())
     setKFpause(stream.attributes().value("KFpause").toString().toFloat());

if(!stream.attributes().value("SOut").isEmpty())
   {
   QStringList list=stream.attributes().value("SOut").toString().split(",");

   if(list.size()==2)
     {
     setElementSOut(static_cast<typeElement>(list.at(0).toUShort())
                   ,(quint8)list.at(1).toUShort());
     }
   }
}

void  WLModulePlanner::readCommand(QByteArray Data)
{
quint8 index,ui1,ui2,ui3,ui4;
quint32 ui32;
float f1,f2;

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
                         Stream>>ui2;//lastIndex uint8_t
                         Stream>>ui3;//status
 					     Stream>>ui4;//flags
						 Stream>>ui32;									
                         Stream>>f1;//k element complete
                         Stream>>f2;//Star

                        emit changedSOut(f2);

                        if(m_lastIndexElementBuf==ui2)
                             {
                             m_curIdElementBuf=ui32;
                             emit changedCurIElement(m_curIdElementBuf);

                             Flags.m_Data=ui4;

                             if(m_status!=(statusPlanner)(ui3))
                                 {
                                 emit changedStatus(m_status=(statusPlanner)(ui3));
                                 }

                             emit changedFree(m_free=ui1);                            
                             }
                           break;
								
	case  sendModule_prop: Stream>>ui1; 
                           m_sizeBuf=ui1;
                           update();
                           break;
	case sendModule_error:   
				                  Stream>>ui1;  //Error
								  Stream>>index;
                                  qDebug()<<"MPlanner err"<<ui1<<index;
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
