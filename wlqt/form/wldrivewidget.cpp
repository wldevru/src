#include "wldrivewidget.h"

WLDriveWidget::WLDriveWidget(WLDrive *_Drive,QWidget *parent)
	: QDialog(parent)
{	
    m_Drive=_Drive;

    WLAxis *Axis=m_Drive->getAxis();

    m_ddim=m_Drive->getDriveDim();

    ui.setupUi(this);

    addTabWidget(new WLPamListWidget(m_Drive,this),tr("motion parametrs"));

    ui.cbTypeDim->addItems(QString(tr("step on size,one step size,ratio A/B")).split(","));
    ui.cbTypeDim->setCurrentIndex(static_cast<int>(m_ddim.type));

    ui.sbDimA->setValue(m_ddim.A);
    ui.sbDimB->setValue(m_ddim.B);

    updateCBDimm(static_cast<int>(m_ddim.type));

    connect(ui.cbTypeDim,SIGNAL(activated(int)),SLOT(updateCBDimm(int)));

    ui.sbPLIM->setValue(m_Drive->maxPosition());
    ui.sbMLIM->setValue(m_Drive->minPosition());
	
    ui.editInALM->setModule(Axis->getModuleIOPut());
    ui.editInORG->setModule(Axis->getModuleIOPut());
    ui.editInPEL->setModule(Axis->getModuleIOPut());
    ui.editInMEL->setModule(Axis->getModuleIOPut());

    ui.editInALM->setLabel("inALM");
    ui.editInORG->setLabel("inORG");
    ui.editInPEL->setLabel("inPEL");
    ui.editInMEL->setLabel("inMEL");

    ui.editInALM->setValue(Axis->getInput(AXIS_inALM)->getIndex());
    ui.editInORG->setValue(Axis->getInput(AXIS_inORG)->getIndex());
    ui.editInPEL->setValue(Axis->getInput(AXIS_inPEL)->getIndex());
    ui.editInMEL->setValue(Axis->getInput(AXIS_inMEL)->getIndex());

    ui.editOutRALM->setModule(Axis->getModuleIOPut(),false);
    ui.editOutENB ->setModule(Axis->getModuleIOPut(),false);

    ui.editOutRALM->setValue(Axis->getOutput(AXIS_outRALM)->getIndex());
    ui.editOutENB ->setValue(Axis->getOutput(AXIS_outENB)->getIndex());

    ui.editOutRALM->setLabel("outRALM");
    ui.editOutENB ->setLabel("outENB");

    ui.cbTypePulse->addItems(QString("SD,CW/CCW,AB,ABx2,ABx4,SDx2,CW/CCWx2").split(","));
	connect(ui.cbTypePulse,SIGNAL(activated(int)),SLOT(updateCBTypePulse(int))); 

	ui.cbTypePulse->setCurrentIndex(Axis->getTypePulse());

    ui.cbInvStep->setChecked(Axis->getOutSDInv()&MAF_invStep);
    ui.cbInvDir ->setChecked(Axis->getOutSDInv()&MAF_invDir);

	ui.comboBoxLogicFind->addItems(QString(tr("no Find,only ORG,only PEL,only MEL,only ORG back,only PEL back,only MEL back")).split(","));

    connect(ui.comboBoxLogicFind,SIGNAL(currentIndexChanged(int)),SLOT(updateFindLogic(int)));

    ui.comboBoxLogicFind->setCurrentIndex(m_Drive->getLogicFindPos());

    ui.sbOrgSize->setValue(m_Drive->getORGSize());
    ui.sbBackFindPosition->setValue(m_Drive->homePosition());
    ui.sbOrgPosition->setValue(m_Drive->getOrgPosition());

    //ui.sbVfind->setRange(0.0001,Drive->Pad->getData("main").Vma);
	connect(ui.sbVfind,SIGNAL(valueChanged(double)),SLOT(updateLabelSDDist(double)));

    ui.sbVfind->setValue(m_Drive->feedVFind());

	ui.cbActInALM->addItems(QString("no,SDstop,EMGStop").split(","));
	ui.cbActInPEL->addItems(QString("no,SDstop,EMGStop").split(","));
	ui.cbActInMEL->addItems(QString("no,SDstop,EMGStop").split(","));

	ui.cbActInALM->setCurrentIndex(Axis->getActIn(AXIS_inALM));
	ui.cbActInPEL->setCurrentIndex(Axis->getActIn(AXIS_inPEL));
	ui.cbActInMEL->setCurrentIndex(Axis->getActIn(AXIS_inMEL));	

	ui.sbDelaySCurve->setValue(Axis->getDelaySCurve());

    ui.cbTypeDrive->setCurrentIndex(m_Drive->type());
    ui.gbLimit->setChecked(!m_Drive->isInfinity());

	connect(ui.pbVerError,SIGNAL(clicked()),SLOT(onVerifyError()));

    setModal(true);

    setWindowTitle(windowTitle()+" "+m_Drive->getName());

    ui.gbInput->setToolTip(
                 tr(
                "<b>Inputs number</font></b>"
                "<ol>"
                  "<li>inPEL - plus  end limit</li>"
                  "<li>inMEL - minus end limit</li>"
                  "<li>inALM - alarm input from driver controller</li>"
                "</ol>"
                "<b>Type Action</font></b>"
                "<ol>"
                  "<li>no - no action</li>"
                  "<li>EMGStop - emergency stop</li>"
                  "<li>SDStop - slow down stop</li>"
                "</ol>"
                  )
                );

    ui.gbOutput->setToolTip(
                tr(
                "<b>Outputs number</font></b>"
                "<ol>"
                  "<li>outENB -  enable to driver controller</li>"
                  "<li>outRALM - reset alarm to driver controller</li>"
                "</ol>"
                  )
                );

     ui.gbDynamic->setToolTip("<img src='/image/scurve.png'/> Book");

     setWindowTitle(tr("Edit Drive: ")+m_Drive->getName());
}

