#include "wldrive.h"
#include <math.h>

QList<WLDrive*> WLDrive::driveList;

WLDrive::WLDrive(QString _nameDrive)
{
m_name = _nameDrive;

setModuleAxis(nullptr);

setLogicFindPos(0);

curKSpeed=1;

m_homePosition=0;
setOrgPosition(0);

setDimension(WLDriveDim::oneStepSize,0.01);

setManualPercent(100);

m_feedVFind=10;
m_Vnow=0;

pad()->SaveAD(0,100,100,-100,"main");

m_type=Linear;

setObjectName("Drive");

driveList+=this;
}


WLDrive::~WLDrive()
{
qDebug()<<"~WLDrive()";
driveList.removeOne(this);
}


int WLDrive::setPosition(double pos)
{
QMutexLocker locker1(&MutexDrivePosition);

if(isMotion())
     {sendMessage(getFullName(),tr("error setting axis position"),-34);return -1;}

long lastPosStep=m_nowPosition.step;

m_nowPosition.set(pos,dim);

emit changedPosition(pos);

qDebug()<<"changedPosition(pos)"<<pos;

setTruPosition(false);

if((long) m_nowPosition.step!=lastPosStep)
{
if(getAxis()->setPos(m_nowPosition.step))   Flag.set(fl_setpos,true);

return 1;
}

return 0;
}

bool WLDrive::setDimension(WLDriveDim::typeDim _type,double A, double B)
{
const double lastPosition=position();

if(dim.set(_type,A,B))
{
if(getAxis())
 {
 getAxis()->setMinMaxPos(minPosition()/dim.value
                        ,maxPosition()/dim.value);

 setPosition(lastPosition);
 }
return true;
}

return false;
}

bool WLDrive::setPad(dataPad pad,typeMParAxis type)
{
return getAxis()->setParMov(pad.Aac/dim.value
                           ,pad.Ade/dim.value
                           ,pad.Vst/dim.value
                           ,pad.Vma/dim.value,type);
}

bool WLDrive::setMainPad()
{
if(pad()->findData("main"))
 {
 if(pad()->findData("mainMinus"))
     {
     setPad(pad()->getData("main"),typeMParAxis::AXIS_MParPlus);
     setPad(pad()->getData("mainMinus"),typeMParAxis::AXIS_MParMinus);
     }
     else
     {
     setPad(pad()->getData("main"),typeMParAxis::AXIS_MParAll);
     }
 return true;
 }

return false;
}


void WLDrive::updatePosition()
{
QMutexLocker locker(&MutexDrivePosition);
}

int WLDrive::startMotion(float _Vmov)
{
qDebug()<<"startMotionDrive"<<getName()
                           <<minPosition()
                           <<maxPosition()
                           <<position()<<">>"
                           <<nextPosition();

QMutexLocker locker(&MutexDrive);
QMutexLocker locker1(&MutexDrivePosition);


if(!Flag.get(fl_activ)
  ||isMotion()
  ||!getAxis()) {return -1;}

Flag.set(fl_latch2
	    |fl_latch3,0);

if(isAlarm()) {sendMessage(getFullName(),tr("drive controller has an error."),-31);return -31;}

if(_Vmov>=0.0f)   m_Vmov= _Vmov;

if(!isDone())
 {
 if(waitForStartMotion()<0) {sendMessage(getFullName(),tr("error when preparing for movement"),-32);return -1;}
 //if(!Flag.get(fl_enmov))    {sendMessage(Name(),tr("no permission for movement"),-15);return -1;}

 m_startPosition=position();

 if(getAxis()->movPos(MASK_abs,nextPositionDrive().step,m_Vmov/dim.value))
   { 
   qDebug()<<"+"<<positionDrive().step<<">>"<<nextPositionDrive().step;
   m_nowPosition.offset=m_nextPosition.offset;
   setMotion();
   waitAfterStartMotion();
   }

 }
else
 if(isInfinity())
 {
 if(getAxis()->movVel(Flag.get(fl_rot) ? MASK_dir:0,m_Vmov/dim.value))
   {
   setMotion();
   waitAfterStartMotion();
   }
 }
 else
 {

 qDebug()<<"Error Drive start noActiv"<<m_name;
 emit finished();
 }

return -1;
}

