#include "wleditmpgwidget.h"
#include "ui_wleditmpgwidget.h"

WLEditMPGWidget::WLEditMPGWidget(WLMPG *_MPG,WLModuleIOPut *MIOPut,WLModuleEncoder *MEncoder,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WLEditMPGWidget)
{
    MPG=_MPG;

    ui->setupUi(this);

    createInputs(MIOPut);

    ui->cbInAbianry->setChecked(MPG->getFlag()&MPGF_inAbinary);
    ui->cbInXbianry->setChecked(MPG->getFlag()&MPGF_inXbinary);

    ui->editOutENB->setModule(MIOPut,false);
    ui->editOutENB->setLabel("outENB");
    ui->editOutENB->setValue(MPG->getOutENB());

    ui->editInV->setModule(MIOPut);
    ui->editInV->setLabel("inV");
    ui->editInV->setValue(MPG->getInVmode());
    ui->editInV->setCheckable(false);

    ui->gbInA->setChecked(!(MPG->getFlag()&MPGF_manualA));
    ui->gbInX->setChecked(!(MPG->getFlag()&MPGF_manualX));
    ui->gbInV->setChecked(!(MPG->getFlag()&MPGF_manualV));

    ui->cbInv->setChecked((MPG->getFlag()&MPGF_inv));

    ui->gbInA->setTitle(ui->gbInA->title()+" (Axis)");
    ui->gbInX->setTitle(ui->gbInX->title()+" (X1,X..)");
    ui->gbInV->setTitle(ui->gbInV->title()+" (Vmode)");

    ui->encoder->setModule(MEncoder);
    ui->encoder->setValue(MPG->getEncoder());

    ui->sbPulses->setValue(MPG->getPulses());

    QTimer *timer = new QTimer;

    connect(timer,&QTimer::timeout,this,&WLEditMPGWidget::updateIndexs);
    timer->start(100);

    setWindowTitle(tr("Edit MPG: ") +QString::number(MPG->getIndex()));
}

WLEditMPGWidget::~WLEditMPGWidget()
{
    delete ui;
}

void WLEditMPGWidget::saveData()
{
quint8 iInA[sizeInAxis];
quint8 iInX[sizeInX];

for(int i=0;i<sizeInAxis;i++)
    iInA[i]=ListEIWAxis[i]->value();

MPG->setInAxis(iInA,sizeInAxis);

for(int i=0;i<sizeInX;i++)
    iInX[i]=ListEIWX[i]->value();

MPG->setInX(iInX,sizeInX);

MPG->setOutENB(ui->editOutENB->value());
MPG->setInVmode(ui->editInV->value());

MPG->setFlag((ui->cbInAbianry->isChecked() ? MPGF_inAbinary:0)
              |(ui->cbInXbianry->isChecked() ? MPGF_inXbinary:0)
              |(ui->gbInA->isChecked() ? 0:MPGF_manualA)
              |(ui->gbInX->isChecked() ? 0:MPGF_manualX)
              |(ui->gbInV->isChecked() ? 0:MPGF_manualV)
              |(ui->cbInv->isChecked() ? MPGF_inv : 0));

MPG->setEncoder(ui->encoder->value());
MPG->setPulses(ui->sbPulses->value());
}

void WLEditMPGWidget::createInputs(WLModuleIOPut *MIOPut)
{
WLEditIOWidget *EIW;

quint8 *iInA=MPG->getIndexInAxis();
quint8 *iInX=MPG->getIndexInX();

for(int i=0;i<sizeInAxis;i++)
  {
  EIW= new WLEditIOWidget(this);
  EIW->setModule(MIOPut);
  EIW->setLabel("in"+QString::number(i));
  EIW->setValue(iInA[i]);

  ListEIWAxis+=EIW;

  if(i>2)
      connect(ui->cbInAbianry,SIGNAL(toggled(bool)),EIW,SLOT(setDisabled(bool)));
  }

for(int i=0;i<sizeInX;i++)
  {
  EIW= new WLEditIOWidget(this);
  EIW->setModule(MIOPut);
  EIW->setLabel("in"+QString::number(i));;
  EIW->setValue(iInX[i]);

  ListEIWX+=EIW;

  if(i>1)
      connect(ui->cbInXbianry,SIGNAL(toggled(bool)),EIW,SLOT(setDisabled(bool)));
  }


for(int i=sizeInAxis-1;i>=0;i--)
 {
 ui->vLayoutInputAxis->addWidget(ListEIWAxis[i]);
 }

for(int i=sizeInX-1;i>=0;i--)
 {
 ui->vLayoutInputX->addWidget(ListEIWX[i]);
 }

}

void WLEditMPGWidget::updateIndexs()
{
quint8 iA=0;
quint8 iX=0;

 for(quint8 i=0;i<ListEIWAxis.size();i++)
     if((ListEIWAxis[i]->isChecked())
      &&(ListEIWAxis[i]->getIOPut()->getNow()))
         {
         if(ui->cbInAbianry->isChecked())
             iA+=1<<i;
         else
             iA=i+1;
         }

 for(quint8 i=0;i<ListEIWX.size();i++)
     if((ListEIWX[i]->isChecked())
      &&(ListEIWX[i]->getIOPut()->getNow()))
         {
         if(ui->cbInXbianry->isChecked())
             iX+=1<<i;
         else
             iX=i+1;
         }

ui->labelA->setText(iA==0 ? "off":QString::number(iA));
ui->labelX->setText(QString("XE%1").arg(iX));
}
