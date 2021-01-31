#include "wldrivewidget.h"
#include "wlenternum.h"

WLDriveWidget::WLDriveWidget(WLDrive *_Drive,QWidget *parent)
	: QDialog(parent)
{	
    m_Drive=_Drive;

    m_ddim=m_Drive->getDriveDim();

    ui.setupUi(this);

    ui.lineEditAxis->setText(m_Drive->getIndexModuleAxisStr());
    updateTabAxis();

    m_PamTab = new WLPamListWidget(m_Drive,this);

    connect(this,SIGNAL(changedUnit(QString)),m_PamTab,SLOT(setUnit(QString)));

    addTabWidget(m_PamTab,tr("motion parametrs"));

    ui.cbTypeDim->addItems(QString(tr("step on size,one step size,ratio A/B")).split(","));
    ui.cbTypeDim->setCurrentIndex(static_cast<int>(m_ddim.type));

    ui.sbDimA->setValue(m_ddim.A);
    ui.sbDimB->setValue(m_ddim.B);

    updateCBDimm(static_cast<int>(m_ddim.type));

    connect(ui.cbTypeDim,SIGNAL(activated(int)),SLOT(updateCBDimm(int)));

    ui.sbPLIM->setValue(m_Drive->maxPosition());
    ui.sbMLIM->setValue(m_Drive->minPosition());


	ui.comboBoxLogicFind->addItems(QString(tr("no Find,only ORG,only PEL,only MEL,only ORG back,only PEL back,only MEL back")).split(","));

    connect(ui.comboBoxLogicFind,SIGNAL(currentIndexChanged(int)),SLOT(updateFindLogic(int)));

    ui.comboBoxLogicFind->setCurrentIndex(m_Drive->getLogicFindPos());

    connect(ui.pbCorrectStepSize,&QPushButton::clicked,this,&WLDriveWidget::onCorrectStepSize);

    ui.sbOrgSize->setValue(m_Drive->getORGSize());

    ui.sbBackFindPosition->setValue(m_Drive->homePosition());
    ui.sbOrgPosition->setValue(m_Drive->getOrgPosition());

    //ui.sbVfind->setRange(0.0001,Drive->Pad->getData("main").Vma);
    connect(ui.sbVfind,SIGNAL(valueChanged(double)),SLOT(updateLabelSDDist()));
    connect(ui.tabWidget,SIGNAL(currentChanged(int)),SLOT(updateLabelSDDist()));

    ui.sbVfind->setValue(m_Drive->feedVFind());

    connect(ui.cbTypeDrive,SIGNAL(currentIndexChanged(int)),this,SLOT(updateUnit()));

    ui.cbTypeDrive->setCurrentIndex(m_Drive->getType());



    ui.gbLimit->setChecked(!m_Drive->isInfinity());

	connect(ui.pbVerError,SIGNAL(clicked()),SLOT(onVerifyError()));

    connect(ui.pbApplyAxis,&QPushButton::clicked,this,&WLDriveWidget::updateTabAxis);
    connect(ui.lineEditAxis,&QLineEdit::textChanged,[=](){ui.pbApplyAxis->setEnabled(true);});

    setModal(true);

    setWindowTitle(windowTitle()+" "+m_Drive->getName());

    setWindowTitle(tr("Edit Drive: ")+m_Drive->getName());

    updateFindLogic(m_Drive->getLogicFindPos());
    updateUnit();


}

WLDriveWidget::~WLDriveWidget()
{

}


void WLDriveWidget::updateLabelSDDist()
{
double V=ui.sbVfind->value();
dataPad Pad=m_Drive->pad()->getData("main");
double ScurveMs = axisWidgetList.isEmpty() ? 0 : axisWidgetList.first()->geDelaytSCurveMs();
ui.labelSDDist->setText(QString(tr("slow down distance: %1 ")+m_unit).arg(((Pad.Vst-V)/Pad.Ade+ScurveMs/1000)*(V+Pad.Vst)/2,0,'g',2));
}

