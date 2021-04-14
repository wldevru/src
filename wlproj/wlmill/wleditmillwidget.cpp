#include "wleditmillwidget.h"

WLEditMillWidget::WLEditMillWidget(WLMillMachine *_MillMachine,QDialog *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	MillMachine=_MillMachine;

    ui.editOutSPWM->setModule(MillMachine->getMotionDevice()->getModulePWM(),false);
    ui.editOutSAOUT->setModule(MillMachine->getMotionDevice()->getModuleAIOPut(),false);

    QButtonGroup *group=new QButtonGroup(this);

    if(ui.editOutSPWM->isEnable()) group->addButton(ui.editOutSPWM->getButton());
    if(ui.editOutSAOUT->isEnable()) group->addButton(ui.editOutSAOUT->getButton());

    ui.gbSOut->setChecked(true);

    ui.editOutSPWM ->setCheckable(true);
    ui.editOutSAOUT->setCheckable(true);

    switch(MillMachine->getMotionDevice()->getModulePlanner()->getTypeSOut())
    {
    case typeEOutPWM:   ui.editOutSPWM->setChecked(true);
                        ui.editOutSPWM->setValue(MillMachine->getMotionDevice()->getModulePlanner()->getISOut());
                        break;

    case typeEAOutput:  ui.editOutSAOUT->setChecked(true);
                        ui.editOutSAOUT->setValue(MillMachine->getMotionDevice()->getModulePlanner()->getISOut());
                        break;

    default: ui.gbSOut->setChecked(false);
             ui.editOutSPWM->setChecked(true);
             break;
    }

    ui.sbPerFpause->setValue(MillMachine->getMotionDevice()->getModulePlanner()->getKFpause()*100);

    group->setExclusive(true);

	ui.sbSmax->setValue(MillMachine->Smax());
    ui.sbSmin->setValue(MillMachine->Smin());

	ui.sbSmaxOut->setValue(MillMachine->maxSOut());
    ui.sbSminOut->setValue(MillMachine->minSOut());

    ui.leStrFindDrivePos->setText(MillMachine->getStrFindDrivePos());

    WLModuleAxis *ModuleAxis=static_cast<WLModuleAxis*>(MillMachine->getMotionDevice()->getModule(typeMAxis));

    ui.editInEMG->  setModule(ModuleAxis->getModuleIOPut());
    ui.editInSD->   setModule(ModuleAxis->getModuleIOPut());
    ui.editInProbe->setModule(ModuleAxis->getModuleIOPut());

    ui.editInEMG->  setLabel("InEMGStop");
    ui.editInSD->   setLabel("InSDStop");
    ui.editInProbe->setLabel("InProbe");
		
    ui.editInEMG->  setValue(ModuleAxis->getInput(MAXIS_inEMGStop)->getIndex());
    ui.editInSD->   setValue(ModuleAxis->getInput(MAXIS_inSDStop)->getIndex());
    ui.editInProbe->setValue(ModuleAxis->getInput(MAXIS_inProbe)->getIndex());

    ui.editInEMG->  setCheckable(true);
    ui.editInSD->   setCheckable(true);
    ui.editInProbe->setCheckable(true);

    ui.editInEMG->  setChecked(ui.editInEMG->  value()!=0);
    ui.editInSD->   setChecked(ui.editInSD->   value()!=0);
    ui.editInProbe->setChecked(ui.editInProbe->value()!=0);

    ui.sbSmoothAng->setValue(MillMachine->getMotionDevice()->getModulePlanner()->getSmoothAng());
    ui.sbHeartMs->setValue(MillMachine->getMotionDevice()->getModuleConnect()->getTimeHeartVal());
    ui.sbTimeoutMs->setValue(MillMachine->getMotionDevice()->getModuleConnect()->getTimeoutConnectVal());

    ui.cbHPause->setChecked(MillMachine->isUseHPause());
    ui.sbHPause->setValue(MillMachine->HPause());
    ui.sbHPause->setEnabled(ui.cbHPause->isChecked());

	ui.sbFbls->setValue(MillMachine->VBacklash());
    ui.sbFprobe->setValue(MillMachine->VProbe());

	ui.sbTabletHProbe->setValue(MillMachine->getHProbeData().hTablet);
	ui.sbBackZHProbe->setValue(MillMachine->getHProbeData().zPos);

    ui.gbPWMOut->setChecked(MillMachine->getMotionDevice()->getModulePlanner()->getTypeSOut()!=typeElement::typeEEmpty);

    ui.cbAutoStart->setChecked(MillMachine->isAutoStart());

    ui.cbUseMPG->setChecked(MillMachine->isUseMPG());

    ui.cbUseDriveA->setChecked(MillMachine->getDrive("A")!=nullptr);
    ui.cbUseDriveB->setChecked(MillMachine->getDrive("B")!=nullptr);
    ui.cbUseGModel->setChecked(MillMachine->isUseGModel());

    ui.sbOffsetHToolProbe->setValue(MillMachine->getGCode()->getOffsetHTool());

    ui.sbAccSOut->setValue(MillMachine->getMotionDevice()->getModulePlanner()->getAccSOut()!=0 ?
                          ui.sbSmaxOut->value()/100.0/1000.0/MillMachine->getMotionDevice()->getModulePlanner()->getAccSOut()
                          :0);
    ui.sbDecSOut->setValue(MillMachine->getMotionDevice()->getModulePlanner()->getDecSOut()!=0 ?
                         -ui.sbSmaxOut->value()/100.0/1000.0/MillMachine->getMotionDevice()->getModulePlanner()->getDecSOut()
                          :0);

	initTableCorrectS();

	connect(ui.pbVerError,SIGNAL(clicked()),SLOT(onVerifyError()));

	setModal(true);

}

