#include "WLAXIS.h"

WLAxis::WLAxis(QObject *parent) 
	:WLElement(parent)
{
setTypeElement(typeEAxis);

nowPosition=0;
maxPosition=INT32_MAX;
minPosition=INT32_MIN;
homePosition=0;

status=AXIS_stop;
mode=AXIS_standby;

orgSize=1;

kSTCurve=0;
delaySCurve=0;
kGear=1;

Freq=0;
latchPos2=0;
latchPos3=0;

error=0;

typePulse=AXIS_pulse_empty;

homePosition=0;
orgSize=100;

ModuleIOPut=NULL;

inORG=&WLIOPut::In0;
inPEL=&WLIOPut::In0;
inMEL=&WLIOPut::In0;
inALM=&WLIOPut::In0;
outRALM=&WLIOPut::Out;
outENB=&WLIOPut::Out;

actIn[AXIS_inALM]=AXIS_actEmgStop;
actIn[AXIS_inPEL]=AXIS_actEmgStop;
actIn[AXIS_inMEL]=AXIS_actEmgStop;
}

WLAxis::~WLAxis()
{
}


WLIOPut*  WLAxis::getInput(typeInputAxis type)
{
WLIOPut *ret=NULL;
switch(type)
{
case AXIS_inORG: ret=inORG;break;
case AXIS_inALM: ret=inALM;break;
case AXIS_inPEL: ret=inPEL;break;
case AXIS_inMEL: ret=inMEL;break;

default: ret=&WLIOPut::In0;
}

return ret;
}

WLIOPut*  WLAxis::getOutput(typeOutputAxis type)
{
WLIOPut *ret=NULL;
switch(type)
{
case AXIS_outRALM: ret=outRALM;break;
case AXIS_outENB:  ret=outENB; break;

default: ret=&WLIOPut::Out;
}
return ret;
}

void WLAxis::init(WLModuleIOPut *_ModuleIOPut,quint8 index)
{
ModuleIOPut=_ModuleIOPut;
setIndex(index);
}

void  WLAxis::setInALM(int index)
{
inALM->removeComment("inALM"+QString::number(getIndex()));
disconnect(inALM,SIGNAL(changed(bool)),this,SIGNAL(ChangedInALM(bool)));
inALM=ModuleIOPut->getInputV(index);
inALM->addComment("inALM"+QString::number(getIndex()));

setInput(AXIS_inALM,index);

connect(inALM,SIGNAL(changed(bool)),SIGNAL(ChangedInALM(bool)),Qt::QueuedConnection);
}

void  WLAxis::setInORG(int index)
{
inORG->removeComment("inORG"+QString::number(getIndex()));
inORG=ModuleIOPut->getInputV(index);
inORG->addComment("inORG"+QString::number(getIndex()));

setInput(AXIS_inORG,index);
}


void  WLAxis::setInPEL(int index)
{
inPEL->removeComment("inPEL"+QString::number(getIndex()));
inPEL=ModuleIOPut->getInputV(index);
inPEL->addComment("inPEL"+QString::number(getIndex()));

setInput(AXIS_inPEL,index);
}

void  WLAxis::setInMEL(int index)
{
inMEL->removeComment("inMEL"+QString::number(getIndex()));
inMEL=ModuleIOPut->getInputV(index);
inMEL->addComment("inMEL"+QString::number(getIndex()));

setInput(AXIS_inMEL,index);
}


void  WLAxis::setOutRALM(int index)
{
outRALM->removeComment("outRALM"+QString::number(getIndex()));
outRALM=ModuleIOPut->getOutputV(index);
outRALM->addComment("outRALM"+QString::number(getIndex()));
}


void  WLAxis::setOutENB(int index)
{
outENB->removeComment("outENB"+QString::number(getIndex()));
outENB=ModuleIOPut->getOutputV(index);
outENB->addComment("outENB"+QString::number(getIndex()));

setOutput(AXIS_outENB,index);
}


bool WLAxis::setTypePulse(typePulseAxis type,quint8 _SDinv)
{
typePulse=type;
outSDinv=_SDinv;

QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comAxis_setTypePulse<<getIndex()<<((((quint8)type)<<4)|outSDinv);

emit sendCommand(data);
return true;
}

bool WLAxis::setKSTCurve(float _kSTCurve)
{
if(0<=_kSTCurve&&_kSTCurve<=1)
{
kSTCurve=_kSTCurve;

QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comAxis_setKSTCurve<<getIndex()<<kSTCurve;

emit sendCommand(data);
return true;
}
else
return false;
}