void WLDrive::reset()
{
QMutexLocker locker(&MutexDrive);

if(Flag.get(fl_auto)) emit autoFinished();

resetAuto();

setMotion(false);

Flag.set(fl_activ
        |fl_auto
	    |fl_wait
	    |fl_interp
        |fl_manual,0);

setVerifyPosition();

updatePosition();

m_nextPosition=m_nowPosition;

if(getAxis())
  {
  getAxis()->reset();
  getAxis()->setKF(1.0);
  }

emit finished();
}


int WLDrive::Mov(double dist)
{
return Mot(m_nowPosition.get(dim)+dist);
}

int WLDrive::Mot(double pos)
{
if(isMotion())
 { 
 emit sendMessage(getFullName(),tr("unfinished previous move"),-1);
 return -1;
 }

if(isTruPosition()
 &&(pos<minPosition()||maxPosition()<pos)
 &&!isInfinity())
 {
 emit sendMessage(getFullName(),tr("task out limit axis"),-1);
 return -1;
 }

m_nextPosition.set(pos,dim);

if(isDone())
 {
 m_nowPosition=m_nextPosition;
 Flag.set(fl_activ,false);
 return 0;
 }
else
 {
 if(calcForStartMotion()<0)  return -1;

 Flag.set(fl_rot,m_nextPosition.step>m_nowPosition.step);
 Flag.set(fl_activ,true);
 return 1;
 }
}

int WLDrive::Vel(bool dir)
{
if(isMotion())
 {
 emit sendMessage(getFullName(),tr("unfinished previous move"),-1);
 return -1;
 }

if(!isInfinity())
 {
 emit sendMessage(getFullName(),tr("err vellocity mode axis"),-1);
 return -1;
 }

if(calcForStartMotion()<0)  return -1;

Flag.set(fl_rot,dir);
Flag.set(fl_activ,true);
return 1;
}

int WLDrive::setCorMov(double cor)
{
QMutexLocker locker(&MutexDrive);

if(isMotion()
 ||cor==0.0) return -1;

if(Flag.get(fl_activ))
  return Mot(nextPosition()+cor);
  else
  return Mov(cor);
}

int WLDrive::addMov(double l)
{
QMutexLocker locker(&MutexDrive);

if(isMotion()||l==0.0) return -1;

if(Flag.get(fl_activ))
  return Mot(nextPosition()+l);
 else
    return Mov(l);
}

bool WLDrive::setMinMaxPosition(double minPos, double maxPos)
{
if(minPos<maxPos)
{
m_minPosition=minPos;
m_maxPosition=maxPos;

if(getAxis())
 {
 WLDrivePosition minDPos,maxDPos;

 minDPos.set(m_minPosition,dim);
 maxDPos.set(m_maxPosition,dim);

 getAxis()->setMinMaxPos(minDPos.step,maxDPos.step);

 emit changedMaxPosition(maxPos);
 emit changedMinPosition(minPos);
 }

return true;
}

return false;
}



int WLDrive::setHomePosition(double pos)
{
    m_homePosition=pos;

    if(getAxis())
    {
 WLDrivePosition homeDPos;

 homeDPos.set(m_homePosition,dim);

 getAxis()->setHomePos(homeDPos.step);
 }

return 1;
}



void WLDrive::setFinished()
{
qDebug()<<"Drive setFinished";

//MutexDrive.lock();
if(!isMotion()) 	return;

setMotion(false);

if(isAuto()) 
    {
	//MutexDrive.unlock(); 
	updateAuto();	
    }

waitAfterMotion();

if(Flag.get(fl_manual))
 {
 Flag.set(fl_manual,0);
 setDone();
 }

//if(isActiv())//если только активен то посылает сигналы
if(isDone())   
  {
  Flag.set(fl_activ
	      |fl_interp,0);
  qDebug()<<"Finshed drive"<<getName()<<m_nowPosition.step;
  emit finished();
  }
else
  {
  qDebug()<<"Paused drive"<<getName()<<m_nowPosition.step<<m_nextPosition.step;
  emit paused();
  }
}



