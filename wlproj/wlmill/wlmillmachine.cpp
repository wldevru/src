#include "wlmillmachine.h"

#include <QTimer>
#include <QFile>
#include <QCoreApplication>
#include <QXmlStreamWriter>

WLMillMachine::WLMillMachine(WLGProgram *_Program,WLEVScript *_EVMScript,QObject *parent)
    :WLMachine(parent)
{
m_Program=_Program;

m_EVMScript=_EVMScript;
m_EVLScript=nullptr;
m_motDevice=nullptr;

m_hPause=0;

m_MScriptCode="";

hProbeData.hTablet=25;
hProbeData.zPos=80;

m_curTool=0;
m_smoothAng=10;
m_mainDim=0.01;
//m_simpliDist=0;
//m_smoothDist=0;
//VG1=0;
m_Fbacklash=100;
//VManual=100;
m_Fprobe=10;

tarSOut=0;

m_baseOffsetTool=0;

QList <WL3DPointf> List;

List+=WL3DPointf(0  ,0,1);
List+=WL3DPointf(50 ,0,2);
List+=WL3DPointf(100,0,3);
List+=WL3DPointf(150,0,4);
List+=WL3DPointf(200,0,5);

m_mapHeight.points+=List;
List.clear();

List+=WL3DPointf(0  ,50,5);
List+=WL3DPointf(50 ,50,4);
List+=WL3DPointf(100,50,3);
List+=WL3DPointf(150,50,2);
List+=WL3DPointf(200,50,1);

m_mapHeight.points+=List;
List.clear();

List+=WL3DPointf(0  ,100,1);
List+=WL3DPointf(50 ,100,2);
List+=WL3DPointf(100,100,3);
List+=WL3DPointf(150,100,2);
List+=WL3DPointf(200,100,1);

m_mapHeight.points+=List;
List.clear();

List+=WL3DPointf(0  ,150,5);
List+=WL3DPointf(50 ,150,4);
List+=WL3DPointf(100,150,2);
List+=WL3DPointf(150,150,4);
List+=WL3DPointf(200,150,5);

m_mapHeight.points+=List;
List.clear();

List+=WL3DPointf(0  ,200,5);
List+=WL3DPointf(50 ,200,1);
List+=WL3DPointf(100,200,5);
List+=WL3DPointf(150,200,1);
List+=WL3DPointf(200,200,5);

m_mapHeight.points+=List;

m_percentManual=100;
m_percentSpeed=100;


m_minS=300;
m_maxS=24000;

m_maxSOut=100;
m_minSOut=0;

setContinueMov(true);
setBLNextMov(true);

QFile FileJS(mScriptFile);

if(!FileJS.open(QIODevice::ReadOnly|QIODevice::Text))
    {
    FileJS.setFileName(":/data/wlmillconfig/mscript.js");
    FileJS.open(QIODevice::ReadOnly|QIODevice::Text);
    }

if(FileJS.isOpen())
    {
    m_MScriptCode=QTextCodec::codecForName("Windows-1251")->toUnicode(FileJS.readAll());
    }

connect(m_EVMScript,&WLEVScript::changedBusy,this,&WLMillMachine::verifyPosibleManual);

QTimer *autoSaveTimer = new QTimer;
connect(autoSaveTimer,SIGNAL(timeout()),SLOT(saveConfig()));
autoSaveTimer->start(5*60*1000);

connect(&m_GCode,SIGNAL(changedSK(int)),SLOT(saveConfig()));

Flag.set(ma_go,false);
Flag.set(ma_busy,false);
//flag(ma_activ,false);
Flag.set(ma_pause,false);
}

WLMillMachine::~WLMillMachine()
{
//qDebug()<<"~WLMillMachine()"<<thread()<<this->currentThread();

saveConfig();

m_motDevice->deleteLater();

//quit();
//wait();

qDebug()<<"end MillMachine";
}


void WLMillMachine::sortCorrectSList()
{
int jmin;
SCorrectSOut Scor;

for(int i=0;i<m_correctSList.size();i++)
{
if(m_correctSList[i].Sadj<m_minS)
    {
    m_correctSList.removeAt(i);
    i--;
    }
}

for(int i=0;i<m_correctSList.size();i++)
{
if(m_correctSList[i].Sadj>m_maxS)
    {
    m_correctSList.removeAt(i);
    i--;
    }
}

for(int i=0;i<m_correctSList.size();i++)
    for(int j=i+1;j<m_correctSList.size();j++)
        if(m_correctSList[i].Sadj==m_correctSList[j].Sadj)
          {
          m_correctSList.removeAt(j);
          i--;
          break;
          }

for(int i=0;i<m_correctSList.size();i++)
    {
    jmin=i;
    for(int j=i+1;j<m_correctSList.size();j++)
      if(m_correctSList[j].Sadj<m_correctSList[jmin].Sadj) jmin=j;

    Scor=m_correctSList[i];
    m_correctSList[i]=m_correctSList[jmin];
    m_correctSList[jmin]=Scor;
    }


if((m_correctSList.isEmpty())||(m_correctSList.first().Sadj!=m_minS))
  {
  Scor.Sadj=m_minS;
  Scor.Scor=m_minS;
  m_correctSList.prepend(Scor);
  }

if((m_correctSList.isEmpty())||(m_correctSList.last().Sadj!=m_maxS))
  {
  Scor.Sadj=m_maxS;
  Scor.Scor=m_maxS;
  m_correctSList.append(Scor);
  }


}

WLMPG *WLMillMachine::getMPG()
{
WLModuleMPG *MMPG=m_motDevice->getModuleMPG();

if(MMPG)
  return MMPG->getMPG(0);
else
  return nullptr;
}

void WLMillMachine::addCurrentSCor()
{
SCorrectSOut addScor;

addScor.Sadj=tarSOut;
addScor.Scor=calcCorrectSOut(curSOut);

m_correctSList.prepend(addScor);

sortCorrectSList();

setPercentSOut(100.0);
setSOut(getSTar());
}

void WLMillMachine::clearSCorList()
{
m_correctSList.clear();
sortCorrectSList();

setSOut(getSTar());
}

void WLMillMachine::setOff(bool off) 
{
setOn(!off);
}

WLMillDrive *WLMillMachine::getDrive(QString nameDrive,bool send)
{
WLDrive *drive=WLDrive::getDrive(nameDrive);

if(drive!=nullptr)
{
if(strcmp(drive->metaObject()->className(),"WLMillDrive")==0)
             return static_cast<WLMillDrive*>(drive);
}

if(!drive&&send)
    setMessage(nameClass(),tr("error name drive"),-1);

return nullptr;
}

QList<WLMillDrive *> WLMillMachine::getDrives()
{
QList <WLMillDrive *> retList;
QList <WLDrive *> driveList=WLDrive::getDriveList();

foreach(WLDrive *drive,driveList)
 {
 if(strcmp(drive->metaObject()->className(),"WLMillDrive")==0)
                     retList+=static_cast<WLMillDrive*>(drive);
 }

return retList;
}

void WLMillMachine::setOn(bool on)   
{
WLMPG *Whell=getMPG();

if(!on) runScript("OFF()");

Flag.set(ma_on,on);  

if(!Flag.get(ma_on)) Stop();

emit changedOn(Flag.get(ma_on));

if(on)
  {
  runScript("ON()");

  WLDrive::setMainPads();  

  QVector <quint8> indexsAxis;

  foreach(WLMillDrive *mD,millDrives)
      if(mD->getAxis())  indexsAxis+=mD->getAxis()->getIndex();

  WLModulePlanner *ModulePlanner=getMotionDevice()->getModulePlanner();

  qDebug()<<"Indexs size"<<indexsAxis.size();
  if(ModulePlanner) ModulePlanner->setIAxisSlave(indexsAxis.data(),indexsAxis.size());

  if(Whell&&isUseMPG())
   {
   for(quint8 i=0;i<millDrives.size();i++)
      {
      if(millDrives[i]->getAxis())
          Whell->setDataAxis(i,millDrives[i]->getAxis()->getIndex(),1.0f/Whell->getPulses()/millDrives[i]->dimension());
      }

   getMPG()->setEnable(true);
   }
  }
else
  {
  if(Whell) getMPG()->setEnable(false);
  }

}


bool WLMillMachine::isPossiblyManual()
{
WLModulePlanner *MPlanner=getMotionDevice()->getModulePlanner();

if(MPlanner)
{
return  (MPlanner->getStatus()==MPLANNER_stop||MPlanner->getStatus()==MPLANNER_pause)
      &&(!isActivScript());
}

return true;
}

long WLMillMachine::getTrajIProgramSize()
{
QMutexLocker locker(&MutexMillTraj);

return MillTraj.isEmpty() ? 0 : (MillTraj.last().index-MillTraj.first().index);
}

void WLMillMachine::init(void)
{
qDebug()<<"Init MillMachine"<<thread();

if(!QDir(configMMDir).exists())
    QDir().mkdir(configMMDir);

m_motDevice=new WLMotion;

connect(m_motDevice,SIGNAL(sendMessage(QString,QString,int)),this,SLOT(setMessage(QString,QString,int)),Qt::QueuedConnection);

loadConfig();

updateMainDimXYZ();
qDebug("runned machine");
setEVMScript();
qDebug("runned machine");
Flag.set(ma_ready);
emit ready();

qDebug("runned machine");
}



bool WLMillMachine::isEmptyMotion()
{
WLModulePlanner *ModulePlanner=m_motDevice->getModulePlanner();

if(ModulePlanner)
     return    MillTraj.isEmpty()
            && ModulePlanner->isEmpty()
            &&!ModulePlanner->isMoving()
            &&!(isRunProgram()&&!isCompleteProgram())
            &&m_MList.isEmpty();
            //&&(!m_EVMScript->isBusy()||Flag.get(ma_runscript));
else
    return true;
}



void WLMillMachine::updateMainDimXYZ()
{
double minDim;

double pos[3];
QList <WLDrive*> drivesXYZ;

if(WLDrive::getDrive("X")) drivesXYZ+=WLDrive::getDrive("X");
if(WLDrive::getDrive("Y")) drivesXYZ+=WLDrive::getDrive("Y");
if(WLDrive::getDrive("Z")) drivesXYZ+=WLDrive::getDrive("Z");

if(drivesXYZ.isEmpty()) return;

if(drivesXYZ.size()==1)
{
m_mainDim=drivesXYZ.first()->getDriveDim().valueReal;
}
else
{
minDim=drivesXYZ.first()->getDriveDim().valueReal;

for(int i=1;i<3;i++)
    if(drivesXYZ[i]->getDriveDim().valueReal<minDim)	minDim=drivesXYZ[i]->getDriveDim().valueReal;

m_mainDim=minDim;

for(int i=0;i<3;i++)
    {
    drivesXYZ[i]->setKGear(m_mainDim/(drivesXYZ[i]->getDriveDim().valueReal));
    }

m_mainDim/=1<<xPD;
}

//WLModuleWhell *ModuleWhell=motDevice->getModuleWhell();

qDebug()<<"MainDimm"<<m_mainDim;
}

void WLMillMachine::setEVMScript()
{
QScriptValue objectMM = m_EVMScript->engine->newQObject(this);
m_EVMScript->engine->globalObject().setProperty("MACHINE",objectMM);

QScriptValue objectGC = m_EVMScript->engine->newQObject(this->getGCode());
m_EVMScript->engine->globalObject().setProperty("GCODE",objectGC);

connect(m_EVMScript,SIGNAL(sendMessage(QString,QString,int)),this,SLOT(setMessage(QString,QString,int)));
connect(m_EVMScript,SIGNAL(complete(QString)),SLOT(setCompleteScript(QString)));

m_EVMScript->setCode(m_MScriptCode);
}

