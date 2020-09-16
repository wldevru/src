#include <QMessageBox>
#include "wlmillcontrol.h"

WLMillControl::WLMillControl(WLMillMachine *_MillMachine,WLGProgram *_Program,QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

    m_stepSper=2.5;
    m_stepFper=2.5;

	stepSize[0]=0.01;
	stepSize[1]=0.1;
	stepSize[2]=1;
	stepSize[3]=10;

    turnSize[0]=1;
    turnSize[1]=10;
    turnSize[2]=100;
    turnSize[3]=1000;

    ListFper<<0.1<<0.25<<1<<5<<10<<25<<50<<75<<100;

	MillMachine=_MillMachine;
	Program=_Program;

	connect(ui.sbSmoothDist,SIGNAL(valueChanged(double)),MillMachine,SLOT(setSmoothDist(double)));
	ui.sbSmoothDist->setValue(MillMachine->getSmoothDist());

	connect(ui.sbSimpliDist,SIGNAL(valueChanged(double)),MillMachine,SLOT(setSimpliDist(double)));
	ui.sbSimpliDist->setValue(MillMachine->getSimpliDist());

    connect(ui.cbAutoStart,SIGNAL(toggled(bool)),MillMachine,SLOT(setAutoStart(bool)));    

	connect(ui.cbSmooth,SIGNAL(toggled(bool)),MillMachine,SLOT(setSmooth(bool)));    
	connect(ui.cbSimpli,SIGNAL(toggled(bool)),MillMachine,SLOT(setSimpli(bool)));    

    connect(MillMachine,&WLMillMachine::changedReadyRunList,this,&WLMillControl::updateStackedWidget);

	connect(ui.cbBLNextMov,SIGNAL(toggled(bool)),MillMachine,SLOT(setBLNextMov(bool)));
	connect(ui.pushButtonOnProgram,SIGNAL(clicked()),SLOT(onSendProgramTraj()));

    ui.labelF->setPrefix("F:");
    ui.labelF->setDataN(0);


    ui.labelS->setPrefix("S:");
    ui.labelS->setDataN(0);

    connect(ui.sbFper,SIGNAL(valueChanged(double)),MillMachine,SLOT(setPercentSpeed(double)));
    MillMachine->setPercentSpeed(100);

    connect(ui.sbSper,SIGNAL(valueChanged(double)),MillMachine,SLOT(setPercentSOut(double)));
    MillMachine->setPercentSOut(100);


    connect(ui.pbS100,SIGNAL(clicked()),SLOT(onSetS100Per()));
    connect(ui.pbF100,SIGNAL(clicked()),SLOT(onSetF100Per()));

	QTimer *timer= new QTimer;
    QTimer *timer1= new QTimer;

	connect(timer,SIGNAL(timeout()),SLOT(updateFSLabel()));
    timer->start(50);
	
    connect(ui.tabWidget,&QTabWidget::currentChanged,this,&WLMillControl::updateTab);
    connect(ui.tabWidgetManual,&QTabWidget::currentChanged,this,&WLMillControl::updateTab);
	
    connect(ui.pbPlusX,SIGNAL(pressed()),SLOT  (onChangedPBPlusX()));
	connect(ui.pbPlusX,SIGNAL(released()),SLOT (onChangedPBPlusX()));
	connect(ui.pbMinusX,SIGNAL(pressed()),SLOT (onChangedPBMinusX()));
	connect(ui.pbMinusX,SIGNAL(released()),SLOT(onChangedPBMinusX()));

	connect(ui.pbPlusY,SIGNAL(pressed()),SLOT  (onChangedPBPlusY()));
	connect(ui.pbPlusY,SIGNAL(released()),SLOT (onChangedPBPlusY()));
	connect(ui.pbMinusY,SIGNAL(pressed()),SLOT (onChangedPBMinusY()));
	connect(ui.pbMinusY,SIGNAL(released()),SLOT(onChangedPBMinusY()));

    connect(ui.pbPlusZ,SIGNAL(pressed()),SLOT  (onChangedPBPlusZ()));
	connect(ui.pbPlusZ,SIGNAL(released()),SLOT (onChangedPBPlusZ()));
	connect(ui.pbMinusZ,SIGNAL(pressed()),SLOT (onChangedPBMinusZ()));
	connect(ui.pbMinusZ,SIGNAL(released()),SLOT(onChangedPBMinusZ()));

	connect(ui.pbPlusA,SIGNAL(pressed()),SLOT  (onChangedPBPlusA()));
	connect(ui.pbPlusA,SIGNAL(released()),SLOT (onChangedPBPlusA()));
	connect(ui.pbMinusA,SIGNAL(pressed()),SLOT (onChangedPBMinusA()));
	connect(ui.pbMinusA,SIGNAL(released()),SLOT(onChangedPBMinusA()));


	connect(ui.comboBoxWhellAxis,SIGNAL(activated(int)),SLOT(updateWhellAxis()));

    ui.buttonGroupWhellX->setId(ui.pbWhellX1,0);
    ui.buttonGroupWhellX->setId(ui.pbWhellX10,1);
    ui.buttonGroupWhellX->setId(ui.pbWhellX100,2);

    connect(ui.buttonGroupWhellX,SIGNAL(buttonClicked(int)),SLOT(updateWhellAxis()));
	connect(ui.rbWhellVMode,SIGNAL(toggled(bool)),SLOT(updateWhellAxis()));
    connect(MillMachine,SIGNAL(changedOn(bool)),SLOT(updateWhellAxis()));

    WLWhell *Whell=MillMachine->getWhell();
    if(Whell)
     {
     qDebug()<<"Whell connect";
     connect(Whell,&WLWhell::changedCurIndexAxis,ui.comboBoxWhellAxis,&QComboBox::setCurrentIndex);
     connect(Whell,&WLWhell::changedCurIndexX,this,&WLMillControl::updateWhellXButton);
     connect(Whell,&WLWhell::changedCurVmode,ui.rbWhellVMode,&QRadioButton::setChecked);
     }
	

	connect(ui.pbPlusProbeX,SIGNAL(clicked()),SLOT(updateProbeButtons()));
	connect(ui.pbMinusProbeX,SIGNAL(clicked()),SLOT(updateProbeButtons()));
	connect(ui.pbPlusProbeY,SIGNAL(clicked()),SLOT(updateProbeButtons()));
	connect(ui.pbMinusProbeY,SIGNAL(clicked()),SLOT(updateProbeButtons()));
	connect(ui.pbPlusProbeZ,SIGNAL(clicked()),SLOT(updateProbeButtons()));
	connect(ui.pbMinusProbeZ,SIGNAL(clicked()),SLOT(updateProbeButtons()));
	connect(ui.pbMinusProbeH,SIGNAL(clicked()),SLOT(updateProbeButtons()));
	
    ui.sbFtouch->setValue(MillMachine->VProbe());

    connect(ui.pushButtonGo,SIGNAL(clicked()),MillMachine,SLOT(Start()));
    connect(ui.pushButtonPause,SIGNAL(clicked()),MillMachine,SLOT(Pause()));//Stop()



	connect(ui.pbResetScript,SIGNAL(clicked()),MillMachine->m_EVMScript,SLOT(reset()),Qt::DirectConnection);
	connect(ui.pbEditScript,SIGNAL(clicked()),SLOT(onEditScript()));

	connect(MillMachine->m_EVMScript,SIGNAL(changedBusy(bool)),ui.pbEditScript,SLOT(setDisabled(bool)));
	connect(MillMachine->m_EVMScript,SIGNAL(changedBusy(bool)),ui.groupBoxScript,SLOT(setDisabled(bool)));
	connect(MillMachine->m_EVMScript,SIGNAL(changedBusy(bool)),ui.pbResetScript,SLOT(setEnabled(bool)));

	
	connect(ui.leRunScript,SIGNAL(returnPressed()),SLOT(updateRunSrcipt()));
	connect(timer,SIGNAL(timeout()),SLOT(updateLabelInProbe()));

	connect(ui.pbStartTeachAxis,SIGNAL(clicked()),SLOT(onTeachAxis()));
	connect(ui.pbStartFindAxis,SIGNAL(clicked()),SLOT(onFindAxis()));
	connect(ui.pbRFindAxis,SIGNAL(clicked()),SLOT(onRFindAxis()));

	connect(ui.pbEditOffsetTool,SIGNAL(clicked()),SLOT(onEditOffsetTool()));

	updateLabelBaseOffsetTool();
	updateTableTools();
		
    updateTab();
	updateFeedTouch();
/*
    if(!MillMachine->getDrive("Z"))
        {
        delete ui.pbPlusZ;
        ui.pbPlusZ=nullptr;
        delete ui.pbMinusZ;
        ui.pbMinusZ=nullptr;
        }

    if(!MillMachine->getDrive("A"))
        {
        delete ui.pbPlusA;
        ui.pbPlusA=nullptr;
        delete ui.pbMinusA;
        ui.pbMinusA=nullptr;
        }
*/

    ui.labelTimeLeft->setPrefix(tr("Left: "));
    ui.labelTimeEnd->setPrefix(tr("End: "));

    connect(timer,SIGNAL(timeout()),SLOT(updateLabelBuffer()));
    connect(timer1,SIGNAL(timeout()),SLOT(updateLabelTime()));
    timer1->start(1000);

    connect(ui.pbUpdateTool,SIGNAL(clicked()),SLOT(updateTableTools()));
    connect(ui.pbAcceptTool,SIGNAL(clicked()),SLOT(onAcceptTableTools()));
    connect(ui.tableTools,SIGNAL(cellChanged(int,int)),SLOT(onSetChangedTable()));

    connect(ui.pbSetSCor,SIGNAL(clicked()),this,SLOT(onSetSCor()));
    connect(ui.pbClearSCor,SIGNAL(clicked()),this,SLOT(onClearSCorList()));

    ui.stackedWidget->setContentsMargins(0,0,0,0);

}

