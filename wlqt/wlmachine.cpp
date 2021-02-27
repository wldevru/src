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
WLDrive::startStops(true);
}


void WLMachine::goDriveManual(QString nameDrive,int IncDec,float step)
{
qDebug()<<"go drive Manual "<<IncDec<<step;

if(IncDec!=0&&!verifyReadyMotion()) return;

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
if(!verifyReadyMotion()) return;

if(isAuto())
   {
   SDStop();
   }
else
 {
 WLDrive::resets();

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

void WLMachine::goDriveFind(QString nameDrive)
{
qDebug()<<"goDriveFind"<<nameDrive;

if(!verifyReadyMotion()) {return;}

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
if(!verifyReadyMotion()) {return;}

WLDrive *drive=WLDrive::getDrive(nameDrive);

if(drive)
 {
 drive->reset();
 drive->setMovTeach();
 drive->startTask();
 }
}


/*
void WLMachine::goDriveTouch(QString nameDrive,int dir,float F)
{
qDebug()<<"goDriveTouch"<<nameDrive;

if(!verifyReadyMotion()) {return;}

WLMillDrive *Drive=getDrive(nameDrive,true);

if(Drive)
{
Drive->reset();

Drive->setMovTouch(dir,F);
Drive->startTask();
}
}*/