void WLMillMachine::setEVLScript()
{
connect(m_EVLScript,SIGNAL(sendMessage(QString,QString,int)),this,SLOT(setMessage(QString,QString,int)));

timeLoopPLC = new QTimer;

connect(timeLoopPLC,SIGNAL(timeout()),this,SLOT(runLoopPLC));

m_EVLScript->setCode(m_MScriptCode);
}

void WLMillMachine::setDataSOut(float val)
{	
val*=m_percentSOut;

qDebug()<<"setDataSout"<<val;

double k=(m_maxSOut-m_minSOut)/(m_maxS-m_minS);

float S=(val-m_minSOut)/k+m_minS;

if(isUseCorrectSOut()&&m_correctSList.size()>2)
 {
 if(S<=m_correctSList.first().Scor)  S=m_correctSList.first().Sadj;
 else
  if(S>=m_correctSList.last().Scor)  S=m_correctSList.last().Sadj;
  else {
   for(int i=1;i<m_correctSList.size();i++)
     {
     if(m_correctSList[i].Scor>S)
      {
      double k=(m_correctSList[i].Sadj-m_correctSList[i-1].Sadj)/(m_correctSList[i].Scor-m_correctSList[i-1].Scor);
      S=m_correctSList[i-1].Sadj+k*(S-m_correctSList[i-1].Scor);
      break;
      }
     }
   }
 }

emit changedSValue(curSOut=S);
}


void WLMillMachine::Stop() //полная остановка
{
qDebug()<<"Stop MM";

MillTraj.clear();

MutexShowTraj.lock();
showMillTraj.clear(); 
MutexShowTraj.unlock();

emit changedTrajSize(MillTraj.size());

resetAuto();

Flag.reset(ma_runlist
          |ma_runprogram);

WLModulePlanner *ModulePlanner=m_motDevice->getModulePlanner();

if(ModulePlanner) ModulePlanner->stopMov();

WLModuleAxis *ModuleAxis=m_motDevice->getModuleAxis();

if(ModuleAxis)
   ModuleAxis->setActInProbe(AXIS_actNo);

SDStop();

if(Flag.get(ma_runprogram)
 &&!Flag.get(ma_stop)
 &&!Flag.get(ma_runscript)
 &&isOn())
 {
 Flag.set(ma_stop,runScript("STOP()"));
 }

QTimer::singleShot(0,this,SLOT(setFinished()));
}


void WLMillMachine::goOff() //выключение станка
{

}

void WLMillMachine::goOn() //включение станка
{

}



void WLMillMachine::reset()
{
if(isRunProgram())
     sendMessage("program reset: \""+m_Program->getName()+"\"",QString(" element: %1").arg(m_Program->getLastMovElement()),1);

MillTraj.clear();
m_MList.clear();
m_elementsTime=0;

MutexShowTraj.lock();
showMillTraj.clear();
MutexShowTraj.unlock();

baseTraj.clear();
lastEndPos.clear();

Flag.reset(ma_runlist
          |ma_runscript
          |ma_pause
          |ma_continue);

if(m_EVMScript) m_EVMScript->reset();

Stop();

m_iProgram=0;

emit changedReadyRunList(Flag.set(ma_readyRunList,false));
}

void WLMillMachine::startMovList() 
{
qDebug()<<"startListMov";

QMutexLocker locker(&Mutex);

WLModulePlanner *ModulePlanner=m_motDevice->getModulePlanner();

if(!verifyReadyMotion()) {reset();return;}

saveConfig();

if((ModulePlanner->getStatus()==MPLANNER_pause
  ||ModulePlanner->getStatus()==MPLANNER_stop)
 &&!Flag.get(ma_runlist))
{
if(Flag.get(ma_pause))
 {
 Flag.set(ma_pause,0);
 Flag.set(ma_continue,runScript("CONTINUE()"));
 }

qDebug()<<isEmptyMotion()<<isActivScript()<<isRunScript();

 if(!isEmptyMotion()&&(!isActivScript()||isRunScript()))
  {
   Flag.set(ma_runlist,1);
   setActiv();

   //emit ChangedRunList(true);
   if(!Flag.get(ma_continue))
   {
   m_programTime.start();
   m_elementsTime=m_iProgram;


   foreach(WLMillDrive *mD,millDrives)
                        mD->setMainPad();
   if(getDrive("Z"))
      ModulePlanner->setHPause(isUseHPause(),m_hPause/getDrive("Z")->dimension());

  if(!Flag.get(ma_continue))
    {
    ModulePlanner->startMov();
    updateMovBuf();
    }
   }
 }
}
}


QString WLMillMachine::correctSOut()
{
QString ret;
for(int i=0;i<m_correctSList.size();i++)
    {
	if(i!=0) ret+=",";

    ret+=QString::number(m_correctSList[i].Sadj)+","+QString::number(m_correctSList[i].Scor);
    }

return ret;
}

void WLMillMachine::setStringCorrectSOut(QString str)
{
QStringList List=str.split(",");
SCorrectSOut Scorr;

m_correctSList.clear();

for(int i=1;i<List.size();i+=2)
  {
  Scorr.Sadj=List[i-1].toDouble();
  Scorr.Scor=List[i].toDouble();

  m_correctSList+=Scorr;
  }

sortCorrectSList();
}


void WLMillMachine::saveConfig()
{
QFile FileXML(configMMFile);

QByteArray Data;

QXmlStreamWriter stream(&Data);

if(!Flag.get(ma_ready)) return;

stream.setAutoFormatting(true);

stream.setCodec(QTextCodec::codecForName("Windows-1251"));
stream.writeStartDocument("1.0");

stream.writeStartElement("WhiteLineMillConfig");

//stream.writeAttribute("usePWMS",QString::number(isUsePWMS()));
stream.writeAttribute("useCorrectSOut",QString::number(isUseCorrectSOut()));
stream.writeAttribute("strFindDrivePos",getStrFindDrivePos());

stream.writeAttribute("correctSOut",correctSOut());

stream.writeAttribute("MinMaxS",QString::number(m_minS)+","+QString::number(m_maxS));
stream.writeAttribute("MinMaxOutS",QString::number(m_minSOut)+","+QString::number(m_maxSOut));
stream.writeAttribute("iCurTool",QString::number(m_curTool));
stream.writeAttribute("AutoStart",QString::number(isAutoStart()));

stream.writeAttribute("useGModel",QString::number(isUseGModel()));

if(isUseHPause())
stream.writeAttribute("hPause",QString::number(HPause()));

stream.writeAttribute("useMPG",QString::number(isUseMPG()));

stream.writeAttribute("feedVBacklash",  QString::number(VBacklash()));
stream.writeAttribute("feedVProbe",     QString::number(VProbe()));

//stream.writeAttribute("iSOutPWM",   QString::number(getIndexSOutPWM()));

stream.writeAttribute("hProbeData",QString::number(hProbeData.hTablet)
	                          +","+QString::number(hProbeData.zPos));


stream.writeAttribute("ContinueMov",QString::number(isContinueMov()));
stream.writeAttribute("BacklashNextMov",QString::number(isBLNextMov()));

/*
stream.writeAttribute("SmoothDist",QString::number(m_smoothDist));
stream.writeAttribute("SimpliDist",QString::number(m_simpliDist));
*/

 stream.writeStartElement("Device");
     stream.writeAttribute("WLMotion",m_motDevice->getNameDevice());

 stream.writeEndElement();

 stream.writeStartElement("Drive");
 QList <WLDrive*> driveList=WLDrive::getDriveList();

  for (int i=0;i<driveList.size();i++)
  {
  stream.writeStartElement(driveList[i]->metaObject()->className());
    driveList[i]->writeXMLData(stream);
  stream.writeEndElement();
  }
 stream.writeEndElement();

 stream.writeStartElement("Position");
 stream.writeAttribute("G28",m_GCode.getG28Position().toString());
 stream.writeAttribute("G43",m_GCode.getG43Position().toString());
 stream.writeAttribute("offsetHTool",QString::number(m_GCode.getOffsetHTool()));
 stream.writeEndElement();

 stream.writeStartElement("GModel");
  m_GModel.writeXMLData(stream);
 stream.writeEndElement();

 for(int i=0;i<sizeSC;i++)
 {
 stream.writeStartElement("SC");
 stream.writeAttribute("i",QString::number(i));

 stream.writeAttribute("GPoint",m_GCode.getOffsetSC(i).toString());
 stream.writeAttribute("refPoint0",m_GCode.getRefPoint0SC(i).toString());
 stream.writeAttribute("refPoint1",m_GCode.getRefPoint1SC(i).toString());
 stream.writeEndElement();
 } 

 for(int i=1;i<sizeTools;i++)
 {
 stream.writeStartElement("Tool");
 stream.writeAttribute("i",QString::number(i));

 stream.writeAttribute("Data",m_GCode.getDataTool(i).toString());
 stream.writeEndElement();
 }

stream.writeEndElement();

stream.writeEndDocument();

if(FileXML.open(QIODevice::WriteOnly))
{
FileXML.write(Data.constData());
FileXML.close();
qDebug()<<"Write XML";
}

m_motDevice->writeToFile(configMMDir+m_motDevice->getNameDevice()+".xml");

 QFile FileJS(mScriptFile);
 qDebug()<<"save mScriptFile";

 if(FileJS.open(QIODevice::WriteOnly))      
      {
      FileJS.write(QTextCodec::codecForName("Windows-1251")->fromUnicode(m_EVMScript->getCode()));
      FileJS.close();
      }
}

void WLMillMachine::addDrive(WLMillDrive *millDrive)
{
millDrive->moveToThread(this->thread());

connect(millDrive,SIGNAL(finished()),this,SLOT(setFinished()),Qt::QueuedConnection);
connect(millDrive,SIGNAL(paused()),this,SLOT(setFinished()),Qt::QueuedConnection);
connect(millDrive,SIGNAL(sendMessage(QString,QString,int)),this,SLOT(setMessage(QString,QString,int)),Qt::QueuedConnection);

millDrive->setModuleAxis(m_motDevice->getModuleAxis());
}

void WLMillMachine::removeDrive(WLMillDrive *millDrive)
{
disconnect(millDrive,nullptr,nullptr,nullptr);

millDrives.removeOne(millDrive);

millDrive->deleteLater();
}

