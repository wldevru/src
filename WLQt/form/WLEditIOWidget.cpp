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

    ui->spinBox->setEnabled(false);

    QTimer *timer = new QTimer;

    connect(timer,SIGNAL(timeout()),SLOT(update()));
    timer->start(50);
}

WLEditIOWidget::~WLEditIOWidget()
{
delete ui;
}

void WLEditIOWidget::setModule(WLModule *_Module,bool _input)
{
if(m_Module)
 {
 Q_ASSERT(m_Module);
 return;
 }
m_Module=_Module;
m_input=_input;

switch(m_Module->type())
{
 case typeMIOPut:  {
                   WLModuleIOPut *ModuleIOPut = static_cast<WLModuleIOPut*>(m_Module);

                   ui->spinBox->setRange(0,(m_input? ModuleIOPut->getSizeInputs():ModuleIOPut->getSizeOutputs())-1);
                   ui->spinBox->setEnabled(true);

                   connect(ModuleIOPut,&WLModuleIOPut::changedInput,this,&WLEditIOWidget::setLatchInput);

                  break;;
                   }

case typeMPWM:  {
                  WLModulePWM *ModulePWM = static_cast<WLModulePWM*>(m_Module);

                  ui->spinBox->setRange(0,(ModulePWM->getSizeOutPWM()-1));
                  ui->spinBox->setEnabled(true);

                 break;
                 }
 default:
             ui->spinBox->setEnabled(false);
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

void WLEditIOWidget::update()
{
QPalette pal;

if(m_Module->type()==typeMIOPut)
{
if(m_enLatchInput)
    pal.setColor(QPalette::Base,QColor(110,255,110));
 else
    pal.setColor(QPalette::Base,getIOPut()->getNow() ?
                            QColor(255,110,110)
                            :
                            Qt::white);

ui->spinBox->setPalette(pal);

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

void WLEditIOWidget::setLatchInput(int index)
{
if(m_enLatchInput)
  {
  m_enLatchInput=false;
  ui->spinBox->setValue(index);
  ui->spinBox->setDisabled(m_enLatchInput);
  }
}

void WLEditIOWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);

    QAction *actTog=menu.addAction(tr("invers"),this,SLOT(onActTogInvers()));

    actTog->setCheckable(true);

    if(m_Module->type()==typeMIOPut)
      {
      actTog->setChecked(getIOPut()->isInv());
      }

    if(m_Module->type()==typeMIOPut
     &&m_input)
      {
      QAction *actLatchIn=menu.addAction(tr("latch input"),this,SLOT(onActLatchInput()));;

      actLatchIn->setCheckable(true);
      actLatchIn->setChecked(m_enLatchInput);
      }

    menu.exec(event->globalPos());

}