WLMillControl::~WLMillControl()
{

}

void WLMillControl::onEditOffsetTool()
{
WLEnterNum EnterNum(this);
EnterNum.setMinMaxNow(-200,200,MillMachine->getBaseOffsetTool());
EnterNum.setDecimals(0);
EnterNum.setLabel(tr("Enter base offset tool:"));
EnterNum.show();
if(EnterNum.exec()) 
 {
 MillMachine->setBaseOffsetTool(EnterNum.getNow());
 }

updateLabelBaseOffsetTool();
}

void WLMillControl::onAcceptTableTools()
{
double D,L;

for(int i=0;i<ui.tableTools->rowCount();i++)
  {
  D=ui.tableTools->item(i,0)->data(0).toString().toDouble();
  L=ui.tableTools->item(i,1)->data(0).toString().toDouble();

  MillMachine->m_GCode.setDataTool(i+1,D,L);
  }

ui.pbAcceptTool->setEnabled(false);
}

void WLMillControl::updateTableTools()
{
ui.tableTools->setColumnCount(2);
ui.tableTools->setRowCount(sizeTools-1);

ui.tableTools->setHorizontalHeaderLabels(QString("D,L").split(","));

for(int i=0;i<ui.tableTools->rowCount();i++)
  {
  ui.tableTools->setItem(i,0,new QTableWidgetItem(QString::number(MillMachine->m_GCode.getTool(i+1).d)));
  ui.tableTools->setItem(i,1,new QTableWidgetItem(QString::number(MillMachine->m_GCode.getTool(i+1).l)));
  }

ui.pbAcceptTool->setEnabled(false);
}