QString WLDriveWidget::verifyError()
{
QString str;

foreach(WLAxisWidget *AW,axisWidgetList)
{
if(!AW->isUniqueInputs())
    str+=tr("input numbers are not unique")+QString("(Axis-%1").arg(AW->getAxis()->getIndex())+")\n";

if(!AW->isUniqueOutputs())
    str+=tr("output numbers are not unique")+QString("(Axis-%1").arg(AW->getAxis()->getIndex())+")\n";

}

if(ui.sbMLIM->value()>=ui.sbPLIM->value()
 &&ui.gbLimit->isChecked())
 str+=tr("invalid movement limits")+"\n";
else
 {
 if((ui.sbBackFindPosition->value()<ui.sbMLIM->value()
   ||ui.sbBackFindPosition->value()>ui.sbPLIM->value())&&(ui.comboBoxLogicFind->currentIndex()>3))
  str+=tr("invalid base position")+"\n";
 }

switch(ui.comboBoxLogicFind->currentIndex())
{
case 4: //ORG
case 1: foreach(WLAxisWidget *AW,axisWidgetList)
          {
          if(AW->getIndexInORG()<2)
              str+=tr("no sensor installed to search")+" (inORG)"+QString("(Axis-%1").arg(AW->getAxis()->getIndex())+")\n";
          }

        if(ui.sbOrgSize->value()>0)
        {}
        else
        str+=tr("not specified size ORG")+"\n";
        break;

case 2:  //PEL
case 5: foreach(WLAxisWidget *AW,axisWidgetList)
         {
         if(AW->getIndexInPEL()<2)
             str+=tr("no sensor installed to search")+" (inPEL)"+QString("(Axis-%1").arg(AW->getAxis()->getIndex())+")\n";

         if(AW->getActInPEL()==typeActIOPutAxis::AXIS_actNo)
             str+=tr("no sensor installed to search or action")+" (inPEL)"+QString("(Axis-%1").arg(AW->getAxis()->getIndex())+")\n";
         }

        break;

case 3: //MEL
case 6: foreach(WLAxisWidget *AW,axisWidgetList)
        {
        if(AW->getIndexInMEL()<2)
            str+=tr("no sensor installed to search")+" (inMEL)"+QString("(Axis-%1").arg(AW->getAxis()->getIndex())+")\n";

        if(AW->getActInMEL()==typeActIOPutAxis::AXIS_actNo)
            str+=tr("no sensor installed to search or action")+" (inMEL)"+QString("(Axis-%1").arg(AW->getAxis()->getIndex())+")\n";
        }

        break;
}

if(ui.comboBoxLogicFind->currentIndex()>0&&ui.sbVfind->value()<=0)
str+=tr("search speed not set")+"\n";

return str;
}

void WLDriveWidget::onVerifyError()
{
QString str=verifyError();

if(str.isEmpty()) str=tr("No error!!!");

QMessageBox::information(this, tr("Verify error"),str,QMessageBox::Ok);
}

void WLDriveWidget::onCorrectStepSize()
{
double R,T;
WLEnterNum EN(this);
EN.setMinMaxNow(0.1,999999,90);
EN.setLabel(tr("Enter real distance(measure)"));

EN.show();
if(EN.exec())
  {
  R=EN.getNow();

  EN.setLabel(tr("Enter calc distance(display)"));
  EN.show();
   if(EN.exec())
   {
   T=EN.getNow();

   m_ddim.set(static_cast<WLDriveDim::typeDim>(ui.cbTypeDim->currentIndex())
             ,ui.sbDimA->value()
             ,ui.sbDimB->value());

   switch(ui.cbTypeDim->currentIndex())
   {
   case WLDriveDim::typeDim::ratio:        ui.sbDimA->setValue(R/T*ui.sbDimA->value());break;
   case WLDriveDim::typeDim::oneStepSize:  ui.sbDimA->setValue(R/T*ui.sbDimA->value());break;
   case WLDriveDim::typeDim::stepPerSize:  ui.sbDimA->setValue(T/R*ui.sbDimA->value());break;
   }

   }
  }
}