void WLDrive::startMovManual(bool _rot,double dist)
{
qDebug()<<"Start Manual"<<getName()<<_rot;

if(isMotion()) 
   {

   if(_rot==rot())
       startAccel();
   else
       startStop();

   return;
   }

reset();

pad()->Load("main");
if(!_rot) pad()->Load("mainMinus");

pad()->Load("manual");

setCurPad();

setKSpeed(manualPercent/100.0);

Flag.set(fl_manual,1);

if(dist!=0.0)
{
setMov(_rot ? dist:-dist);
}
else   
if(isInfinity())
{
setVel(_rot);
}
else
{
if(isTruPosition())
 {
 if(_rot)
    {
    if(position()<maxPosition()) setMot(maxPosition());
    }
   else
    {
    if(position()>minPosition()) setMot(minPosition());
    }
 }    
else
  setMov((_rot ? 2:-2)*(maxPosition()-minPosition()));

}

startMotion();
}

void WLDrive::resetAlarm()
{
getAxis()->getOutput(AXIS_outRALM)->setOutPulse(1,100);
}

void WLDrive::updateInALM()
{
if(getAxis()->getInput(AXIS_inALM)->getNow())
 {
 sendMessage(getFullName(),tr("controller error (inALM)"),33);
 setTruPosition(false);
 }
}

/*
void WLDrive::inicial()
{

}
*/
bool WLDrive::setVmov(double V)
{
if(V>=0)
{
m_Vmov=V;
//qDebug()<<"Vmov="<<V;
/*
if(isMotion())
     getAxis()->setNewF(Vmov/getDriveDim().value);
*/
return true;
}
else
    return false;
}


bool WLDrive::setKGear(float k)
{
const double lastPosition=position();

if(dim.setKGear(k))
{
if(getAxis())
 {
 m_Axis->setKGear(k);

 setMinMaxPosition(minPosition(),maxPosition());

 }
setPosition(lastPosition);

return true;
}

return false;

}

void WLDrive::setInterp(bool set)
{
Flag.set(fl_interp,set);
interPad=pad()->getData();
//interPad.Vma=Vtar;
}


void WLDrive::addInResolutionMov(WLIOPut *_inEnableMov,bool state)
{
resolutMovIOData+=WLIOData(_inEnableMov,state);

connect(_inEnableMov,SIGNAL(changed()),SLOT(updateInResolutionMov()),Qt::QueuedConnection);
}

void WLDrive::removeInResolutionMov(WLIOPut *_inEnableMov)
{
for(int i=0;i<resolutMovIOData.size();i++)
{
WLIOData data=resolutMovIOData.at(i);

if(data.IOput==_inEnableMov)
  {
  resolutMovIOData.removeAt(i);
  disconnect(_inEnableMov,SIGNAL(changed()),this,SLOT(updateInResolutionMov()));
  break;
  }
}
}

double WLDrive::calcRotaryInfEndPosition(double startPos, double endPos)
{
double sP,sPC,eP,ePC;

sP=modf(startPos/360.0,&sPC);
eP=modf(endPos/360.0,&ePC);

if(qAbs(eP-sP)>0.5)
 {
 if(eP>sP)
     eP-=1.0;
 else
     eP+=1.0;
 }

qDebug()<<"calcRotaryInfEndPosition"<<startPos<<endPos<<"calc="<<(sPC+eP)*360.0;

return (sPC+eP)*360.0;
}

void WLDrive::updateInResolutionMov()
{
for(int i=0;i<resolutMovIOData.size();i++)
 if(!resolutMovIOData[i].isTry())
 {
 if(isMotion())  
   {
   startStop();
   sendMessage(getFullName(),tr("wrong resolution:")
              +(resolutMovIOData[i].IOput->isInput() ? "input:":"output:")
              +QString::number(resolutMovIOData[i].IOput->getIndex())
              +" ("+resolutMovIOData[i].IOput->getComment()+")",-15);
   }
 return;
 }
};

