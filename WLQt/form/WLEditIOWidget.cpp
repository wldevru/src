#include "WLEditIOWidget.h"
#include "ui_WLEditIOWidget.h"

WLEditIOWidget::WLEditIOWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WLEditIOWidget)
{
    m_Module=nullptr;

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

                  break;
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
WLModuleIOPut *ModuleIOPut = static_cast<WLModuleIOPut*>(m_Module);

pal.setColor(QPalette::Base,getIOPut()->getNow() ?
                            QColor(255,120,120)
                            :
                            Qt::white);

ui->spinBox->setPalette(pal);

}
}

void WLEditIOWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
if(QMessageBox::question(this,tr("Question")
                        ,m_input ? tr("invert input"):tr("invert output")
                        ,QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
             {
             togInvers();
             }
}