void WLDriveWidget::accept()
{
uint8_t iA=0;

if(!verifyError().isEmpty())
    onVerifyError();
 else
  {
  saveDataDrive();

  for(int i=1;i<ui.tabWidget->count();i++)    {
    QDialog *Dialog=static_cast<QDialog*>(ui.tabWidget->widget(i));

    Dialog->accept();
    qDebug()<<Dialog->metaObject()->className();

    if(Dialog->metaObject()->className()==(tr("WLAxisWidget")))
       {
       m_Drive->setOffsetAxis(iA,static_cast<WLAxisWidget*>(Dialog)->getOffset());
       iA++;
       }
    }

  QDialog::accept();
  }
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

ui.sbDimB->setVisible(tdim==WLDriveDim::typeDim::ratio);

ui.sbDimA->setValue(m_ddim.A);
ui.sbDimB->setValue(m_ddim.B);
}

void WLDriveWidget::updateCBTypePulse(int index)
{

}

void WLDriveWidget::updateFindLogic(int index)
{
if(index==1
 ||index==4)    
    ui.sbOrgSize->setEnabled(true);
else
    ui.sbOrgSize->setEnabled(false);


if(index==4
 ||index==5
 ||index==6)
     ui.sbBackFindPosition->setEnabled(true);
   else
     ui.sbBackFindPosition->setEnabled(false);

ui.sbVfind->setEnabled(index!=0);

switch(index)
{
case 0:  ui.labelOrgPosition->setText(tr("position"));break;
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
m_Drive->setKGear(1);

m_Drive->setDimension(static_cast<WLDriveDim::typeDim>(ui.cbTypeDim->currentIndex())
                     ,ui.sbDimA->value()
                     ,ui.sbDimB->value());

m_Drive->setLogicFindPos(ui.comboBoxLogicFind->currentIndex());

m_Drive->setORGSize(ui.sbOrgSize->value());
m_Drive->setHomePosition(ui.sbBackFindPosition->value());
m_Drive->setOrgPosition(ui.sbOrgPosition->value());

m_Drive->setFeedVFind(ui.sbVfind->value());
m_Drive->setType(static_cast<WLDrive::typeDrive>(ui.cbTypeDrive->currentIndex()));
m_Drive->setInfinity(!ui.gbLimit->isChecked());
m_Drive->setMinMaxPosition(ui.sbMLIM->value(),ui.sbPLIM->value());
}

void WLDriveWidget::updateUnit()
{
if(ui.cbTypeDrive->currentIndex()==0)
 {
 m_unit=tr(" mm");
 }
else
 {
 m_unit=tr(" gr");
 }

ui.sbBackFindPosition->setSuffix(m_unit);
ui.sbOrgPosition->setSuffix(m_unit);
ui.sbOrgSize->setSuffix(m_unit);
ui.sbMLIM->setSuffix(m_unit);
ui.sbPLIM->setSuffix(m_unit);
ui.sbVfind->setSuffix(m_unit+"/"+tr("s"));

updateLabelSDDist();

emit changedUnit(m_unit);
}

void WLDriveWidget::updateTabAxis()
{
foreach(WLAxisWidget *tw,axisWidgetList)
{
ui.tabWidget->removeTab(ui.tabWidget->indexOf(tw));
}

m_Drive->setIndexModuleAxisStr(ui.lineEditAxis->text());

for(uint8_t i=0;i<m_Drive->getAxisList().size();i++)
{
WLAxisWidget *AW=new WLAxisWidget(m_Drive->getAxisList().at(i),i!=0,m_Drive->getOffsetAxis(i),this);

insertTabWidget(1+i,AW,("Axis-")+QString::number(m_Drive->getAxisList().at(i)->getIndex()));

connect(this,&WLDriveWidget::changedUnit,AW,&WLAxisWidget::setUnit);

axisWidgetList+=AW;
}

ui.pbApplyAxis->setDisabled(true);
}