bool WLAxis::setDelaySCurve(float _delaySCurve)
{
if(_delaySCurve>=0) 
{
delaySCurve=_delaySCurve;

QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comAxis_setDelaySCurve<<getIndex()<<delaySCurve;

emit sendCommand(data);
return true;
}
else
 return false;
}

bool WLAxis::setKGear(float _kGear)
{
if(_kGear>0)
{
kGear=_kGear;

QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comAxis_setKGear<<getIndex()<<kGear;

emit sendCommand(data);
return true;
}
else
	return false;
}

bool WLAxis::setEnable(bool enable)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comAxis_setEnable<<getIndex()<<(quint8)enable;

emit sendCommand(data);
return true;
}

bool WLAxis::setInput(typeInputAxis type,quint8 num)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comAxis_setInput<<getIndex()<<(quint8)type<<num;

emit sendCommand(data);
return true;
}

bool WLAxis::setOutput(typeOutputAxis type,quint8 num)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comAxis_setOutput<<getIndex()<<(quint8)type<<num;

emit sendCommand(data);
return true;
}

bool WLAxis::setDisableLimit(bool dis)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comAxis_setDisableLimit<<getIndex()<<(quint8)dis;

Flags.set(AF_disableLimit);

emit sendCommand(data);
return true;
}

bool WLAxis::setLatchSrc(quint8 num)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comAxis_setLatchSrc<<getIndex()<<num;

emit sendCommand(data);
return true;
}

bool WLAxis::setActIn(typeInputAxis type,typeActIOPutAxis typeAct)
{
actIn[type]=typeAct;

QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comAxis_setActIn<<getIndex()<<(quint8)type<<(quint8)typeAct;

emit sendCommand(data);
return true;
}

bool WLAxis::sendGetData()
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comAxis_getData<<getIndex();

emit sendCommand(data);
return true;
}

bool WLAxis::setParMov(float Aac,float Ade,float Fst,float Fma)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comAxis_setParMov<<getIndex()<<Aac<<Ade<<Fst<<Fma;

emit sendCommand(data);
return true;
}

bool WLAxis::setParMovPlus(float Aac,float Ade,float Fst,float Fma)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comAxis_setParMovPlus<<getIndex()<<Aac<<Ade<<Fst<<Fma;

emit sendCommand(data);
return true;
}

bool WLAxis::setParMovMinus(float Aac,float Ade,float Fst,float Fma)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comAxis_setParMovMinus<<getIndex()<<Aac<<Ade<<Fst<<Fma;

emit sendCommand(data);
return true;
}

bool WLAxis::mov(quint8 mask,qint32 Dist,float Fmov)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comAxis_mov<<mask<<getIndex()<<Dist<<Fmov;

emit sendCommand(data);
return true;
}


bool WLAxis::acc()
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comAxis_acc<<(quint8)getIndex();

emit sendCommand(data);
return true;
}

bool WLAxis::dec()
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comAxis_dec<<(quint8)getIndex();

emit sendCommand(data);
return true;
}

bool WLAxis::sdStop()
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comAxis_sdStop<<(quint8)getIndex();

emit sendCommand(data);
return true;
}

bool WLAxis::setNewF(float newF)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comAxis_newF<<(quint8)getIndex()<<newF;

emit sendCommand(data);
return true;
}

bool WLAxis::emgStop()
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

qDebug()<<data.size();

Stream<<(quint8)comAxis_emgStop<<(quint8)getIndex();

emit sendCommand(data);
return true;
}

bool WLAxis::addSyhData(qint32 pos)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comAxis_addSyhData<<(quint8)getIndex()<<pos;

emit sendCommand(data);
return true;
}

bool WLAxis::setPos(qint32 pos)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comAxis_setPos<<(quint8)getIndex()<<pos;

emit sendCommand(data);
return true;
}

bool WLAxis::setMinMaxPos(qint32 minpos,qint32 maxpos)
{
if(maxpos>minpos)
{
maxPosition=maxpos;
minPosition=minpos;

QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comAxis_setMinMaxPos<<(quint8)getIndex()<<minPosition<<maxPosition;

emit sendCommand(data);
return true;
}
else
	return false;
}

bool WLAxis::setKF(float _KFA)
{
if(_KFA>0)
 {
 QByteArray data;
 QDataStream Stream(&data,QIODevice::WriteOnly);
 
 Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
 Stream.setByteOrder(QDataStream::LittleEndian);

 Stream<<(quint8)comAxis_setKF<<(quint8)getIndex()<<_KFA;
 
 emit sendCommand(data);
 return true;
 }
return false;
}