void WLDrive::writeXMLData(QXmlStreamWriter &stream)
{
stream.writeAttribute("name",         getName());
stream.writeAttribute("indexMAxis",   QString::number(indexMAxis()));

stream.writeAttribute("type", QString::number(getType()));

stream.writeAttribute("Dim",getDriveDim().toString());

if(!isInfinity())
 {
 stream.writeAttribute("MinPosition",  QString::number(minPosition()));
 stream.writeAttribute("MaxPosition",  QString::number(maxPosition()));
 }

stream.writeAttribute("Position",     QString::number(position()));
stream.writeAttribute("orgPosition",  QString::number(getOrgPosition())); 
stream.writeAttribute("homePosition", QString::number(homePosition()));
stream.writeAttribute("orgSize",      QString::number(getORGSize()));
stream.writeAttribute("logicFindPos", QString::number(getLogicFindPos()));


/*
stream.writeAttribute("kSTCurve",     QString::number(getKSTCurve()));
stream.writeAttribute("delaySCurve",  QString::number(getDelaySCurve()));

stream.writeAttribute("typePulse",    QString::number(typePulse));
stream.writeAttribute("outSDinv",     QString::number(outSDinv));
*/

stream.writeAttribute("feedVFind",     QString::number(feedVFind()));
stream.writeAttribute("Pad",     m_Pad.toString());

}

void WLDrive::readXMLData(QXmlStreamReader &stream)
{
if(!stream.attributes().value("name").isEmpty())
  setName(stream.attributes().value("name").toString());

setIndexModuleAxis(stream.attributes().value("indexMAxis").toString().toInt());

if(!stream.attributes().value("DimensionN").isEmpty()
 &&!stream.attributes().value("DimensionD").isEmpty())
setDimension(WLDriveDim::typeDim::oneStepSize,stream.attributes().value("DimensionN").toString().toDouble()/(1<<xPD)
                                             ,stream.attributes().value("DimensionD").toString().toDouble());

if(!stream.attributes().value("Dim").isEmpty())
   {
   WLDriveDim dd;

   dd.fromString(stream.attributes().value("Dim").toString());

   setDriveDim(dd);
   }

if(!stream.attributes().value("type").isEmpty())
   setType(static_cast<typeDrive>(stream.attributes().value("type").toInt()));
else
   setType();

if(!stream.attributes().value("MinPosition").isEmpty()
 &&!stream.attributes().value("MaxPosition").isEmpty())
    setMinMaxPosition(stream.attributes().value("MinPosition").toString().toDouble()
                     ,stream.attributes().value("MaxPosition").toString().toDouble());
else
    setInfinity();

setPosition(stream.attributes().value("Position").toString().toDouble());

if(!stream.attributes().value("orgPosition").isEmpty()) 
       setOrgPosition(stream.attributes().value("orgPosition").toString().toDouble());

if(!stream.attributes().value("homePosition").isEmpty()) 
       setHomePosition(stream.attributes().value("homePosition").toString().toDouble());

if(!stream.attributes().value("orgSize").isEmpty()) 
       setORGSize(stream.attributes().value("orgSize").toString().toFloat());

if(!stream.attributes().value("logicFindPos").isEmpty()) 
       setLogicFindPos(stream.attributes().value("logicFindPos").toString().toInt());

if(!stream.attributes().value("feedVFind").isEmpty()) 
       setFeedVFind(stream.attributes().value("feedVFind").toString().toFloat());

if(!stream.attributes().value("Pad").isEmpty())
       pad()->fromString(stream.attributes().value("Pad").toString());

Init();
}

