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
connect(ui.pbWriteCloud,SIGNAL(clicked()),SLOT(onWriteCloud()));
connect(ui.pbCopyUID,SIGNAL(clicked()),SLOT(onCopyUID()));

m_timerReboot = new QTimer;
m_timerReboot->setInterval(100);
connect(m_timerReboot,&QTimer::timeout,this,&WLFW::updateRebootProgress);

DFW = new WLDevFW;

connect(DFW,SIGNAL(changedProp(QString)),ui.labelName,SLOT(setText(QString)));
connect(DFW,SIGNAL(changedReady(bool)),this,SLOT(updateReady(bool)));
connect(DFW,SIGNAL(changedConnect(bool)),SLOT(updateConnect(bool)));
connect(DFW,SIGNAL(changedUID96(QString)),SLOT(setUID96(QString)));
connect(DFW,SIGNAL(reconnected()),DFW,SLOT(closeConnect()));

connect(ui.pbReboot,&QPushButton::clicked,this,&WLFW::onPBReboot);
connect(ui.pbUpdate,&QPushButton::clicked,this,&WLFW::onUpdateDevices);


fileName=QCoreApplication::applicationDirPath()+"/FW/";

QDir dir;
dir.mkdir(fileName);

m_netManager = new QNetworkAccessManager;

QTimer::singleShot(500,this,SLOT(onUpdateDevices()));
}

WLFW::~WLFW()
{
delete DFW;
}

void WLFW::onReplyFinished()
{
QNetworkReply *reply=qobject_cast<QNetworkReply *>(sender());

if(reply->error() == QNetworkReply::NoError)
{
if(!fileName.isEmpty())
 {
 QFile File(fileName+"/cloud/"+reply->url().fileName());

 QDir dir;
 dir.mkdir(fileName+"/cloud/");

 qDebug()<<"write from url:"<<reply->url().toString();

 if(File.open(QIODevice::WriteOnly))
     {
     program=reply->readAll();
     qDebug()<<"write cloud file"<<File.write(program);
     File.close();

     if(program.size()==DFW->getModuleFW()->getSizeFW())
        {
        ui.label->setText("write: "+fileName);
        DFW->getModuleFW()->startWriteFW(program);
        }
     else
        {
        QMessageBox::information(this,tr("Message:"),tr("error size file!"));
        }
     }
    else
     {
     QMessageBox::information(this,tr("Message:"),tr("error save file: ")+fileName);
     }


 }
}
else
 {
 QMessageBox::information(this,tr("Message:"),tr("error download: ")+reply->errorString());
 }

disconnect(reply,SIGNAL(finished()),this, SLOT(onReplyFinished()));
reply->deleteLater();

setEnabled(true);
}

void WLFW::updateRebootProgress()
{
m_progressReboot+=(float)m_timerReboot->interval()/(float)m_timeReboot;
ui.progressBar->setValue(m_progressReboot*ui.progressBar->maximum());
}

void WLFW::showEndWrite()
{
QMessageBox::information(this,tr("Message:"),tr("write data complete!"));
}

void WLFW::showEndRead()
{
    QMessageBox::information(this,tr("Message:"),tr("read data complete!"));
}

