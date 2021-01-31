#include "wleditiowidget.h"
#include <QMenu>
#include <QContextMenuEvent>
#include "ui_wleditiowidget.h"

WLEditIOWidget::WLEditIOWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WLEditIOWidget)
{
    m_Module=nullptr;
    m_enLatchInput=false;

    ui->setupUi(this);

    QTimer *timer = new QTimer;

    connect(timer,SIGNAL(timeout()),SLOT(update()));
    timer->start(50);

    ui->checkBox->setVisible(false);

    connect(ui->checkBox,&QCheckBox::toggled,ui->spinBox,&QSpinBox::setEnabled);
    connect(ui->checkBox,&QCheckBox::toggled,ui->label,&QLabel::setEnabled);
    connect(ui->checkBox,&QCheckBox::toggled,this,&WLEditIOWidget::toggle);

    ui->checkBox->setChecked(true);
}

WLEditIOWidget::~WLEditIOWidget()
{
delete ui;
}

void WLEditIOWidget::setModule(WLModule *_Module,bool _input)
{
if(!_Module)
 {
// Q_ASSERT(m_Module);
 setVisible(false);
 return;
 }

m_Module=_Module;
m_input=_input;

switch(m_Module->type())
{
 case typeMIOPut:  {
                   WLModuleIOPut *ModuleIOPut = static_cast<WLModuleIOPut*>(m_Module);

                   ui->spinBox->setRange(0,(m_input? ModuleIOPut->getSizeInputs():ModuleIOPut->getSizeOutputs())-1);

                   ui->spinBox->setVisible(true);
                     ui->label->setVisible(true);

                   connect(ModuleIOPut,&WLModuleIOPut::changedInput,this,&WLEditIOWidget::setLatchInput);

                   setLabel(m_input ? ("input"):("output"));
                  break;;
                   }

case typeMPWM:  {
                  WLModulePWM *ModulePWM = static_cast<WLModulePWM*>(m_Module);

                  ui->spinBox->setRange(0,(ModulePWM->getSizeOutPWM()-1));

                  ui->spinBox->setVisible(true);
                    ui->label->setVisible(true);

                  setLabel(m_input ? ("in PWM"):("out PWM"));

                 break;
                 }

case typeMAIOPut: {
                  WLModuleAIOPut *ModuleAIOPut = static_cast<WLModuleAIOPut*>(m_Module);

                  ui->spinBox->setRange(0,(m_input? ModuleAIOPut->getSizeInputs():ModuleAIOPut->getSizeOutputs())-1);

                  ui->spinBox->setVisible(true);
                    ui->label->setVisible(true);

                  setLabel(m_input ? ("ainput"):("aoutput"));
                  break;
                  }

case typeMEncoder:{
                  WLModuleEncoder *ModuleEncoder = static_cast<WLModuleEncoder*>(m_Module);

                  ui->spinBox->setRange(0,ModuleEncoder->getSizeEncoder());

                  ui->spinBox->setVisible(true);
                    ui->label->setVisible(true);

                  setLabel(("encoder"));
                  break;
                  }
default:

break;
}


}

void WLEditIOWidget::setLabel(QString label)
{
ui->label->setText(label);
}

void WLEditIOWidget::setValue(int val)
{
ui->spinBox->setValue(val);
}

int WLEditIOWidget::value()
{
return ui->spinBox->value();
}

WLIOPut *WLEditIOWidget::getIOPut()
{
if(m_Module->type()==typeMIOPut)
    {
        WLModuleIOPut *ModuleIOPut = static_cast<WLModuleIOPut*>(m_Module);
        return  m_input ? ModuleIOPut->getInput(value()): ModuleIOPut->getOutput(value());
    }
    else
        return nullptr;
}

WLEncoder *WLEditIOWidget::getEncoder()
{
    if(m_Module->type()==typeMEncoder)
    {
        WLModuleEncoder *ModuleEncoder = static_cast<WLModuleEncoder*>(m_Module);
        return  m_input ? ModuleEncoder->getEncoder(value()): nullptr;
    }
    else
        return nullptr;
}