bool WLDrive::startInterp()
{
QList <WLDrive*> Drives;

qDebug()<<"startInterp";

for(int i=0;i<driveList.size();i++)
    {
	if(driveList[i]->isInterp())  
		{
        if(driveList[i]->isWait()) return false; //ждем когда все могут двигатьс€
		Drives+=driveList[i];
	    }
    }

if(Drives.size()<=1) return true;

qDebug()<<"size"<<Drives.size();

int const n=Drives.size();

double *kDist=new double[n];

dataPad  mainPad,Pad;

//находим самое длинное перемещение
int iDistMax=0;

for(int i=1;i<n;i++)
  if(qAbs((float)Drives[i]->distance())
    >qAbs((float)Drives[iDistMax]->distance()))
	iDistMax=i;

mainPad=Drives[iDistMax]->pad()->getData(); //у кого самый большой путь
//находим коэффицинеты
for(int i=0;i<n;i++)
  kDist[i]=qAbs((float)Drives[i]->distance())
          /qAbs((float)Drives[iDistMax]->distance());

for(int i=0;i<n;i++)  
    qDebug()<<Drives[i]->distance()<<"K="<<kDist[i]<<"Pad"<<Drives[i]->pad()->getData().Vst<<Drives[i]->pad()->getData().Vma;

qDebug()<<"mPad0"<<mainPad.Vst<<mainPad.Vma<<mainPad.Aac<<mainPad.Ade;
//находим коэффиуиенты kTac kTde kVst kVfi дл€ всех
for(int i=0;i<n;i++)
 {
 if(qAbs(Drives[i]->interPad.Aac/kDist[i])<qAbs(mainPad.Aac)) //если ускорение превышает возможное
    mainPad.Aac=Drives[i]->interPad.Aac/kDist[i];
    
 if(qAbs(Drives[i]->interPad.Ade/kDist[i])<qAbs(mainPad.Ade)) //если торможение превышает возможное
    mainPad.Ade=Drives[i]->interPad.Ade/kDist[i];

 if(Drives[i]->interPad.Vst<(kDist[i]*mainPad.Vst)) //если скорость превышает возможное
    mainPad.Vst*=Drives[i]->interPad.Vst/(kDist[i]*mainPad.Vst);
 
 if(Drives[i]->interPad.Vma<(kDist[i]*mainPad.Vma)) //если скорость превышает возможное
    mainPad.Vma*=Drives[i]->interPad.Vma/(kDist[i]*mainPad.Vma);
 }
qDebug()<<"mPad1"<<mainPad.Vst<<mainPad.Vma<<mainPad.Aac<<mainPad.Ade;;
//заполн€ем
Pad.Aac=mainPad.Aac;
Pad.Ade=mainPad.Ade;

for(int i=0;i<n;i++)
 {
 Drives[i]->interPad.Aac=kDist[i]*mainPad.Aac;
 Drives[i]->interPad.Ade=kDist[i]*mainPad.Ade;
 Drives[i]->interPad.Vst=kDist[i]*mainPad.Vst;
 Drives[i]->interPad.Vma=kDist[i]*mainPad.Vma;

 Drives[i]->setPad(Drives[i]->interPad);
 Drives[i]->setVmov();
 Drives[i]->startMotion();
 }

return true;
}

void WLDrive::toStartAccel()
{
getAxis()->acc();
}

void WLDrive::setKSpeed(float k)
{
if(k>0&&k<=1)
 { 
 if(isInterp())
      {
      for(int i=0;i<driveList.size();i++)
		  if(driveList[i]->isInterp())  
			  {
			  driveList[i]->toSetKSpeed(k);
		      }
	  }
 else
   toSetKSpeed(k);
 }
}

void WLDrive::setManualPercent(float per)
{
if((0.0f<per)&&(per<=100.0f))
 {
 manualPercent=per; qDebug()<<"manualPercent"<<manualPercent;
 if(isMotion()) setKSpeed(manualPercent/100.0f);
 }

};


void WLDrive::toSetKSpeed(float k)
{
   getAxis()->setKF(k);
}

void WLDrive::toStartDecel()   
{
   getAxis()->dec();
}

void WLDrive::toStartStop()   
{
  getAxis()->sdStop();
}

 void WLDrive::startAccel()   
{
if(isInterp())
   {
   for(int i=0;i<driveList.size();i++)
       if(driveList[i]->isInterp())  driveList[i]->toStartAccel();
   }
else
 toStartAccel();
}

void WLDrive::startDecel()   
{
if(isInterp())
   {
   for(int i=0;i<driveList.size();i++)
       if(driveList[i]->isInterp())  driveList[i]->toStartDecel();
   }
else
 toStartDecel();
}

void WLDrive::startStop(bool reset)
{
if(reset) resetAuto();

if(isInterp())
   {
   for(int i=0;i<driveList.size();i++)
       if(driveList[i]->isInterp())  driveList[i]->toStartStop();
   }
else
 toStartStop();
}