WLEditMillWidget::~WLEditMillWidget()
{

}

QString WLEditMillWidget::verifyError()
{
QString str;

if(ui.sbBackZHProbe->value()<ui.sbTabletHProbe->value())
str+=tr("Back Z is under height probe")+"\n";

WLMillDrive *ZD=MillMachine->getDrive("Z");

 if(ui.cbHPause->isChecked()
 &&!ZD->isInfinity()
&&((ZD->maxPosition()<ui.sbHPause->value())||(ZD->minPosition()>ui.sbHPause->value())))
    str+=tr("Pause height off-axis position")+"\n";


return str;
}

bool WLEditMillWidget::getNeedClose() const
{
return m_needClose;
}

void WLEditMillWidget::onVerifyError()
{
    QString str=verifyError();

if(str.isEmpty()) str=tr("No error!!!");

QMessageBox::information(this, tr("Verify error"),str,QMessageBox::Ok);
}

void WLEditMillWidget::accept()
{
m_needClose=saveDataMill();

foreach(QDialog *dialog,dialogList)
                dialog->accept();

QDialog::accept();
}


QList <SCorrectSOut> WLEditMillWidget::getCorrectSList()
{
QList <SCorrectSOut> correctSList;

SCorrectSOut corrS;

for(int i=0;i<ui.twCorrectS->rowCount();i++) 
 {
 corrS.reset();
 
 if(ui.twCorrectS->item(i,0)!=nullptr
  &&ui.twCorrectS->item(i,1)!=nullptr)
  {
  corrS.Sadj=ui.twCorrectS->item(i,0)->data(0).toString().toDouble();
  corrS.Scor=corrS.Sadj*ui.twCorrectS->item(i,1)->data(0).toString().toDouble()/100;

  if(corrS.Sadj!=0&&corrS.Scor!=0) correctSList+=corrS;
  }
 }

return correctSList;
}

void WLEditMillWidget::initTableCorrectS()
{
QList <SCorrectSOut> correctSList=MillMachine->correctSList();

ui.gbCorrectSOut->setChecked(MillMachine->isUseCorrectSOut());

ui.twCorrectS->setColumnCount(2);
ui.twCorrectS->setRowCount(10);

ui.twCorrectS->setHorizontalHeaderLabels (QString("S "+tr("adjusted")+",S "+tr("percent")).split(","));

for(int i=0;i<ui.twCorrectS->rowCount()&&i<correctSList.size();i++)
 {
 ui.twCorrectS->setItem (i,0,new QTableWidgetItem(QString::number(correctSList[i].Sadj)));
 ui.twCorrectS->setItem (i,1,new QTableWidgetItem(QString::number(correctSList[i].Scor/correctSList[i].Sadj*100)));
 }
}