bool WLMillMachine::loadConfig()
{
QFile FileXML(configMMFile);
QXmlStreamReader stream;
QStringList List;
int i=0;

qDebug()<<"load config MillMachine";

if(!FileXML.open(QIODevice::ReadOnly))    {
           FileXML.setFileName(":/data/wlmillconfig/mmconfig.xml");
           FileXML.open(QIODevice::ReadOnly);
           }

if(FileXML.isOpen())
  {
  qDebug()<<"open XML";
  stream.setDevice(&FileXML);

  while(!stream.atEnd())
   {
   stream.readNextStartElement();

   if(stream.name()=="WhiteLineMillConfig")
     {

	 if(!stream.attributes().value("MinMaxOutS").isEmpty()) 
	     { 
		 List=stream.attributes().value("MinMaxOutS").toString().split(",");
		 setRangeSOut(List[0].toFloat(),List[1].toFloat());
	     }

	 if(!stream.attributes().value("MinMaxS").isEmpty()) 
	     { 
		 List=stream.attributes().value("MinMaxS").toString().split(",");
		 setRangeS(List[0].toFloat(),List[1].toFloat());
	     }


	 if(!stream.attributes().value("iCurTool").isEmpty()) 
		 setCurTool(stream.attributes().value("iCurTool").toString().toInt());

     if(!stream.attributes().value("AutoStart").isEmpty())  setAutoStart(true);

	 if(!stream.attributes().value("hProbeData").isEmpty()) 
	     {
		 List=stream.attributes().value("hProbeData").toString().split(",");
		 if(List.size()==2)
		  {
		  hProbeData.hTablet=List[0].toDouble();
		  hProbeData.zPos=List[1].toDouble();
		  }
	     }

     if(!stream.attributes().value("hPause").isEmpty())
        setHPause(stream.attributes().value("hPause").toString().toFloat());
	 

	 if(!stream.attributes().value("ContinueMov").isEmpty()) 
	     setContinueMov(stream.attributes().value("ContinueMov").toString().toInt());

	 if(!stream.attributes().value("BacklashNextMov").isEmpty()) 
		 setBLNextMov(stream.attributes().value("BacklashNextMov").toString().toInt());

     if(!stream.attributes().value("useGModel").isEmpty())
         setEnableGModel(stream.attributes().value("useGModel").toInt());

     if(!stream.attributes().value("hPause").isEmpty())
         {
         setEnableHPause(true);
         setHPause(stream.attributes().value("hPause").toString().toFloat());
         }

     if(!stream.attributes().value("useMPG").isEmpty())
         {
         setUseMPG(stream.attributes().value("useMPG").toInt());
         }

     if(!stream.attributes().value("strFindDrivePos").isEmpty())
         setStrFindDrivePos(stream.attributes().value("strFindDrivePos").toString());

	 if(!stream.attributes().value("feedVBacklash").isEmpty()) 
		 setFeedVBacklash(stream.attributes().value("feedVBacklash").toString().toFloat());

	 if(!stream.attributes().value("feedVProbe").isEmpty()) 
		 setFeedVProbe(stream.attributes().value("feedVProbe").toString().toFloat());
/*
	  if(!stream.attributes().value("usePWMS").isEmpty()) 
         {
         if(stream.attributes().value("usePWMS").toString().toInt())
           {
           if(!stream.attributes().value("iSOutPWM").isEmpty())
                 setIndexSOutPWM(stream.attributes().value("iSOutPWM").toString().toInt());
           }
         }
*/
	  if(!stream.attributes().value("useCorrectSOut").isEmpty()) 
	     setEnableUseCorrectSOut(stream.attributes().value("useCorrectSOut").toString().toInt());

      if(!stream.attributes().value("correctSOut").isEmpty())
	    setStringCorrectSOut(stream.attributes().value("correctSOut").toString()); 
/*
     if(!stream.attributes().value("SmoothDist").isEmpty())
		 {
         m_smoothDist=stream.attributes().value("SmoothDist").toString().toFloat();
         if(m_smoothDist<0) m_smoothDist=0;
		   else
             if(m_smoothDist>5) m_smoothDist=5;
         }

	 if(!stream.attributes().value("SimpliDist").isEmpty()) 
		 {
         setSimpliDist(stream.attributes().value("SimpliDist").toString().toFloat());
         }
*/
	 while(!stream.atEnd())
	 { 
	  stream.readNextStartElement();

	  if(stream.name()=="WhiteLineMillConfig") break;
	  if(stream.tokenType()!=QXmlStreamReader::StartElement) continue;

	  if(stream.name()=="Device"
	  &&stream.tokenType()==QXmlStreamReader::StartElement)
	   {


       if(!stream.attributes().value("WLMotion").isEmpty())
            {
            QString initFile=configMMDir+stream.attributes().value("WLMotion").toString()+".xml";

            WLMotion WLMDev;

            if(!WLMDev.initFromFile(initFile))
              {
              initFile=":/data/wlmillconfig/WLM35A.xml";
              WLMDev.initFromFile(initFile);
              }

            auto infoList=WLDevice::availableDevices();

            bool findOk=false;

            foreach(WLDeviceInfo info,infoList)
            {
            qDebug()<<"info"<<info.comPort<<info.UID96;
            if(info.isValid(WLMDev.getInfo()))
               {
               findOk=true;

               m_motDevice->setInfo(info);
               m_motDevice->openConnect();
               break;
               }

            }

            m_motDevice->initFromFile(initFile);

            if(m_motDevice->getModuleConnect())
                             m_motDevice->getModuleConnect()->setEnableHeart(true);

            if(!findOk
             &&!m_motDevice->getUID96().isEmpty())
                emit sendMessage("WLMillMachine",tr("device %1 not found.").arg(m_motDevice->getNameDevice())+" ("+m_motDevice->getUID96()+")",0);
            }

       }


	  if(stream.name()=="Outputs"
	  &&stream.tokenType()==QXmlStreamReader::StartElement)
	   {
	   QStringList List;

	     while(!stream.atEnd())
	      {
          stream.readNextStartElement();
	  	
	  	  if(stream.name()=="Outputs") break;
	  	  if(stream.tokenType()!=QXmlStreamReader::StartElement) continue;
	   
	  	///if(stream.name()=="WLMotion") motDevice->readXMLData(stream);
	     }
	   }	

      if(stream.name()=="Drive")
       {
       if(m_motDevice->getModuleAxis())
           while(!stream.atEnd())
            {
            stream.readNextStartElement();

            if(stream.name()=="Drive") break;
            if(stream.tokenType()!=QXmlStreamReader::StartElement) continue;


            if(stream.name()=="WLMillDrive")
             {
             WLMillDrive *millDrive = new WLMillDrive();

             addDrive(millDrive);

             millDrive->readXMLData(stream);
             }

            }
      }

//--old Style
    if(stream.name()=="HomePos"){
         WLGPoint GP;
         GP.fromString(stream.attributes().value("GPoint").toString());
         m_GCode.setG28Position(GP);
         continue;
         }
//---
    if(stream.name()=="Position")
         {
         WLGPoint GP;

         if(!stream.attributes().value("G28").isEmpty()){
           GP.fromString(stream.attributes().value("G28").toString());
           m_GCode.setG28Position(GP);
           }

         if(!stream.attributes().value("G43").isEmpty()){
           GP.fromString(stream.attributes().value("G43").toString());
           m_GCode.setG43Position(GP);
           }

         if(!stream.attributes().value("offsetHTool").isEmpty()){
           getGCode()->setOffsetHTool(stream.attributes().value("offsetHTool").toDouble());
           }

         continue;
         }

    if(stream.name()=="GModel"){
         m_GModel.readXMLData(stream);
         continue;
         }

    if(stream.name()=="SC"){
		 qDebug()<<"loadSC";
		 WL3DPoint SC;

		 i=stream.attributes().value("i").toString().toInt();

         WLGPoint GP;

         if(!stream.attributes().value("Frame").isEmpty())
           {
           WLFrame Fr;
           Fr.fromString(stream.attributes().value("Frame").toString());

           GP.x=Fr.x;
           GP.y=Fr.y;
           GP.z=Fr.z;
           m_GCode.setOffsetSC(i,GP,false);

           Fr.fromString(stream.attributes().value("refPoint0").toString());
           GP.x=Fr.x;
           GP.y=Fr.y;
           GP.z=Fr.z;
           m_GCode.setRefPoint0SC(i,GP);

           Fr.fromString(stream.attributes().value("refPoint1").toString());
           GP.x=Fr.x;
           GP.y=Fr.y;
           GP.z=Fr.z;
           m_GCode.setRefPoint1SC(i,GP);
           }
           else
           {
           GP.fromString(stream.attributes().value("GPoint").toString());
           m_GCode.setOffsetSC(i,GP,false);

           GP.fromString(stream.attributes().value("refPoint0").toString());
           m_GCode.setRefPoint0SC(i,GP);

           GP.fromString(stream.attributes().value("refPoint1").toString());
           m_GCode.setRefPoint1SC(i,GP);
           continue;
           }

	     }

        if(stream.name()=="Tool")
         {
         qDebug()<<"loadTool";
         WLGTool GTool;

         i=stream.attributes().value("i").toString().toInt();

         if(!stream.attributes().value("Data").isEmpty())
           {
           GTool.fromString(stream.attributes().value("Data").toString());
           m_GCode.setDataTool(i,GTool);
           continue;
           }

         }
     
     }
	}
   }

  if(m_motDevice->getModuleAxis())
    {
    connect(m_motDevice->getModuleAxis(),SIGNAL(changedInEMGStop()),SLOT(updateInput()));
    connect(m_motDevice->getModuleAxis(),SIGNAL(changedInSDStop()),SLOT(updateInput()));
    }

  if(getDrive("X")) millDrives+=getDrive("X");
  if(getDrive("Y")) millDrives+=getDrive("Y");
  if(getDrive("Z")) millDrives+=getDrive("Z");
  if(getDrive("A")) millDrives+=getDrive("A");
  if(getDrive("B")) millDrives+=getDrive("B");
  if(getDrive("C")) millDrives+=getDrive("C");
  if(getDrive("U")) millDrives+=getDrive("U");
  if(getDrive("V")) millDrives+=getDrive("V");
  if(getDrive("W")) millDrives+=getDrive("W");

  WLModulePlanner *ModulePlanner=m_motDevice->getModulePlanner();  

  if(ModulePlanner)
  {
  connect(ModulePlanner,&WLModulePlanner::reset,this,&WLMillMachine::Stop,Qt::QueuedConnection);
  connect(ModulePlanner,&WLModulePlanner::changedStatus,this,&WLMillMachine::setFinished,Qt::QueuedConnection);
  connect(ModulePlanner,&WLModulePlanner::changedFree,this,&WLMillMachine::setFinished,Qt::QueuedConnection);

  connect(ModulePlanner,&WLModulePlanner::changedStatus,this,&WLMillMachine::verifyPosibleManual);

  connect(ModulePlanner,SIGNAL(changedStatus(int)),SLOT(on_changedStatusMPlanner(int)));

  connect(m_motDevice->getModulePlanner(),SIGNAL(changedSOut(float)),SLOT(setDataSOut(float)));
  setSOut(m_GCode.getValue('S'));
/*
  if(m_motDevice->getModulePWM())
     {   
     setEnablePWMS(isUsePWMS());//устанавливаем связь
	 
     connect(m_motDevice->getModulePlanner(),SIGNAL(changedSOut(float)),SLOT(setDataSOut(float)));
     setSOut(m_GCode.getValue('S'));
     }
*/
  }



  return true;
  }



return false;
}


void WLMillMachine::setFinished()
{
qDebug()<<"setFinished?";

if(!isReady()) return;

QMutexLocker locker(&Mutex);

setActiv(isActivDrives());
qDebug()<<"setFinished"<<isActivDrives()<<!isEmptyMotion()
                                        <<Flag.get(ma_runprogram)
                                        <<isAuto();
if(isAuto())
 updateAuto();
else
{
updateMovBuf();

if(isEmptyMotion()
 &&Flag.get(ma_readyRunList)
 &&(!isActivScript()||isRunScript()))//if no mov data and last mov
   {
   if(Flag.get(ma_runprogram))
       {
       long h,m;
       float ms;
       long time_s=m_programTime.elapsed();

       h=time_s/3600000;
       time_s-=h*3600000;

       m=time_s/60000;
       time_s-=m*60000;

       ms=time_s;

       m_Program->setLastMovElement(0);
       sendMessage("WLMillMachine",QString("\"%1\" time: %2:%3:%4 ").arg(m_Program->getName()).arg(h).arg(m).arg(ms/1000.0,1),1);     
       }

   Stop();
   emit changedReadyRunList(Flag.set(ma_readyRunList,false));
   }
}
}
void WLMillMachine::updateAuto()
{
if(isAuto()&&(m_typeAutoMMachine!=AUTO_no))
 {
 updateMillMachineAuto();
 }
else
 {
 WLMachine::updateAuto();
 }
}