void WLDrive::startEMGStop()    
{
resetAuto();

if(isInterp())
   {
   for(int i=0;i<driveList.size();i++)
       if(driveList[i]->isInterp())  
		   {
		   driveList[i]->resetAuto();
		   driveList[i]->toStartStop();///!!!
	       }
   }
else
 toStartEMGStop();
}


void WLDrive::toStartEMGStop()    
{
resetAuto(); 
getAxis()->emgStop();
}

void WLDrive::updateInputs()
{
}

void WLDrive::resets()
{
for(int i=0;i<driveList.size();i++)
        driveList[i]->reset();
}

bool WLDrive::isActivs()
{
bool ret=false;

for(int i=0;i<driveList.size();i++)
    if(driveList[i]->isActiv()) ret=true;

return ret;
}

bool WLDrive::isMotions()
{
bool ret=false;

for(int i=0;i<driveList.size();i++)
    if(driveList[i]->isMotion()) ret=true;

return ret;
}


WLDrive *WLDrive::getDrive(QString name)
{
WLDrive *ret=nullptr;

name=name.toLower();

for(int i=0;i<driveList.size();i++)
 if(driveList[i]->getName().toLower()==name)
  {
  ret=driveList[i];
  break;
  }

return ret;
}

void WLDrive::startStops(bool reset)
{
foreach(WLDrive *drive,driveList)
          drive->startStop(reset);
}

void WLDrive::setMainPads()
{
foreach(WLDrive *drive,driveList)
           drive->setMainPad();
}

bool WLDrive::Init()
{
if(m_Axis)
{
connect(getAxis(),&WLAxis::changedLatch2,this,&WLDrive::setLatch2);
connect(getAxis(),&WLAxis::changedLatch3,this,&WLDrive::setLatch3);
connect(getAxis(),&WLAxis::changedError,this,&WLDrive::setError);

connect(getAxis(),&WLAxis::changedPosition,this,&WLDrive::updatePos,Qt::DirectConnection);

connect(getAxis(),&WLAxis::finished,this,&WLDrive::setFinished,Qt::QueuedConnection);

connect(getAxis(),&WLAxis::changedFreq,this,&WLDrive::updateFreq);

setEnable(true);
setTruPosition(false);
return true;
}

return false;
}

void WLDrive::setError( quint8 error)
{ 
if(error!=0)
    {
    reset();
    if(error==errorAxis_emg) setTruPosition(false);
	}	
}


void WLDrive::updatePos(qint32 Pos)
{
QMutexLocker locker1(&MutexDrivePosition);                      



/*
oldPos=nowPosition.step;
qint64 newPos=nowPosition.step;

newPos/=4294967296;

if(qAbs(qint64(Pos)-(qint64)oldPos)>0xFFFFF)
 {
 if(Pos>0)
     newPos--;
 else
     newPos++;

 }
newPos*=4294967296;

newPos+=Pos;
oldPos=Pos;
*/
qint64 newPos=Pos;

if(Flag.get(fl_setpos))
  {
  if((qint32)m_nowPosition.step==(qint32)newPos) 	Flag.set(fl_setpos,0); //позици€ установлена
  return;
  }
  else
  {/*
  qint64  nowPosF0;

  qint64   newPosPlus;
  qint64  newPosMinus;

  nowPosF0=m_nowPosition.step&(0xFFFFFFFF00000000);

  newPosPlus=nowPosF0+Pos;
  newPosMinus=nowPosF0-Pos;

  if(qAbs(newPosPlus-m_nowPosition.step)
   <qAbs(newPosMinus-m_nowPosition.step))
    {
    newPos=newPosPlus;
    }
  else
    {
    newPos=newPosMinus;
    }
*/
  if(m_nowPosition.step!=newPos)
	   {
       Flag.set(fl_rot,newPos>m_nowPosition.step);
       m_nowPosition.step=newPos;
       waitAfterUpdatePosition();
	   }  
  }
}

void WLDrive::updateFreq(float F)
{
m_Vnow=dimension()*static_cast<double>(F);
emit changedVnow(m_Vnow);
}
 

void WLDrive::setLatch2(qint32 Pos)
{
Q_UNUSED(Pos)
Flag.set(fl_latch2,true);
updateAuto();
}

