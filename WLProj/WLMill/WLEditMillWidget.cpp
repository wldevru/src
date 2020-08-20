#include "wleditmillwidget.h"

WLEditMillWidget::WLEditMillWidget(WLMillMachine *_MillMachine,QDialog *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	MillMachine=_MillMachine;

    ui.sbIndexOutPWM->setRange(0,MillMachine->m_motDevice->getModulePWM()->getSizeOutPWM()-1);
    ui.sbIndexOutPWM->setValue(MillMachine->getIndexSOutPWM());

	ui.sbFreqPWM->setValue(MillMachine->getOutPWM()->freq());
	ui.cbInvPWM->setChecked(MillMachine->getOutPWM()->isInv());

	ui.sbSmax->setValue(MillMachine->Smax());
    ui.sbSmin->setValue(MillMachine->Smin());

	ui.sbSmaxOut->setValue(MillMachine->maxSOut());
    ui.sbSminOut->setValue(MillMachine->minSOut());



	WLModuleAxis *ModuleAxis=static_cast<WLModuleAxis*>(MillMachine->m_motDevice->getModule(typeMAxis));

    ui.editInEMG->  setModule(ModuleAxis->getModuleIOPut());
    ui.editInSD->   setModule(ModuleAxis->getModuleIOPut());
    ui.editInProbe->setModule(ModuleAxis->getModuleIOPut());

    ui.editInEMG->  setLabel("InEMG");
    ui.editInSD->   setLabel("InSD");
    ui.editInProbe->setLabel("InProbe");
		
    ui.editInEMG->  setValue(ModuleAxis->getInput(MAXIS_inEMGStop)->getIndex());
    ui.editInSD->   setValue(ModuleAxis->getInput(MAXIS_inSDStop)->getIndex());
    ui.editInProbe->setValue(ModuleAxis->getInput(MAXIS_inProbe)->getIndex());

	ui.sbSmoothAng->setValue(MillMachine->m_motDevice->getModulePlanner()->getSmoothAng());
	ui.sbWhellSize->setValue(MillMachine->whellSize());

    ui.cbHPause->setChecked(MillMachine->isUseHPause());
    ui.sbHPause->setValue(MillMachine->HPause());
    ui.sbHPause->setEnabled(ui.cbHPause->isChecked());
   // dataPad Pad=MillMachine->getPad("base");

   //ui.sbFg0 ->setRange(0.1,Pad.Vma*60);
   // ui.sbFman->setRange(0.1,Pad.Vma*60);
   // ui.sbFbls->setRange(0.1,Pad.Vma*60);

    //ui.sbFg1 ->setValue(MillMachine->getFeedVG1());
    //ui.sbFman->setValue(MillMachine->getFeedVManual());
	ui.sbFbls->setValue(MillMachine->VBacklash());

	ui.sbTabletHProbe->setValue(MillMachine->getHProbeData().hTablet);
	ui.sbBackZHProbe->setValue(MillMachine->getHProbeData().zPos);

	ui.gbPWMOut->setChecked(MillMachine->isUsePWMS());

	initTableCorrectS();


	if(MillMachine->m_motDevice->getModuleWhell()
	 &&MillMachine->m_motDevice->getModuleWhell()->getWhell(0))
	 {	 
	// ui.gbWhell->setChecked(MillMachine->motDevice->getModuleWhell()->getWhell(0)->getFlag()&WHF_enable);
	 ui.sbWEncoder->setRange(0,MillMachine->m_motDevice->getModuleEncoder()->getSizeEncoder()-1);
	 ui.sbWEncoder->setValue(MillMachine->m_motDevice->getModuleWhell()->getWhell(0)->getEncoder());
	 }
	else
	 ui.gbWhell->setEnabled(false);

    connect(ui.buttonBox,SIGNAL(accepted()),SLOT(onAccept()));
	connect(ui.buttonBox,SIGNAL(rejected()),SLOT(onReject()));

    //connect(ui.pbVCPAccept,SIGNAL(clicked()),SLOT(onSetPort()));

	connect(ui.pbVerError,SIGNAL(clicked()),SLOT(onVerifyError()));

    //updatePort();
	setModal(true);

}

