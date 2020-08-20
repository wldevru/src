#include "wlfw.h"

#include <QSerialPortInfo>
#include <QDebug>
#include <QMessageBox>

WLFW::WLFW(QWidget *parent)
    : QWidget(parent)
{
ui.setupUi(this);

connect(ui.pbRead,SIGNAL(clicked()),SLOT(onPBRead()));
connect(ui.pbWrite,SIGNAL(clicked()),SLOT(onPBWrite()));
connect(ui.pbConnect,SIGNAL(clicked()),SLOT(onPBConnect()));
connect(ui.pbFileDevice,SIGNAL(clicked()),SLOT(onCreateFile()));

QTimer *timer = new QTimer();
connect(timer,SIGNAL(timeout()),SLOT(updatePort()));
//timer->start(250);

DFW = new WLDevFW;

QThread *thread=new QThread;

thread->moveToThread(thread);
thread->start();

connect(DFW,SIGNAL(changedProp(QString)),ui.labelName,SLOT(setText(QString)));
connect(DFW,SIGNAL(changedReady(bool)),this,SLOT(updateReady(bool)));
connect(DFW,SIGNAL(changedConnect(bool)),SLOT(updateConnect(bool)));
connect(DFW,SIGNAL(changedUID96(QString)),SLOT(setUID96(QString)));
connect(DFW,SIGNAL(reconnected()),DFW,SLOT(closeConnect()));

connect(ui.pbReboot,&QPushButton::clicked,this,&WLFW::onPBReboot);
connect(ui.pbUpdate,&QPushButton::clicked,this,&WLFW::onUpdateDevices);


fileName=QCoreApplication::applicationDirPath()+"//FW//";

QDir dir;
dir.mkdir(fileName);

onUpdateDevices();
}

WLFW::~WLFW()
{
delete DFW;
}

void WLFW::showEndWrite()
{
QMessageBox::information(this,tr("Message:"),tr("write data complete!"));
}

void WLFW::showEndRead()
{
QMessageBox::information(this,tr("Message:"),tr("read data complete!"));
}


void WLFW::updateConnect(bool enable)
{
if(!enable)
  {
  ui.labelName->setText("no connect");
  ui.pbReboot->setEnabled(enable);
  }

ui.pbUpdate->setDisabled(enable);
ui.cbPorts->setDisabled(enable);
ui.pbConnect->setText(enable? tr("Disconnect"):tr("Connect"));


}

void WLFW::updateReady(bool enable)
{
if(enable)
{
QStringList List=DFW->getProp().split(".");

if(!List.isEmpty())
    {	
	ui.gbReadWrite->setEnabled(List.first()=="WLFW");
	ui.pbFileDevice->setEnabled(List.first()!="WLFW");

    if(List.size()>2)
        if(List[0]=="WLM55J"
         ||List[2]=="WLM55J"
         ||List[0]=="WLM100S"
         ||List[2]=="WLM100S") ui.pbReboot->setEnabled(enable);
    }

 connect(DFW->getModuleFW(),SIGNAL(changedProgress(int)),ui.progressBar,SLOT(setValue(int)));;
 connect(DFW->getModuleFW(),SIGNAL(endReadFW()),this,SLOT(saveProgram()));

 connect(DFW->getModuleFW(),SIGNAL(changedActiv(bool)),ui.progressBar,SLOT(setEnabled(bool)));
 connect(DFW->getModuleFW(),SIGNAL(changedActiv(bool)),ui.pbRead,SLOT(setDisabled(bool)));
 connect(DFW->getModuleFW(),SIGNAL(changedActiv(bool)),ui.pbWrite,SLOT(setDisabled(bool)));

 connect(DFW->getModuleFW(),SIGNAL(endWriteFW()),this,SLOT(showEndWrite()),Qt::QueuedConnection);
 connect(DFW->getModuleFW(),SIGNAL(endReadFW()),this,SLOT(showEndRead()),Qt::QueuedConnection);

 if(DFW->getModuleConnect())
     DFW->getModuleConnect()->setEnableHeart(false);
}
else
 {
 disconnect(DFW->getModuleFW(),SIGNAL(changedProgress(int)),ui.progressBar,SLOT(setValue(int)));;
 disconnect(DFW->getModuleFW(),SIGNAL(endReadFW()),this,SLOT(saveProgram()));
  
 disconnect(DFW->getModuleFW(),SIGNAL(changedActiv(bool)),ui.progressBar,SLOT(setEnabled(bool)));
 disconnect(DFW->getModuleFW(),SIGNAL(changedActiv(bool)),ui.pbRead,SLOT(setDisabled(bool)));
 disconnect(DFW->getModuleFW(),SIGNAL(changedActiv(bool)),ui.pbWrite,SLOT(setDisabled(bool)));

 disconnect(DFW->getModuleFW(),SIGNAL(endWriteFW()),this,SLOT(showEndWrite()));
 disconnect(DFW->getModuleFW(),SIGNAL(endReadFW()),this,SLOT(showEndRead()));

 ui.gbReadWrite->setEnabled(enable);
 ui.pbFileDevice->setEnabled(enable);
 }
}