void WLMillMachine::updateMillMachineAuto()
{    
qDebug()<<"update Auto MillMachine";

QMutexLocker locker(&MutexAuto);

if(isAuto()) 
switch(m_typeAutoMMachine)
 {
 case AUTO_ProbeEMG:
 case AUTO_ProbeSD:      updateProbe();
 case AUTO_HProbeEMG:
 case AUTO_HProbeSD:     updateHProbe();
 case AUTO_HToolEMG:
 case AUTO_HToolSD:      updateHToolProbe();
 //case AUTO_Program: return updateProgram();
 }

}

bool WLMillMachine::updateProbe()
{
qDebug()<<"update Auto Probe"<<iOperation<<driveProbe->isMotion();

WLModuleAxis *ModuleAxis=m_motDevice->getModuleAxis();

if(!driveProbe->isMotion())
switch(iOperation)
{
 case 0: //driveProbe->reset();
         driveProbe->setMainPad();
         driveProbe->setKSpeed(1);

         ModuleAxis->resetLatchProbe();

         if(!ModuleAxis->getInput(MAXIS_inProbe)->getNow())
                    iOperation=2;
                 else
                    iOperation=3;

         ModuleAxis->setActInProbe(m_typeAutoMMachine==AUTO_ProbeSD ? AXIS_actSdStop:AXIS_actEmgStop);


         driveProbe->startMovPos(iDriveDir ? driveProbe->maxPosition():driveProbe->minPosition(),m_Fprobe/60);
		 break;

 case 2: if(ModuleAxis->isLatchProbe2())
		  {
          iOperation=4;

          if(driveProbe->startMovPos(ModuleAxis->getLatchProbe2(driveProbe->getAxis()->getIndex())*driveProbe->dimension()
                                 +(driveProbe->rot()? -getDrive(driveProbe->getName())->getHalfBacklash():getDrive(driveProbe->getName())->getHalfBacklash())
                                  ,m_Fprobe/60))
             break;

		  }
		 else
		  {
		  sendMessage(tr("no sensor signal"),"inProbe",0);
          }

         resetAuto();
         QTimer::singleShot(10,this,SLOT(setFinished()));
         qDebug()<<"Complete probeR";
		 break;	

 case 3: if(ModuleAxis->isLatchProbe3())
		  {
          iOperation=4;

          if(driveProbe->startMovPos(ModuleAxis->getLatchProbe3(driveProbe->getAxis()->getIndex())*driveProbe->dimension()
                                 +(driveProbe->rot()? -getDrive(driveProbe->getName())->getHalfBacklash():getDrive(driveProbe->getName())->getHalfBacklash())
                                  ,m_Fprobe/60))
              break;

          }
         else
		  {
		  sendMessage(tr("no sensor signal"),"inProbe",0);		 
		  }

         resetAuto();
         QTimer::singleShot(10,this,SLOT(setFinished()));
         qDebug()<<"Complete probeF";
		 break;	

 case 4: resetAuto();
	     QTimer::singleShot(10,this,SLOT(setFinished()));
         qDebug()<<"Complete probe+";
	     break;
 }

return 1;
}


bool WLMillMachine::isTryProbe(bool dir) 
{
if(dir) 
   return m_motDevice->getModuleAxis()->isLatchProbe2();
 else
   return m_motDevice->getModuleAxis()->isLatchProbe3();
}

double WLMillMachine::getProbePosition(QString nameDrive,bool dir)
{
double ret;

WLMillDrive *MDrive=getDrive(nameDrive);

if(MDrive
 &&MDrive->getAxis())
{
 if(dir)
  {
  ret=m_motDevice->getModuleAxis()->getLatchProbe2(MDrive->getAxis()->getIndex());
  }
  else
  {
  ret=m_motDevice->getModuleAxis()->getLatchProbe3(MDrive->getAxis()->getIndex());
  }
return ret*MDrive->dimension();
}

return 0;
}

double WLMillMachine::getCurPositionSC(QString name)
{
WLGPoint GP=getCurrentPositionActivSC();

name=name.toUpper();

if(name=="X") return GP.x; else
if(name=="Y") return GP.y; else
if(name=="Z") return GP.z; else
if(name=="A") return GP.a; else
if(name=="B") return GP.b; else
if(name=="C") return GP.c; else
if(name=="U") return GP.u; else
if(name=="V") return GP.v; else
if(name=="W") return GP.w; else

return 0;
}

bool WLMillMachine::isActivDrive(QString name)
{
WLDrive *Drive=WLDrive::getDrive(name);

if(Drive) return Drive->isActiv();
return 0;
}
 

bool WLMillMachine::updateHToolProbe()
{
qDebug()<<"update Auto HTool %d"<<iOperation<<!WLDrive::isMotionDrives()<<!Flag.get(ma_runlist);

WLModuleAxis *ModuleAxis=m_motDevice->getModuleAxis();

if(!WLDrive::isMotionDrives())
switch(iOperation)
{
case 0: /*runGCode("G0 G53 X"+QString::number(getGCode()->getG43Position().x)
                      +" Y"+QString::number(getGCode()->getG43Position().y));

         Start();

         iOperation=1;
         break;*/

case 1:  driveProbe->setMainPad();
         driveProbe->setKSpeed(1);

          ModuleAxis->resetLatchProbe();

         if(m_typeAutoMMachine==AUTO_HToolSD)
            ModuleAxis->setActInProbe(AXIS_actSdStop);
         else
            ModuleAxis->setActInProbe(AXIS_actEmgStop);

         if(!ModuleAxis->getInput(MAXIS_inProbe)->getNow())
              iOperation=2;
             else
              iOperation=3;

        m_backProbePosition=driveProbe->position();

        driveProbe->startMovPos(driveProbe->minPosition(),m_Fprobe/60);
        break;

case 2: if(ModuleAxis->isLatchProbe2())
         {
         double H=ModuleAxis->getLatchProbe2(driveProbe->getAxis()->getIndex())*driveProbe->dimension();

         if(getGCode()->getValue('H')==0)
            getGCode()->setOffsetHTool(H);
         else
            getGCode()->setHTool(getGCode()->getValue('H'),H-getGCode()->getOffsetHTool());

         driveProbe->startMovPos(m_backProbePosition,0);
         iOperation=4;
         }
        else
         {
         sendMessage(tr("no sensor signal"),"inProbe",0);
         reset();
         QTimer::singleShot(10,this,SLOT(setFinished()));
         }

        break;

case 3: if(ModuleAxis->isLatchProbe3())
         {
         double H=ModuleAxis->getLatchProbe3(driveProbe->getAxis()->getIndex())*driveProbe->dimension();

         if(getGCode()->getValue('H')==0)
            getGCode()->setOffsetHTool(H);
         else
            getGCode()->setHTool(getGCode()->getValue('H'),H-getGCode()->getOffsetHTool());

         driveProbe->startMovPos(m_backProbePosition,0);
         iOperation=4;
         }
        else
         {
         sendMessage(tr("no sensor signal"),"inProbe",0);
         reset();
         QTimer::singleShot(10,this,SLOT(setFinished()));
         }
        break;

case 4: resetAuto();
        QTimer::singleShot(10,this,SLOT(setFinished()));
        break;

}

return 1;
}


bool WLMillMachine::updateHProbe()
{
qDebug("update Auto HProbe %d",iOperation);

WLModuleAxis *ModuleAxis=m_motDevice->getModuleAxis();

if(!driveProbe->isMotion())
switch(iOperation)
{
 case 0: //driveProbe->reset();
         driveProbe->setMainPad();
         driveProbe->setKSpeed(1);

		 ModuleAxis->resetLatchProbe();

         if(m_typeAutoMMachine==AUTO_HProbeSD)
			ModuleAxis->setActInProbe(AXIS_actSdStop);
		 else
            ModuleAxis->setActInProbe(AXIS_actEmgStop);

		 if(!ModuleAxis->getInput(MAXIS_inProbe)->getNow())
		      iOperation=2;
		     else
		 	  iOperation=3;
		  

         driveProbe->startMovPos(driveProbe->minPosition(),m_Fprobe/60);
		 break;

 case 2: if(ModuleAxis->isLatchProbe2())
		  {
          qDebug()<<"go Back 2";

          driveProbe->startMovPos(ModuleAxis->getLatchProbe2(driveProbe->getAxis()->getIndex())*driveProbe->dimension()
                                  +hProbeData.zPos-hProbeData.hTablet
                                  ,0);

		  iOperation=4;
		  }
		 else
		  {
		  sendMessage(tr("no sensor signal"),"inProbe",0);
          resetAuto();
	      QTimer::singleShot(10,this,SLOT(setFinished()));
		  }

		 break;	

 case 3: if(ModuleAxis->isLatchProbe3())
		  {
          qDebug()<<"go Back 3";

          driveProbe->startMovPos(ModuleAxis->getLatchProbe3(driveProbe->getAxis()->getIndex())*driveProbe->dimension()
                                 +hProbeData.zPos-hProbeData.hTablet
                                 ,0);

		  iOperation=4;
          }
         else
		  {
		  sendMessage(tr("no sensor signal"),"inProbe",0);
          resetAuto();
	      QTimer::singleShot(10,this,SLOT(setFinished()));
		  }
		 break;	

 case 4: resetAuto();
         setCurPositionSC(driveProbe->getName(),hProbeData.zPos);

         QTimer::singleShot(10,this,SLOT(setFinished()));
	     break;
 }

return 1;
}


void WLMillMachine::setCurPositionSC(QString nameCoord,double pos)
{
WLGPoint curPos=getCurrentPositionActivSC();
WLGPoint newPos=curPos;
WLGPoint SCG;

int iSC=m_GCode.getActivSC(&SCG);

qDebug()<<"curPos"<<curPos.toString();
//newPos.fromM(getGCode()->getSC(getGCode()->getActivSC()).to6D().toM().inverted()*curPos.to6D().toM());

if(nameCoord=="X") newPos.x=pos;
else
if(nameCoord=="Y") newPos.y=pos;
else
if(nameCoord=="Z") newPos.z=pos+getGCode()->getHofst();
else
if(nameCoord=="A") newPos.a=pos;
else
if(nameCoord=="B") newPos.b=pos;
else
if(nameCoord=="C") newPos.c=pos;
else
if(nameCoord=="U") newPos.u=pos;
else
if(nameCoord=="V") newPos.v=pos;
else
if(nameCoord=="W") newPos.w=pos;


WLFrame    OffsetSC;
WLFrame newOffsetSC;
WLFrame    newPosFr;
WLFrame    curPosFr;

curPosFr.x=curPos.x;
curPosFr.y=curPos.y;
curPosFr.z=curPos.z;
curPosFr.a=-m_GCode.getRefPoint0SC(iSC).a;

newPosFr.x=newPos.x;
newPosFr.y=newPos.y;
newPosFr.z=newPos.z;
newPosFr.a=-m_GCode.getRefPoint0SC(iSC).a;

OffsetSC.x=SCG.x;
OffsetSC.y=SCG.y;
OffsetSC.z=SCG.z;
OffsetSC.a=m_GCode.getRefPoint0SC(iSC).a;

newOffsetSC.fromM(newPosFr.toM().inverted()*curPosFr.toM()*OffsetSC.toM());

WLGPoint newSCG=SCG-(newPos-curPos);

newSCG.x=newOffsetSC.x;
newSCG.y=newOffsetSC.y;
newSCG.z=newOffsetSC.z;

m_GCode.setOffsetSC(iSC,newSCG);
}