void WLMillControl::updateWhellXButton(quint8 id)
{
ui.buttonGroupWhellX->button(id)->click();
}

void WLMillControl::updateLabelBaseOffsetTool()
{
    ui.labelBaseOffsetTool->setText(tr("Base offset tool:")+QString::number(MillMachine->getBaseOffsetTool())+tr("mm"));
}

void WLMillControl::onTeachAxis()
{
const QString nameDrive=ui.cbServiceAxis->currentText();
WLMillDrive *Drive=MillMachine->getDrive(nameDrive);
if(Drive!=nullptr)
 {
 WLEnterNum  EnterNum (this);
 EnterNum.setLabel(tr("Current position Drive ")+nameDrive+" = ");
 EnterNum.setNow(Drive->getAxisPosition());
 //EnterNum.setSuffix(tr("gr"));

 if(EnterNum.exec())
        {
        Drive->setPosition(EnterNum.getNow());
        MillMachine->goDriveTeach(ui.cbServiceAxis->currentText());
        }
 }
}

#define maxFPercent 300.0
#define maxSPercent 150.0

void WLMillControl::updateLabelBuffer()
{	
	ui.labelProgram->setText(QString(tr("Program:%1 (%2%)").arg(MillMachine->getIProgram())
                                                           .arg((float)(MillMachine->getIProgram())
                                                               /(float)(Program->getElementCount())*100.0,0,'f',3)));
	ui.labelBufPC-> setText(tr("PC     :")+QString::number(MillMachine->getTrajSize()));
    ui.labelBufDev->setText(tr("Device :")+QString::number(MillMachine->m_motDevice->getModulePlanner()->getSizeBuf()
                                                          -MillMachine->m_motDevice->getModulePlanner()->getFree()));
}