WLDriveWidget::~WLDriveWidget()
{

}


void WLDriveWidget::updateLabelSDDist(double V)
{
dataPad Pad=m_Drive->pad()->getData("main");
ui.labelSDDist->setText(QString(tr("slow down distance: %1 mm")).arg((Pad.Vst-V)/Pad.Ade*(V+Pad.Vst)/2,0,'g',2));
}

void WLDriveWidget::onVerifyError()
{
QString str;

if((ui.editInALM->value()==ui.editInORG->value()&&ui.editInALM->value()>1&&ui.editInORG->value()>1)
 ||(ui.editInALM->value()==ui.editInPEL->value()&&ui.editInALM->value()>1&&ui.editInPEL->value()>1)
 ||(ui.editInALM->value()==ui.editInMEL->value()&&ui.editInALM->value()>1&&ui.editInMEL->value()>1)
 ||(ui.editInORG->value()==ui.editInPEL->value()&&ui.editInORG->value()>1&&ui.editInPEL->value()>1)
 ||(ui.editInORG->value()==ui.editInMEL->value()&&ui.editInORG->value()>1&&ui.editInMEL->value()>1)
 ||(ui.editInPEL->value()==ui.editInMEL->value()&&ui.editInPEL->value()>1&&ui.editInMEL->value()>1))
str+=tr("input numbers are not unique")+"\n";

if((ui.editOutRALM->value()==ui.editOutENB->value()&&ui.editOutRALM->value()>0&&ui.editOutENB->value()>0))
str+=tr("output numbers are not unique")+"\n";

if(ui.sbMLIM->value()>=ui.sbPLIM->value()
 &&ui.gbLimit->isChecked())
 str+=tr("invalid movement limits")+"\n";
else
 {
 if((ui.sbBackFindPosition->value()<ui.sbMLIM->value()
   ||ui.sbBackFindPosition->value()>ui.sbPLIM->value())&&(ui.comboBoxLogicFind->currentIndex()>3))
  str+=tr("invalid base position")+"\n";
 }
/*
if((typePulseAxis)ui.cbTypePulse->currentIndex()==typePulseAxis::AXIS_pulse_empty)
 str+=tr("invalid type pulse")+"\n";
*/
switch(ui.comboBoxLogicFind->currentIndex())
{
case 4:
case 1: if(ui.editInORG->value()>1)
		{}
		else
		str+=tr("no sensor installed to search")+" (inORG)"+"\n";

	    if(ui.sbOrgSize->value()>0)
		{}
		else
		str+=tr("not specified size ORG")+"\n";
	    break;
	    break;

case 2: 
case 5: if(ui.editInPEL->value()>1&&ui.cbActInPEL->currentIndex()>0)
		{}
		else
		str+=tr("no sensor installed to search or action")+" (inPEL)"+"\n";
	    break;

case 3: 
case 6: if(ui.editInMEL->value()>1&&ui.cbActInMEL->currentIndex()>0)
		{}
		else
		str+=tr("no sensor installed to search or action")+" (inMEL)""\n";
	    break;
}

if(ui.comboBoxLogicFind->currentIndex()>0&&ui.sbVfind->value()<=0)
str+=tr("search speed not set")+"\n";


if(str.isEmpty())
	str=tr("No error!!!");

QMessageBox::information(this, tr("Verify error"),str,QMessageBox::Ok);
}