double WLMillMachine::getCurPosition(QString name)
{
WLGPoint GP=getCurrentPosition();

name=name.toUpper();

if(name=="X") return GP.x; else
if(name=="Y") return GP.y; else
if(name=="Z") return GP.z; else
if(name=="A") return GP.a; else
if(name=="B") return GP.b; else
if(name=="C") return GP.c; else
if(name=="U") return GP.u; else
if(name=="V") return GP.v; else
if(name=="W") return GP.w; else

    return 0;
}

QString WLMillMachine::getCurPosition()
{
QString ret;

WLGPoint GP=getCurrentPosition();

ret+="G53 ";

if(getDrive("X")) ret+="X"+QString::number(GP.x);
if(getDrive("Y")) ret+="Y"+QString::number(GP.y);
if(getDrive("Z")) ret+="Z"+QString::number(GP.z);
if(getDrive("A")) ret+="A"+QString::number(GP.a);
if(getDrive("B")) ret+="B"+QString::number(GP.b);
if(getDrive("C")) ret+="C"+QString::number(GP.c);
if(getDrive("U")) ret+="U"+QString::number(GP.u);
if(getDrive("V")) ret+="V"+QString::number(GP.v);
if(getDrive("W")) ret+="W"+QString::number(GP.w);

return ret;
}

void  WLMillMachine::rotAboutRotPointSC(int i,float a)
{
m_GCode.rotAboutRotPointSC(i,a);
}


void WLMillMachine::setDriveManualWhell(QString nameDrive,quint8 X1,bool vmode)
{
WLModuleMPG *ModuleMPG=m_motDevice->getModuleMPG();

WLMillDrive *Drive=getDrive(nameDrive,false);

if(ModuleMPG)
{
 if(nameDrive.isEmpty()
  ||Drive==nullptr
  ||Drive->getName().isEmpty())
 {
 ModuleMPG->getMPG(0)->setIndexAxis(0);
 }
 else
  if(isOn())
  {
   Drive->setMainPad();

   Drive->setKSpeed(1);
   Drive->setVmov(0);

   ModuleMPG->getMPG(0)->setVmode(vmode);
   ModuleMPG->getMPG(0)->setIndexAxis(Drive->getAxis()->getIndex()+1);
   ModuleMPG->getMPG(0)->setIndexX(X1);
  }

}

}

void WLMillMachine::goDriveProbe(QString nameDrive,int dir,float F,int type)
{
qDebug()<<"goDriveProbe"<<nameDrive<<F;

if(!verifyReadyMotion()) return;

driveProbe=getDrive(nameDrive,true);

if(isAuto())
   {
   Stop();
   }
else if(driveProbe
     &&(!driveProbe->isMotion())
      &&(driveProbe->getAxis()))
     {
     iDriveDir=dir;
     iOperation=0;
     m_Fprobe=F;

      switch(type)
      {
      case 1:  m_typeAutoMMachine=AUTO_ProbeSD;     break;
      default: m_typeAutoMMachine=AUTO_ProbeEMG;    break;
      }

     driveProbe->reset();
     setAuto();
     updateAuto();
     }
     else
      {
      qWarning()<<"driveProbe is Motion"<<driveProbe->isMotion();
      }

}




void WLMillMachine::goHProbe(float F,bool sd)
{
if(!verifyReadyMotion()) {return;}

driveProbe=getDrive("Z",true);

if(driveProbe)
{
iDriveDir=0;
iOperation=0;
m_Fprobe=F;

if(sd)
  m_typeAutoMMachine=AUTO_HProbeSD;
else
  m_typeAutoMMachine=AUTO_HProbeEMG;

setAuto();
updateAuto();
}

}

void WLMillMachine::goHToolProbe(float F, bool sd)
{
if(!verifyReadyMotion()) {return;}

driveProbe=getDrive("Z",true);

if(driveProbe)
{
iDriveDir=0;
iOperation=0;
m_Fprobe=F;

if(sd)
  m_typeAutoMMachine=AUTO_HToolSD;
else
  m_typeAutoMMachine=AUTO_HToolEMG;

setAuto();
updateAuto();
}
}
/*
void WLMillMachine::goDriveFind(QString nameDrive)
{
qDebug()<<"goDriveFind"<<nameDrive;

if(!verifyReadyMotion()) {return;}

WLMillDrive *Drive=static_cast<WLMillDrive*> (getDrive(nameDrive));

if(Drive->getName().isEmpty())
{
qDebug()<<"emptyName";
}
else    
 {
 if(Drive->isAuto())
    {
    qDebug()<<"already set Auto";
    Drive->reset();
    }
 else if(Drive->getAxis())
        {
        Drive->setMovFind();
        Drive->startTask();
        }
 }
}

void WLMillMachine::goDriveTeach(QString nameDrive)
{
qDebug()<<"goDriveTeach"<<nameDrive;
if(!verifyReadyMotion()) {return;}

WLMillDrive *Drive=static_cast<WLMillDrive*> (getDrive(nameDrive));

if(Drive)
 {
 Drive->reset();
 Drive->setMovTeach();
 Drive->startTask();
 }
}
*/

void WLMillMachine::goDriveTouch(QString nameDrive,int dir,float F)
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
}/*

void WLMillMachine::goDriveManual(QString nameDrive,int IncDec,float step)
{
qDebug()<<"go drive Manual "<<IncDec<<step;

if(IncDec!=0&&!verifyReadyMotion()) return;

WLMillDrive *Drive=static_cast<WLMillDrive*> (getDrive(nameDrive));

if(isAuto())
   {
   Stop();
   }
else
if(Drive
 &&Drive->getAxis())
{
if(IncDec==0)
    Drive->startStop();
 else
 {
 Drive->setVmov(0);
 Drive->startMovManual(IncDec>0,step);
 }
}
}
*/
void WLMillMachine::Pause(bool pause) //остановка в любой момент
{
QMutexLocker locker(&Mutex);

qDebug()<<"MillMachine Pause()"<<pause;
if(isAuto()) 
{
//Stop(); -- иначе пробинг не срабатывает
updateAuto();
}
else if(pause)
     {
     if(isRunList())
      {
      if(m_motDevice->getModulePlanner())
          m_motDevice->getModulePlanner()->pauseMov();

      if(isRunProgram())
          sendMessage("program pause: \""+m_Program->getName()+"\"",QString(" element: %1").arg(m_Program->getLastMovElement()),1);
      }
      else if(!isRunProgram())
           {
           reset();//!!!
           }
     }
     else
       {
       startMovList();
       }
}

void WLMillMachine::on_changedStatusMPlanner(int status)
{
switch(status)
 {
 case MPLANNER_pause:    Flag.set(ma_pause,1);
                         Flag.set(ma_runlist,0);

                         runScript("PAUSE()");    break;

 default: break;
 }
}

float WLMillMachine::calcCorrectSOut(float S)
{
if(isUseCorrectSOut()&&m_correctSList.size()>2)
 {
 if(S<=m_correctSList.first().Sadj) S=m_correctSList.first().Scor;
 else
 if(S>=m_correctSList.last().Sadj)  S=m_correctSList.last().Scor;
 else
 for(int i=1;i<m_correctSList.size();i++)
   {
   if(m_correctSList[i].Sadj>S)
      {
      double k=(m_correctSList[i].Scor-m_correctSList[i-1].Scor)/(m_correctSList[i].Sadj-m_correctSList[i-1].Sadj);
      S=m_correctSList[i-1].Scor+k*(S-m_correctSList[i-1].Sadj);
      break;
      }
   }
 }

return S;
}

float WLMillMachine::calcSOut(float S)
{
float ret;

S=calcCorrectSOut(S);

if(S<=m_minS)  ret=m_minSOut;
  else
  if(S>=m_maxS) ret=m_maxSOut;
  else
  {
  double k=(m_maxSOut-m_minSOut)/(m_maxS-m_minS);
  ret=m_minSOut+k*(S-m_minS);
  } 

return ret;
}

WLGPoint WLMillMachine::getAxisPosition()
{
WLGPoint GP;

if(getDrive("X")) GP.x=getDrive("X")->position();
if(getDrive("Y")) GP.y=getDrive("Y")->position();
if(getDrive("Z")) GP.z=getDrive("Z")->position();
if(getDrive("A")) GP.a=getDrive("A")->position();
if(getDrive("B")) GP.b=getDrive("B")->position();
if(getDrive("C")) GP.c=getDrive("C")->position();
if(getDrive("U")) GP.u=getDrive("U")->position();
if(getDrive("V")) GP.v=getDrive("V")->position();
if(getDrive("W")) GP.w=getDrive("W")->position();

return GP;
}

WLGPoint WLMillMachine::getCurrentPosition(bool real)
{
WLGPoint GP;

if(real)
 {
 if(getDrive("X")) GP.x=getDrive("X")->getRealPosition();
 if(getDrive("Y")) GP.y=getDrive("Y")->getRealPosition();
 if(getDrive("Z")) GP.z=getDrive("Z")->getRealPosition();
 if(getDrive("A")) GP.a=getDrive("A")->getRealPosition();
 if(getDrive("B")) GP.b=getDrive("B")->getRealPosition();
 if(getDrive("C")) GP.c=getDrive("C")->getRealPosition();
 if(getDrive("U")) GP.u=getDrive("U")->getRealPosition();
 if(getDrive("V")) GP.v=getDrive("V")->getRealPosition();
 if(getDrive("W")) GP.w=getDrive("W")->getRealPosition();
 }
else
 {
 if(getDrive("X")) GP.x=getDrive("X")->getViewPosition();
 if(getDrive("Y")) GP.y=getDrive("Y")->getViewPosition();
 if(getDrive("Z")) GP.z=getDrive("Z")->getViewPosition();
 if(getDrive("A")) GP.a=getDrive("A")->getViewPosition();
 if(getDrive("B")) GP.b=getDrive("B")->getViewPosition();
 if(getDrive("C")) GP.c=getDrive("C")->getViewPosition();
 if(getDrive("U")) GP.u=getDrive("U")->getViewPosition();
 if(getDrive("V")) GP.v=getDrive("V")->getViewPosition();
 if(getDrive("W")) GP.w=getDrive("W")->getViewPosition();
 }

return GP;
}

WLGPoint WLMillMachine::getCurrentPositionActivSC()
{
return m_GCode.getPointActivSC(getCurrentPosition(),true);
}

void WLMillMachine::setAuto()
{
if(getMPG()&&isUseMPG())
   getMPG()->setEnable(false);

WLMachine::setAuto();
}

void WLMillMachine::resetAuto()
{
if(getMPG()&&isUseMPG())
   getMPG()->setEnable(true);

WLMachine::resetAuto();
}

void WLMillMachine::setSOut(float S)
{
    tarSOut=S;
    m_motDevice->getModulePlanner()->setSOut(calcSOut(tarSOut)/100);
}