void WLFW::closeEvent(QCloseEvent *event)
{
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
    ui.gbReadWrite->setEnabled(DFW->getModuleFW()!=nullptr);
	ui.pbFileDevice->setEnabled(List.first()!="WLFW");

   /* if(List.size()>1)
        if(List[1]=="WLM55J"
         ||List[2]=="WLM55J"
         ||List[0]=="WLM100S"
         ||List[2]=="WLM100S")*/ ui.pbReboot->setEnabled(enable);
    }

 if(DFW->getModuleFW())
  {
  connect(DFW->getModuleFW(),SIGNAL(changedProgress(int)),ui.progressBar,SLOT(setValue(int)));;
  connect(DFW->getModuleFW(),SIGNAL(endReadFW()),this,SLOT(saveProgram()));

  connect(DFW->getModuleFW(),SIGNAL(changedActiv(bool)),ui.progressBar,SLOT(setEnabled(bool)));
  connect(DFW->getModuleFW(),SIGNAL(changedActiv(bool)),ui.pbRead,SLOT(setDisabled(bool)));
  connect(DFW->getModuleFW(),SIGNAL(changedActiv(bool)),ui.pbWrite,SLOT(setDisabled(bool)));
  connect(DFW->getModuleFW(),SIGNAL(changedActiv(bool)),ui.pbWriteCloud,SLOT(setDisabled(bool)));

  connect(DFW->getModuleFW(),SIGNAL(endWriteFW()),this,SLOT(showEndWrite()),Qt::QueuedConnection);
  connect(DFW->getModuleFW(),SIGNAL(endReadFW()),this,SLOT(showEndRead()),Qt::QueuedConnection);
  }

 if(DFW->getModuleConnect())
     DFW->getModuleConnect()->setEnableHeart(false);
}
else
 {
 if(DFW->getModuleFW())   disconnect(DFW->getModuleFW(),nullptr);

 ui.gbReadWrite->setEnabled(enable);
 ui.pbFileDevice->setEnabled(enable);
 }

ui.pbCopyUID->setEnabled(enable);
}

void WLFW::onCopyUID()
{
QClipboard *clipboard=QGuiApplication::clipboard();

clipboard->setText(DFW->getUID96());
}

void WLFW::onWriteCloud()
{
QStringList List=DFW->getProp().split(".");
QString suffix;

if(List.size()<3) return;

if(List[0]=="WLFW")
    suffix=List[1]=="B1" ? "_B1": "_B0";

QNetworkRequest request(QUrl("https://raw.githubusercontent.com/wldevru/fw/master/"+List.at(2)+suffix+".wlfw"));

QNetworkReply *reply =  m_netManager->get(request);

connect(reply,SIGNAL(finished()),this, SLOT(onReplyFinished()));

setDisabled(true);
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
setConnect(0);

if(!DFW->getInfo().HA.isNull())
    m_timeReboot=5000;
else
    m_timeReboot=2500;

m_rebootDI=DFW->getInfo();
m_reboot=true;

m_progressReboot=0;
ui.progressBar->reset();

m_timerReboot->start();

setEnabled(false);
QTimer::singleShot(m_timeReboot,this,SLOT(onUpdateDevices()));
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

setEnabled(true);

if(m_reboot)
 {
 m_reboot=false;

 m_timerReboot->stop();
 ui.progressBar->reset();

 for(int i=0;i<m_listDevice.size();i++)
  if(m_listDevice[i].UID96 == m_rebootDI.UID96)
     {
     ui.cbPorts->setCurrentIndex(i);
     onPBConnect();
     }
 }

}

void WLFW::setConnect(bool enable)
{
ui.labelName->setText("no connect");

qDebug()<<"set Connect "<<enable<<ui.cbPorts->currentText();
if(!m_listDevice.isEmpty())
{
 if(enable) {
     DFW->closeConnect();
     DFW->removeModules();
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
//ui.lineEditUID->setText(uid96);
}


void WLFW::onPBRead()
{
program.clear();

QString dir =QFileDialog::getExistingDirectory(this, tr("Save firmware to dir"),fileName);

QStringList List=DFW->getProp().split(".");
QString suffix;

if(!dir.isEmpty())
	{
    if(List[0]=="WLFW")
                suffix=List[1]=="B1" ? "_B1": "_B0";

    fileName = dir+"/"+List[2]+suffix+".wlfw";

    ui.label->setText("read: "+fileName);
    DFW->getModuleFW()->startReadFW(0);
    }	
}

void WLFW::saveProgram()
{
qDebug()<<"saveProgram()";
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