void WLFW::onCreateFile()
{
QString dir;

dir=QFileDialog::getExistingDirectory(this, tr("Save File Device"),fileName);

if(!dir.isEmpty())
	{
    DFW->writeToDir(dir);
    }	
}

void WLFW::onPBConnect()
{
setConnect(!DFW->isOpenConnect());
}

void WLFW::onPBReboot()
{
DFW->reboot(ui.pbFileDevice->isEnabled() ? 1:0);
}

void WLFW::onUpdateDevices()
{
ui.cbPorts->clear();

m_listDevice=WLDevice::availableDevices();

foreach(WLDeviceInfo info,m_listDevice)
 {
 ui.cbPorts->addItem(info.name+" ("+info.comPort+info.HA.toString()+") id:"+info.UID96);
 }

ui.pbConnect->setDisabled(m_listDevice.isEmpty());
}

void WLFW::setConnect(bool enable)
{
ui.labelName->setText("no connect");

qDebug()<<"set Connect "<<ui.cbPorts->currentText();
if(!m_listDevice.isEmpty())
{
 if(enable) {
     DFW->setInfo(m_listDevice[ui.cbPorts->currentIndex()]);
     DFW->openConnect();
 }
 else
  {
  DFW->closeConnect();
  DFW->removeModules();
  }
}
}

void WLFW::setUID96(QString uid96)
{
ui.lineEditUID->setText(uid96);
}

void WLFW::updatePort()
{
QList<QSerialPortInfo> portList=QSerialPortInfo::availablePorts(); 
QStringList namePortList;
QString curPort;
int i;

if(portList.size()!=ui.cbPorts->count())
 {
 for(i=0;i<portList.size();i++)
     if(DFW->getPortName()==portList[i].portName()) break;

 for(i=0;i<portList.size();i++)
	 namePortList+=portList[i].portName();

 curPort=ui.cbPorts->currentText();

 ui.cbPorts->clear();
 ui.cbPorts->addItems(namePortList); 
 ui.cbPorts->setEditText(curPort);
 }
}


void WLFW::onPBRead()
{
program.clear();

QString dir =QFileDialog::getExistingDirectory(this, tr("Save firmware to dir"),fileName);

QStringList List=DFW->getProp().split(".");

if(!dir.isEmpty())
	{
    fileName = dir+"/"+List[2]+".wlfw";
    ui.label->setText("read to file\: "+fileName);
    DFW->getModuleFW()->startReadFW(0);
    }	
}

void WLFW::saveProgram()
{
qDebug()<<"saveProgram()";

program=DFW->getModuleFW()->getBufFW();

if(!fileName.isEmpty())
{
QFile File(fileName);

if(File.open(QIODevice::WriteOnly)) 
	{
    qDebug()<<"write file"<<File.write(DFW->getModuleFW()->getBufFW());
	File.close();	
    }
}
}

void WLFW::onPBWrite()
{
program.clear();

if(fileName.isEmpty()) fileName=QCoreApplication::applicationDirPath();

fileName = QFileDialog::getOpenFileName(this, tr("Load firmware from file"),fileName,"wlfw (*.wlfw)");

if(!fileName.isEmpty())
{
QFile File(fileName);

if(File.open(QIODevice::ReadOnly)) 
	{
    program=File.readAll();

	File.close();	
    
    if(program.size()==DFW->getModuleFW()->getSizeFW())
       {
       ui.label->setText("write from file\: "+fileName);
       DFW->getModuleFW()->startWriteFW(program);
	   }
	else
	   {
       QMessageBox::information(this,tr("Message:"),tr("error size file!"));
	   }
    }
}

}