bool WLMillMachine::runGProgram(int istart)
{
//WLFrame Fr;	
//WLElementTraj ETraj;
WLGPoint curPos=getCurrentPosition(true);
QList <WLElementTraj> curTraj;
WLElementTraj           ETraj;
WLElementTraj      startETraj;
QString txt;

MillTraj.clear();

MutexShowTraj.lock();
showMillTraj.clear();
MutexShowTraj.unlock();

baseTraj.clear();

if(MillTraj.isEmpty())
   {//getCurrentPositionActivSC()
   lastGPoint=getCurrentPositionActivSC();
   lastMillGPoint=getAxisPosition();
   }


if(istart>0)
 {
 for(m_iProgram=0;m_iProgram<istart;m_iProgram++)
   {   
   txt=m_Program->getTextElement(m_iProgram);
   WLGProgram::translate(txt,curTraj,lastGPoint,&m_GCode,true);
   } 

 WLGProgram::translate(txt,curTraj,lastGPoint,&m_GCode,m_iProgram);
 }
else
 m_iProgram=0;

Flag.set(ma_runprogram);


QStringList GDrive=QString(GPointNames).split(",");
foreach(QString name,GDrive)
 {
 if(getDrive(name))
  m_nowBL.set(name,getDrive(name)->rot() ? getDrive(name)->getHalfBacklash()
                                         :-getDrive(name)->getHalfBacklash());
 }


if(istart!=0)
{
ETraj.reset();

ETraj.index=m_iProgram;

ETraj.setFast();
ETraj.endPoint=curPos;

if(ETraj.endPoint.z<m_GCode.getG28Position().z)
           ETraj.endPoint.z=m_GCode.getG28Position().z;

ETraj.setLineXYZ(curPos,ETraj.endPoint);

if(curTraj.isEmpty())
 {
 startETraj=ETraj;
 }
 else
 {
 startETraj=curTraj.last();
 curTraj.clear();
 }

curTraj+=ETraj;

ETraj.setFast();
ETraj.startPoint=ETraj.endPoint;
ETraj.endPoint.x=startETraj.endPoint.x;
ETraj.endPoint.y=startETraj.endPoint.y; 
ETraj.setLineXYZ(ETraj.startPoint,ETraj.endPoint);

curTraj+=ETraj;

ETraj.setFast();
ETraj.startPoint=ETraj.endPoint;
ETraj.endPoint.a=startETraj.endPoint.a;
ETraj.endPoint.b=startETraj.endPoint.b;
ETraj.endPoint.c=startETraj.endPoint.c;
ETraj.setLineXYZ(ETraj.startPoint,ETraj.endPoint);

curTraj+=ETraj;

if(!startETraj.isFast())
 {
 if((startETraj.endPoint.z+20)<m_GCode.getG28Position().z)
  {
  ETraj.setFast();
  ETraj.startPoint=ETraj.endPoint;
  ETraj.endPoint.z=startETraj.endPoint.z+20;
  ETraj.setLineXYZ(ETraj.startPoint,ETraj.endPoint);
   
  curTraj+=ETraj;
  } 

 ETraj.setF(startETraj.getF()<=0? 200:startETraj.getF()/2);
 ETraj.startPoint=ETraj.endPoint;
 ETraj.endPoint=startETraj.endPoint;
 ETraj.setLineXYZ(ETraj.startPoint,ETraj.endPoint);
 
 curTraj+=ETraj;
 }

/*
for(int i=0;i<100;i++)
    if(m_GCode.isMCode(i))
        curTraj.last().addM(i);
*/

for(int i=0;i<curTraj.size();i++)
     curTraj[i].setS(m_GCode.getValue('S'));

addElementTraj(curTraj);
}

updateMovProgram();

emit changedTrajSize(MillTraj.size());
emit changedReadyRunList(Flag.set(ma_readyRunList,!MillTraj.isEmpty()));

if(Flag.get(ma_autostart)) startMovList();

return true;
}


bool WLMillMachine::runGCode(QString gtxt) 
{
//WL6DPoint lastGPoint=getCurrentPositionActivSC(); 		 
WLFrame Fr;	
QList <WLElementTraj> curListTraj;
QList <WLElementTraj>    ListTraj;

qDebug()<<"GCode"<<gtxt;

const float simpliD=m_mainDim*(1<<xPD);

WLModulePlanner *ModulePlanner=m_motDevice->getModulePlanner();

if(MillTraj.isEmpty()
&& ModulePlanner->isEmpty()
&&!ModulePlanner->isMoving())
    {
    lastGPoint=m_GCode.getPointActivSC(getCurrentPosition(),true);
    lastMillGPoint=getAxisPosition();
    }

if(WLGProgram::translate(gtxt,curListTraj,lastGPoint,&m_GCode,0))
    {		
    WLElementTraj::simpliTrajectory(ListTraj,curListTraj,simpliD);

	addElementTraj(curListTraj);
	
	if(!curListTraj.isEmpty())
	 {
     if(curListTraj.first().isNoMov()
     &&!isRunProgram())
		 {
	     setSOut(curListTraj.first().getS());		 
	     }
	 }
    /*
	if(curListTraj.size()==1
	 &&curListTraj.first().isNoMov()
	 &&curListTraj.first().isEmptyM())
	{
    curListTraj.clear();
    qDebug()<<"no mov element";
	}
    else*/
	  {
      emit changedTrajSize(MillTraj.size());
      emit changedReadyRunList(Flag.set(ma_readyRunList,!MillTraj.isEmpty()));
	  
      //Flag.set(ma_runscript,m_EVMScript->isBusy());

      if(!isPause())
       {
       if(isRunList())
         {
         updateMovBuf();
         }
       else  if(Flag.get(ma_autostart)
              ||Flag.get(ma_runscript)) Start();
       }
	  }
	return true;
    }

return false;
}

int WLMillMachine::updateMovProgram() 
{
QString txt;
QList<WLElementTraj> simpliTraj;
QList<WLElementTraj> curTraj;
//WLElementTraj ETraj;

float simpliD=(float)m_mainDim*(1<<xPD);

int isimpli;

if(!MillTraj.isEmpty()&&!MillTraj.last().isEmptyM()) return 0;

if(!MillTraj.isEmpty())
qDebug()<<"last M"<<MillTraj.last().isEmptyM();

qDebug()<<"updateMovProgram m_iProgram"<<m_iProgram<<isRunProgram()<<isRunScript()<<m_MList.isEmpty();

if(isRunProgram()
&&!isRunScript()
&&m_MList.isEmpty())
 {
  {
  for(;(MillTraj.size()<100)&&(m_iProgram<m_Program->getElementCount());m_iProgram++)
   {
   txt=m_Program->getTextElement(m_iProgram);
   WLGProgram::translate(txt,curTraj,lastGPoint,&m_GCode,m_iProgram);

   for(int i=0;i<curTraj.size();i++)
	   if(curTraj[i].isEmpty()) curTraj.removeAt(i--);
 
   baseTraj+=curTraj;

   if(!curTraj.isEmpty())
       qDebug()<<"MCode"<<!curTraj.first().isEmptyM();

/*
   if(m_GCode.isGCode(61))
   {
   addElementTraj(baseTraj);
   baseTraj.clear();
   }
   else*/
   if(m_iProgram==(m_Program->getElementCount()-1)
    ||(!curTraj.isEmpty()&&!curTraj.first().isEmptyM())) //если дошли до конца то полностью перебераем и сглаживаем
    {
    isimpli=WLElementTraj::simpliTrajectory(simpliTraj
 	                                       ,baseTraj
 	            		 				   ,simpliD
										   ,false);
	addElementTraj(simpliTraj);

    baseTraj.clear();

    m_iProgram++;
    break;
    }
   else
    {
	isimpli=WLElementTraj::simpliTrajectory(simpliTraj
 	                                       ,baseTraj
 	            		 				   ,simpliD
 								           ,true);
    

    if(isimpli<baseTraj.size()) //если сгладили и дошли до точки, но не до конца
      {		  
	  if(simpliTraj.size()==2
	   &&simpliTraj[0].isLine()
	   &&simpliTraj[1].isLine())
       {
       simpliTraj[0].endPoint=simpliTraj[1].endPoint;
       simpliTraj.removeLast();
       }	  		

      addElementTraj(simpliTraj);

      baseTraj=baseTraj.mid(isimpli+1);
      }
    }
	
   }  
  }
 }
return 1;
}

bool WLMillMachine::verifyReadyMotion()
{
if(!isOn())
   {sendMessage(metaObject()->className(),tr("is off!"),0); return false;}
if(getMotionDevice()->getModuleAxis()->getInput(MAXIS_inEMGStop)->getNow())
   {sendMessage(nameClass(),tr("wrong state")+"(inEMGStop=0)",0);return false;}
if(getMotionDevice()->getModuleAxis()->getInput(MAXIS_inSDStop)->getNow())
   {sendMessage(nameClass(),tr("wrong state")+"(inSDStop=0)",0);return false;}

return true;
}

bool verifyLineHeightMap (QList<WLElementTraj> &Traj)
{
/*
QList<WLElementTraj> newTraj;

for(int i=0;i<Traj.size();i++)
 {
 if(!Traj[i].isLine()) return false;
   {
   Traj[i]

   }
 }
*/
return true;
}

void WLMillMachine::addHeightMap(QList<WLElementTraj> &Traj,double dist)
{
WLElementTraj ET;

QList<WLElementTraj> newTraj;
QList<WL6DPoint>      points;


WLGPoint GPointS,GPointE;

double addZ=5;

bool ok;

//if(heightMap

for(int i=0;i<Traj.size();i++) {
 if(Traj[i].isLine()) {
    points=Traj[i].calcPoints(&ok,&m_GModel,dist);

    for(int j=0;j<points.size();j++)
      {
      points[i].z+=m_mapHeight.getHeight(points[i].to3Df());
      }

    ET=Traj[i];

    for(int j=0;j<(points.size()-1);j++){

      //addZ+=0.01;

     qDebug()<<j<<points[j].toString();

     GPointS.from6D(points[j]);
     GPointE.from6D(points[j+1]);

     ET.setLineXYZ(GPointS,GPointE);

     newTraj+=ET;

     if(j==0)
        ET.clearMList();
     }

    }
 }


Traj=newTraj;
}