void WLMillControl::updateLabelTime()
{
    long           made=MillMachine->getIProgram();
    long          order=Program->getElementCount();
    double timeElement=MillMachine->getTimeElement()/1000;

    long time_s=timeElement*(order-made+MillMachine->m_motDevice->getModulePlanner()->getCountBuf()
                                       +MillMachine->getTrajIProgramSize());

    long h,m,s,d;

    h=time_s/3600;
    time_s-=h*3600;

    m=time_s/60;
    time_s-=m*60;

    s=time_s;

    ui.labelTimeLeft->setText(QString(("%1:%2:%3")).arg(h).arg(m).arg(s));

    if(h<0)
    qDebug()<<":updateLabelTime()"<<made<<order<<timeElement;
    QTime nowTime=QTime::currentTime();

    s+=nowTime.second();
    if(s>=60) {m++; s-=60;}

    m+=nowTime.minute();
    if(m>=60) {h++; m-=60;}

    d=0;
    h+=nowTime.hour();
    while(h>=24)
         {h-=24;d++;}

    ui.labelTimeEnd->setText(QString(("%1:%2:%3:%4")).arg(d).arg(h).arg(m).arg(s));

}

void WLMillControl::onSetSCor()
{
if(MillMachine->isUseCorrectSOut())  {
 MillMachine->addCurrentSCor();
 onSetS100Per();
 }
else {
     QMessageBox::information(this,tr("information"),tr("S correct is off, please on in Edit->WLMill"));
     }
}

void WLMillControl::onClearSCorList()
{
auto ret=QMessageBox::question(this,tr("Question")
                              ,tr("Delete all data correct S?")
                              ,QMessageBox::Ok|QMessageBox::Cancel);
if(ret==QMessageBox::Ok)
 {
 MillMachine->clearSCorList();
 }


}
void WLMillControl::updateLabelInProbe()
{
WLModuleAxis *ModuleAxis=static_cast<WLModuleAxis*>(MillMachine->m_motDevice->getModule(typeMAxis));

if(ModuleAxis->getInput(MAXIS_inProbe)->getNow())
    ui.labelInProbe->setPixmap(QPixmap(":/data/icons/ion.png"));
else
    ui.labelInProbe->setPixmap(QPixmap(":/data/icons/ioff.png"));
}

void WLMillControl::updateRunSrcipt()
{/*
int M=(this->sender()->objectName().remove("pbM")).toInt();

if(M!=0)
  MillMachine->runMScript(M);
else*/

MillMachine->runScript(ui.leRunScript->text()); 
}

void WLMillControl::onEditScript()
{
WLEditText EditText;
WLMCodeSH  codeSH(EditText.getDocument());
EditText.setText(MillMachine->m_EVMScript->getCode());
EditText.setLabel(tr("Please modify script:"));

EditText.show();
if(EditText.exec())
  {
  MillMachine->m_EVMScript->setCode(EditText.getText());
  }

}


void WLMillControl::updateLabelOnMachine(bool on)
{
Q_UNUSED(on)
}



void WLMillControl::updateStackedWidget(bool ready)
{
qDebug()<<"readyRun"<<ready;
if(ready) 
    {
    ui.stackedWidget->setCurrentIndex(1);
    ui.gbFcor->setVisible(true);
    MillMachine->setEnableManualWhell(false);
    }
else
	{
	ui.stackedWidget->setCurrentIndex(0);
    updateTab();
    }

qDebug()<<"end readyRun";
}