void WLAxis::reset()
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comAxis_reset<<(quint8)getIndex();

emit sendCommand(data);
}

void WLAxis::setData(quint8 statusMode,quint8 _flag,qint32 Pos,float F)
{
Flags.m_Data=_flag;

modeAxis nmode=(modeAxis)(statusMode&0x0F);
statusAxis nstatus=(statusAxis)(statusMode>>4);     

if(Flags.get(AF_update)||mode!=nmode)       
	                     emit ChangedMode(mode=nmode); 
if(Flags.get(AF_update)||status!=nstatus)   
	                   emit ChangedStatus(status=nstatus); 
if(Flags.get(AF_update)||nowPosition!=Pos)  
	                   emit ChangedPos(nowPosition=Pos);
if(Flags.get(AF_update)||Freq!=F)           
	                   emit ChangedFreq(Freq=F);
}

void WLAxis::readXMLData(QXmlStreamReader &stream)
{
if(!stream.attributes().value("kSTCurve").isEmpty())  	  setKSTCurve(stream.attributes().value("kSTCurve").toString().toFloat());

if(!stream.attributes().value("delaySCurve").isEmpty())   setDelaySCurve(stream.attributes().value("delaySCurve").toString().toFloat());

if(!stream.attributes().value("typePulse").isEmpty()
 &&!stream.attributes().value("outSDinv").isEmpty())  setTypePulse((typePulseAxis)stream.attributes().value("typePulse").toString().toInt()
                                                                                  ,stream.attributes().value("outSDinv").toString().toInt());
                                                    
if(!stream.attributes().value("inORG").isEmpty()) setInORG(stream.attributes().value("inORG").toString().toInt());

if(!stream.attributes().value("inALM").isEmpty()) setInALM(stream.attributes().value("inALM").toString().toInt());
if(!stream.attributes().value("inPEL").isEmpty()) setInPEL(stream.attributes().value("inPEL").toString().toInt());
if(!stream.attributes().value("inMEL").isEmpty()) setInMEL(stream.attributes().value("inMEL").toString().toInt());

if(!stream.attributes().value("actInALM").isEmpty()) setActIn(AXIS_inALM,static_cast<typeActIOPutAxis>(stream.attributes().value("actInALM").toString().toInt()));
if(!stream.attributes().value("actInPEL").isEmpty()) setActIn(AXIS_inPEL,static_cast<typeActIOPutAxis>(stream.attributes().value("actInPEL").toString().toInt()));
if(!stream.attributes().value("actInMEL").isEmpty()) setActIn(AXIS_inMEL,static_cast<typeActIOPutAxis>(stream.attributes().value("actInMEL").toString().toInt()));   

if(!stream.attributes().value("outRALM").isEmpty())	setOutRALM(stream.attributes().value("outRALM").toString().toInt());
if(!stream.attributes().value("outENB").isEmpty())	setOutENB(stream.attributes().value("outENB").toString().toInt());

//if(!stream.attributes().value("invLocalInput").isEmpty())  setInputInvStr(stream.attributes().value("invLocalInput").toString());
//if(!stream.attributes().value("invLocalOutput").isEmpty()) setOutputInvStr(stream.attributes().value("invLocalOutput").toString());
}

void WLAxis::writeXMLData(QXmlStreamWriter &stream)
{
stream.writeAttribute("kSTCurve",   QString::number(getKSTCurve()));
stream.writeAttribute("delaySCurve",QString::number(getDelaySCurve()));

stream.writeAttribute("typePulse",QString::number(typePulse));
stream.writeAttribute("outSDinv", QString::number(outSDinv));

stream.writeAttribute("inORG",QString::number(inORG->getIndex()));

stream.writeAttribute("inPEL",QString::number(inPEL->getIndex()));
stream.writeAttribute("actInPEL",QString::number(actIn[AXIS_inPEL]));

stream.writeAttribute("inMEL",QString::number(inMEL->getIndex()));
stream.writeAttribute("actInMEL",QString::number(actIn[AXIS_inMEL]));

stream.writeAttribute("inALM",QString::number(inALM->getIndex()));
stream.writeAttribute("actInALM",QString::number(actIn[AXIS_inALM]));

stream.writeAttribute("outRALM",QString::number(outRALM->getIndex()));
stream.writeAttribute("outENB",QString::number(outENB->getIndex()));
}