#define useULine
void WLMillMachine::addSmooth(QList<WLElementTraj> &addTraj)
{
if(!MillTraj.isEmpty())
    {
    addTraj.prepend(MillTraj.takeLast());

    MutexShowTraj.lock();
    showMillTraj.removeLast();
    MutexShowTraj.unlock();
    }

WLElementTraj ET;
WL3DPoint PS,PE,PO,Pm,P;
WLGPoint GPm;
float B;
float V=0,L=0;
bool ok;

#ifndef useULine
QMatrix3x3 T;
T(0,0)= 1; T(0,1)= 0; T(0,2)= 0;
T(1,0)=-3; T(1,1)= 4; T(1,2)=-1;
T(2,0)= 2; T(2,1)=-4; T(2,2)= 2;

double ax[3],ay[3],az[3],dt;

dt=1.0f/20;
#endif


for(int i=1;i<addTraj.size();i++)
  {
  qDebug()<<"addTraj.smooth"<<addTraj[i].getG64P();
  if(addTraj[i-1].isNoMov()
   ||addTraj[i].isNoMov()
   ||addTraj[i-1].isCirc()
   ||addTraj[i].isCirc()
   ||!addTraj[i-1].isEmptyM()
   ||!addTraj[i].isEmptyM()
   ||addTraj[i-1].isFast()
   ||addTraj[i].isFast()
   ||addTraj[i].isBacklash()
   ||addTraj[i-1].isBacklash()
   ||addTraj[i].getG64P()==0.0f
   ) continue;

  ET=addTraj[i];

  qDebug()<<addTraj[i-1].startV.to3D().toString()<<" "<<addTraj[i-1].startV.to3D().toString();

  B=calcAngleGrd(addTraj[i-1].startV.to3D(),addTraj[i].startV.to3D())/2;


  if(B>0.1f)
//  if(qAbs(B) <(90-smoothAng)
//   &&qAbs(B*2)>(smoothAng+0.1))
   {
   V=2.0f*addTraj[i].getG64P()/sin(B/180.0f*M_PI);
   qDebug()<<addTraj[i-1].startV.to3D().toString()<<" "<<addTraj[i-1].startV.to3D().toString();

   V=qMin((float)V,qMin(addTraj[i-1].movDistance*0.95f,addTraj[i].movDistance)/2.0f);

   L=V*sin(B/180.0*M_PI)/2.0;

   PO=addTraj[i-1].endPoint.to3D();

   PS=addTraj[i-1].endPoint.to3D();
   PE=addTraj[i].startPoint.to3D();

   PS-=addTraj[i-1].endV.to3D()*V;
   PE+=addTraj[i].startV.to3D()*V;

   addTraj[i-1].endPoint.x=PS.x;
   addTraj[i-1].endPoint.y=PS.y;
   addTraj[i-1].endPoint.z=PS.z;

   addTraj[i].startPoint.x=PE.x;
   addTraj[i].startPoint.y=PE.y;
   addTraj[i].startPoint.z=PE.z;

   GPm=addTraj[i].startPoint;

   Pm=((PS+PE)/2-PO).normalize()*L+PO;

#ifndef useULine
   ax[0]=PS.x*T(0,0)+Pm.x*T(0,1)+PE.x*T(0,2);
   ax[1]=PS.x*T(1,0)+Pm.x*T(1,1)+PE.x*T(1,2);
   ax[2]=PS.x*T(2,0)+Pm.x*T(2,1)+PE.x*T(2,2);

   ay[0]=PS.y*T(0,0)+Pm.y*T(0,1)+PE.y*T(0,2);
   ay[1]=PS.y*T(1,0)+Pm.y*T(1,1)+PE.y*T(1,2);
   ay[2]=PS.y*T(2,0)+Pm.y*T(2,1)+PE.y*T(2,2);

   az[0]=PS.z*T(0,0)+Pm.z*T(0,1)+PE.z*T(0,2);
   az[1]=PS.z*T(1,0)+Pm.z*T(1,1)+PE.z*T(1,2);
   az[2]=PS.z*T(2,0)+Pm.z*T(2,1)+PE.z*T(2,2);

   ET.setF(addTraj[i-1].getF());

   WLGPoint SGP;
   WLGPoint  GP;

   SGP=addTraj[i-1].endPoint;
   GP=SGP;

   for(float d=dt;d<1;d+=dt)
    {
    GP.x=ax[0]+ax[1]*d+ax[2]*d*d;
    GP.y=ay[0]+ay[1]*d+ay[2]*d*d;
    GP.z=az[0]+az[1]*d+az[2]*d*d;

    ET.setLineXYZ(SGP,GP);
    ET.calcPoints(&ok,getGModel());
    addTraj.insert(i++,ET);

    SGP=GP;
    }
#else
   GPm.x=Pm.x;
   GPm.y=Pm.y;
   GPm.z=Pm.z;

   ET.setULineXYZ(addTraj[i-1].endPoint,GPm,addTraj[i].startPoint);
   //ET.setLineXYZ(addTraj[i-1].endPoint,addTraj[i].startPoint);
   ET.setF(addTraj[i-1].getF());
   ET.calcPoints(&ok,getGModel());

   addTraj.insert(i++,ET);
#endif

   }
  }
}

void WLMillMachine::addCalcGModel(QList<WLElementTraj> &addTraj)
{
QList<WLElementTraj> addModelTraj;
bool ok;

for(int i=0;i<addTraj.size();i++)
   {
   if(i>0)
       {
       addTraj[i].startPoint=addTraj[i-1].endPoint;
       }

   if(getDrive("A")
    &&getDrive("A")->getType()==WLDrive::Rotary
    &&getDrive("A")->isInfinity())
      addTraj[i].endPoint.a=getDrive("A")->calcRotaryInfEndPosition(addTraj[i].startPoint.a,addTraj[i].endPoint.a);

   if(getDrive("B")
    &&getDrive("B")->getType()==WLDrive::Rotary
    &&getDrive("B")->isInfinity())
      addTraj[i].endPoint.b=getDrive("B")->calcRotaryInfEndPosition(addTraj[i].startPoint.b,addTraj[i].endPoint.b);

   if(getDrive("C")
    &&getDrive("C")->getType()==WLDrive::Rotary
    &&getDrive("C")->isInfinity())
      addTraj[i].endPoint.c=getDrive("C")->calcRotaryInfEndPosition(addTraj[i].startPoint.c,addTraj[i].endPoint.c);

   //addTraj[i].calcPoints(&ok,getGModel());

   getGModel()->setOffsetFrame(getGCode()->getSC(getGCode()->getActivSC()).to3D());

   addModelTraj+=addTraj[i].calcModelPoints(&ok,getGModel(),2);
   }

addTraj=addModelTraj;
}

void WLMillMachine::addBacklash(QList<WLElementTraj> &Traj)
{
//перебор и добавление отработки люфтов
//можно сделать в реальном времени
WLElementTraj ETraj;
//WL3DPoint nowBL;
WLGPoint nextBL;
WLGPoint nextNBL;

WLGPoint deltaBL;
WLGPoint lastDeltaBL;

WLGPoint lastBL;
WLGPoint movV;
WLGPoint movNV;
WLGPoint lastMBL;

QStringList GDrive=QString(GPointNames).split(",");

lastDeltaBL=m_nowBL;

bool ok;

for(int i=0;i<Traj.size();i++)
{
//qDebug()<<"Traj:"<<Traj[i].str;

if(Traj[i].getType()==WLElementTraj::nomov) continue;

movV=Traj[i].isCirc() ? Traj[i].startV+Traj[i].endV : Traj[i].startV;

if((i+1)<Traj.size())
 movNV=Traj[i+1].isCirc() ? Traj[i+1].startV+Traj[i+1].endV : Traj[i+1].startV;
else
 movNV=movV;

nextNBL=WLGPoint();
nextBL=m_nowBL;

foreach(QString name,GDrive)
{
 if(getDrive(name))
 {
  if(movV.get(name)!=0.0)
     {
   //  qDebug()<<"name !=0"<<name<<movV.get(name);
     nextBL.set(name,movV.get(name) > 0 ?  getDrive(name)->getHalfBacklash():-getDrive(name)->getHalfBacklash());
     }
    /* else
      {
      if(movNV.get(name)!=0&&isBLNextMov())	nextNBL.x= movNV.x > 0 ?   getDrive(name)->getHalfBacklash():-getDrive(name)->getHalfBacklash();
      nextBL.x=m_nowBL.x;
      }*/
 }
}

deltaBL=nextBL-m_nowBL;

//qDebug()<<"movV"<<movV.toString()<<" deltaBL"<<deltaBL.toString()<<" nextBL"<<nextBL.toString()<<" nowBL"<<m_nowBL.toString();;

if(Traj[i].isFast())//if fast set backlash in element
  {
  foreach(QString name,GDrive)
   {
   if(deltaBL.get(name)==0.0
    &&nextNBL.get(name)!=0.0) nextBL.set(name,nextNBL.get(name));
   }
  //if(deltaBL.x==0.0&&nextNBL.x!=0.0) nextBL.x=nextNBL.x;
  Traj[i].setLineXYZ(Traj[i].startPoint+m_nowBL,Traj[i].endPoint+nextBL);
  }
else  if(!deltaBL.isNull())
        {
        ETraj=Traj[i];
        ETraj.setBckl();
        ETraj.setLineXYZ(Traj[i].startPoint+m_nowBL,Traj[i].startPoint+nextBL);

        if(m_Fbacklash!=0.0f)    ETraj.setF(m_Fbacklash);

        ETraj.calcPoints(&ok,getGModel());

        Traj.insert(i,ETraj);
        }
       else  if(Traj[i].isCirc())
             {
             Traj[i].setCircleXY(Traj[i].startPoint+m_nowBL
                                ,Traj[i].centerPoint+m_nowBL
                                ,Traj[i].endPoint+m_nowBL
                                ,Traj[i].isCCW()
                                ,Traj[i].plane);
              }
             else
              {
              foreach(QString name,GDrive)
               {
               if(deltaBL.get(name)==0.0
                &&nextNBL.get(name)!=0.0) nextBL.set(name,nextNBL.get(name));
               }

              Traj[i].setLineXYZ(Traj[i].startPoint+m_nowBL
                                   ,Traj[i].endPoint+nextBL);
              }


lastDeltaBL=deltaBL;
m_nowBL=nextBL;
}

}

int WLMillMachine::updateMovBuf() 
{
qDebug()<<"update MovBuf"<<Flag.get(ma_runprogram);

QMutexLocker locker(&MutexMillTraj);

WLModulePlanner *ModulePlanner=m_motDevice->getModulePlanner();

if(!ModulePlanner) return 0;

if(Flag.get(ma_runprogram)) // if run program
  {    
  if(!ModulePlanner->isEmpty())
      {
      m_Program->setLastMovElement(ModulePlanner->getCurIdElement());
      }

  updateMovProgram();
  }

if(!Flag.get(ma_runlist)) return 0;

if(isEmptyMotion())  return 1;

if(0<MillTraj.size()
 &&MillTraj.size()<=1 //wait 1 element in buf
 &&(!m_MList.isEmpty()||!MillTraj.first().isEmptyM())
 &&ModulePlanner->isEmpty()
 &&!ModulePlanner->isMoving())
       {
       m_MList=MillTraj.first().getMList();
       MillTraj.first().clearMList();
       runMScript(m_MList.takeFirst());
       }

while((ModulePlanner->getFree()>0)
    &&(!MillTraj.isEmpty())) //если можно отправлять
{
if(!MillTraj.first().isEmptyM())
{
qDebug()<<"takeMovElement M";
break;
}
else
{
WLElementTraj ME=MillTraj.takeFirst();

qDebug()<<"takeMovElement";

if(ME.getType()!=WLElementTraj::nomov) 
{
QVector <long> sPos;
QVector <long> ePos;
QVector <long> distPos;
QVector <long> mPos;
QVector <long> cPos;
QVector <quint8> indexs;

double dFxyz;
double dF;
double dFscale;
double dL;
double kF;
qint64 pos;
quint8 i=0;

if(lastEndPos.isEmpty())
{
foreach(WLMillDrive *mD,millDrives)
     lastEndPos+=mD->position();
}

foreach(WLMillDrive *mD,millDrives)
{
if(!mD->getAxis()) continue;

pos=ME.startPoint.get(mD->getName())/mD->dimension();
sPos+=pos;

pos=ME.midPoint.get(mD->getName())/mD->dimension();
mPos+=pos;

pos=ME.endPoint.get(mD->getName())/mD->dimension();
ePos+=pos;

distPos+=ePos.last()-sPos.last();

pos=ME.centerPoint.get(mD->getName())/mD->dimension();
cPos+=pos;

indexs+=i;

i++;
}


switch(ME.Type)
{
case WLElementTraj::line:
                           dFxyz=0;
                           dF=0;
                           dFscale=0;

                           if(!isUseGModel())
                           {
                           foreach(WLMillDrive *mD,millDrives)
                            {
                            dL=(ME.endPoint.get(mD->getName())-ME.startPoint.get(mD->getName()))/mD->dimension();
                            dL*=dL;

                            dF+=dL;

                            if(mD->getName()=="X"
                             ||mD->getName()=="Y"
                             ||mD->getName()=="Z") dFxyz+=dL;
                            }

                           kF= dFxyz!=0.0 ? sqrt(dF/dFxyz) : 1;
                           }
                           else
                           {
                           foreach(WLMillDrive *mD,millDrives)
                            {
                            dL=(ME.endPoint.get(mD->getName())-ME.startPoint.get(mD->getName()))/mD->dimension();

                            dF+=dL*dL;

                            dL*=mD->dimension()/m_mainDim;

                            dFscale+=dL*dL;
                            }

                           kF= sqrt(dF/dFscale);
                           }

                           //qDebug()<<"ME.speedF"<<ME.speedF<<kF;

                           if(kF!=0.0)
                              {							    
                              ModulePlanner->addLine (MASK_abs
                                                    |(ME.isFast()  ? MASK_fline:0)
                                                    |(ME.isSmooth()? MASK_ensmooth:0)
                                                    ,indexs.size()
                                                    ,indexs.data()
                                                    ,ePos.data()
                                                    ,calcSOut(ME.speedS)/100
                                                    ,(kF*ME.speedF/60)/m_mainDim
                                                    ,ME.index);
                              }                            
                           break;

case WLElementTraj::uline:
                              ModulePlanner->addULine(MASK_abs
                                                     |(ME.isFast()  ? MASK_fline:0)
                                                     |(ME.isSmooth()? MASK_ensmooth:0)
                                                     ,indexs.size()
                                                     ,indexs.data()
                                                     ,ePos.data()
                                                     ,mPos.data()
                                                     ,calcSOut(ME.speedS)/100
                                                     ,(ME.speedF/60)/m_mainDim
                                                     ,ME.index);                              
                           
                          break;

case WLElementTraj::circ:
                          if(!getDrive("X")||!getDrive("Y"))
                             {
                             setMessage("Machine",tr("error set circle"),-1);
                             break;
                             }

                          long ePosIJK[3];
                          long cPosIJ[2];
                          
                          quint8 Ib=0;
                          quint8 Jb=1;
                          quint8 Kb= getDrive("Z") ? 2 :0;

                          quint8 I,J,K;

                          switch(ME.plane)
                          {                           
                          case 18: I=Kb;J=Ib;K=Jb; break;
                          case 19: I=Jb;J=Kb;K=Ib; break;
                          default: I=Ib;J=Jb;K=Kb; break;
                          }                          
                          

                          cPosIJ[0]=cPos[I];
                          cPosIJ[1]=cPos[J];

                          ePosIJK[0]=ePos[I];
                          ePosIJK[1]=ePos[J];
                          ePosIJK[2]=ePos[K];

                          ePos[0]=ePosIJK[0];
                          ePos[1]=ePosIJK[1];


                          indexs[0]=I;
                          indexs[1]=J;


                          if(getDrive("Z"))
                           {
                           ePos[2]=ePosIJK[2];
                           indexs[2]=K;
                           }
                         // qDebug()<<"EPos"<<ePos[0]<<ePos[1]<<ePos[2];
                         // qDebug()<<"CPos"<<cPos[0]<<cPos[1]<<cPos[2];

                         ModulePlanner->addCirc(MASK_abs
                                            |(ME.isCCW()    ? MASK_ccw:0)
                                            |(ME.isFast()   ? MASK_fline:0)
                                            |(getDrive("Z") ? MASK_circxyz:0)
                                            |(ME.isSmooth() ? MASK_ensmooth:0)
                                            ,indexs.size()
                                            ,indexs.data()
                                            ,ePos.data()
                                            ,cPosIJ
                                            ,calcSOut(ME.speedS)/100
                                            ,(ME.speedF/60)/m_mainDim
  	                       					,ME.index);
						  break;

}


}
}
}


emit changedTrajSize(MillTraj.size());

return (ModulePlanner->getFree()>0)&&(!MillTraj.isEmpty())&&(!m_EVMScript->isBusy());
}