bool WLEditMillWidget::saveDataMill()
{
bool ret=false;

MillMachine->setRangeS(ui.sbSmin->value(),ui.sbSmax->value());
MillMachine->setRangeSOut(ui.sbSminOut->value(),ui.sbSmaxOut->value());

WLModuleAxis *ModuleAxis=static_cast<WLModuleAxis*>(MillMachine->getMotionDevice()->getModule(typeMAxis));

MillMachine->setHPause(ui.sbHPause->value());

ModuleAxis->setInEMGStop(ui.editInEMG->isChecked()  ? ui.editInEMG->value()  :0);
ModuleAxis->setInSDStop (ui.editInSD->isChecked()   ? ui.editInSD->value()   :0);
ModuleAxis->setInProbe  (ui.editInProbe->isChecked()? ui.editInProbe->value():0);

MillMachine->getMotionDevice()->getModulePlanner()->setSmoothAng(ui.sbSmoothAng->value());

MillMachine->getMotionDevice()->getModuleConnect()->setTimersConnect(ui.sbTimeoutMs->value(),ui.sbHeartMs->value());

MillMachine->setFeedVBacklash(ui.sbFbls->value());

SHProbeData hPData;
hPData.hTablet=ui.sbTabletHProbe->value();
hPData.zPos=ui.sbBackZHProbe->value();

MillMachine->setHProbeData(hPData);

MillMachine->setEnableHPause(ui.cbHPause->isChecked());

MillMachine->setHPause(ui.sbHPause->value());
MillMachine->setUseMPG(ui.cbUseMPG->isChecked());

MillMachine->setCorrectSList(getCorrectSList());
MillMachine->setEnableUseCorrectSOut(ui.gbCorrectSOut->isChecked());

MillMachine->setStrFindDrivePos(ui.leStrFindDrivePos->text());
MillMachine->setAutoStart(ui.cbAutoStart->isChecked());
MillMachine->setFeedVProbe(ui.sbFprobe->value());

MillMachine->getMotionDevice()->getModulePlanner()->setKFpause(ui.sbPerFpause->value()/100.0f);

MillMachine->getMotionDevice()->getModulePlanner()->setAccSOut(ui.sbAccSOut->value()!=0 ? ui.sbSmaxOut->value()/100.0/1000.0/ui.sbAccSOut->value():0);
MillMachine->getMotionDevice()->getModulePlanner()->setDecSOut(ui.sbDecSOut->value()!=0 ?-ui.sbSmaxOut->value()/100.0/1000.0/ui.sbDecSOut->value():0);

if(!ui.gbSOut->isChecked())
{
MillMachine->getMotionDevice()->getModulePlanner()->resetElementSOut();
}
else
if(ui.editOutSPWM->isChecked())
{
MillMachine->getMotionDevice()->getModulePlanner()->setElementSOut(typeEOutPWM,ui.editOutSPWM->value());
}
else if(ui.editOutSAOUT->isChecked())
{
MillMachine->getMotionDevice()->getModulePlanner()->setElementSOut(typeEAOutput,ui.editOutSAOUT->value());
}

if(ui.cbUseDriveA->isChecked())
{
if(MillMachine->getDrive("A")==nullptr)
    {
    WLMillDrive *MD = new WLMillDrive("A",MillMachine->getMotionDevice()->getModuleAxis());

    MillMachine->addDrive(MD);
    ret=true;
    }
}
else if(MillMachine->getDrive("A")!=nullptr)
       {
       MillMachine->removeDrive(MillMachine->getDrive("A"));
       ret=true;
       }

if(ui.cbUseDriveB->isChecked())
{
if(MillMachine->getDrive("B")==nullptr)
    {
    WLMillDrive *MD = new WLMillDrive("B",MillMachine->getMotionDevice()->getModuleAxis());

    MillMachine->addDrive(MD);
    ret=true;
    }
}
else if(MillMachine->getDrive("B")!=nullptr)
       {
       MillMachine->removeDrive(MillMachine->getDrive("B"));
       ret=true;
       }

MillMachine->getGCode()->setOffsetHTool(ui.sbOffsetHToolProbe->value());
MillMachine->setEnableGModel(ui.cbUseGModel->isChecked());


return ret;
}


void WLEditMillWidget::keyPressEvent(QKeyEvent *event)
{
event->accept();
}