void WLDrive::setLatch3(qint32 Pos)
{
Q_UNUSED(Pos);
Flag.set(fl_latch3,true);
updateAuto();
}

void WLDrive::addSyhData(double pos)
{
WLDrivePosition drivePos;

drivePos.set(pos,dim);

getAxis()->addSyhData(drivePos.step);
}


int WLDrive::setMovFind()  
{
QMutexLocker locker(&MutexDrive);
qDebug("go Find");
if(setAuto())
   {
   setVerifyPosition(false);
   autoOperation=0; 
   autoTypeDrive=autoFind;
   return 1;
   }
  else
    sendMessage(getFullName(),tr("movement setup error"),-10);

return 0;
}; 

int  WLDrive::setMovTeach()  
{
QMutexLocker locker(&MutexDrive);
qDebug("go Teach");
if(setAuto())
   {
   setVerifyPosition(false);
   autoOperation=0; 
   autoTypeDrive=autoTeach;
   return 1;
   }
   else
   sendMessage(getFullName(),tr("movement setup error"),-10);

return 1;
}; 

int WLDrive::updateAuto()
{
qDebug("updateAuto Drive");
if(isAuto()&&autoTypeDrive!=autoNo)	
 {
 qDebug()<<autoTypeDrive<<logicFindPos<<isMotion()<<autoOperation;
 switch(logicFindPos)
 {
 case noFind:  setTruPosition(true);
	           reset();
	           break;

 case onlyORGHome:
 case onlyORG:   //if(!isMotion())
	             switch(autoOperation)
                   {
                    case 0: if(getAxis()->getInput(AXIS_inORG)->getNow())
    					    {
							setTruPosition(false);

    						autoOperation=1;
                            getAxis()->setLatchSrc(getAxis()->getInput(AXIS_inORG)->getIndex());
                            getAxis()->setActIn(AXIS_inORG,AXIS_actSdStop);

                            setMainPad();
                            setVmov();

                            setKSpeed(1);

    						setMov(-getORGSize()*1.5);
                            startMotion(m_feedVFind);
                            m_posCount=0;
    						}
    					   else
    					    {
                            reset();
                            emit sendMessage(getFullName(),tr("wrong starting position")+"(inORG=1)",-8);
    					    }
    						break;
    
                   case 1: if(!isMotion())
                           {
                           if(isLatch2()||isLatch3())
    						{
                            getAxis()->setLatchSrc(getAxis()->getInput(AXIS_inORG)->getIndex());
				
    						setMov(getORGSize()*3);

                            startMotion(m_feedVFind);
      	            	    autoOperation=15;
    					    }
    					   else
    						{
                            reset();
                            emit sendMessage(getFullName(),tr("no sensor signal")+"(inORG)",-212);
                            }
                           }
      	            	   break; 
    
    			   case 15: if(isMotion())
						     {
                             qDebug()<<"isLatch2()&&isLatch3()"<<isLatch2()<<isLatch3();
						     if(isLatch2()&&isLatch3())
							    {
                                startStop();
                                autoOperation=2;
                                qDebug()<<"to 2";
							    }

						     }
                             else
                              {
                              reset();
                              emit sendMessage(getFullName(),tr("no sensor signal")+"(inORG)",-212);
                              }
							 break;

                   case 2:  if(!isMotion())
                            {
                            if(isLatch2()&&isLatch3())
    					     {
                             m_posCount+=getLatch2Pos();
                             m_posCount+=getLatch3Pos();

                             getAxis()->setLatchSrc(getAxis()->getInput(AXIS_inORG)->getIndex());
    						 
    						 setMov(getORGSize()*-3);
                             startMotion(m_feedVFind);
      	            	     autoOperation=25;
    					     }
    					   else
				  		     {
    						 reset();
                             emit sendMessage(getFullName(),tr("no sensor signal")+"(inORG)",-213);
    						 }
                           }
      	            	   break; 

    			   case 25: if(isMotion())
						     {
						     if(isLatch2()&&isLatch3())
							    {
								startStop();
								autoOperation=3;								
							    }
						     }
                             else
                              {
                              reset();
                              emit sendMessage(getFullName(),tr("no sensor signal")+"(inORG)",-212);
                              }
							 break;

    			   case 3: if(!isMotion())
						   {
					       if(isLatch2()&&isLatch3())
    					      {
                              m_posCount+=getLatch2Pos();
                              m_posCount+=getLatch3Pos();
    
                              m_posCount/=4;
							  
    						  if(autoTypeDrive==autoTeach) 
							      {
                                  setOrgPosition(m_posCount);
								  setTruPosition();
								  reset();
							      }
    						  else	 
    						     if(autoTypeDrive==autoFind)   
							       {
                                   corPosition(m_posCount);
    					           setTruPosition();

								   reset();
								   
								   if(logicFindPos==onlyORGHome)
                                      {
                                      if(setMovHome())  startMotion();
								      }							        					      
							       }
						      }
    					   else
    						  {			
							  reset();
                              emit sendMessage(getFullName(),tr("no sensor signal")+"(inORG)",-214);
      	            	      }
						   }
      	              	   break;
                    }
		     break;

 case onlyPELHome:
 case onlyPEL:  if(!isMotion())
	      switch(autoOperation)
                   {
                    case 0: if(!getAxis()->getInput(AXIS_inPEL)->getNow())
    					    {
							setTruPosition(false);

    						autoOperation=1;
                            getAxis()->setLatchSrc(getAxis()->getInput(AXIS_inPEL)->getIndex());
    
                            setMainPad();
                            setVmov();

                            setKSpeed(1);                   

                            setMov((maxPosition()-minPosition())*2);
                            startMotion(m_feedVFind);
    						}
    					   else
    					    {
    						reset();
                            emit sendMessage(getFullName(),tr("wrong starting position")+"(inPEL=0)",-8);
    					    }
    						break;

                   case 1: if(isLatch2())
    					      {
                              m_posCount=getLatch2Pos();
    						  
    						  if(autoTypeDrive==autoTeach) 
								 {
                                 setOrgPosition(m_posCount);
								 setTruPosition();
								 reset();
							     }
    						  else	 
    						  if(autoTypeDrive==autoFind)     
								 {
                                 corPosition(m_posCount);
								 setTruPosition(true);    

                                 reset();

              				     if(logicFindPos==onlyPELHome)
							      {
                                  if(setMovHome())  startMotion(0);
							      }				  				  
							     }
    					      }
    					     else
    						  {	
							  reset();
                              emit sendMessage(getFullName(),tr("no sensor signal")+"(inPEL)",-214);
    						  }
      	              	     break;
                    }
		            break;

 case onlyMELHome:
 case onlyMEL:  if(!isMotion())
	      switch(autoOperation)
                   {
                    case 0: if(!getAxis()->getInput(AXIS_inMEL)->getNow())
    					    {
    						autoOperation=1;

							setTruPosition(false);
                            getAxis()->setLatchSrc(getAxis()->getInput(AXIS_inMEL)->getIndex());
							    
                            setMainPad();
                            setVmov();

                            setKSpeed(1);

                            setMov(-(maxPosition()-minPosition())*2);
                            startMotion(m_feedVFind);
    						}
    					    else
    					    {
    						reset();
                            emit sendMessage(getFullName(),tr("wrong starting position")+"(inMEL=0)",-8);
    					    }
    						break;

                   case 1:  getAxis()->setDisableLimit(false);
					        //setActIn(AXIS_inMEL,2);					 
                            

					        if(isLatch2())
    					      {
                              m_posCount=getLatch2Pos();
    						  
    						  if(autoTypeDrive==autoTeach) 
								{
                                setOrgPosition(m_posCount);
								setTruPosition();
								reset();
							    }
    						  else	 
								if(autoTypeDrive==autoFind)     
								{
                                corPosition(m_posCount);
    						  	setTruPosition();                             						  					  
    						 
								reset();
							    if(logicFindPos==onlyMELHome)
                                  {
                                  if(setMovHome())  startMotion(0);
							      }						  			  
							    }

    					      }
    					     else
    						  {
                              reset();
                              emit sendMessage(getFullName(),tr("no sensor signal")+"(inMEL)",-214);
      	            	      }
      	              	   break;
                    }
		     break;

 default: reset();
 }
 return 1;
 }
else
 return 0;
}
