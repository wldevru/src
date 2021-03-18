#include "wlmachine.h"

WLMachine::WLMachine(QObject *parent)
{

}

WLMachine::~WLMachine()
{
quit();
wait();
}

void WLMachine::SDStop()
{
WLDrive::startStopDrives(true);
}


void WLMachine::goDriveManual(QString nameDrive,int IncDec,float step)
{
qDebug()<<nameDrive<<"goDriveManual"<<IncDec<<step;

if(IncDec!=0&&!verifyReadyManualMotion()) return;

WLDrive *drive=WLDrive::getDrive(nameDrive);

if(isAuto())
   {
   SDStop();
   }
else
if(drive
 &&drive->getAxis())
{
if(IncDec==0)
    drive->startStop();
 else
 {
 drive->setVmov(0);
 drive->startMovManual(IncDec>0,step);
 }
}
}

void WLMachine::updateAuto()
{
qDebug()<<"update Auto Machine";

QMutexLocker locker(&MutexAuto);

if(isAuto())
switch(m_typeAutoMachine)
 {
 case AUTO_FindDrivePos: updateFindDrivePos();
 }
}

bool WLMachine::updateFindDrivePos()
{
if(!isActivDrives())
{
 if(m_listFindDrivePos.isEmpty())
 {
 resetAuto();
 QTimer::singleShot(10,this,SLOT(setFinished()));
 return 0;
 }
 else
 {
 QString curAxisFind=(m_listFindDrivePos.takeFirst()).toUpper();

 for(int i=0;i<curAxisFind.size();i++)
   {
   goDriveFind(curAxisFind.at(i));
   }
 }
}

return 1;
}

void WLMachine::goFindDrivePos()
{
if(!verifyReadyManualMotion()) return;

if(isAuto())
   {
   SDStop();
   }
else
 {
 WLDrive::resetDrives();

 m_listFindDrivePos=m_strFindDrivePos.split(",");

 m_typeAutoMachine=AUTO_FindDrivePos;

 setAuto();
 updateAuto();
 }
}

void WLMachine::setPercentManual(float per)
{
if(isPossiblyManual())
{
m_percentManual=per;

foreach(WLDrive *Drive,WLDrive::getDriveList())
    Drive->setManualPercent(m_percentManual);
}
}

void WLMachine::setReady(bool ready)
{
if(m_ready!=ready){
     m_ready=ready;
     emit changedReady(m_ready);
     }
}

void WLMachine::goDriveFind(QString nameDrive)
{
qDebug()<<"goDriveFind"<<nameDrive;

if(!verifyReadyAutoMotion()) {return;}

WLDrive *drive=WLDrive::getDrive(nameDrive);

if(drive->getName().isEmpty())
{
qDebug()<<"emptyName";
}
else
 {
 if(drive->isAuto())
    {
    qDebug()<<"already set Auto";
    drive->reset();
    }
 else if(drive->getAxis())
        {
        drive->setMovFind();
        drive->startTask();
        }
 }
}

void WLMachine::goDriveTeach(QString nameDrive)
{
qDebug()<<"goDriveTeach"<<nameDrive;
if(!verifyReadyAutoMotion()) {return;}

WLDrive *drive=WLDrive::getDrive(nameDrive);

if(drive)
 {
 drive->reset();
 drive->setMovTeach();
 drive->startTask();
 }
}

void WLMachine::goDriveVerify(QString nameDrive)
{
qDebug()<<"goDriveVerify"<<nameDrive;
if(!verifyReadyAutoMotion()) {return;}

WLDrive *drive=WLDrive::getDrive(nameDrive);

if(drive)
 {
 drive->reset();
 drive->setMovVerify();
 drive->startTask();
 }
}