WLEditMillWidget::~WLEditMillWidget()
{

}

void WLEditMillWidget::onVerifyError()
{
QString str;

if(ui.sbBackZHProbe->value()<ui.sbTabletHProbe->value())
str+=tr("Back Z is under height probe")+"\n";

if(str.isEmpty())
	str=tr("No error!!!");

QMessageBox::information(this, tr("Verify error"),str,QMessageBox::Ok);
}

/*
void WLEditMillWidget::updatePort()
{
QList<QSerialPortInfo> portList=QSerialPortInfo::availablePorts(); 
QStringList namePortList;

for(int i=0;i<portList.size();i++)
	namePortList+=portList[i].portName();

ui.cbPorts->clear();
ui.cbPorts->addItems(namePortList);

#if QT_VERSION >= 0x050000
  ui.cbPorts->setCurrentText(MillMachine->motDevice->getPortName());
#else
 ui.cbPorts->setCurrentIndex(ui.cbPorts->findText(MillMachine->motDevice->getPortName()));
#endif

}
*/
/*
void WLEditMillWidget::onSetPort()
{
if(ui.cbPorts->currentText().isEmpty())
 {

 }
else
 {
 //MillMachine->motDevice->closeConnect();
 MillMachine->motDevice->initSerialPort(ui.cbPorts->currentText());
// MillMachine->motDevice->openConnect();
 QMessageBox::information(this,tr("Message"),tr("you need to exit the program to accept changes"));
 }
}
*/

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

void WLEditMillWidget::saveData()
{
MillMachine->setIndexSOutPWM(ui.sbIndexOutPWM->value());
MillMachine->getOutPWM()->setFreq(ui.sbFreqPWM->value());
MillMachine->getOutPWM()->setInv(ui.cbInvPWM->isChecked());

MillMachine->setRangeS(ui.sbSmin->value(),ui.sbSmax->value());
MillMachine->setRangeSOut(ui.sbSminOut->value(),ui.sbSmaxOut->value());

WLModuleAxis *ModuleAxis=static_cast<WLModuleAxis*>(MillMachine->m_motDevice->getModule(typeMAxis));

MillMachine->setHPause(ui.sbHPause->value());

ModuleAxis->setInEMGStop(ui.editInEMG->value());
ModuleAxis->setInSDStop (ui.editInSD->value());
ModuleAxis->setInProbe  (ui.editInProbe->value());

MillMachine->m_motDevice->getModulePlanner()->setSmoothAng(ui.sbSmoothAng->value());
MillMachine->setWhellSize(ui.sbWhellSize->value());

MillMachine->setFeedVBacklash(ui.sbFbls->value());
//MillMachine->setFeedVManual(ui.sbFman->value());
//MillMachine->setFeedVG1(ui.sbFg1->value());

SHProbeData hPData;
hPData.hTablet=ui.sbTabletHProbe->value();
hPData.zPos=ui.sbBackZHProbe->value();

MillMachine->setHProbeData(hPData);

MillMachine->setEnablePWMS(ui.gbPWMOut->isChecked());
MillMachine->setEnableHPause(ui.cbHPause->isChecked());

MillMachine->setHPause(ui.sbHPause->value());

MillMachine->setCorrectSList(getCorrectSList());
MillMachine->setEnableUseCorrectSOut(ui.gbCorrectSOut->isChecked());

if(MillMachine->m_motDevice->getModuleWhell()
 &&MillMachine->m_motDevice->getModuleWhell()->getWhell(0))
	 {	 
	 //MillMachine->motDevice->getModuleWhell()->getWhell(0)->setEnable(ui.gbWhell->isChecked());
	 MillMachine->m_motDevice->getModuleWhell()->getWhell(0)->setEncoder(ui.sbWEncoder->value());
     }


}