WLPWM *WLEditIOWidget::getPWM()
{
    if(m_Module->type()==typeMPWM)
    {
        WLModulePWM *ModulePWM = static_cast<WLModulePWM*>(m_Module);
        return  m_input ? nullptr : ModulePWM->getOutPWM(value());
    }
    else
        return nullptr;
}

bool WLEditIOWidget::isChecked()
{
return ui->checkBox->isChecked();
}

bool WLEditIOWidget::isEnable()
{
return m_Module!=nullptr;
}

QAbstractButton *WLEditIOWidget::getButton()
{
return ui->checkBox;
}

void WLEditIOWidget::update()
{
    if(!m_Module) return;

    if(m_Module->type()==typeMIOPut)
    {
        if(m_enLatchInput)
            ui->spinBox->setStyleSheet("background-color: rgb(20, 255, 205)");
        else  if (getIOPut()->getNow())
            ui->spinBox->setStyleSheet("background-color: rgb(255, 120, 120)");
        else
            ui->spinBox->setStyleSheet("background-color: rgb(255,250,250)");
    }
}

void WLEditIOWidget::togInvers()
{
 switch(m_Module->type())
 {
 case typeMIOPut: getIOPut()->togInv();break;
 case typeMPWM:   getPWM()->togInv();break;

 default: break;
 }
}


void WLEditIOWidget::onActTogInvers()
{
    if(QMessageBox::question(this,tr("Question")
                             ,m_input ? tr("invert input"):tr("invert output")
                        ,QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
             {
             togInvers();
}
}

void WLEditIOWidget::onActLatchInput()
{
m_enLatchInput=!m_enLatchInput;
ui->spinBox->setDisabled(m_enLatchInput);
}

void WLEditIOWidget::onActResetEncoder()
{
getEncoder()->setCount(0);
}

void WLEditIOWidget::onActSetFreq()
{
WLEnterNum EN(this);

EN.setMinMaxNow(1,30000, getPWM()->freq());
EN.setLabel(tr("Eneter Frequency:"));
EN.setSuffix(tr("Hz"));

if(EN.exec())
  {
  getPWM()->setFreq(EN.getNow());
  }
}

void WLEditIOWidget::setLatchInput(int index)
{
if(m_enLatchInput)
  {
  m_enLatchInput=false;
  ui->spinBox->setValue(index);
  ui->spinBox->setDisabled(m_enLatchInput);
}
}

void WLEditIOWidget::setCheckable(bool enable)
{
if(m_Module) ui->checkBox->setVisible(enable);
}

void WLEditIOWidget::setChecked(bool check)
{
ui->checkBox->setChecked(check);
emit toggle(check);
}

void WLEditIOWidget::mousePressEvent(QMouseEvent *event)
{
QMenu menu(this);

if(!m_Module) return;

    if(m_Module->type()==typeMIOPut)
    {
    QAction *actTog=menu.addAction(tr("invers"),this,SLOT(onActTogInvers()));

     actTog->setCheckable(true);
     actTog->setChecked(getIOPut()->isInv());

     if(m_input)
       {
       QAction *actLatchIn=menu.addAction(tr("latch input"),this,SLOT(onActLatchInput()));;

       actLatchIn->setCheckable(true);
       actLatchIn->setChecked(m_enLatchInput);
       }
     }
    else
    if(m_Module->type()==typeMEncoder
      &&m_input)
       {
       QAction *actCount=menu.addAction(QString::number(getEncoder()->count()),this,SLOT(onActResetEncoder()));

       }
    else
    if(m_Module->type()==typeMPWM)
       {
       QAction *actTog=menu.addAction(tr("invers"),this,SLOT(onActTogInvers()));

       actTog->setCheckable(true);
       actTog->setChecked(getPWM()->isInv());

       menu.addAction("F:"+QString::number(getPWM()->freq())+"Hz",this,SLOT(onActSetFreq()));
       }


    menu.exec(event->globalPos());
}