int WLMillMachine::updateMovList()
{
return 1;
}





void  WLMillMachine::addElementTraj(QList<WLElementTraj>  ListTraj)
{
WLElementTraj ETraj;
QList<WLElementTraj>  addTraj;
QList<WLElementTraj>  addModelTraj;
bool ok;

if(!ListTraj.isEmpty())
{
while(!ListTraj.isEmpty())
    { 
    ETraj=ListTraj.takeFirst();

    if(ETraj.isCirc())
        addTraj+=addCirclePoints(ETraj);
      else
        addTraj+=ETraj;
    }

for(int i=0;i<addTraj.size();i++)
   {
   if(i==0)
      addTraj.first().startPoint=lastMillGPoint;
    else
       {
       addTraj[i].startPoint=addTraj[i-1].endPoint;
       }

   addTraj[i].calcPoints(&ok,getGModel());
   }


if(isUseGModel())
    addCalcGModel(addTraj);

lastMillGPoint=addTraj.last().endPoint;

addBacklash(addTraj);
addSmooth(addTraj);
//G64 P - ULine

foreach(WLElementTraj ET,addTraj)
 {
 ET.setScript(Flag.get(ma_runscript));
 }

MillTraj+=addTraj;

MutexShowTraj.lock();
showMillTraj+=addTraj;
MutexShowTraj.unlock();
}

}



void WLMillMachine::updateInput()
{
//QMutexLocker locker(&MutexInput);
WLModuleAxis *ModuleAxis=m_motDevice->getModuleAxis();


if(ModuleAxis->getInput(MAXIS_inEMGStop)->getCond()>1) emit changedEMG(ModuleAxis->getInput(MAXIS_inEMGStop));

if(ModuleAxis->getInput(MAXIS_inSDStop)->getCond()==2) //если была нажата
    {
  //  emit sendPause(tr("the stop button")+" SD-stop "+tr("is pressed"));
    sendMessage("WLMill",tr("the stop button")+" SD-stop "+tr("is pressed"),0);
  //saveLog("Machine",("the stop button is pressed"));
    }

if(ModuleAxis->getInput(MAXIS_inEMGStop)->getCond()==2) //если была нажата
	{
    emit sendPause(tr("the stop button")+" EMG-stop "+tr("is pressed"));
  //saveLog("Machine",("the stop button is pressed"));
	}

if(ModuleAxis->getInput(MAXIS_inEMGStop)->getCond()==3) //если была отжата
    {
  //saveLog("Machine",("the stop button is pressed"));		
	}

}

QList<WLElementTraj>  WLMillMachine::addCirclePoints(WLElementTraj  _ETraj)
{
qDebug()<<"addCirclePonts";
QList<WLElementTraj> ListTraj;

///ETraj.Points.clear();
WLElementTraj  ETraj=_ETraj;

bool addPointXAxis;
bool addPointYAxis;

ETraj.startPoint =WLGCode::convertPlane(_ETraj.startPoint,_ETraj.plane,true);
ETraj.centerPoint=WLGCode::convertPlane(_ETraj.centerPoint,_ETraj.plane,true);
ETraj.endPoint   =WLGCode::convertPlane(_ETraj.endPoint,_ETraj.plane,true);

WLMillDrive *Xd=getDrive("X");
WLMillDrive *Yd=getDrive("Y");
WLMillDrive *Zd=getDrive("Z");

switch(ETraj.plane)
{
case 17: addPointXAxis=Xd->getBacklash()!=0;
	     addPointYAxis=Yd->getBacklash()!=0;
		 break;
case 18: addPointXAxis=Zd->getBacklash()!=0;
	     addPointYAxis=Xd->getBacklash()!=0;
		 break;
case 19: addPointXAxis=Yd->getBacklash()!=0;
	     addPointYAxis=Zd->getBacklash()!=0;
		 break;

default: addPointXAxis=addPointYAxis=false;
}

if(ETraj.isSpiral()
 ||ETraj.isCirc())
   {
   double Ast=ETraj.startPoint.to3D().getAxy(ETraj.centerPoint.to3D());
   double Aen=ETraj.endPoint.to3D()  .getAxy(ETraj.centerPoint.to3D());
   double   R=ETraj.endPoint.to3D()  .getRxy(ETraj.centerPoint.to3D());

   if((ETraj.isCCW()) &&(Aen<=Ast)) Aen+=2*M_PI;
   if((!ETraj.isCCW())&&(Aen>=Ast)) Aen-=2*M_PI;

   Ast*=180/M_PI;
   Aen*=180/M_PI;

   if(qAbs(Aen-Ast)>300) addPointXAxis=true;

   int iAst=qRound(Ast);
   int iAen=qRound(Aen);
   
   float zA=(ETraj.endPoint.z-ETraj.startPoint.z)
	        /qAbs(iAen-iAst);

  // qDebug("Ast/en= %d / %d",iAst,iAen);

   int idA=ETraj.isCCW()? 1:-1;

   qDebug()<<"addPoinXYAxis"<<addPointXAxis;
   qDebug()<<"addPointYAxis"<<addPointYAxis;

   if(addPointXAxis
	||addPointYAxis)
   {
   for(int iAnow=iAst+idA;(iAst!=iAen)&&(iAnow!=iAen);iAnow+=idA)
   {   //qDebug()<<"iAnow"<<iAnow;
    switch(iAnow)
    {
    case -720:
    case -360:
    case    0:
    case  360:
	case  720:  if(addPointXAxis)
				{
		        ListTraj+=ETraj;
       		    ListTraj.last().endPoint=ListTraj.last().centerPoint;
				ListTraj.last().endPoint.x+=R;
			    ListTraj.last().endPoint.z+=zA*qAbs(iAnow-iAst);
				}
    		   //qDebug("add Right");
    		   break;
    case -990:
    case -630:
    case -270:
    case   90:
    case  450:
    case  810: if(addPointYAxis)
				{
		        ListTraj+=ETraj;
       		    ListTraj.last().endPoint=ListTraj.last().centerPoint;
				ListTraj.last().endPoint.y+=R;
			    ListTraj.last().endPoint.z+=zA*qAbs(iAnow-iAst);
				}
    		   //qDebug("add Up");
    		   break;
    case -900:
    case -540:
    case -180:
    case  180:
    case  540:
    case  900: if(addPointXAxis)
				{
		        ListTraj+=ETraj;
       		    ListTraj.last().endPoint=ListTraj.last().centerPoint;
				ListTraj.last().endPoint.x-=R;
			    ListTraj.last().endPoint.z+=zA*qAbs(iAnow-iAst);
				}
    		  // qDebug("add Left");
    		   break;
    case -810:
    case -450:
    case  -90:
    case  270:
    case  630: 
	case  990: 	if(addPointYAxis) 
				{
		        ListTraj+=ETraj;
       		    ListTraj.last().endPoint=ListTraj.last().centerPoint;
				ListTraj.last().endPoint.y-=R;
			    ListTraj.last().endPoint.z+=zA*qAbs(iAnow-iAst);
				}
    		  // qDebug("add Down");
    		   break;
    		   
    }

   }
   }

ListTraj+=ETraj;

for(int i=1;i<ListTraj.size();i++)
    {
    ListTraj[i].startPoint=ListTraj[i-1].endPoint;
    }

for(int i=0;i<ListTraj.size();i++)
    {
	ListTraj[i].startPoint =WLGCode::convertPlane(ListTraj[i].startPoint,_ETraj.plane,false);
    ListTraj[i].centerPoint=WLGCode::convertPlane(ListTraj[i].centerPoint,_ETraj.plane,false);
    ListTraj[i].endPoint   =WLGCode::convertPlane(ListTraj[i].endPoint,_ETraj.plane,false);
    }

    }

return ListTraj;
}

bool WLMillMachine::runMScript(int iM)
{
return runScript("M"+QString::number(iM)+"()");
}

bool WLMillMachine::runScript(QString txt)
{
if(m_EVMScript)
    {
    qDebug()<<"runScript"<<txt<<isActiv();
    Flag.set(ma_runscript,m_EVMScript->runFunc(txt));
    return Flag.get(ma_runscript);
    }

return true;
}

void WLMillMachine::setCompleteScript(QString func)
{
qDebug()<<"setCompleteScript"<<func;

Flag.reset(ma_runscript);

if(func.isNull()) return;
else
if(func=="CONTINUE()") {
    Flag.reset(ma_continue);
    m_motDevice->getModulePlanner()->startMov();
    QTimer::singleShot(0,this,SLOT(updateMovBuf()));
   }
else
if(func=="STOP()") {
        Flag.reset(ma_stop);
        setFinished();
       }
else
   setFinished();

}



