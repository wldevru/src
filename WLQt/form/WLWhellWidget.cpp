#include "WLWhellWidget.h"
#include "ui_WLWhellWidget.h"

WLWhellWidget::WLWhellWidget(WLWhell *_Whell,WLModuleIOPut *_ModuleIOPut,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WLWhellWidget)
{
    Whell=_Whell;
    ModuleIOPut=_ModuleIOPut;

    ui->setupUi(this);

    createInputs();

    ui->cbInAbianry->setChecked(Whell->getFlag()&WHF_inAbinary);
    ui->cbInXbianry->setChecked(Whell->getFlag()&WHF_inXbinary);

    ui->editOutENB->setModuleIOPut(ModuleIOPut,false);
    ui->editOutENB->setLabel("outENB");
    ui->editOutENB->setValue(Whell->getOutENB());

    ui->editInV->setModuleIOPut(ModuleIOPut);
    ui->editInV->setLabel("inV");
    ui->editInV->setValue(Whell->getInVmode());

    ui->gbInA->setChecked(!(Whell->getFlag()&WHF_manualA));
    ui->gbInX->setChecked(!(Whell->getFlag()&WHF_manualX));
    ui->gbInV->setChecked(!(Whell->getFlag()&WHF_manualV));

    ui->cbInv->setChecked((Whell->getFlag()&WHF_inv));

    ui->gbInA->setTitle(ui->gbInA->title()+" (Axis)");
    ui->gbInX->setTitle(ui->gbInX->title()+" (X1,X..)");
    ui->gbInV->setTitle(ui->gbInV->title()+" (Vmode)");

    setWindowTitle(windowTitle()+" : "+QString::number(Whell->getIndex()));
}

WLWhellWidget::~WLWhellWidget()
{
    delete ui;
}

void WLWhellWidget::saveData()
{
quint8 iInA[sizeInAxis];
quint8 iInX[sizeInX];

for(int i=0;i<sizeInAxis;i++)
    iInA[i]=ListEIWAxis[i]->value();

Whell->setInAxis(iInA,sizeInAxis);

for(int i=0;i<sizeInX;i++)
    iInX[i]=ListEIWX[i]->value();

Whell->setInX(iInX,sizeInX);

Whell->setOutENB(ui->editOutENB->value());
Whell->setInVmode(ui->editInV->value());

Whell->setFlag((ui->cbInAbianry->isChecked() ? WHF_inAbinary:0)
              |(ui->cbInXbianry->isChecked() ? WHF_inXbinary:0)
              |(ui->gbInA->isChecked() ? 0:WHF_manualA)
              |(ui->gbInX->isChecked() ? 0:WHF_manualX)
              |(ui->gbInV->isChecked() ? 0:WHF_manualV)
              |(ui->cbInv->isChecked() ? WHF_inv : 0));

//Whell->setOutputENB(ui->)
}

void WLWhellWidget::createInputs()
{
WLEditIOPutWidget *EIW;

quint8 *iInA=Whell->getIndexInAxis();
quint8 *iInX=Whell->getIndexInX();

for(int i=0;i<sizeInAxis;i++)
  {
  EIW= new WLEditIOPutWidget(this);
  EIW->setModuleIOPut(ModuleIOPut);
  EIW->setLabel("in"+QString::number(i));
  EIW->setValue(iInA[i]);
  ListEIWAxis+=EIW;

  if(i>2)
      connect(ui->cbInAbianry,SIGNAL(toggled(bool)),EIW,SLOT(setDisabled(bool)));
  }

for(int i=0;i<sizeInX;i++)
  {
  EIW= new WLEditIOPutWidget(this);
  EIW->setModuleIOPut(ModuleIOPut);
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