void WLDriveWidget::accept()
{
saveDataDrive();

for(int i=1;i<ui.tabWidget->count();i++)    {
  static_cast<QDialog*>(ui.tabWidget->widget(i))->accept();
  }

QDialog::accept();
}

void WLDriveWidget::updateCBDimm(int index)
{
m_ddim.set(m_ddim.type,ui.sbDimA->value(),ui.sbDimB->value());

WLDriveDim::typeDim tdim=static_cast<WLDriveDim::typeDim>(index);

if(tdim!=m_ddim.type)
switch(tdim)
{
case WLDriveDim::typeDim::stepPerSize: m_ddim.set(tdim,1/m_ddim.valueReal);         break;
case WLDriveDim::typeDim::oneStepSize: m_ddim.set(tdim,m_ddim.valueReal);           break;
case WLDriveDim::typeDim::ratio:       m_ddim.set(tdim,m_ddim.valueReal*1000,1000); break;
}

ui.sbDimB->setEnabled(tdim==WLDriveDim::typeDim::ratio);

ui.sbDimA->setValue(m_ddim.A);
ui.sbDimB->setValue(m_ddim.B);
}

void WLDriveWidget::updateCBTypePulse(int index)
{
   // ui.cbInvStep->setEnabled(index<4);
}

void WLDriveWidget::updateFindLogic(int index)
{
if(index==1
 ||index==4)
    ui.groupBoxORG->setEnabled(true);
else
    ui.groupBoxORG->setEnabled(false);


if(index==4
 ||index==5
 ||index==6)
     ui.sbBackFindPosition->setEnabled(true);
   else
     ui.sbBackFindPosition->setEnabled(false);

ui.sbVfind->setEnabled(index!=0);
ui.sbOrgPosition->setEnabled(index!=0);

switch(index)
{
case 1:
case 4:  ui.labelOrgPosition->setText("inORG "+tr("position"));break;
case 2:
case 5:  ui.labelOrgPosition->setText("inPEL "+tr("position"));break;
case 3:
case 6:  ui.labelOrgPosition->setText("inMEL "+tr("position"));break;
}


}

void WLDriveWidget::saveDataDrive()
{
WLAxis *Axis=m_Drive->getAxis();

m_Drive->setKGear(1);

m_Drive->setDimension(static_cast<WLDriveDim::typeDim>(ui.cbTypeDim->currentIndex())
                   ,ui.sbDimA->value()
                   ,ui.sbDimB->value());

Axis->setDelaySCurve(ui.sbDelaySCurve->value());

Axis->setInALM(ui.editInALM->value());
Axis->setInORG(ui.editInORG->value());
Axis->setInPEL(ui.editInPEL->value());
Axis->setInMEL(ui.editInMEL->value());

Axis->setOutRALM(ui.editOutRALM->value());
Axis->setOutENB(ui.editOutENB->value());

Axis->setActIn(AXIS_inALM,static_cast<typeActIOPutAxis>(ui.cbActInALM->currentIndex())); 
Axis->setActIn(AXIS_inPEL,static_cast<typeActIOPutAxis>(ui.cbActInPEL->currentIndex())); 
Axis->setActIn(AXIS_inMEL,static_cast<typeActIOPutAxis>(ui.cbActInMEL->currentIndex())); 

m_Drive->setLogicFindPos(ui.comboBoxLogicFind->currentIndex());

m_Drive->setORGSize(ui.sbOrgSize->value());
m_Drive->setHomePosition(ui.sbBackFindPosition->value());
m_Drive->setOrgPosition(ui.sbOrgPosition->value());

Axis->setTypePulse((typePulseAxis)ui.cbTypePulse->currentIndex()
                  ,(ui.cbInvStep->isChecked()?MAF_invStep:0)
                  |(ui.cbInvDir->isChecked() ?MAF_invDir:0));

m_Drive->setFeedVFind(ui.sbVfind->value());
m_Drive->setTypeDrive(static_cast<WLDrive::typeDrive>(ui.cbTypeDrive->currentIndex()));
m_Drive->setInfinity(!ui.gbLimit->isChecked());
m_Drive->setMinMaxPosition(ui.sbMLIM->value(),ui.sbPLIM->value());

}