float WLMillControl::calcFtouch()
{
return ui.sbFtouch->value();
}

void WLMillControl::updateFeedTouch()
{
double Ft=calcFtouch();

//ui.FtouchLabel->setData(Ft);

///dataPad Pad=MillMachine->getPad("main");
//qDebug()<<"Ft"<<Ft;
//ui.labelProbeDistSD->setData((Pad.Vst-Ft/60)/Pad.Ade*(Ft/60+Pad.Vst)/2,2);
}

void WLMillControl::updateProbeButtons()
{
QString name=this->sender()->objectName();

if(QMessageBox::question(this, tr("Question:"),tr("are you sure?"),QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
{
if(name=="pbPlusProbeX") MillMachine->goDriveProbe("X",1,calcFtouch(),ui.rbProbeSD->isChecked());
else	
if(name=="pbMinusProbeX") MillMachine->goDriveProbe("X",0,calcFtouch(),ui.rbProbeSD->isChecked());
else	
if(name=="pbPlusProbeY") MillMachine->goDriveProbe("Y",1,calcFtouch(),ui.rbProbeSD->isChecked());
else	
if(name=="pbMinusProbeY") MillMachine->goDriveProbe("Y",0,calcFtouch(),ui.rbProbeSD->isChecked());
else	
if(name=="pbPlusProbeZ") MillMachine->goDriveProbe("Z",1,calcFtouch(),ui.rbProbeSD->isChecked());
else	
if(name=="pbMinusProbeZ") MillMachine->goDriveProbe("Z",0,calcFtouch(),ui.rbProbeSD->isChecked());
else
if(name=="pbPlusProbeA") MillMachine->goDriveProbe("A",1,calcFtouch(),ui.rbProbeSD->isChecked());
else	
if(name=="pbMinusProbeA") MillMachine->goDriveProbe("A",0,calcFtouch(),ui.rbProbeSD->isChecked());
else	
if(name=="pbMinusProbeH") MillMachine->goDriveHProbe(calcFtouch(),ui.rbProbeSD->isChecked());

}

}

void WLMillControl::onSetChangedTable()
{
ui.pbAcceptTool->setEnabled(true);
}



void WLMillControl::setSValue()
{
if(MillMachine->isManual())
{
WLEnterNum EnterNum(this);
EnterNum.setMinMaxNow(MillMachine->Smin(),MillMachine->Smax(),MillMachine->getSTar());
EnterNum.setDecimals(0);
EnterNum.setLabel(tr("Please ente S value:"));
EnterNum.show();
if(EnterNum.exec()) 
	MillMachine->setSOut(EnterNum.getNow());
}
}

void WLMillControl::updateButtonClicked()
{
QString name=this->sender()->objectName();
name=name.remove("pushButtonM");
qDebug()<<"changedM"<<name.toInt();
MillMachine->runMScript(name.toInt());
}

void WLMillControl::updateWhellAxis()
{
if((ui.tabWidget->currentIndex()==1)
 &&(ui.tabWidgetManual->currentIndex()==1))
{
MillMachine->setEnableManualWhell(true);
MillMachine->setDriveManualWhell(ui.comboBoxWhellAxis->currentText(),ui.buttonGroupWhellX->checkedId(),ui.rbWhellVMode->isChecked());

  WLWhell *Whell=MillMachine->getWhell();

  if(Whell)
      {
      ui.gbAxisWhell->setEnabled(Whell->getFlag()&WHF_manualA);
      ui.gbXWhell->setEnabled(Whell->getFlag()&WHF_manualX);
      ui.gbVmodeWhell->setEnabled(Whell->getFlag()&WHF_manualV);
      }
      else {
      ui.gbAxisWhell->setDisabled(true);
      ui.gbXWhell->setDisabled(true);
      ui.gbVmodeWhell->setDisabled(true);
     }
}
else
{
MillMachine->setEnableManualWhell(false);
}

}

void WLMillControl::updateTab()
{
MillMachine->Stop();

updateWhellAxis();

switch(ui.tabWidget->currentIndex())
{
case 1:
        switch(ui.tabWidgetManual->currentIndex())
        {
        case 0:
                //MillMachine->setManual(1);
                //setFocus();
                ui.gbFcor->setVisible(true);
                break;

        case 1: //MillMachine->setManual(0);
                ui.gbFcor->setVisible(false);
               // enableWhellAxis(true);
                break;
        }
        break;

default: ui.gbFcor->setVisible(false);

}
}


float WLMillControl::calcStepMov()
{
if(ui.pbStep0->isChecked())  return stepSize[0];
if(ui.pbStep1->isChecked())  return stepSize[1];
if(ui.pbStep2->isChecked())  return stepSize[2];

return 0.0;
}

float WLMillControl::calcWhellTurn()
{
return 0;//turnSize[ui.hScrollBarWhellX->value()];
}

/*
void WLMillControl::updateStepMov()
{
ui.labelSizeStep->setData(calcStepMov(),3);
}
*/
void WLMillControl::updateFSLabel()
{
ui.labelF->setData(MillMachine->getCurSpeed()*60);
ui.labelS->setData(MillMachine->getCurSOut());
}

void WLMillControl::updateChangedPBAxis(QToolButton *tb,QString nameDrive,int rot)
{
if(tb)
 {
 if(tb->isDown())
    {
    if(ui.pbFast->isDown())
        MillMachine->setPercentManual(100.0f);
    else
        MillMachine->setPercentManual(ui.sbFman->value());

    MillMachine->goDriveManual(nameDrive,rot,calcStepMov());
    }
 else
    MillMachine->goDriveManual(nameDrive,0,calcStepMov());
 }
}




void WLMillControl::onSendProgramTraj()
{
if(Program->getLastMovElement()!=0)
 if(QMessageBox::question(this,tr("Question"),tr("Continue ?"),QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
  {
  qDebug()<<"getLastMovElement"<<Program->getLastMovElement();
  Program->setActivElement(Program->getLastMovElement());
  }

WLEnterNum EnterNum(this);
EnterNum.setMinMaxNow(0,Program->getElementCount(),Program->getActivElement());
EnterNum.setDecimals(0);
EnterNum.setLabel(tr("Which element to start processing?:"));
EnterNum.show();
if(EnterNum.exec()) 
 {
 MillMachine->runGProgram(EnterNum.getNow());
 }

}
/*
void WLMillControl::updateSizeWhellTurn()
{
ui.labelSizeWhell->setData(calcWhellTurn());
}
*/

void WLMillControl::focusInEvent ( QFocusEvent * event )
{
Q_UNUSED(event)
//ui.comboBoxWhellAxis->setEnabled(true);
ui.gbDirManualKey->setEnabled(true);

//qDebug()<<event->gotFocus();
}

void WLMillControl::focusOutEvent ( QFocusEvent * event )
{
Q_UNUSED(event)
	
//if(!ui.groupBoxStepMov->hasFocus())
  {
 //ui.comboBoxWhellAxis->setEnabled(false);
  ui.pbFast->setDown(false);
  ui.gbDirManualKey->setEnabled(false);
  }
}

void WLMillControl::keyPressEvent ( QKeyEvent * event )
{
//qDebug()<<"ch press manual"<<(QApplication::keyboardModifiers()&Qt::ShiftModifier)<<event->isAutoRepeat();

//bool const fast=QApplication::keyboardModifiers()&Qt::ShiftModifier;
//qDebug()<<"keyPressEvent";
if(!event->isAutoRepeat())
{
if(ui.tabWidget->currentIndex()==1)
switch(ui.tabWidgetManual->currentIndex())
{
case 0 :
   switch(event->key())
   {
   case Qt::Key_Shift:   ui.pbFast->setDown(true);
                         on_pbFast_pressed();
                         break;

   case Qt::Key_Left:    ui.pbMinusX->setDown(true); onChangedPBMinusX(); break;
   case Qt::Key_Right:   ui.pbPlusX->setDown(true);  onChangedPBPlusX();break;
   case Qt::Key_Down:    ui.pbMinusY->setDown(true); onChangedPBMinusY(); break;
   case Qt::Key_Up:      ui.pbPlusY->setDown(true);  onChangedPBPlusY();break;
   case Qt::Key_PageDown:ui.pbMinusZ->setDown(true); onChangedPBMinusZ(); break;
   case Qt::Key_PageUp:  ui.pbPlusZ->setDown(true);  onChangedPBPlusZ();break;

  // case Qt::Key_4:   ui.pbMinusA->setDown(true); onChangedPBMinusA(); break;
  // case Qt::Key_7:    ui.pbPlusA->setDown(true);  onChangedPBPlusA();break;
   
/*

   case Qt::Key_Plus:    if(ui.hScrollBarSizeStep->value()==ui.hScrollBarSizeStep->maximum())
                            ui.cbStepMov->setChecked(false);
                              else
                           ui.hScrollBarSizeStep->setSliderPosition(ui.hScrollBarSizeStep->value()+ui.hScrollBarSizeStep->singleStep());
	                     break;  

   case Qt::Key_Minus:  if(ui.hScrollBarSizeStep->value()==ui.hScrollBarSizeStep->maximum()
                         &&!ui.cbStepMov->isChecked())
                             {}
                       else
                           ui.hScrollBarSizeStep->setSliderPosition(ui.hScrollBarSizeStep->value()-ui.hScrollBarSizeStep->singleStep());

                       ui.cbStepMov->setChecked(true);
                        break;*/
   case Qt::Key_A:     ui.tabWidget->setCurrentIndex(0);break;
   case Qt::Key_M:     ui.tabWidget->setCurrentIndex(1);break;


   }
   break;
case 1:
   switch(event->key())//Whell
   {
   case Qt::Key_0:
   case Qt::Key_1:
   case Qt::Key_2:
   case Qt::Key_3:       ui.comboBoxWhellAxis->setCurrentIndex(event->key()-Qt::Key_0); updateWhellAxis();break;
/*
   case Qt::Key_Plus:    ui.hScrollBarWhellX->setSliderPosition(ui.hScrollBarWhellX->value()+ui.hScrollBarWhellX->singleStep());
	                     break;  

   case Qt::Key_Minus:   ui.hScrollBarWhellX->setSliderPosition(ui.hScrollBarWhellX->value()-ui.hScrollBarWhellX->singleStep());
	                     break;
*/
   }
   break;
}
else
if(ui.tabWidget->currentIndex()==3)
{
   switch(event->key())
   {
   case Qt::Key_Shift:    //ui.pbFast->setDown(true);
	                      break;
   }
}  
/*
if(Tab->currentIndex()==0)
{
// if(chBoxArrowEn->isChecked())
/*	qDebug()<<"+"<<event->key();
 switch(event->key())
 {
 case Qt::Key_4:  MillMachine->goDriveManual(XDrive,-1,fast);break;
 case Qt::Key_6:  MillMachine->goDriveManual(XDrive,1,fast); break;
 
 case Qt::Key_8:  MillMachine->goDriveManual(YDrive,1,fast); break;
 case Qt::Key_2:  MillMachine->goDriveManual(YDrive,-1,fast);break;
 
 case Qt::Key_9:  MillMachine->goDriveManual(ZDrive,1,fast); break;
 case Qt::Key_3:  MillMachine->goDriveManual(ZDrive,-1,fast); break;
 }
 else*/
/*
 switch(event->key())
 {
 case Qt::Key_Plus:  ButtonInc->setDown(true);   on_ButtonInc(); break;
 case Qt::Key_Minus: ButtonDec->setDown(true);   on_ButtonDec(); break;
 }
}
*/
}

event->accept();
}

void WLMillControl::keyReleaseEvent ( QKeyEvent * event )
{
//qDebug()<<"keyReleaseEvent";
if(!event->isAutoRepeat())
{
//if(Tab->currentIndex()==0)
{
// /*//if(chBoxArrowEn->isChecked())
/* switch(event->key())
 {
 case Qt::Key_4: 
 case Qt::Key_6:     MillMachine->goDriveManual(XDrive,0); break;
 
 case Qt::Key_8:    
 case Qt::Key_2:     MillMachine->goDriveManual(YDrive,0); break;
 
 case Qt::Key_9:   
 case Qt::Key_3:     MillMachine->goDriveManual(ZDrive,0); break;
 }
/* else*/
if(ui.tabWidget->currentIndex()==1)
if(ui.tabWidgetManual->currentIndex()==0)
switch(event->key())
{

case Qt::Key_Left:    ui.pbMinusX->setDown(false); onChangedPBMinusX(); break;
case Qt::Key_Right:   ui.pbPlusX->setDown(false);  onChangedPBPlusX();break;
case Qt::Key_Down:    ui.pbMinusY->setDown(false); onChangedPBMinusY(); break;
case Qt::Key_Up:      ui.pbPlusY->setDown(false);  onChangedPBPlusY();break;
case Qt::Key_PageDown:ui.pbMinusZ->setDown(false); onChangedPBMinusZ(); break;
case Qt::Key_PageUp:  ui.pbPlusZ->setDown(false);  onChangedPBPlusZ();break;
//case Qt::Key_4:       ui.pbMinusA->setDown(false); onChangedPBMinusA(); break;
//case Qt::Key_7:       ui.pbPlusA->setDown(false);  onChangedPBPlusA();break;
case Qt::Key_Shift:   ui.pbFast->setDown(false);
                     // ui.sbFman->setDisabled(false);
                      //MillMachine->setPercentManual(ui.sbFman->value());
                      on_pbFast_released();
                      break;
 
 }
}    
}
else
if(ui.tabWidget->currentIndex()==3)
{
   switch(event->key())
   {
   case Qt::Key_Shift:    //ui.pbFast->setDown(true);
	                      break;
   }
} 
event->accept();
}

void WLMillControl::on_pbGetMSLimit_clicked()
{
WLDrive *drive=MillMachine->getDrive(ui.cbServiceAxis->currentText());

if(drive)
 {
 drive->setMinPosition(drive->position());
 }
}

void WLMillControl::on_pbGetPSLimit_clicked()
{
WLDrive *drive=MillMachine->getDrive(ui.cbServiceAxis->currentText());

if(drive)
 {
 drive->setMaxPosition(drive->position());
 }
}

void WLMillControl::on_pbPlusFman_pressed()
{
  //ui.sbFper->stepUp();
int index=ListFper.indexOf(ui.sbFman->value());

if(index!=-1)
 {
 index++;
 if(index<ListFper.size())  ui.sbFman->setValue(ListFper[index]);
 }
else {
 for(int i=0;i<ListFper.size();i++)
  {
  if(ui.sbFman->value()<ListFper[i])
      {
      ui.sbFman->setValue(ListFper[i]);
      break;
      }
  }
}


}

void WLMillControl::on_pbMinusFman_pressed()
{
//  ui.sbFper->stepDown();

int index=ListFper.indexOf(ui.sbFman->value());

if(index!=-1)
  {
  index--;
  if(index>=0)  ui.sbFman->setValue(ListFper[index]);
  }
else {
 for(int i=ListFper.size()-1;i>=0;i--)
  {
  if(ui.sbFman->value()>ListFper[i])
      {
      ui.sbFman->setValue(ListFper[i]);
      break;
      }
  }
}
}





void WLMillControl::on_pbStopTouch_pressed()
{
    MillMachine->Stop();
}



void WLMillControl::on_pbMinusF_clicked()
{
ui.sbFper->setValue(ui.sbFper->value()-m_stepFper);
}

void WLMillControl::on_pbPlusF_clicked()
{
ui.sbFper->setValue(ui.sbFper->value()+m_stepFper);
}

void WLMillControl::on_pbMinusS_clicked()
{
ui.sbSper->setValue(ui.sbSper->value()-m_stepSper);
}

void WLMillControl::on_pbPlusS_clicked()
{
ui.sbSper->setValue(ui.sbSper->value()+m_stepSper);
}

void WLMillControl::on_sbFman_valueChanged(double arg1)
{
if(!ui.pbFast->isDown())
        MillMachine->setPercentManual(arg1);
}

void WLMillControl::on_pbFast_pressed()
{
MillMachine->setPercentManual(100.0);
}

void WLMillControl::on_pbFast_released()
{
MillMachine->setPercentManual(ui.sbFman->value());
}
